import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, EnvironmentVariable
from launch.substitutions import PythonExpression

def generate_launch_description():

    return LaunchDescription([
        DeclareLaunchArgument(
            'uav_id',
            default_value=EnvironmentVariable('UAV_ID', default_value='/uav2'),
            description='UAV_ID'
        ),

        Node(
            package="bpl_mission_flier",
            executable="bpl_mission_flier",
            namespace=LaunchConfiguration('uav_id'),
            name="mission_flier_node",
            output="screen"
        )
    ])