#include <cstdio>
#include <chrono>
#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "navi_interfaces/msg/coord2d.hpp"

using namespace std::chrono_literals;

class NaviPublisher : public rclcpp::Node
{
public:
  NaviPublisher() : Node("navi_publisher"), count(0)
  {
    publisher = this->create_publisher<navi_interfaces::msg::Coord2d>("navi_topic", 10);
    timer = this->create_wall_timer(500ms, std::bind(&NaviPublisher::publish_callback, this));
  }

private:
  size_t count;
  rclcpp::TimerBase::SharedPtr timer;
  rclcpp::Publisher<navi_interfaces::msg::Coord2d>::SharedPtr publisher;

  void publish_callback(){
    auto message = navi_interfaces::msg::Coord2d();
    message.x = this->count++;
    message.y = 0;
    RCLCPP_INFO_STREAM(this->get_logger(),"Publishing: '" << message.x << "," << message.y << "'");
    this->publisher->publish(message);     
  }
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<NaviPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
