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

#ifndef OHOS_DRM_MEDIA_KEY_SYSTEMP_IMPL_H
#define OHOS_DRM_MEDIA_KEY_SYSTEMP_IMPL_H

#include <thread>
#include <queue>
#include "ipc_skeleton.h"
#include "nocopyable.h"
#include "drm_log.h"
#include "drm_death_recipient.h"
#include "key_session_impl.h"
#include "drm_listener_stub.h"
#include "imedia_key_system_service.h"
#include "media_key_system_service_callback_stub.h"

namespace OHOS {
namespace DrmStandard {
namespace MediaKeySystemEvent {
const std::string EVENT_STR_PROVISION_REQUIRED = "keySystemRequired";
}
class MediaKeySystemImplCallback : public RefBase {
public:
    MediaKeySystemImplCallback() = default;
    virtual ~MediaKeySystemImplCallback() = default;
    virtual void SendEvent(const std::string &event, int32_t extra, const std::vector<uint8_t> &data) = 0;
};

class MediaKeySystemCallback;

class MediaKeySystemImpl : public RefBase {
public:
    explicit MediaKeySystemImpl(sptr<IMediaKeySystemService> &mediaKeysystem);
    ~MediaKeySystemImpl();

    int32_t SetConfigurationString(std::string &configName, std::string &value);
    int32_t GetConfigurationString(std::string &configName, std::string &value);
    int32_t SetConfigurationByteArray(std::string &configName, std::vector<uint8_t> &value);
    int32_t GetConfigurationByteArray(std::string &configName, std::vector<uint8_t> &value);
    int32_t CreateMediaKeySession(ContentProtectionLevel securityLevel,
        sptr<MediaKeySessionImpl> *keySessionImpl);
    int32_t GetStatistics(std::vector<MetircKeyValue> &metrics);
    int32_t GetMaxContentProtectionLevel(ContentProtectionLevel *securityLevel);

    int32_t GenerateKeySystemRequest(std::vector<uint8_t> &request, std::string &defaultUrl);
    int32_t ProcessKeySystemResponse(const std::vector<uint8_t> &response);

    int32_t GetOfflineMediaKeyIds(std::vector<std::vector<uint8_t>> &licenseIds);
    int32_t GetOfflineMediaKeyStatus(std::vector<uint8_t> &licenseId,
        OfflineMediaKeyStatus &status);
    int32_t ClearOfflineMediaKeys(std::vector<uint8_t> &licenseId);

    int32_t GetCertificateStatus(CertificateStatus *certStatus);
    sptr<MediaKeySystemImplCallback> GetApplicationCallback();
    int32_t SetCallback(const sptr<MediaKeySystemImplCallback> &callback);
    int32_t Release();

private:
    void MediaKeySystemServerDied(pid_t pid);
    std::recursive_mutex mutex_;
    sptr<IMediaKeySystemService> serviceProxy_;
    sptr<MediaKeySystemImplCallback> mediaKeySystemApplicationCallback_;
    sptr<MediaKeySystemCallback> serviceCallback_;
    sptr<DrmDeathRecipient> deathRecipient_ = nullptr;
};

struct MediaKeySystemEventMessage {
    DrmEventType event;
    int32_t extra;
    std::vector<uint8_t> data;
    MediaKeySystemEventMessage(DrmEventType t, int32_t e, std::vector<uint8_t> d) : event(t), extra(e), data(d)
    {}
};

class MediaKeySystemCallback : public MediaKeySystemServiceCallbackStub {
public:
    MediaKeySystemCallback() : systemImpl_(nullptr)
    {
        InitEventMap();
    };
    explicit MediaKeySystemCallback(MediaKeySystemImpl *systemImpl) : systemImpl_(systemImpl)
    {
        InitEventMap();
    };
    ~MediaKeySystemCallback();
    void InitEventMap();
    std::string GetEventName(DrmEventType event);
    int32_t SendEvent(DrmEventType event, int32_t extra, const std::vector<uint8_t> &data) override;
    void Release();
    void Init();
private:
    int32_t SendEventHandler(DrmEventType event, int32_t extra, const std::vector<uint8_t> &data);
    std::recursive_mutex mutex_;
    MediaKeySystemImpl *systemImpl_;
    std::unordered_map<int32_t, std::string> eventMap_;
    bool serviceThreadRunning = false;
    void ProcessEventMessage();
    std::thread eventQueueThread;
    std::queue<MediaKeySystemEventMessage> eventQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
};
} // DrmStandard
} // OHOS
#endif // OHOS_DRM_MEDIA_KEY_SYSTEMP_IMPL_H
