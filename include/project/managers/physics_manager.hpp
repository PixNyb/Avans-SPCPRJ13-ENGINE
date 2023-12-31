/**
 * @file physics_manager.hpp
 * @author Daan Groot (d.groot3@student.avans.nl)
 * @brief This file contains the PhysicsManager class definition.
 * @version 0.1
 * @date 2023-11-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DEFUNBOBENGINE_PHYSICS_MANAGER_HPP
#define DEFUNBOBENGINE_PHYSICS_MANAGER_HPP

#include "physics_facade.hpp"
#include <memory>
#include <vector>

class GameObject;

/**
 * @class PhysicsManager
 * @brief This class is the link between the PhysicsFacade and the engine. The PhysicsManager
 * contains the same functions as described in the PhysicsFacade.
 */
class PhysicsManager
{
  private:
    PhysicsFacade physicsFacade;

  public:
    PhysicsManager() = default;
    ~PhysicsManager() = default;

    /**
     * @brief Creates the world the gameobjects will be simulated in
     * @param gameObjects are the gameobjects that contain a rigicbody or colliders
     */
    void CreateWorld(std::vector<std::shared_ptr<GameObject>> gameObjects);

    /**
     * @brief Destroys the world
     */
    void DestroyWorld() { physicsFacade.DepopulateWorld(); }

    /**
     * @brief Removes the gameobject from the simulated world
     * @param gameObject is the object to be removed
     */
    void RemoveBody(const std::shared_ptr<GameObject> &gameObject);

    /**
     * @brief Creates a body in the world simulation
     * @param gameObject the object for which a body will be created
     */
    void CreateBody(std::shared_ptr<GameObject> &gameObject);

    /**
     * @brief Adds a force to a gameobject (will allways create a force on the center of the body)
     * @param gameObject is the object the force will be added to
     * @param vx horizontal velocity
     * @param vy vertical velocity
     */
    void AddForce(const std::shared_ptr<GameObject> &gameObject, float vx, float vy);

    /**
     * @brief Adds a linear impulse to a gameobject (will allways create a force on the center of
     * the body)
     * @param gameObject is the object the force will be added to
     * @param vx horizontal velocity
     * @param vy vertical velocity
     */
    void AddLinearImpulse(const std::shared_ptr<GameObject> &gameObject, float vx, float vy);

    /**
     * @brief Adds a rotation to a gameobject (will also apply the rotation on the center and is
     * clockwise when amount is positive)
     * @param gameObject is the object the rotation will be added to
     * @param amount the speed at which the object should spin
     */
    void AddRotationalForce(const std::shared_ptr<GameObject> &gameObject, float amount);

    /**
     * @brief Simulates the world for 1 step
     */
    void Step();

    /**
     * @brief Sets the given gameobject to sleep
     * @param gameObject the gameobject that is set asleep
     */
    void Sleep(const std::shared_ptr<GameObject> &gameObject);

    /**
     * @brief Sets the given gameobject to wake up
     * @param gameObject the gameobject that is set awake
     */
    void Wake(const std::shared_ptr<GameObject> &gameObject);

    /**
     * @brief Sets the debug mode
     * @param debug
     */
    void SetDebug(bool debug) { physicsFacade.DEBUG = debug; }

    /**
     * @brief Updates the rotation of the given GameObject
     */
    void UpdateRotation(const std::shared_ptr<GameObject> &gameObject, double rotation);

    /**
     * @brief Updates the position of the given GameObject
     */
    void UpdatePosition(const std::shared_ptr<GameObject> &gameObject, double xPos, double yPos);

    /**
     * @brief Updates the velocity of the GameObject
     * @param gameObject the object
     * @param vX velocity on the x-axis
     * @param vY velocity on the y-axis
     */
    void UpdateVelocity(const std::shared_ptr<GameObject> &gameObject, double vX, double vY);

    /**
     * Gets the velocity of the given gameobject
     * @param gameObject
     * @return Point
     */
    Point GetVelocity(const std::shared_ptr<GameObject> &gameObject);
};

#endif // DEFUNBOBENGINE_PHYSICS_MANAGER_HPP
