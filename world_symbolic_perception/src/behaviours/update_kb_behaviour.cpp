#include "world_symbolic_perception/behaviours/update_kb_behaviour.hpp"
#include <behaviortree_ros2/plugins.hpp>

UpdateKBBehaviour::UpdateKBBehaviour(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
: SyncActionNode(name, conf), node(params.nh)
{
    this->getInput("kb_update_srv_name", this->kb_update_srv_name);

    RCLCPP_INFO(this->node->get_logger(), "Creating a KB update client for server %s", this->kb_update_srv_name.c_str());
    this->kb_update_client = node->create_client<robot_swiss_knife_msgs::srv::UpdateKB>(this->kb_update_srv_name);
    while (!this->kb_update_client->wait_for_service(1s))
    {
        RCLCPP_INFO(this->node->get_logger(), "Service %s not available, waiting...", this->kb_update_srv_name.c_str());
    }
    RCLCPP_INFO(this->node->get_logger(), "Client for service %s created", this->kb_update_srv_name.c_str());
}

PortsList UpdateKBBehaviour::providedPorts()
{
    return { InputPort<std::string>("kb_update_srv_name"),
             InputPort<std::vector<robot_swiss_knife_msgs::msg::Fluent>>("scene_symbols") };
}

NodeStatus UpdateKBBehaviour::tick()
{
    std::vector<robot_swiss_knife_msgs::msg::Fluent> scene_symbols;
    this->getInput("scene_symbols", scene_symbols);

    ////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Call the service that updates the knowledge base with the contents in scene_symbols
    ////////////////////////////////////////////////////////////////////////////////////////////

    // Notes:
    // We send all the fluents in scene_symbols to the knowledge base in one INSERT request and wait for the answer.
    // The behaviour returns FAILURE if the service is not available, does not answer in time, or reports an error.
    // The request is sent with async_send_request and we wait on the future: the tree runs in its own thread and
    // the node is already spun by the executor in tree_executor.cpp, so the response is processed meanwhile
    // (rclcpp::spin_until_future_complete cannot be used here, since the node already belongs to an executor).

    constexpr auto SERVICE_TIMEOUT = 5s;  // max time to wait for the knowledge base to answer

    const rclcpp::Logger logger = this->node->get_logger();

    const bool service_available = this->kb_update_client->service_is_ready();
    if (!service_available)
    {
        RCLCPP_ERROR(logger, "[update_kb] Service %s is not available", this->kb_update_srv_name.c_str());
        return NodeStatus::FAILURE;
    }

    auto request = std::make_shared<robot_swiss_knife_msgs::srv::UpdateKB::Request>();
    request->operation = robot_swiss_knife_msgs::srv::UpdateKB::Request::INSERT;
    request->fluents = scene_symbols;

    // RCLCPP_INFO(logger, "[update_kb] Sending %zu fluents to %s", request->fluents.size(), this->kb_update_srv_name.c_str());
    auto response_future = this->kb_update_client->async_send_request(request);

    const bool response_received = response_future.wait_for(SERVICE_TIMEOUT) == std::future_status::ready;
    if (!response_received)
    {
        RCLCPP_ERROR(logger, "[update_kb] No response from %s after %ld s", this->kb_update_srv_name.c_str(),
                     static_cast<long>(std::chrono::duration_cast<std::chrono::seconds>(SERVICE_TIMEOUT).count()));
        this->kb_update_client->remove_pending_request(response_future);
        return NodeStatus::FAILURE;
    }

    const auto response = response_future.get();
    const bool update_failed = !response->success;
    if (update_failed)
    {
        RCLCPP_ERROR(logger, "[update_kb] The knowledge base reported an error while inserting the fluents");
        return NodeStatus::FAILURE;
    }

    // RCLCPP_INFO(logger, "[update_kb] Knowledge base updated with %zu fluents", request->fluents.size());

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return NodeStatus::SUCCESS;
}

CreateRosNodePlugin(UpdateKBBehaviour, "UpdateKBBehaviour");