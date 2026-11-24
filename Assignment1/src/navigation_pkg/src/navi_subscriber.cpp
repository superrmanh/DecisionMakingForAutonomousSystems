#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "navi_interfaces/msg/coord2d.hpp"

// Task 3: create a subscriber node which subscribes to navi_topic.
// I basically copied this from the Humble tutorial referenced in the readme and changed a few things to match our specific assignment. 

using std::placeholders::_1;

class NaviSubscriber : public rclcpp::Node
{
  public:
    NaviSubscriber()
    : Node("navi_subscriber")
    {
      subscription_ = this->create_subscription<navi_interfaces::msg::Coord2d>(
      "navi_topic", 10, std::bind(&NaviSubscriber::topic_callback, this, _1));
    }

private:
  void topic_callback(const navi_interfaces::msg::Coord2d & message) const
  {
    RCLCPP_INFO_STREAM(this->get_logger(),
      "Subscriber reads: '" << message.x << "," << message.y << "'");
  }
  rclcpp::Subscription<navi_interfaces::msg::Coord2d>::SharedPtr subscription_;};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NaviSubscriber>());
  rclcpp::shutdown();
  return 0;
}