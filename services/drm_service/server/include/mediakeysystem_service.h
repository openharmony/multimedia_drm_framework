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

#ifndef OHOS_DRM_MEDIA_KEY_SYSTEM_SERVICE_H
#define OHOS_DRM_MEDIA_KEY_SYSTEM_SERVICE_H

#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <refbase.h>
#include "media_key_system_service_stub.h"
#include "key_session_service.h"
#include "drm_dfx_utils.h"
#include "drm_host_manager.h"
#include "drm_log.h"
#include "iremote_stub.h"
#include "system_ability.h"

#include "v1_0/media_key_session_proxy.h"
#include "v1_0/media_key_system_proxy.h"

namespace OHOS {
namespace DrmStandard {
using namespace OHOS::HDI::Drm::V1_0;
using namespace OHOS::HDI;
class IMediaKeySystemServiceOperatorsCallback;
class MediaKeySystemService : public MediaKeySystemServiceStub,
    public DrmHostManager::StatusCallback,
    public IMediaKeySessionServiceOperatorsCallback,
    public IMediaKeySystemCallback {
public:
    explicit MediaKeySystemService(sptr<OHOS::HDI::Drm::V1_0::IMediaKeySystem> hdiKeySystem);
    explicit MediaKeySystemService(sptr<OHOS::HDI::Drm::V1_0::IMediaKeySystem> hdiKeySystem,
        StatisticsInfo statisticsInfo);
    ~MediaKeySystemService() override;
    int32_t Release() override;
    int32_t SetMediaKeySystemServiceOperatorsCallback(wptr<IMediaKeySystemServiceOperatorsCallback> callback);
    int32_t CloseMediaKeySystemServiceByCallback();
    int32_t SetConfigurationString(const std::string &configName, const std::string &value) override;
    int32_t GetConfigurationString(const std::string &configName, std::string &value) override;
    int32_t SetConfigurationByteArray(const std::string &configName, const std::vector<uint8_t> &value) override;
    int32_t GetConfigurationByteArray(const std::string &configName, std::vector<uint8_t> &value) override;
    int32_t GetMaxContentProtectionLevel(ContentProtectionLevel &securityLevel) override;
    int32_t CreateMediaKeySession(ContentProtectionLevel securityLevel,
        sptr<IMediaKeySessionService> &keySessionProxy) override;
    int32_t GenerateKeySystemRequest(std::vector<uint8_t> &request, std::string &defaultUrl) override;
    int32_t ProcessKeySystemResponse(const std::vector<uint8_t> &response) override;
    int32_t GetCertificateStatus(CertificateStatus &certStatus) override;

    int32_t GetOfflineMediaKeyIds(std::vector<std::vector<uint8_t>> &licenseIds) override;
    int32_t GetOfflineMediaKeyStatus(const std::vector<uint8_t> &licenseId,
        OfflineMediaKeyStatus &status) override;
    int32_t ClearOfflineMediaKeys(const std::vector<uint8_t> &licenseId) override;

    int32_t CloseMediaKeySessionService(sptr<MediaKeySessionService> sessionService) override;
    int32_t GetStatistics(std::vector<MetircKeyValue> &metrics) override;
    int32_t SetCallback(const sptr<IMediaKeySystemServiceCallback> &callback) override;
    std::string GetPluginName();
    sptr<OHOS::HDI::Drm::V1_0::IMediaKeySystem> getMediaKeySystem();
    int32_t SetBundleName();
    int32_t SetApiTargetVersion();

    // for hdi callback
    int32_t SendEvent(OHOS::HDI::Drm::V1_0::EventType eventType, int32_t extra,
        const std::vector<uint8_t> &data) override;
    std::string GetSessionsDumpInfo();

private:
    void OnDrmPluginDied(std::string &name) override;
    std::recursive_mutex mutex_;
    std::recursive_mutex callbackMutex_;
    sptr<IMediaKeySystemServiceCallback> callback_;
    wptr<IMediaKeySystemServiceOperatorsCallback> keySystemOperatoersCallback_;
    std::mutex sessionsSetMutex_;
    std::set<sptr<MediaKeySessionService>> sessionsSet_;
    sptr<OHOS::HDI::Drm::V1_0::IMediaKeySystem> hdiKeySystem_;
    StatisticsInfo statisticsInfo_;
    std::string generationResult_;
    uint32_t generationDuration_ = 0;
    uint32_t currentKeySessionNumber = 0;
};

class IMediaKeySystemServiceOperatorsCallback : public virtual RefBase {
public:
    IMediaKeySystemServiceOperatorsCallback() = default;
    virtual ~IMediaKeySystemServiceOperatorsCallback() = default;
    virtual int32_t CloseMediaKeySystemService(sptr<MediaKeySystemService> mediaKeySystemService) = 0;
};
} // DrmStandard
} // OHOS

#endif // OHOS_DRM_MEDIA_KEY_SYSTEM_SERVICE_H