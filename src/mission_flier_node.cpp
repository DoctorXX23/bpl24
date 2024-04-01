#include <rclcpp/rclcpp.hpp>

#include "mission_flier.hpp"

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);

    rclcpp::executors::SingleThreadedExecutor exec;

    std::shared_ptr<MissionFlier::MissionFlier> missionFlierNode = nullptr;
  
    try
    {
        missionFlierNode = std::make_shared<MissionFlier::MissionFlier>();
    }
    catch(const std::exception& e)
    {
        fprintf(stderr, "%s Exiting..\n", e.what());

        return 1;
    }

    exec.add_node(missionFlierNode);

    exec.spin();

    rclcpp::shutdown();

    return 0;
}