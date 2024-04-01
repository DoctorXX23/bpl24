#include "mission_flier.hpp"

#include <stdexcept>

using std::chrono::seconds;
using std::this_thread::sleep_for;
using namespace std::placeholders;

namespace MissionFlier
{
    /**
     * @brief Construct a new Mission Flier based on declaration
     * 
     */
    MissionFlier::MissionFlier() : Node("MissionFlier")
    {

    }

    std::shared_ptr<mavsdk::System> MissionFlier::getSystem(mavsdk::Mavsdk& aMavsdk)
    {
        
    }

    void MissionFlier::cbPosition(mavsdk::Telemetry::Position aPosition)
    {
    }

    void MissionFlier::cbBattery(mavsdk::Telemetry::Battery aBattery)
    {
    }

    void MissionFlier::cbStartMission(const std::shared_ptr<std_srvs::srv::Trigger::Request> aRequest, const std::shared_ptr<std_srvs::srv::Trigger::Response> aResponse)
    {
        
    }

    void MissionFlier::cbStopMission(const std::shared_ptr<std_srvs::srv::Trigger::Request> aRequest, const std::shared_ptr<std_srvs::srv::Trigger::Response> aResponse)
    {
        
    }

    void MissionFlier::cbTakeOff(const std::shared_ptr<std_srvs::srv::Trigger::Request> aRequest, const std::shared_ptr<std_srvs::srv::Trigger::Response> aResponse)
    {
        
    }

    void MissionFlier::cbLand(const std::shared_ptr<std_srvs::srv::Trigger::Request> aRequest, const std::shared_ptr<std_srvs::srv::Trigger::Response> aResponse)
    {
        
    }

    void MissionFlier::cbUploadMission(const std::shared_ptr<std_srvs::srv::Trigger::Request> aRequest, const std::shared_ptr<std_srvs::srv::Trigger::Response> aResponse)
    {
        std::vector<mavsdk::Mission::MissionItem> missionItems;

        missionItems.push_back(makeMissionItem(
            47.398170327054473,
            8.5456490218639658,
            10.0f,
            5.0f,
            false,
            20.0f,
            60.0f,
            mavsdk::Mission::MissionItem::CameraAction::None));

        missionItems.push_back(makeMissionItem(
            47.398241338125118,
            8.5455360114574432,
            10.0f,
            2.0f,
            true,
            0.0f,
            -60.0f,
            mavsdk::Mission::MissionItem::CameraAction::TakePhoto));

        missionItems.push_back(makeMissionItem(
            47.398139363821485,
            8.5453846156597137,
            10.0f,
            5.0f,
            true,
            -45.0f,
            0.0f,
            mavsdk::Mission::MissionItem::CameraAction::StartVideo));

        missionItems.push_back(makeMissionItem(
            47.398058617228855,
            8.5454618036746979,
            10.0f,
            2.0f,
            false,
            -90.0f,
            30.0f,
            mavsdk::Mission::MissionItem::CameraAction::StopVideo));

        missionItems.push_back(makeMissionItem(
            47.398100366082858,
            8.5456969141960144,
            10.0f,
            5.0f,
            false,
            -45.0f,
            -30.0f,
            mavsdk::Mission::MissionItem::CameraAction::StartPhotoInterval));

        missionItems.push_back(makeMissionItem(
            47.398001890458097,
            8.5455576181411743,
            10.0f,
            5.0f,
            false,
            0.0f,
            0.0f,
            mavsdk::Mission::MissionItem::CameraAction::StopPhotoInterval));

        mavsdk::Mission::MissionPlan mission_plan{};

        mission_plan.mission_items = missionItems;

        const mavsdk::Mission::Result upload_result = _mission.get()->upload_mission(mission_plan);

        if(upload_result != mavsdk::Mission::Result::Success)
        {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Mission upload failed");

            aResponse->success = false;

            return;
        }

        aResponse->success = true;

        std::cout << "Got mission data. Size: " << missionItems.size() << std::endl;
    }

    mavsdk::Mission::MissionItem makeMissionItem(double latitude_deg,
                                                   double longitude_deg,
                                                   float relative_altitude_m,
                                                   float speed_m_s,
                                                   bool is_fly_through,
                                                   float gimbal_pitch_deg,
                                                   float gimbal_yaw_deg,
                                                   mavsdk::Mission::MissionItem::CameraAction camera_action)
    {
        mavsdk::Mission::MissionItem new_item{};

        new_item.latitude_deg = latitude_deg;
        new_item.longitude_deg = longitude_deg;
        new_item.relative_altitude_m = relative_altitude_m;
        new_item.speed_m_s = speed_m_s;
        new_item.is_fly_through = is_fly_through;
        new_item.gimbal_pitch_deg = gimbal_pitch_deg;
        new_item.gimbal_yaw_deg = gimbal_yaw_deg;
        new_item.camera_action = camera_action;

        return new_item;
    }
}