/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "key_session_service_callback_proxy.h"
#include "drm_log.h"
#include "remote_request_code.h"

namespace OHOS {
namespace DrmStandard {

KeySessionServiceCallbackProxy::KeySessionServiceCallbackProxy(const sptr<IRemoteObject> &impl)
    : IRemoteProxy<IKeySessionServiceCallback>(impl) { };

int32_t KeySessionServiceCallbackProxy::OnKeySessionKeyExpired(const KeyStatus status)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    DRM_INFO_LOG("KeySessionServiceCallbackProxy OnKeySessionKeyExpired called");
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        DRM_ERR_LOG("KeySessionServiceCallbackProxy OnKeySessionKeyExpired Write interface token failed");
        return IPC_PROXY_ERR;
    }
    if (!data.WriteInt32(status)) {
        DRM_ERR_LOG("KeySessionServiceCallbackProxy OnKeySessionKeyExpired Write status failed");
        return IPC_PROXY_ERR;
    }
    int error = Remote()->SendRequest(KEY_SESSION_SERVICE_CALLBACK_ON_KEY_EXPIRED, data, reply, option);
    if (error != ERR_NONE) {
        DRM_ERR_LOG("KeySessionServiceCallbackProxy OnKeySessionKeyExpired failed, error: %{public}d", error);
    }
    return error;
}

int32_t KeySessionServiceCallbackProxy::OnKeySessionReclaimed(const SessionStatus status)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    DRM_INFO_LOG("KeySessionServiceCallbackProxy OnKeySessionReclaimed called");
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        DRM_ERR_LOG("KeySessionServiceCallbackProxy OnKeySessionReclaimed Write interface token failed");
        return IPC_PROXY_ERR;
    }
    if (!data.WriteInt32(status)) {
        DRM_ERR_LOG("KeySessionServiceCallbackProxy OnKeySessionReclaimed Write status failed");
        return IPC_PROXY_ERR;
    }
    int error = Remote()->SendRequest(KEY_SESSION_SERVICE_CALLBACK_ON_KEY_SESSION_RECLAIMED, data, reply, option);
    if (error != ERR_NONE) {
        DRM_ERR_LOG("KeySessionServiceCallbackProxy OnKeySessionReclaimed failed, error: %{public}d", error);
    }
    return error;
}

} // DrmStandard
} // namespace OHOS