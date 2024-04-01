#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/mission/mission.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/info/info.h>

#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <string>
#include <memory>
#include <mutex>

#include <stdint.h>

#include <Eigen/Dense>

#include <rclcpp/rclcpp.hpp>

#include "std_srvs/srv/trigger.hpp"
#include "std_srvs/srv/empty.hpp"
#include "std_msgs/msg/string.hpp"

namespace MissionFlier
{
    mavsdk::Mission::MissionItem makeMissionItem(double latitude_deg,
                                                   double longitude_deg,
                                                   float relative_altitude_m,
                                                   float speed_m_s,
                                                   bool is_fly_through = false,
                                                   float gimbal_pitch_deg = 0,
                                                   float gimbal_yaw_deg = 0,
                                                   mavsdk::Mission::MissionItem::CameraAction camera_action = mavsdk::Mission::MissionItem::CameraAction::None);

    class MissionFlier : public rclcpp::Node
    {
    public:
        MissionFlier();

    private:
        std::string _connection = std::string("udp://:14541");

        std::unique_ptr<mavsdk::Mavsdk> _mavsdk;

        std::unique_ptr<mavsdk::Mission> _mission;
        std::unique_ptr<mavsdk::Action> _action;
        std::unique_ptr<mavsdk::Telemetry> _telemetry;

        mavsdk::Mission::MissionProgress _missionProgress;

        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr _srvTakeOff;
        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr _srvLand;

        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr _srvStartMission;
        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr _srvStopMission;

        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr _srvUploadMission;

        void cbPosition(mavsdk::Telemetry::Position aPosition);
        void cbBattery(mavsdk::Telemetry::Battery aBattery);

        void cbUploadMission(const std::shared_ptr<std_srvs::srv::Trigger::Request> aRequest, const std::shared_ptr<std_srvs::srv::Trigger::Response> aResponse);
        void cbTakeOff(const std::shared_ptr<std_srvs::srv::Trigger::Request> aRequest, const std::shared_ptr<std_srvs::srv::Trigger::Response> aResponse);
        void cbLand(const std::shared_ptr<std_srvs::srv::Trigger::Request> aRequest, const std::shared_ptr<std_srvs::srv::Trigger::Response> aResponse);

        void cbStartMission(const std::shared_ptr<std_srvs::srv::Trigger::Request> aRequest, const std::shared_ptr<std_srvs::srv::Trigger::Response> aResponse);
        void cbStopMission(const std::shared_ptr<std_srvs::srv::Trigger::Request> aRequest, const std::shared_ptr<std_srvs::srv::Trigger::Response> aResponse);
    
        std::shared_ptr<mavsdk::System> getSystem(mavsdk::Mavsdk& aMavsdk);
    };
}