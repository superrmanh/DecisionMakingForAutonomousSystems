// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from navi_interfaces:msg/Coord2d.idl
// generated code does not contain a copyright notice

#ifndef NAVI_INTERFACES__MSG__DETAIL__COORD2D__STRUCT_H_
#define NAVI_INTERFACES__MSG__DETAIL__COORD2D__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Coord2d in the package navi_interfaces.
typedef struct navi_interfaces__msg__Coord2d
{
  float x;
  float y;
} navi_interfaces__msg__Coord2d;

// Struct for a sequence of navi_interfaces__msg__Coord2d.
typedef struct navi_interfaces__msg__Coord2d__Sequence
{
  navi_interfaces__msg__Coord2d * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} navi_interfaces__msg__Coord2d__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // NAVI_INTERFACES__MSG__DETAIL__COORD2D__STRUCT_H_
