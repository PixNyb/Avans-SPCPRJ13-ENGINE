/**
 * @file polygon_collider.hpp
 * @author Daan Groot (d.groot3@student.avans.nl)
 * @brief This file contains the PolygonCollider class definition.
 * @version 0.1
 * @date 2023-11-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DEFUNBOBENGINE_POLYGON_COLLIDER_HPP
#define DEFUNBOBENGINE_POLYGON_COLLIDER_HPP

#include "collider.hpp"
#include "point.hpp"
#include "vector"

class PolygonCollider : public Collider
{
  public:
    /**
     * Constructs a PolygonCollider
     */
    PolygonCollider() = default;

    /**
     * @brief Copy constructor for PolygonCollider.
     *
     * Initializes a new PolygonCollider with the values of an existing one.
     * @param other The PolygonCollider to copy values from.
     */
    PolygonCollider(const PolygonCollider &other);

    /**
     * @brief Make a clone of the component.
     * @param parent The parent GameObject.
     * @return The cloned component.
     */
    std::shared_ptr<Component> Clone(std::weak_ptr<GameObject> parent) override;

    /**
     *Sets the vertices on this PolygonCollider
     * @param vertices are Points that make the outline of the PolygonCollider
     */
    void Vertices(const std::vector<Point> &vertices);

    /**
     * Gets the list of points that make the outline of the PolygonCollider
     * @return a vector of Point objects
     */
    std::vector<Point> Vertices() const { return vertices; }

  private:
    /**
     * A list of Point objects that make the outline of the PolygonCollider
     */
    std::vector<Point> vertices;
};

#endif // DEFUNBOBENGINE_POLYGON_COLLIDER_HPP
