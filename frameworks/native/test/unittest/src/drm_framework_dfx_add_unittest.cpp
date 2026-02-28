/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <mutex>
#include <string>
#include "cstdio"
#include "cstdlib"
#include "drm_dfx.h"
#include "drm_dfx_utils.h"
#include <securec.h>
#include "native_drm_common.h"
#include "native_drm_err.h"
#include "gmock/gmock.h"
#include "native_drm_base.h"
#include "native_drm_object.h"
#include "drm_framework_unittest.h"
#include "http.h"


using namespace testing::ext;
using namespace std;


namespace OHOS {
namespace DrmStandard {
    HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_051, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_51";
    cert.currentTime = 1697730051;
    cert.appName = "MyApp51";
    cert.instanceId = "instance_051";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_051";
    cert.clientVersion = "v1.2.51";
    cert.generationDuration = 1051;
    cert.generationResult = "failed";
    cert.processDuration = 351;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731051;
    cert.serverCostDuration = 151;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_052, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_52";
    cert.currentTime = 1697730052;
    cert.appName = "MyApp52";
    cert.instanceId = "instance_052";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_052";
    cert.clientVersion = "v1.2.52";
    cert.generationDuration = 1052;
    cert.generationResult = "success";
    cert.processDuration = 352;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731052;
    cert.serverCostDuration = 152;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_053, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_53";
    cert.currentTime = 1697730053;
    cert.appName = "MyApp53";
    cert.instanceId = "instance_053";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_053";
    cert.clientVersion = "v1.2.53";
    cert.generationDuration = 1053;
    cert.generationResult = "timeout";
    cert.processDuration = 353;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731053;
    cert.serverCostDuration = 153;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}
HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_054, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_54";
    cert.currentTime = 1697730054;
    cert.appName = "MyApp54";
    cert.instanceId = "instance_054";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_054";
    cert.clientVersion = "v1.2.54";
    cert.generationDuration = 1054;
    cert.generationResult = "success";
    cert.processDuration = 354;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731054;
    cert.serverCostDuration = 154;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_055, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_55";
    cert.currentTime = 1697730055;
    cert.appName = "MyApp55";
    cert.instanceId = "instance_055";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_055";
    cert.clientVersion = "v1.2.55";
    cert.generationDuration = 1055;
    cert.generationResult = "failed";
    cert.processDuration = 355;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731055;
    cert.serverCostDuration = 155;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}
HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_056, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_56";
    cert.currentTime = 1697730056;
    cert.appName = "MyApp56";
    cert.instanceId = "instance_056";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_056";
    cert.clientVersion = "v1.2.56";
    cert.generationDuration = 1056;
    cert.generationResult = "success";
    cert.processDuration = 356;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731056;
    cert.serverCostDuration = 156;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_057, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_57";
    cert.currentTime = 1697730057;
    cert.appName = "MyApp57";
    cert.instanceId = "instance_057";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_057";
    cert.clientVersion = "v1.2.57";
    cert.generationDuration = 1057;
    cert.generationResult = "failed";
    cert.processDuration = 357;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731057;
    cert.serverCostDuration = 157;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_058, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_58";
    cert.currentTime = 1697730058;
    cert.appName = "MyApp58";
    cert.instanceId = "instance_058";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_058";
    cert.clientVersion = "v1.2.58";
    cert.generationDuration = 1058;
    cert.generationResult = "timeout";
    cert.processDuration = 358;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731058;
    cert.serverCostDuration = 158;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_059, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_59";
    cert.currentTime = 1697730059;
    cert.appName = "MyApp59";
    cert.instanceId = "instance_059";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_059";
    cert.clientVersion = "v1.2.59";
    cert.generationDuration = 1059;
    cert.generationResult = "success";
    cert.processDuration = 359;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731059;
    cert.serverCostDuration = 159;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_060, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_60";
    cert.currentTime = 1697730060;
    cert.appName = "MyApp60";
    cert.instanceId = "instance_060";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_060";
    cert.clientVersion = "v1.2.60";
    cert.generationDuration = 1060;
    cert.generationResult = "failed";
    cert.processDuration = 360;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731060;
    cert.serverCostDuration = 160;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_061, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_61";
    cert.currentTime = 1697730061;
    cert.appName = "MyApp61";
    cert.instanceId = "instance_061";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_061";
    cert.clientVersion = "v1.2.61";
    cert.generationDuration = 1061;
    cert.generationResult = "success";
    cert.processDuration = 361;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731061;
    cert.serverCostDuration = 161;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_062, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_62";
    cert.currentTime = 1697730062;
    cert.appName = "MyApp62";
    cert.instanceId = "instance_062";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_062";
    cert.clientVersion = "v1.2.62";
    cert.generationDuration = 1062;
    cert.generationResult = "failed";
    cert.processDuration = 362;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731062;
    cert.serverCostDuration = 162;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_063, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_63";
    cert.currentTime = 1697730063;
    cert.appName = "MyApp63";
    cert.instanceId = "instance_063";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_063";
    cert.clientVersion = "v1.2.63";
    cert.generationDuration = 1063;
    cert.generationResult = "timeout";
    cert.processDuration = 363;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731063;
    cert.serverCostDuration = 163;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_064, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_64";
    cert.currentTime = 1697730064;
    cert.appName = "MyApp64";
    cert.instanceId = "instance_064";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_064";
    cert.clientVersion = "v1.2.64";
    cert.generationDuration = 1064;
    cert.generationResult = "success";
    cert.processDuration = 364;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731064;
    cert.serverCostDuration = 164;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_065, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_65";
    cert.currentTime = 1697730065;
    cert.appName = "MyApp65";
    cert.instanceId = "instance_065";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_065";
    cert.clientVersion = "v1.2.65";
    cert.generationDuration = 1065;
    cert.generationResult = "failed";
    cert.processDuration = 365;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731065;
    cert.serverCostDuration = 165;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}
HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_066, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_66";
    cert.currentTime = 1697730066;
    cert.appName = "MyApp66";
    cert.instanceId = "instance_066";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_066";
    cert.clientVersion = "v1.2.66";
    cert.generationDuration = 1066;
    cert.generationResult = "success";
    cert.processDuration = 366;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731066;
    cert.serverCostDuration = 166;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_067, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_67";
    cert.currentTime = 1697730067;
    cert.appName = "MyApp67";
    cert.instanceId = "instance_067";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_067";
    cert.clientVersion = "v1.2.67";
    cert.generationDuration = 1067;
    cert.generationResult = "failed";
    cert.processDuration = 367;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731067;
    cert.serverCostDuration = 167;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_068, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_68";
    cert.currentTime = 1697730068;
    cert.appName = "MyApp68";
    cert.instanceId = "instance_068";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_068";
    cert.clientVersion = "v1.2.68";
    cert.generationDuration = 1068;
    cert.generationResult = "timeout";
    cert.processDuration = 368;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731068;
    cert.serverCostDuration = 168;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_069, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_69";
    cert.currentTime = 1697730069;
    cert.appName = "MyApp69";
    cert.instanceId = "instance_069";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_069";
    cert.clientVersion = "v1.2.69";
    cert.generationDuration = 1069;
    cert.generationResult = "success";
    cert.processDuration = 369;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731069;
    cert.serverCostDuration = 169;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_070, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_70";
    cert.currentTime = 1697730070;
    cert.appName = "MyApp70";
    cert.instanceId = "instance_070";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_070";
    cert.clientVersion = "v1.2.70";
    cert.generationDuration = 1070;
    cert.generationResult = "failed";
    cert.processDuration = 370;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731070;
    cert.serverCostDuration = 170;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_071, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_71";
    cert.currentTime = 1697730071;
    cert.appName = "MyApp71";
    cert.instanceId = "instance_071";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_071";
    cert.clientVersion = "v1.2.71";
    cert.generationDuration = 1071;
    cert.generationResult = "success";
    cert.processDuration = 371;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731071;
    cert.serverCostDuration = 171;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_072, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_72";
    cert.currentTime = 1697730072;
    cert.appName = "MyApp72";
    cert.instanceId = "instance_072";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_072";
    cert.clientVersion = "v1.2.72";
    cert.generationDuration = 1072;
    cert.generationResult = "failed";
    cert.processDuration = 372;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731072;
    cert.serverCostDuration = 172;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_073, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_73";
    cert.currentTime = 1697730073;
    cert.appName = "MyApp73";
    cert.instanceId = "instance_073";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_073";
    cert.clientVersion = "v1.2.73";
    cert.generationDuration = 1073;
    cert.generationResult = "timeout";
    cert.processDuration = 373;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731073;
    cert.serverCostDuration = 173;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_074, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_74";
    cert.currentTime = 1697730074;
    cert.appName = "MyApp74";
    cert.instanceId = "instance_074";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_074";
    cert.clientVersion = "v1.2.74";
    cert.generationDuration = 1074;
    cert.generationResult = "success";
    cert.processDuration = 374;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731074;
    cert.serverCostDuration = 174;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_075, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_75";
    cert.currentTime = 1697730075;
    cert.appName = "MyApp75";
    cert.instanceId = "instance_075";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_075";
    cert.clientVersion = "v1.2.75";
    cert.generationDuration = 1075;
    cert.generationResult = "failed";
    cert.processDuration = 375;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731075;
    cert.serverCostDuration = 175;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}
HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_076, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_76";
    cert.currentTime = 1697730076;
    cert.appName = "MyApp76";
    cert.instanceId = "instance_076";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_076";
    cert.clientVersion = "v1.2.76";
    cert.generationDuration = 1076;
    cert.generationResult = "success";
    cert.processDuration = 376;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731076;
    cert.serverCostDuration = 176;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_077, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_77";
    cert.currentTime = 1697730077;
    cert.appName = "MyApp77";
    cert.instanceId = "instance_077";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_077";
    cert.clientVersion = "v1.2.77";
    cert.generationDuration = 1077;
    cert.generationResult = "failed";
    cert.processDuration = 377;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731077;
    cert.serverCostDuration = 177;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_078, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_78";
    cert.currentTime = 1697730078;
    cert.appName = "MyApp78";
    cert.instanceId = "instance_078";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_078";
    cert.clientVersion = "v1.2.78";
    cert.generationDuration = 1078;
    cert.generationResult = "timeout";
    cert.processDuration = 378;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731078;
    cert.serverCostDuration = 178;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_079, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_79";
    cert.currentTime = 1697730079;
    cert.appName = "MyApp79";
    cert.instanceId = "instance_079";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_079";
    cert.clientVersion = "v1.2.79";
    cert.generationDuration = 1079;
    cert.generationResult = "success";
    cert.processDuration = 379;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731079;
    cert.serverCostDuration = 179;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}

HWTEST_F(DrmFrameworkUnitTest, Drm_unittest_WriteCertificateEvent_080, TestSize.Level0)
{
    DrmEvent *drmevent = new DrmEvent();
    DrmCertificateInfo cert;
    cert.module = "video_80";
    cert.currentTime = 1697730080;
    cert.appName = "MyApp80";
    cert.instanceId = "instance_080";
    cert.drmName = "ClearPlayDRM";
    cert.drmUuid = "uuid_080";
    cert.clientVersion = "v1.2.80";
    cert.generationDuration = 1080;
    cert.generationResult = "failed";
    cert.processDuration = 380;
    cert.processResult = "Processed";
    cert.callServerTime = 1697731080;
    cert.serverCostDuration = 180;
    cert.serverResult = "ServerOK";
    Drm_ErrCode errNo = static_cast<Drm_ErrCode>(
        drmevent->WriteCertificateEvent(
            "DRM_CERTIFICATE_DOWNLOAD_INFO",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            cert));
    EXPECT_EQ(errNo, 0);
    delete drmevent;
}
} // DrmStandard
} // OHOS