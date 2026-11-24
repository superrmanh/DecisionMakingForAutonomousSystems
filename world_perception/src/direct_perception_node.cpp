#include "world_perception/direct_perception_node.hpp"

DirectPerceptionNode::DirectPerceptionNode(const rclcpp::NodeOptions &node_options)
    : rclcpp::Node("direct_perception_node", node_options)
{
    this->declare_parameter("model_state_topic", "/gazebo/model_states");
    this->get_parameter("model_state_topic", this->model_state_topic);

    this->tf_broadcaster = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

    RCLCPP_INFO(this->get_logger(), "Subscribing to gazebo_msgs/msg/ModelStates on topic %s", this->model_state_topic.c_str());

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Initialise the Gazebo model subscriber. Note that the correct topic name is stored in this->model_state_topic.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Subscribe to the Gazebo model states; every message calls model_state_cb
    this->model_state_sub = this->create_subscription<gazebo_msgs::msg::ModelStates>(this->model_state_topic,
                                                                                     10,
                                                                                     std::bind(&DirectPerceptionNode::model_state_cb, this, _1));
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void DirectPerceptionNode::model_state_cb(const gazebo_msgs::msg::ModelStates &model_state_msg)
{
    unsigned int model_count = model_state_msg.name.size();
    std::vector<geometry_msgs::msg::TransformStamped> model_transforms;
    rclcpp::Time current_time = this->get_clock()->now();

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Set all transforms and add them to model_transforms so that they can be published in the TF tree
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // model_state_msg.name[i] and model_state_msg.pose[i] describe the same model
    for (unsigned int model_index = 0; model_index < model_count; model_index++)
    {
        const std::string &model_name = model_state_msg.name[model_index];

        // Skip the robot and the floor: we only want the objects
        if (model_name == "tiago" || model_name == "ground_plane")
        {
            continue;
        }

        // Transform from the world frame to this object, named <object>_direct
        geometry_msgs::msg::TransformStamped object_transform;
        object_transform.header.stamp = current_time;
        object_transform.header.frame_id = "world";
        object_transform.child_frame_id = model_name + "_direct";

        object_transform.transform.translation.x = model_state_msg.pose[model_index].position.x;
        object_transform.transform.translation.y = model_state_msg.pose[model_index].position.y;
        object_transform.transform.translation.z = model_state_msg.pose[model_index].position.z;
        object_transform.transform.rotation = model_state_msg.pose[model_index].orientation;

        model_transforms.push_back(object_transform);
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    this->tf_broadcaster->sendTransform(model_transforms);
}

void spin(rclcpp::Node::SharedPtr node)
{
    rclcpp::executors::SingleThreadedExecutor exec;
    rclcpp::WallRate loop_rate(20ms);
    while(rclcpp::ok())
    {
        exec.spin_node_some(node);
        loop_rate.sleep();
    }
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options = rclcpp::NodeOptions().allow_undeclared_parameters(true);
    auto direct_perception_node = std::make_shared<DirectPerceptionNode>(options);

    rclcpp::WallRate loop_rate(500ms);
    std::thread spinner(spin, direct_perception_node);

    while (rclcpp::ok())
    {
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}