/**
 * @file transform.cpp
 * @author Roël Couwenberg (contact@roelc.me)
 * @brief This file contains the Transform struct implementation.
 * @version 0.1
 * @date 2023-11-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "transform.hpp"

Transform::Transform() : position(0, 0), rotation(0), scale(1.0) {}

Transform::Transform(const Point &position, double rotation, double scale)
    : position(position), rotation(rotation), scale(scale)
{
}
Transform Transform::operator+(const Transform &other) const
{
    return {position + other.position, rotation + other.rotation, scale * other.scale};
}
Transform Transform::operator-(const Transform &other) const
{
    return {position - other.position, rotation - other.rotation, scale / other.scale};
}

bool Transform::operator==(const Transform &other) const
{
    return (rotation == other.rotation && scale == other.scale && position == other.position);
}