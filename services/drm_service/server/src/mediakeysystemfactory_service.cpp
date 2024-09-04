/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <securec.h>
#include <unistd.h>
#include <unordered_set>
#include "system_ability_definition.h"
#include "mem_mgr_client.h"
#include "mem_mgr_proxy.h"
#include "ipc_skeleton.h"
#include "iservice_registry.h"
#include "drm_dfx_utils.h"
#include "drm_log.h"
#include "drm_dfx.h"
#include "drm_error_code.h"
#include "dump_usage.h"
#include "hitrace/tracechain.h"
#include "iservice_registry.h"
#include "mediakeysystem_service.h"
#include "mediakeysystemfactory_service.h"

namespace OHOS {
namespace DrmStandard {
using namespace OHOS::HiviewDFX;
const std::string SPLIT_LINE =
    "----------------------------------------------------------------------------------------\n";

REGISTER_SYSTEM_ABILITY_BY_ID(MediaKeySystemFactoryService, MEDIA_KEY_SYSTEM_SERVICE_ID, true)


void MediaKeySystemFactoryService::OnDrmPluginDied(std::string &name)
{
    DRM_INFO_LOG("OnDrmPluginDied enter.");
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    for (auto pidIt = mediaKeySystemForPid_.begin(); pidIt != mediaKeySystemForPid_.end();) {
        std::set<sptr<MediaKeySystemService>> mediaKeySystemServiceSet = pidIt->second;
        for (auto keySystem = mediaKeySystemServiceSet.begin(); keySystem != mediaKeySystemServiceSet.end();) {
            std::string pluginName = (*keySystem)->GetPluginName();
            if (name == pluginName) {
                CloseMediaKeySystemService(*keySystem);
                mediaKeySystemServiceSet.erase(keySystem++);
            } else {
                ++keySystem;
            }
        }
        if (mediaKeySystemServiceSet.empty()) {
            pidIt = mediaKeySystemForPid_.erase(pidIt);
        } else {
            pidIt++;
        }
    }
    currentMediaKeySystemNum_.erase(name);
}

MediaKeySystemFactoryService::MediaKeySystemFactoryService(int32_t systemAbilityId, bool runOnCreate)
    : SystemAbility(systemAbilityId, runOnCreate)
{
    DRM_INFO_LOG("MediaKeySystemFactoryService enter.");
    drmHostManager_ = new (std::nothrow) DrmHostManager(this);
    if (drmHostManager_ == nullptr) {
        DRM_ERR_LOG("create drmHostManager_ failed.");
        return;
    }
}

MediaKeySystemFactoryService::~MediaKeySystemFactoryService()
{
    DRM_INFO_LOG("~MediaKeySystemFactoryService enter.");
}

void MediaKeySystemFactoryService::OnStart()
{
    DRM_INFO_LOG("OnStart enter.");
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    if (drmHostManager_ == nullptr || drmHostManager_->Init() != DRM_OK) {
        DRM_ERR_LOG("OnStart failed to init drm host manager.");
    }
    bool res = Publish(this);
    if (res) {
        DRM_DEBUG_LOG("MediaKeySystemFactoryService OnStart res=%{public}d", res);
    }
    AddSystemAbilityListener(MEMORY_MANAGER_SA_ID);
    ReportServiceBehaviorEvent("DRM_SERVICE", "start");
}

void MediaKeySystemFactoryService::OnDump()
{
}

void MediaKeySystemFactoryService::OnStop()
{
    DRM_INFO_LOG("OnStop enter.");
    std::lock_guard<std::recursive_mutex> lock(mutex_);

    if (drmHostManager_) {
        drmHostManager_->DeInit();
        delete drmHostManager_;
        drmHostManager_ = nullptr;
    }

    int pid = getpid();
    /* 3012 is the saId of drm_service */
    Memory::MemMgrClient::GetInstance().NotifyProcessStatus(pid, 1, 0, 3012);
    OHOS::HiviewDFX::DumpUsage dumpUse;
    ReportServiceBehaviorEvent("DRM_SERVICE", "end");
}

void MediaKeySystemFactoryService::OnAddSystemAbility(int32_t systemAbilityId, const std::string &deviceId)
{
    DRM_INFO_LOG("OnAddSystemAbility enter.");
    if (systemAbilityId == MEMORY_MANAGER_SA_ID) {
        int32_t pid = getpid();
        /* 3012 is the said of drm service */
        Memory::MemMgrClient::GetInstance().NotifyProcessStatus(pid, 1, 1, 3012);
    }
}

int32_t MediaKeySystemFactoryService::Dump(int32_t fd, const std::vector<std::u16string>& args)
{
    DRM_CHECK_AND_RETURN_RET_LOG(fd > 0, OHOS::INVALID_OPERATION, "Failed to check fd.");
    std::string dumpString;

    auto ret = WriteDumpInfo(fd, dumpString);
    DRM_CHECK_AND_RETURN_RET_LOG(ret == NO_ERROR,
        OHOS::INVALID_OPERATION, "Failed to write framework information");
    return OHOS::NO_ERROR;
}

void MediaKeySystemFactoryService::DistroyForClientDied(pid_t pid)
{
    // destroy all system objects for this pid
    DRM_INFO_LOG("DistroyForClientDied pid: %{public}d.", pid);
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    if (mediaKeySystemForPid_.find(pid) == mediaKeySystemForPid_.end()) {
        return;
    }
    for (auto it = mediaKeySystemForPid_[pid].begin(); it != mediaKeySystemForPid_[pid].end();) {
        if ((*it) != nullptr) {
            // decrease the total count in drm host manager.
            sptr<IMediaKeySystem> hdiMediaKeySystem = (*it)->getMediaKeySystem();
            (*it)->CloseMediaKeySystemServiceByCallback();
            if (hdiMediaKeySystem != nullptr) {
                drmHostManager_->ReleaseMediaKeySystem(hdiMediaKeySystem);
            }
            if (currentMediaKeySystemNum_.find((*it)->GetPluginName()) != currentMediaKeySystemNum_.end()) {
                currentMediaKeySystemNum_[(*it)->GetPluginName()]--;
            }
        }
        it = mediaKeySystemForPid_[pid].erase(it);
    }
    mediaKeySystemForPid_[pid].clear();
    mediaKeySystemForPid_.erase(pid);
}

int32_t MediaKeySystemFactoryService::CreateMediaKeySystem(std::string &name,
    sptr<IMediaKeySystemService> &mediaKeySystemProxy)
{
    DRM_INFO_LOG("CreateMediaKeySystem enter.");
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    sptr<MediaKeySystemService> mediaKeySystemService = nullptr;
    sptr<IMediaKeySystem> hdiMediaKeySystem = nullptr;
    if (currentMediaKeySystemNum_[name] >= KEY_SYSTEM_MAX_NUMBER) {
        DRM_ERR_LOG("The number of MediaKeySystem is greater than 64");
        return DRM_MAX_SYSTEM_NUM_REACHED;
    }
    int32_t ret = drmHostManager_->CreateMediaKeySystem(name, hdiMediaKeySystem);
    if (hdiMediaKeySystem == nullptr || ret != DRM_OK) {
        DRM_ERR_LOG("drmHostManager_ return hdiMediaKeySystem nullptr.");
        ReportFaultEvent(DRM_SERVICE_ERROR, "CreateMediaKeySystem failed", "");
        return DRM_SERVICE_ERROR;
    }

    StatisticsInfo statisticsInfo;
    InitStatisticsInfo(hdiMediaKeySystem, name, statisticsInfo);
    mediaKeySystemService = new(std::nothrow) MediaKeySystemService(hdiMediaKeySystem, statisticsInfo);
    if (mediaKeySystemService == nullptr) {
        DRM_ERR_LOG("CreateMediaKeySystem allocation failed.");
        ReportFaultEvent(DRM_ALLOC_ERROR, "CreateMediaKeySystem failed", "");
        return DRM_ALLOC_ERROR;
    }
    mediaKeySystemService->SetMediaKeySystemServiceOperatorsCallback(this);
    (void)mediaKeySystemService->SetBundleName();

    int32_t pid = IPCSkeleton::GetCallingPid();
    DRM_DEBUG_LOG("CreateMediaKeySystem GetCallingPID: %{public}d.", pid);
    mediaKeySystemForPid_[pid].insert(mediaKeySystemService);
    DRM_DEBUG_LOG("0x%{public}06" PRIXPTR "  Current mediaKeySystemService",
        FAKE_POINTER(mediaKeySystemService.GetRefPtr()));
    mediaKeySystemProxy = mediaKeySystemService;
    if (currentMediaKeySystemNum_.find(name) != currentMediaKeySystemNum_.end()) {
        currentMediaKeySystemNum_[name]++;
    } else {
        currentMediaKeySystemNum_[name] = 1;
    }
    return ret;
}

int32_t MediaKeySystemFactoryService::CloseMediaKeySystemService(sptr<MediaKeySystemService> mediaKeySystemService)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    DRM_INFO_LOG("CloseMediaKeySystemService enter.");
    int32_t currentPid = IPCSkeleton::GetCallingPid();
    DRM_DEBUG_LOG("MediaKeySystemFactoryService GetCallingPID: %{public}d", currentPid);
    sptr<IMediaKeySystem> hdiMediaKeySystem = mediaKeySystemService->getMediaKeySystem();

    for (auto &pidSystemsSet : mediaKeySystemForPid_) {
        if (pidSystemsSet.second.find(mediaKeySystemService) != pidSystemsSet.second.end()) {
            mediaKeySystemService->CloseMediaKeySystemServiceByCallback();
            pidSystemsSet.second.erase(mediaKeySystemService);
            break;
        }
    }
    std::string pluginName = mediaKeySystemService->GetPluginName();
    if (currentMediaKeySystemNum_.find(pluginName) != currentMediaKeySystemNum_.end() &&
        currentMediaKeySystemNum_[pluginName] > 0) {
        currentMediaKeySystemNum_[pluginName]--;
    }
    if (hdiMediaKeySystem != NULL) {
        drmHostManager_->ReleaseMediaKeySystem(hdiMediaKeySystem);
    }
    mediaKeySystemService = nullptr;
    return DRM_OK;
}

int32_t MediaKeySystemFactoryService::IsMediaKeySystemSupported(std::string &name, bool *isSurpported)
{
    DRM_INFO_LOG("IsMediaKeySystemSupported one parameters enter.");
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    int32_t ret = drmHostManager_->IsMediaKeySystemSupported(name, isSurpported);
    if (ret != DRM_OK) {
        DRM_ERR_LOG("IsMediaKeySystemSupported failed.");
        return ret;
    }
    return ret;
}

int32_t MediaKeySystemFactoryService::IsMediaKeySystemSupported(std::string &name, std::string &mimeType,
    bool *isSurpported)
{
    DRM_INFO_LOG("IsMediaKeySystemSupported two parameters enter.");
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    int32_t ret = drmHostManager_->IsMediaKeySystemSupported(name, mimeType, isSurpported);
    if (ret != DRM_OK) {
        DRM_ERR_LOG("IsMediaKeySystemSupported failed.");
        return ret;
    }
    return ret;
}

int32_t MediaKeySystemFactoryService::IsMediaKeySystemSupported(std::string &name, std::string &mimeType,
    int32_t securityLevel, bool *isSurpported)
{
    DRM_INFO_LOG("IsMediaKeySystemSupported three parameters enter.");
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    int32_t ret = drmHostManager_->IsMediaKeySystemSupported(name, mimeType, securityLevel, isSurpported);
    if (ret != DRM_OK) {
        DRM_ERR_LOG("IsMediaKeySystemSupported failed.");
        return ret;
    }
    return ret;
}

int32_t MediaKeySystemFactoryService::GetMediaKeySystems(std::map<std::string, std::string> &mediaKeySystemNames)
{
    DRM_INFO_LOG("GetMediaKeySystems enter.");
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    int32_t ret = drmHostManager_->GetMediaKeySystems(mediaKeySystemNames);
    if (ret != DRM_OK) {
        DRM_ERR_LOG("GetMediaKeySystems failed.");
        return ret;
    }
    return ret;
}

int32_t MediaKeySystemFactoryService::GetMediaKeySystemUuid(std::string &name, std::string &uuid)
{
    DRM_INFO_LOG("GetMediaKeySystemUuid enter.");
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    int32_t ret = drmHostManager_->GetMediaKeySystemUuid(name, uuid);
    if (ret != DRM_OK) {
        DRM_ERR_LOG("GetMediaKeySystemUuid failed.");
        return ret;
    }
    return ret;
}

void MediaKeySystemFactoryService::InitStatisticsInfo(const sptr<IMediaKeySystem> &hdiMediaKeySystem,
    std::string pluginName, StatisticsInfo &statisticsInfo)
{
    DRM_INFO_LOG("InitStatisticsInfo enter.");
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    statisticsInfo.pluginName = pluginName;
    if (drmHostManager_ != nullptr) {
        std::map<std::string, std::string> pluginNameUuidMap;
        drmHostManager_->GetMediaKeySystems(pluginNameUuidMap);
        if (pluginNameUuidMap.find(pluginName) != pluginNameUuidMap.end()) {
            statisticsInfo.pluginUuid = pluginNameUuidMap[pluginName];
        }
    }
    statisticsInfo.bundleName = GetClientBundleName(IPCSkeleton::GetCallingUid());
    if (hdiMediaKeySystem != nullptr) {
        (void)hdiMediaKeySystem->GetConfigurationString("vendor", statisticsInfo.vendorName);
        (void)hdiMediaKeySystem->GetConfigurationString("version", statisticsInfo.versionName);
    }
    DRM_INFO_LOG("uid: %{public}d, appName: %{public}s.",
        IPCSkeleton::GetCallingUid(), statisticsInfo.bundleName.c_str());
    DRM_INFO_LOG("pluginName: %{public}s, pluginUUID: %{public}s",
        statisticsInfo.pluginName.c_str(), statisticsInfo.pluginUuid.c_str());
    DRM_INFO_LOG("vendorName: %{public}s, versionName: %{public}s",
        statisticsInfo.vendorName.c_str(), statisticsInfo.versionName.c_str());
}

int32_t MediaKeySystemFactoryService::WriteDumpInfo(int32_t fd, std::string &dumpString)
{
    OHOS::HiviewDFX::DumpUsage dumpUse;
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    dumpString += "MediaKeySystem MemoryUsage: " + std::to_string(dumpUse.GetPss(getpid())) + "\n";
    std::map<std::string, std::string> mediaKeySystemInfo;
    drmHostManager_->GetMediaKeySystems(mediaKeySystemInfo);
    for (auto &iter : mediaKeySystemInfo) {
        dumpString += SPLIT_LINE;
        std::string tmpStr = "Plugin Name: " + iter.first + "\n" +
                             "Plugin UUID: " + iter.second + "\n" +
                             "Total MediaKeySystem Num: ";
        int32_t systemNum = 0;
        if (currentMediaKeySystemNum_.find(iter.first) != currentMediaKeySystemNum_.end()) {
            systemNum = currentMediaKeySystemNum_[iter.first];
        }
        tmpStr += std::to_string(systemNum) + "\n";
        dumpString += tmpStr;
    }
    uint32_t systemNum = 0;
    for (auto &pidIter : mediaKeySystemForPid_) {
        dumpString += SPLIT_LINE;
        systemNum++;
        dumpString += "#### MediaKeySystem " + std::to_string(systemNum) + " ####\n";
        dumpString += "PID: " + std::to_string(pidIter.first) + "\n";
        for (auto &system : pidIter.second) {
            dumpString += "-------------------------------\n";
            IMediaKeySystemService::CertificateStatus certStatus = IMediaKeySystemService::CERT_STATUS_UNAVAILABLE;
            system->GetCertificateStatus(&certStatus);
            dumpString += "Plugin Name: " + system->GetPluginName() + "\n";
            dumpString += "Certificate Status: " + std::to_string(certStatus) + "\n";
            dumpString += system->GetSessionsDumpInfo();
        }
    }
    dumpString += SPLIT_LINE;
    if (fd != -1) {
        write(fd, dumpString.c_str(), dumpString.size());
    } else {
        DRM_INFO_LOG("%{public}s", dumpString.c_str());
    }
    return OHOS::NO_ERROR;
}

} // DrmStandard
} // OHOS