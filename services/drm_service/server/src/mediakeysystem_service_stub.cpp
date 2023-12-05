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

#include "mediakeysystem_service_stub.h"
#include "drm_error_code.h"
#include "drm_log.h"
#include "ipc_skeleton.h"
#include "xcollie/xcollie.h"
#include "xcollie/xcollie_define.h"

namespace OHOS {
namespace DrmStandard {
using ProcessRemoteRequestFunc = int (*)(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

struct ProcessRemoteRequestFuncArray {
    OHOS::DrmStandard::MediaKeySystemServiceRequestCode requestCode;
    ProcessRemoteRequestFunc processFunc;
};

static int ProcessCreatekeySession(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessKeySystemRequest(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessKeySystemResponse(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessSetConfigurationString(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessGetConfigurationString(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessSetConfigurationByteArray(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessGetConfigurationByteArray(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessGetMetircs(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessReleaseKeySystem(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessGetMaxSecurityLevel(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessGetCertificateStatus(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessGetOfflineLicenseIds(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessGetOfflineLicenseStatus(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static int ProcessRemoveOfflineLicense(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option);

static struct ProcessRemoteRequestFuncArray g_mediaKeySystemServiceStubRequestProcessFunc[] = {
    {MEDIA_KEY_SYSTEM_CREATE_KEY_SESSION, ProcessCreatekeySession},
    {MEDIA_KEY_SYSTEM_GENERATE_KEYSYSTEM_REQUEST, ProcessKeySystemRequest},
    {MEDIA_KEY_SYSTEM_PROCESS_KEYSYSTEM_RESPONSE, ProcessKeySystemResponse},
    {MEDIA_KEY_SYSTEM_SETCONFIGURATION_STRING, ProcessSetConfigurationString},
    {MEDIA_KEY_SYSTEM_GETCONFIGURATION_STRING, ProcessGetConfigurationString},
    {MEDIA_KEY_SYSTEM_SETCONFIGURATION_BYTEARRAY, ProcessSetConfigurationByteArray},
    {MEDIA_KEY_SYSTEM_GETCONFIGURATION_BYTEARRAY, ProcessGetConfigurationByteArray},
    {MEDIA_KEY_SYSTEM_GETMETRIC, ProcessGetMetircs},
    {MEDIA_KEY_SYSTEM_RELEASE, ProcessReleaseKeySystem},
    {MEDIA_KEY_SYSTEM_GETMAXSECURITYLEVEL, ProcessGetMaxSecurityLevel},
    {MEDIA_KEY_SYSTEM_GETCERTIFICATESTATUS, ProcessGetCertificateStatus},
    {MEDIA_KEY_SYSTEM_GET_OFFLINELICENSEIDS, ProcessGetOfflineLicenseIds},
    {MEDIA_KEY_SYSTEM_GET_OFFLINEKEY_STATUS, ProcessGetOfflineLicenseStatus},
    {MEDIA_KEY_SYSTEM_REMOVE_OFFLINELICENSE, ProcessRemoveOfflineLicense},
};

MediaKeySystemServiceStub::MediaKeySystemServiceStub()
{
    deathRecipientMap_.clear();
    DRM_DEBUG_LOG("0x%{public}06" PRIXPTR " Instances create", (POINTER_MASK & reinterpret_cast<uintptr_t>(this)));
}

MediaKeySystemServiceStub::~MediaKeySystemServiceStub()
{
    DRM_DEBUG_LOG("0x%{public}06" PRIXPTR " Instances destroy", (POINTER_MASK & reinterpret_cast<uintptr_t>(this)));
}

static int ProcessCreatekeySession(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_CREATE_KEY_SESSION enter.");
    sptr<IMediaKeySessionService> keySessionServiceProxy = nullptr;
    const int32_t securityLevel = data.ReadInt32();
    int errCode =
        stub->CreateMediaKeySession((IMediaKeySessionService::SecurityLevel)securityLevel, keySessionServiceProxy);
    if (errCode != ERR_NONE) {
        DRM_ERR_LOG("MediaKeySystemServiceStub CreateMediaKeySession failed : %{public}d", errCode);
        return errCode;
    }
    if (!reply.WriteRemoteObject(keySessionServiceProxy->AsObject())) {
        DRM_ERR_LOG("MediaKeySystemServiceStub CreateMediaKeySession Write MediaKeySession obj failed");
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_CREATE_KEY_SESSION exit.");
    return errCode;
}

static int ProcessKeySystemRequest(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GENERATE_KEYSYSTEM_REQUEST enter.");
    std::vector<uint8_t> request;
    std::string defaultUrl;
    int32_t ret = stub->GenerateKeySystemRequest(request, defaultUrl);
    if (!reply.WriteInt32(request.size())) {
        DRM_ERR_LOG("MediaKeySystemServiceStub Write request size failed");
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    for (auto req : request) {
        if (!reply.WriteUint8(req)) {
            DRM_ERR_LOG("MediaKeySystemServiceStub Write request failed");
            return IPC_STUB_WRITE_PARCEL_ERR;
        }
    }
    if (!reply.WriteString(defaultUrl)) {
        DRM_ERR_LOG("MediaKeySystemServiceStub Write GenerateKeySystemRequest failed");
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GENERATE_KEYSYSTEM_REQUEST exit.");
    return ret;
}

static int ProcessKeySystemResponse(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_PROCESS_KEYSYSTEM_RESPONSE enter.");
    std::vector<uint8_t> response;
    uint32_t responseSize = data.ReadInt32();
    for (int i = 0; i < responseSize; i++) {
        response.push_back(data.ReadUint8());
    }
    int32_t ret = stub->ProcessKeySystemResponse(response);
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_PROCESS_KEYSYSTEM_RESPONSE exit.");
    return ret;
}

static int ProcessSetConfigurationString(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("bMediaKeySystemServiceStub MEDIA_KEY_SYSTEM_SETCONFIGURATION enter.");
    std::string configName = data.ReadString();
    std::string value = data.ReadString();
    int32_t ret = stub->SetConfigurationString(configName, value);
    DRM_INFO_LOG("bMediaKeySystemServiceStub MEDIA_KEY_SYSTEM_SETCONFIGURATION exit.");
    return ret;
}

static int ProcessGetConfigurationString(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("bMediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GETCONFIGURATION enter.");
    std::string configName = data.ReadString();
    std::string value;
    int32_t ret = stub->GetConfigurationString(configName, value);
    if (!reply.WriteString(value)) {
        DRM_ERR_LOG("bMediaKeySystemServiceStub Write GenerateKeySystemRequest failed");
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    DRM_INFO_LOG("bMediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GETCONFIGURATION exit.");
    return ret;
}

static int ProcessSetConfigurationByteArray(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("bMediaKeySystemServiceStub MEDIA_KEY_SYSTEM_SETCONFIGURATION enter.");
    std::string configName = data.ReadString();
    std::vector<uint8_t> value;
    uint32_t valueSize = data.ReadInt32();
    for (int i = 0; i < valueSize; i++) {
        value.push_back(data.ReadUint8());
    }
    int32_t ret = stub->SetConfigurationByteArray(configName, value);
    DRM_INFO_LOG("bMediaKeySystemServiceStub MEDIA_KEY_SYSTEM_SETCONFIGURATION exit.");
    return ret;
}

static int ProcessGetConfigurationByteArray(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("bMediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GETCONFIGURATION enter.");
    std::string configName = data.ReadString();
    std::vector<uint8_t> value;
    int32_t ret = stub->GetConfigurationByteArray(configName, value);
    if (!reply.WriteInt32(value.size())) {
        DRM_ERR_LOG("MediaKeySystemServiceStub Write value size failed");
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    for (auto val : value) {
        if (!reply.WriteUint8(val)) {
            DRM_ERR_LOG("MediaKeySystemServiceStub Write value failed");
            return IPC_STUB_WRITE_PARCEL_ERR;
        }
    }
    DRM_INFO_LOG("bMediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GETCONFIGURATION exit.");
    return ret;
}

static int ProcessGetMetircs(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GETMETRIC enter.");
    std::vector<IMediaKeySystemService::MetircKeyValue> metrics;
    int32_t ret = stub->GetMetrics(metrics);
    reply.WriteInt32(metrics.size());
    for (auto info : metrics) {
        reply.WriteString(info.name);
        reply.WriteString(info.value);
    }
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GETMETRIC exit.");
    return ret;
}

static int ProcessReleaseKeySystem(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("MediaKeySystemServiceStub KEY_SESSION_RELEASE enter.");
    int32_t ret = stub->Release();
    DRM_INFO_LOG("MediaKeySystemServiceStub KEY_SESSION_RELEASE exit.");
    return ret;
}

static int ProcessGetMaxSecurityLevel(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GETMAXSECURITYLEVEL enter.");
    IMediaKeySessionService::SecurityLevel securityLevel = IMediaKeySessionService::SECURITY_LEVEL_UNKNOWN;
    int32_t ret = stub->GetMaxSecurityLevel(&securityLevel);
    if (!reply.WriteInt32(securityLevel)) {
        DRM_ERR_LOG("MediaKeySystemServiceStub Write GetMaxSecurityLevel failed");
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GETMAXSECURITYLEVEL exit.");
    return ret;
}

static int ProcessGetCertificateStatus(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GETCERTIFICATESTATUS enter.");
    IMediaKeySystemService::CertificateStatus certStatus = IMediaKeySystemService::CERT_STATUS_PROVISIONED;
    int32_t ret = stub->GetCertificateStatus(&certStatus);
    if (!reply.WriteInt32(certStatus)) {
        DRM_ERR_LOG("MediaKeySystemServiceStub Write GetCertificateStatus failed");
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GETCERTIFICATESTATUS exit.");
    return ret;
}

static int ProcessGetOfflineLicenseIds(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GET_OFFLINELICENSEIDS enter.");
    std::vector<std::vector<uint8_t>> licenseIds;
    int32_t ret = stub->GetOfflineLicenseIds(licenseIds);
    reply.WriteInt32(licenseIds.size());
    for (auto licenseId : licenseIds) {
        int32_t licenseIdSize = licenseId.size();
        reply.WriteInt32(licenseIdSize);
        if (!reply.WriteBuffer(licenseId.data(), licenseId.size())) {
            DRM_ERR_LOG("MediaKeySystemServiceStub GenerateLicenseRequest Write licenseId failed");
            return IPC_STUB_WRITE_PARCEL_ERR;
        }
    }

    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GET_OFFLINELICENSEIDS exit.");
    return ret;
}

static int ProcessGetOfflineLicenseStatus(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GET_OFFLINEKEY_STATUS enter.");
    std::vector<uint8_t> licenseId;
    uint32_t licenseIdSize = data.ReadInt32();
    for (int i = 0; i < licenseIdSize; i++) {
        licenseId.push_back(data.ReadUint8());
    }
    IMediaKeySessionService::OfflineLicenseStatus status;
    int32_t ret = stub->GetOfflineLicenseStatus(licenseId, status);
    if (ret != DRM_OK) {
        DRM_ERR_LOG("MEDIA_KEY_SYSTEM_GET_OFFLINEKEY_STATUS failed");
        return ret;
    }
    if (!reply.WriteInt32((int32_t)status)) {
        DRM_ERR_LOG("MediaKeySystemServiceStub Write state failed");
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_GET_OFFLINEKEY_STATUS exit.");
    return ret;
}

static int ProcessRemoveOfflineLicense(MediaKeySystemServiceStub *stub, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_REMOVE_OFFLINELICENSE enter.");
    std::vector<uint8_t> licenseId;
    uint32_t licenseIdSize = data.ReadInt32();
    for (int i = 0; i < licenseIdSize; i++) {
        licenseId.push_back(data.ReadUint8());
    }
    int32_t ret = stub->RemoveOfflineLicense(licenseId);
    DRM_INFO_LOG("MediaKeySystemServiceStub MEDIA_KEY_SYSTEM_REMOVE_OFFLINELICENSE exit.");
    return ret;
}

int MediaKeySystemServiceStub::OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply,
    MessageOption &option)
{
    DRM_CHECK_AND_RETURN_RET_LOG(data.ReadInterfaceToken() == GetDescriptor(), -1,
        "MediaKeySystemServiceStub: ReadInterfaceToken failed");
    DRM_INFO_LOG("OnRemoteRequest, cmd = %{public}u", code);

    DRM_CHECK_AND_RETURN_RET_LOG((code >= MEDIA_KEY_SYSTEM_CREATE_KEY_SESSION) &&
        (code <= MEDIA_KEY_SYSTEM_REMOVE_OFFLINELICENSE),
        IPCObjectStub::OnRemoteRequest(code, data, reply, option),
        "code not match, need check MediaKeySystemServiceStub");

    return g_mediaKeySystemServiceStubRequestProcessFunc[code].processFunc(this, data, reply, option);
}
} // namespace DrmStandard
} // namespace OHOS