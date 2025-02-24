# Btcpp Studies

This repo is just me trying to simplify as best as I can the tutorials available at [BTCPP's official website](https://www.behaviortree.dev/) and [LADECIC's ROME tutorials](https://github.com/lesunb/rome2024_tutorials) in a ROS2 Jazzy environment.

## Btcpp Installation

My examples are meant to run with ROS2 Jazzy, and it comes with btcpp installed in it, so you just need to [follow the official (and pretty good) instructions on how to install Jazzy](https://docs.ros.org/en/jazzy/Installation.html).

## How to run

In my tutorials, I'm going to run everything on ROS2, so [understanding how to use it before trying this](https://docs.ros.org/en/jazzy/Tutorials/Beginner-Client-Libraries.html) is highly advisable, but I'll explain everything here, so let's go:

First, you have to source your ROS2 distro by doing

`source /opt/ros/jazzy/setup.bash`

Then you have to go to this repo's root, so your terminal should be looking like:

`.../.../btcpp-studies$`

As good practice, a nice rosdep can ensure the packages are cool

`rosdep install -i --from-path src --rosdistro jazzy -y`

You need to then compile it all (IN THE ROOT)

`colcon build`

Then reference your local workspace

`source install/setup.bash`

For this first example, you can run the first behavior tree written here, so you're gonna use the command:

`ros2 run first_tree first_tree`

And so you'll get the result for this first, very silly, behavior tree:

```
[ Battery: OK ]
GripperInterface::open
ApproachObject: approach_object
GripperInterface::close
```
