# SSY236 - Decision Making for Autonomous Systems

This repository is the `src` folder of a ROS 2 Humble workspace. The repository root is the `src` folder, so the workspace is `~/ros2_ws` and this repo lives at `~/ros2_ws/src`.

## 1. Clone the repository

```bash
mkdir -p ~/ros2_ws
git clone --recurse-submodules https://github.com/superrmanh/DecisionMakingForAutonomousSystems.git ~/ros2_ws/src
```

`--recurse-submodules` downloads `BehaviorTree.ROS2` and `gazebo_models`. If you cloned without it, run:

```bash
cd ~/ros2_ws/src
git submodule update --init BehaviorTree.ROS2
git submodule update --init --depth 1 gazebo_models
```

`gazebo_models` is large, so `--depth 1` is recommended.

## 2. Extra steps (not included in this repository)

### 2.1 Course dependencies (`ssy236-dependencies`)

The `ssy236-dependencies/` folder is a copy of the course's private repository. It contains `kb_interface`, `robot_swiss_knife_msgs`, `gazebo_bbox_plugin` and `ssy236.rviz`. It is included, so you do not need to download it again. If you need the latest version, ask the instructor for access and clone it separately:

```bash
git clone https://github.com/alex-mitrevski/ssy236-dependencies.git
```

Then copy the new contents into `~/ros2_ws/src/ssy236-dependencies/`.

### 2.2 Gazebo models: stop colcon from building it

`gazebo_models` is not a ROS package, so colcon must ignore it. Run once after cloning:

```bash
touch ~/ros2_ws/src/gazebo_models/COLCON_IGNORE
```

### 2.3 ROS 2 Humble and system packages

Install ROS 2 Humble on Ubuntu 22.04 (or WSL2 with Ubuntu 22.04), then install the packages from section 2.10 of the course installation instructions. The minimum this workspace needs is:

```bash
sudo apt update
sudo apt install -y ros-humble-tiago-gazebo ros-humble-gazebo-ros-pkgs ros-humble-gazebo-dev \
  ros-humble-gazebo-msgs ros-humble-gazebo-ros2-control ros-humble-ros2-control \
  ros-humble-ros2-controllers ros-humble-vision-msgs ros-humble-behaviortree-cpp \
  ros-humble-teleop-twist-keyboard libfmt-dev
```

### 2.4 Gazebo model path

Add this line to `~/.bashrc` so Gazebo finds the course worlds and models:

```bash
export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:$HOME/ros2_ws/src/gazebo_models
```

### 2.5 MongoDB (assignments 3 and 4)

Install MongoDB following section 5 of the course installation instructions, then start it:

```bash
mongod --dbpath /data/db --fork --logpath ~/mongod.log
```

Create the data folder first if it does not exist: `sudo mkdir -p /data/db && sudo chown $USER /data/db`.

## 3. Build

```bash
cd ~/ros2_ws
colcon build
source install/setup.bash
```

Run `source install/setup.bash` in every new terminal before using the packages.

## 4. Packages

| Folder | Content |
|---|---|
| `navi_interfaces` | Custom message `Coord2d` (Assignment 1) |
| `navigation_pkg` | Publisher and subscriber nodes (Assignment 1) |
| `world_perception` | Perception components with Gazebo and TF (Assignment 2) |
| `ssy236-dependencies` | Course packages and RViz configuration |
| `BehaviorTree.ROS2` | Behavior tree packages (submodule) |
| `gazebo_models` | Gazebo models and worlds (submodule) |
| `Owl`, `PrologScripts` | Ontology and Prolog files |
| `Assignment1` | Original Assignment 1 files from a previous submission (not part of the workspace) |

Each package has its own `README.md` with the commands to run it. Start with `world_perception/README.md`.

## 5. Docker (optional)

If you use the course Docker container, mount this repository as the workspace source folder:

```bash
-v /path/to/DecisionMakingForAutonomousSystems:/root/ros2_ws/src
```

With this mount, the `ssy236.rviz` path in the `world_perception` README (`/root/ros2_ws/src/ssy236-dependencies/ssy236.rviz`) is valid.
