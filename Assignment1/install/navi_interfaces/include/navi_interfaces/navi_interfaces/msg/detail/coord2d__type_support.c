// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from navi_interfaces:msg/Coord2d.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "navi_interfaces/msg/detail/coord2d__rosidl_typesupport_introspection_c.h"
#include "navi_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "navi_interfaces/msg/detail/coord2d__functions.h"
#include "navi_interfaces/msg/detail/coord2d__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  navi_interfaces__msg__Coord2d__init(message_memory);
}

void navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_fini_function(void * message_memory)
{
  navi_interfaces__msg__Coord2d__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_message_member_array[2] = {
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(navi_interfaces__msg__Coord2d, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(navi_interfaces__msg__Coord2d, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_message_members = {
  "navi_interfaces__msg",  // message namespace
  "Coord2d",  // message name
  2,  // number of fields
  sizeof(navi_interfaces__msg__Coord2d),
  navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_message_member_array,  // message members
  navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_init_function,  // function to initialize message memory (memory has to be allocated)
  navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_message_type_support_handle = {
  0,
  &navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_navi_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, navi_interfaces, msg, Coord2d)() {
  if (!navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_message_type_support_handle.typesupport_identifier) {
    navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &navi_interfaces__msg__Coord2d__rosidl_typesupport_introspection_c__Coord2d_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
