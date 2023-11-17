/**
 * @file physicsfacade.cpp
 * @author Daan Groot (d.groot3@student.avans.nl)
 * @brief This file contains the PhysicsFacade class implementation.
 * @version 0.1
 * @date 2023-11-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "physics_facade.hpp"
#include "rigidbody.hpp"
#include "circle_collider.hpp"
#include "box_collider.hpp"
#include "debug_renderer.hpp"
#include "polygon_collider.hpp"

const float TimeStep = 1.0f / 240.0f;
const int VelocityIterations = 12;
const int PositionIterations = 4;
const int TimeIterations = 60;
const double PixelScale = 0.5;
const double GravityScale = 10.0;
bool DEBUG = true;
DebugRenderer debugRenderer;

PhysicsFacade::PhysicsFacade() = default;

void PhysicsFacade::MakeBody(std::shared_ptr<GameObject> gameObject) {
    b2BodyDef bodyDef;
    auto rigidbody = (*gameObject).GetComponent<RigidBody>();
    if (rigidbody->GetBodyType() == BodyType::staticBody)
        bodyDef.type = b2_staticBody;
    if (rigidbody->GetBodyType() == BodyType::dynamicBody)
        bodyDef.type = b2_dynamicBody;
    if (rigidbody->GetBodyType() == BodyType::kinematicBody)
        bodyDef.type = b2_kinematicBody;
    bodyDef.allowSleep = true;
    auto transform = (*gameObject).GetTransform();
    bodyDef.position.Set(static_cast<float>(transform.position.x) * PixelScale,
                         static_cast<float>(transform.position.y) * PixelScale);
    bodyDef.angle = static_cast<float>(transform.rotation);
    auto body = world->CreateBody(&bodyDef);
    bodies.insert(std::pair<std::shared_ptr<GameObject>, b2Body *>(gameObject, body));
}

void PhysicsFacade::PopulateWorld(std::vector<std::shared_ptr<GameObject>> gameObjects) {
    //// PhysicsFacade receives a list of gameobjects that contain a rigidbody
    //// create the world where the bodies will be placed
    b2Vec2 gravity(0.0f, -9.8f);
    world = std::make_unique<b2World>(gravity);

    //// create a b2body for every gameobject
    for (auto &gameObject: gameObjects) {
        MakeBody(gameObject);
    }

    //// add fixtures for every body
    for (auto object_pair = bodies.begin(); object_pair != bodies.end(); ++object_pair) {
        auto game_object = object_pair->first;
        auto body = object_pair->second;

        //// create circles
        for (auto &circleCollider: game_object->GetComponents<CircleCollider>()) {
            b2CircleShape circleShape{};
            circleShape.m_radius = static_cast<float>(circleCollider->Radius() * PixelScale);
            double area = game_object->GetComponent<RigidBody>()->GetBodyType() != BodyType::staticBody ? (
                    (circleCollider->Radius() * circleCollider->Radius()) * 2) : 0.0f;
            SetFixture(body, &circleShape, game_object->GetComponent<RigidBody>(), area);
        }

        //// create boxes
        for (auto &boxCollider: game_object->GetComponents<BoxCollider>()) {
            b2PolygonShape boxShape{};
            boxShape.SetAsBox(static_cast<float>(boxCollider->Width() / 2.0 * PixelScale),
                              static_cast<float>(boxCollider->Height() / 2.0 * PixelScale));
            double area = game_object->GetComponent<RigidBody>()->GetBodyType() != BodyType::staticBody ? (
                    boxCollider->Width() * boxCollider->Height()) : 0.0f;
            SetFixture(body, &boxShape, game_object->GetComponent<RigidBody>(), area);
        }
    }
}

void PhysicsFacade::Step() {
    //// run physics world
    world->Step(TimeStep, VelocityIterations, PositionIterations);

    //// update all gameobjects
    for (auto object_pair = bodies.begin(); object_pair != bodies.end(); ++object_pair) {
        auto gameObject = object_pair->first;
        auto body = object_pair->second;
        auto oldTransform = gameObject->GetTransform();

        //// update all boxcolliders on the gameobject
        for (const auto &boxCollider: gameObject->GetComponents<BoxCollider>()) {
            oldTransform.position.x += (body->GetPosition().x / PixelScale) - gameObject->GetTransform().position.x;
            oldTransform.position.y += (body->GetPosition().y / PixelScale) - gameObject->GetTransform().position.y;
            oldTransform.rotation = (body->GetAngle() * 180 / b2_pi);
            gameObject->SetTransform(oldTransform);
        }

        //// update all circlecolliders on the gameobject
        for (const auto &circleCollider: gameObject->GetComponents<CircleCollider>()) {
            oldTransform.position.x += (body->GetPosition().x / PixelScale) - gameObject->GetTransform().position.x;
            oldTransform.position.y += (body->GetPosition().y / PixelScale) - gameObject->GetTransform().position.y;
            oldTransform.rotation = (body->GetAngle() * 180 / b2_pi);
            gameObject->SetTransform(oldTransform);
        }

        //// update all polygoncolliders on the gameobject
        for (const auto &polygonCollider: gameObject->GetComponents<PolygonCollider>()) {
            for (Point &point : polygonCollider->Vertices()) {
                point.x += (oldTransform.position.x - body->GetPosition().x);
                point.y += (oldTransform.position.y - body->GetPosition().y);
            }
            oldTransform.position.x += (body->GetPosition().x / PixelScale) - gameObject->GetTransform().position.x;
            oldTransform.position.y += (body->GetPosition().y / PixelScale) - gameObject->GetTransform().position.y;
            oldTransform.rotation = (body->GetAngle() * 180 / b2_pi);
            gameObject->SetTransform(oldTransform);
        }
    }
    if (DEBUG) {
        ShowDebug();
    }
}

void PhysicsFacade::SetFixture(b2Body *body, b2Shape *shape, const std::shared_ptr<RigidBody> &rigidBody, double area) {
    b2FixtureDef fixtureDef{};
    fixtureDef.shape = shape;

    if (rigidBody->GetBodyType() != BodyType::staticBody)
        fixtureDef.density = (float) rigidBody->GetMass() / (float) area;
    else
        fixtureDef.density = 0.0f;

    body->CreateFixture(&fixtureDef);
}

void PhysicsFacade::ShowDebug() {
    debugRenderer.Render(bodies);
}

void PhysicsFacade::DestroyBody(const std::shared_ptr<GameObject>& gameObject) {
    auto iterator = bodies.find(gameObject);
    if (iterator != bodies.end())
        world->DestroyBody(bodies.at(gameObject));
}

void PhysicsFacade::AddForce(const std::shared_ptr<GameObject>& gameObject, float vx, float vy) {
    float newVX = vx * 100;
    float newVY = vy * 100;
    auto iterator = bodies.find(gameObject);
    if (iterator != bodies.end()) {
        bodies.at(gameObject)->ApplyForce( b2Vec2(newVX,newVY), bodies.at(gameObject)->GetWorldCenter(), true);
    }
}

void PhysicsFacade::AddRotation(const std::shared_ptr<GameObject>& gameObject, float amount) {
    auto iterator = bodies.find(gameObject);
    if (iterator != bodies.end()) {
        bodies.at(gameObject)->ApplyAngularImpulse(amount, false);
    }
}

void PhysicsFacade::Sleep(const std::shared_ptr<GameObject> &gameObject) {
    auto iterator = bodies.find(gameObject);
    if (iterator != bodies.end()) {
        bodies.at(gameObject)->SetAwake(false);
    }
}

PhysicsFacade::~PhysicsFacade() = default;

