// Solution by Manh
#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
// Task 2.1: Here I am including the header
#include "navi_interfaces/msg/coord2d.hpp"
using namespace std::chrono_literals;


/*
Personal Note:
Building a sender: the publisher that puts messages on navi_topic
*/

class NaviPublisher : public rclcpp::Node // Task 2.2: Creating a class NaviPublisher which inherits from the class rclcpp::Node
{
public:
  NaviPublisher() : Node("navi_publisher"), count(0)        // Task 2.3a
  {
    publisher = this->create_publisher<navi_interfaces::msg::Coord2d>(
      "navi_topic", 10);                                    // Task 2.3b
    timer = this->create_wall_timer(
      500ms, std::bind(&NaviPublisher::publish_callback, this));  // Task 2.3c
  }
private: // Here I am defining a private method, which should take care of message publishing
  void publish_callback()
  {
    auto message = navi_interfaces::msg::Coord2d();         // Task 2.4a
    message.x = this->count++;                              // Task 2.4b
    message.y = 0;
    RCLCPP_INFO_STREAM(this->get_logger(),
      "Publishing: '" << message.x << "," << message.y << "'");  // Task 2.4c
    this->publisher->publish(message);                      // Task 2.4d
  }

  // Task 2.5: Here I am declaring timer, publisher and counter

  rclcpp::TimerBase::SharedPtr timer;
  rclcpp::Publisher<navi_interfaces::msg::Coord2d>::SharedPtr publisher;
  size_t count;
};

//  Here I just copied the main function and modified it so that it fits our assignment 1:
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NaviPublisher>());
  rclcpp::shutdown();
  return 0;
}

/*
This is the default function given by the package, so we do not need it
int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;

  printf("hello world navigation_pkg package\n");
  return 0;
}
  */


  
