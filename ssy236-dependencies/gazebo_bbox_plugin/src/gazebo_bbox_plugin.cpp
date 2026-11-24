// gazebo_bbox_plugin.cpp
//
// Gazebo Classic (gazebo11) WORLD plugin for ROS 2.
// Iterates over every model in the world each update and publishes
// each model's world-frame axis-aligned bounding box (AABB) as a
// vision_msgs/msg/Detection3DArray.
//
// - Detection3D.id   -> model name
// - Detection3D.bbox -> center pose + size of the AABB

#include <string>

#include <gazebo/common/Events.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <ignition/math/AxisAlignedBox.hh>

#include <gazebo_ros/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <vision_msgs/msg/detection3_d.hpp>
#include <vision_msgs/msg/detection3_d_array.hpp>

namespace gazebo_bbox_plugin
{

class BoundingBoxPublisher : public gazebo::WorldPlugin
{
public:
  BoundingBoxPublisher() = default;

  void Load(gazebo::physics::WorldPtr world, sdf::ElementPtr sdf) override
  {
    // Uses Gazebo's own console (not rclcpp logging), so this always
    // shows up in the gzserver terminal regardless of ROS logging
    // config/output redirection. If you don't see this line at all,
    // Load() is never being called - the plugin isn't being loaded,
    // not a ROS-node-creation problem.
    gzmsg << "[gazebo_bbox_plugin] Load() called" << std::endl;

    world_ = world;

    // Creates (or reuses) an rclcpp::Node for this plugin. Reads an
    // optional <ros><namespace>...</namespace></ros> block from the SDF.
    // Requires libgazebo_ros_init.so to be loaded in the world so that
    // rclcpp::init() has already been called - this is done automatically
    // by `ros2 launch gazebo_ros gazebo.launch.py`.
    try {
      ros_node_ = gazebo_ros::Node::Get(sdf);
    } catch (const std::exception & e) {
      gzerr << "[gazebo_bbox_plugin] gazebo_ros::Node::Get() threw: "
            << e.what() << std::endl;
      return;
    } catch (...) {
      gzerr << "[gazebo_bbox_plugin] gazebo_ros::Node::Get() threw an "
               "unknown exception" << std::endl;
      return;
    }

    if (!ros_node_) {
      gzerr << "[gazebo_bbox_plugin] gazebo_ros::Node::Get() returned "
               "nullptr - is libgazebo_ros_init.so loaded and has "
               "rclcpp::init() been called?" << std::endl;
      return;
    }

    gzmsg << "[gazebo_bbox_plugin] ROS node created successfully" << std::endl;

    double update_rate = 10.0;
    if (sdf->HasElement("update_rate")) {
      update_rate = sdf->Get<double>("update_rate");
    }
    update_period_ = update_rate > 0.0 ? 1.0 / update_rate : 0.0;

    std::string topic_name = "bounding_boxes";
    if (sdf->HasElement("topic_name")) {
      topic_name = sdf->Get<std::string>("topic_name");
    }

    frame_id_ = "world";
    if (sdf->HasElement("frame_id")) {
      frame_id_ = sdf->Get<std::string>("frame_id");
    }

    include_static_ = true;
    if (sdf->HasElement("include_static")) {
      include_static_ = sdf->Get<bool>("include_static");
    }

    pub_ = ros_node_->create_publisher<vision_msgs::msg::Detection3DArray>(
      topic_name, rclcpp::QoS(10));

    gzmsg << "[gazebo_bbox_plugin] Publisher created on topic '"
          << topic_name << "'" << std::endl;

    last_update_time_ = world_->SimTime();

    update_connection_ = gazebo::event::Events::ConnectWorldUpdateBegin(
      std::bind(&BoundingBoxPublisher::OnUpdate, this));

    RCLCPP_INFO(
      ros_node_->get_logger(),
      "gazebo_bbox_plugin: publishing bounding boxes on '%s' at %.1f Hz "
      "(include_static=%s)",
      topic_name.c_str(), update_rate, include_static_ ? "true" : "false");
  }

private:
  void OnUpdate()
  {
    const gazebo::common::Time current_time = world_->SimTime();
    if ((current_time - last_update_time_).Double() < update_period_) {
      return;
    }
    last_update_time_ = current_time;

    vision_msgs::msg::Detection3DArray msg;
    msg.header.stamp = ros_node_->get_clock()->now();
    msg.header.frame_id = frame_id_;

    for (const auto & model : world_->Models()) {
      if (!model) {
        continue;
      }
      if (!include_static_ && model->IsStatic()) {
        continue;
      }

      // World-frame AABB combining every link in the model.
      const ignition::math::AxisAlignedBox box = model->BoundingBox();

      vision_msgs::msg::Detection3D det;
      det.id = model->GetName();

      det.bbox.center.position.x = box.Center().X();
      det.bbox.center.position.y = box.Center().Y();
      det.bbox.center.position.z = box.Center().Z();
      det.bbox.center.orientation.w = 1.0;  // AABB -> no rotation

      det.bbox.size.x = box.XLength();
      det.bbox.size.y = box.YLength();
      det.bbox.size.z = box.ZLength();

      msg.detections.push_back(det);
    }

    pub_->publish(msg);
  }

  gazebo::physics::WorldPtr world_;
  gazebo_ros::Node::SharedPtr ros_node_;
  rclcpp::Publisher<vision_msgs::msg::Detection3DArray>::SharedPtr pub_;
  gazebo::event::ConnectionPtr update_connection_;

  gazebo::common::Time last_update_time_;
  double update_period_{0.1};
  bool include_static_{true};
  std::string frame_id_{"world"};
};

GZ_REGISTER_WORLD_PLUGIN(BoundingBoxPublisher)

}  // namespace gazebo_bbox_plugin