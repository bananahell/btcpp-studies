from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration


pkg_pubsub_bt = get_package_share_directory('pubsub_bt')
ARGUMENTS = [
    DeclareLaunchArgument('bt',
                          description='Behavior Tree XML to execute'),
    DeclareLaunchArgument('tick_rate_ms', default_value="1500",
                          description='Rate in milliseconds between ticks'),
]


def generate_launch_description():
  execute_bt_cmd = Node(
      package="pubsub_bt",
      executable="main",
      name="main",
      parameters=[{"bt": LaunchConfiguration('bt'),
                   "tick_rate_ms": LaunchConfiguration("tick_rate_ms")}]
  )
  ld = LaunchDescription(ARGUMENTS)
  ld.add_action(execute_bt_cmd)
  return ld
