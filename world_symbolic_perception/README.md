# world_symbolic_perception

SSY236 Assignment 3: Knowledge Management and Behaviour Trees.

Crisitan Alejandro Garcia Mendoza
Manh Duong
Waleed Mohamed Alzubeir Abubakr

## Video

https://youtu.be/4xJ-8mxzoUM


## Build

```bash
cd ~/ros2_ws && colcon build --packages-select world_symbolic_perception && source install/setup.bash
```

## Run

MongoDB must be running before starting the knowledge base interface.

Terminal 1, simulation:
```bash
ros2 launch world_symbolic_perception tiago_gazebo.launch.py is_public_sim:=True base_type:=omni_base world_name:=custom_world
```

Terminal 2, clear the knowledge base and start the knowledge base interface:
```bash
python3 ~/ros2_ws/src/ssy236-dependencies/kb_interface/test/clear_kb.py && ros2 launch kb_interface kb_interface.launch.py
```

Terminal 3, knowledge base state:
```bash
python3 ~/ros2_ws/src/ssy236-dependencies/kb_interface/test/kb_state_debugger.py
```

Terminal 4, behaviour tree executor:
```bash
ros2 launch world_symbolic_perception tree_executor.launch.xml
```

Terminal 5, keyboard teleoperation:
```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -r cmd_vel:=/mobile_base_controller/cmd_vel_unstamped
```

Terminal 6, start the behaviour tree:
```bash
ros2 action send_goal /behaviour_tree_server btcpp_ros2_interfaces/action/ExecuteTree "{target_tree: WorldPerception}"
```
