// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from navi_interfaces:msg/Coord2d.idl
// generated code does not contain a copyright notice

#ifndef NAVI_INTERFACES__MSG__DETAIL__COORD2D__BUILDER_HPP_
#define NAVI_INTERFACES__MSG__DETAIL__COORD2D__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "navi_interfaces/msg/detail/coord2d__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace navi_interfaces
{

namespace msg
{

namespace builder
{

class Init_Coord2d_y
{
public:
  explicit Init_Coord2d_y(::navi_interfaces::msg::Coord2d & msg)
  : msg_(msg)
  {}
  ::navi_interfaces::msg::Coord2d y(::navi_interfaces::msg::Coord2d::_y_type arg)
  {
    msg_.y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navi_interfaces::msg::Coord2d msg_;
};

class Init_Coord2d_x
{
public:
  Init_Coord2d_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Coord2d_y x(::navi_interfaces::msg::Coord2d::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Coord2d_y(msg_);
  }

private:
  ::navi_interfaces::msg::Coord2d msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::navi_interfaces::msg::Coord2d>()
{
  return navi_interfaces::msg::builder::Init_Coord2d_x();
}

}  // namespace navi_interfaces

#endif  // NAVI_INTERFACES__MSG__DETAIL__COORD2D__BUILDER_HPP_
