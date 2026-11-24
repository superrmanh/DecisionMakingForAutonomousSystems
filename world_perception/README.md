# world_perception

## Videos

- Task 1 (direct perception): https://youtu.be/ubJXJ7vfauY
- Task 2 (perception by moving to objects): https://youtu.be/7WdP7xQL3Fw

## Build

```bash
cd ~/ros2_ws && colcon build --packages-select world_perception && source install/setup.bash
```

## Task 1: direct perception

Terminal 1:
```bash
ros2 launch world_perception tiago_gazebo.launch.py is_public_sim:=True base_type:=omni_base world_name:=custom_world
```

Terminal 2:
```bash
# Windows: C:\Users\cris0\Documents\SSY236\DecisionMakingForAutonomousSystems\ssy236-dependencies\ssy236.rviz
rviz2 -d /root/ros2_ws/src/ssy236-dependencies/ssy236.rviz
```

Terminal 3:
```bash
cd ~/ros2_ws && source install/setup.bash && ros2 launch world_perception direct_perception.launch.py
```

## Task 2: perception by moving to objects

Terminal 1:
```bash
ros2 launch world_perception tiago_gazebo.launch.py is_public_sim:=True base_type:=omni_base world_name:=custom_world
```

Terminal 2:
```bash
# Windows: C:\Users\cris0\Documents\SSY236\DecisionMakingForAutonomousSystems\ssy236-dependencies\ssy236.rviz
rviz2 -d /root/ros2_ws/src/ssy236-dependencies/ssy236.rviz
```

Terminal 3:
```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard --remap cmd_vel:=/mobile_base_controller/cmd_vel_unstamped
```

Terminal 4:
```bash
cd ~/ros2_ws && source install/setup.bash && ros2 launch world_perception perception.launch.py
```
