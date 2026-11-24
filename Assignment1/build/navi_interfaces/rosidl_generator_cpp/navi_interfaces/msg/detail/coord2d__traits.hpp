// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from navi_interfaces:msg/Coord2d.idl
// generated code does not contain a copyright notice

#ifndef NAVI_INTERFACES__MSG__DETAIL__COORD2D__TRAITS_HPP_
#define NAVI_INTERFACES__MSG__DETAIL__COORD2D__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "navi_interfaces/msg/detail/coord2d__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace navi_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Coord2d & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Coord2d & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Coord2d & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace navi_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use navi_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const navi_interfaces::msg::Coord2d & msg,
  std::ostream & out, size_t indentation = 0)
{
  navi_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use navi_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const navi_interfaces::msg::Coord2d & msg)
{
  return navi_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<navi_interfaces::msg::Coord2d>()
{
  return "navi_interfaces::msg::Coord2d";
}

template<>
inline const char * name<navi_interfaces::msg::Coord2d>()
{
  return "navi_interfaces/msg/Coord2d";
}

template<>
struct has_fixed_size<navi_interfaces::msg::Coord2d>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<navi_interfaces::msg::Coord2d>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<navi_interfaces::msg::Coord2d>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // NAVI_INTERFACES__MSG__DETAIL__COORD2D__TRAITS_HPP_
