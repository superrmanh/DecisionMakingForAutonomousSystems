// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from navi_interfaces:msg/Coord2d.idl
// generated code does not contain a copyright notice

#ifndef NAVI_INTERFACES__MSG__DETAIL__COORD2D__FUNCTIONS_H_
#define NAVI_INTERFACES__MSG__DETAIL__COORD2D__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "navi_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "navi_interfaces/msg/detail/coord2d__struct.h"

/// Initialize msg/Coord2d message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * navi_interfaces__msg__Coord2d
 * )) before or use
 * navi_interfaces__msg__Coord2d__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
bool
navi_interfaces__msg__Coord2d__init(navi_interfaces__msg__Coord2d * msg);

/// Finalize msg/Coord2d message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
void
navi_interfaces__msg__Coord2d__fini(navi_interfaces__msg__Coord2d * msg);

/// Create msg/Coord2d message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * navi_interfaces__msg__Coord2d__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
navi_interfaces__msg__Coord2d *
navi_interfaces__msg__Coord2d__create();

/// Destroy msg/Coord2d message.
/**
 * It calls
 * navi_interfaces__msg__Coord2d__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
void
navi_interfaces__msg__Coord2d__destroy(navi_interfaces__msg__Coord2d * msg);

/// Check for msg/Coord2d message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
bool
navi_interfaces__msg__Coord2d__are_equal(const navi_interfaces__msg__Coord2d * lhs, const navi_interfaces__msg__Coord2d * rhs);

/// Copy a msg/Coord2d message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
bool
navi_interfaces__msg__Coord2d__copy(
  const navi_interfaces__msg__Coord2d * input,
  navi_interfaces__msg__Coord2d * output);

/// Initialize array of msg/Coord2d messages.
/**
 * It allocates the memory for the number of elements and calls
 * navi_interfaces__msg__Coord2d__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
bool
navi_interfaces__msg__Coord2d__Sequence__init(navi_interfaces__msg__Coord2d__Sequence * array, size_t size);

/// Finalize array of msg/Coord2d messages.
/**
 * It calls
 * navi_interfaces__msg__Coord2d__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
void
navi_interfaces__msg__Coord2d__Sequence__fini(navi_interfaces__msg__Coord2d__Sequence * array);

/// Create array of msg/Coord2d messages.
/**
 * It allocates the memory for the array and calls
 * navi_interfaces__msg__Coord2d__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
navi_interfaces__msg__Coord2d__Sequence *
navi_interfaces__msg__Coord2d__Sequence__create(size_t size);

/// Destroy array of msg/Coord2d messages.
/**
 * It calls
 * navi_interfaces__msg__Coord2d__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
void
navi_interfaces__msg__Coord2d__Sequence__destroy(navi_interfaces__msg__Coord2d__Sequence * array);

/// Check for msg/Coord2d message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
bool
navi_interfaces__msg__Coord2d__Sequence__are_equal(const navi_interfaces__msg__Coord2d__Sequence * lhs, const navi_interfaces__msg__Coord2d__Sequence * rhs);

/// Copy an array of msg/Coord2d messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_navi_interfaces
bool
navi_interfaces__msg__Coord2d__Sequence__copy(
  const navi_interfaces__msg__Coord2d__Sequence * input,
  navi_interfaces__msg__Coord2d__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // NAVI_INTERFACES__MSG__DETAIL__COORD2D__FUNCTIONS_H_
