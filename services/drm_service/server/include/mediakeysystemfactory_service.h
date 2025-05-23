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

#ifndef OHOS_DRM_MEDIA_KEY_SYSTEM_FACTORY_SERVICE_H
#define OHOS_DRM_MEDIA_KEY_SYSTEM_FACTORY_SERVICE_H

#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <refbase.h>
#include "iremote_stub.h"
#include "system_ability.h"
#include "drm_host_manager.h"
#include "drm_log.h"
#include "media_key_system_factory_service_stub.h"
#include "mediakeysystem_service.h"
#include "idrm_listener.h"
#include "drm_death_recipient.h"

#include "v1_0/media_key_system_factory_proxy.h"
#include "v1_0/media_key_system_proxy.h"

namespace OHOS {
namespace DrmStandard {
using namespace OHOS::HDI::Drm::V1_0;
using namespace OHOS::HDI;
class MediaKeySystemFactoryService : public SystemAbility,
    public MediaKeySystemFactoryServiceStub,
    public DrmHostManager::StatusCallback,
    public IMediaKeySystemServiceOperatorsCallback {
    DECLARE_SYSTEM_ABILITY(MediaKeySystemFactoryService);

public:
    DISALLOW_COPY_AND_MOVE(MediaKeySystemFactoryService);
    explicit MediaKeySystemFactoryService(int32_t systemAbilityId, bool runOnCreate = true);
    ~MediaKeySystemFactoryService() override;
    void OnDump() override;
    void OnStart() override;
    void OnStop() override;
    int32_t OnIdle(const SystemAbilityOnDemandReason& idleReason) override;
    int32_t Dump(int32_t fd, const std::vector<std::u16string>& args) override;
    int32_t IsMediaKeySystemSupported(const std::string &name, bool &isSupported) override;
    int32_t IsMediaKeySystemSupported(const std::string &name, const std::string &mimeType,
        bool &isSupported) override;
    int32_t IsMediaKeySystemSupported(const std::string &name, const std::string &mimeType, int32_t securityLevel,
        bool &isSupported) override;
    int32_t CreateMediaKeySystem(const std::string &name, sptr<IMediaKeySystemService> &mediaKeySystemProxy) override;
    int32_t CloseMediaKeySystemService(sptr<MediaKeySystemService> mediaKeySystemService) override;
    int32_t GetMediaKeySystems(std::map<std::string, std::string> &mediaKeySystemNames) override;
    int32_t GetMediaKeySystemUuid(const std::string &name, std::string &uuid) override;
    void OnDrmPluginDied(std::string &name) override;
    int32_t SetListenerObject(const sptr<IRemoteObject>& object) override;

private:
    void OnAddSystemAbility(int32_t systemAbilityId, const std::string &deviceId) override;
    void InitStatisticsInfo(const sptr<IMediaKeySystem> &hdiMediaKeySystem,
        std::string pluginName, StatisticsInfo &statisticsInfo);
    int32_t WriteDumpInfo(int32_t fd, std::string &dumpString);
    std::recursive_mutex mutex_;
    sptr<DrmHostManager> drmHostManager_;
    std::map<int32_t, std::set<sptr<MediaKeySystemService>>> mediaKeySystemForPid_;
    std::map<std::string, int32_t> currentMediaKeySystemNum_;
    std::recursive_mutex factoryServiceMutex_;
    void DistroyForClientDied(pid_t pid);
    void MediaKeySystemFactoryClientDied(pid_t pid);
    bool IsListenerObjectSet();
    int32_t CancelAbilityIdle();
    std::map<pid_t, sptr<DrmDeathRecipient>> deathRecipientMap_;
    std::map<pid_t, sptr<IDrmListener>> clientListenerMap_;
};
} // DrmStandard
} // OHOS

#endif // OHOS_DRM_MEDIA_KEY_SYSTEM_FACTORY_SERVICE_H