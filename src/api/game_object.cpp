/**
 * @file game_object.cpp
 * @author Roël Couwenberg (contact@roelc.me)
 * @author Daan Groot (d.groot3@student.avans.nl)
 * @brief This file contains the GameObject class implementation.
 * @version 0.1
 * @date 2023-11-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "game_object.hpp"
#include "component.hpp"
#include <memory>

GameObject::GameObject() : name(""), active(true), tag(0), layer(0), transform()
{
    // Constructor default initialization
}

GameObject::GameObject(const std::string &name)
    : name(name), active(true), tag(0), layer(0), transform()
{
    // Constructor with name initialization
}

GameObject::GameObject(const std::string &name, const Transform &transform)
    : name(name), transform(transform), active(true), tag(0), layer(0)
{
    // Constructor with name and transform initialization
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
    components.push_back(component);
}

template<class T>
std::shared_ptr<T> GameObject::GetComponent() const {
    for (std::shared_ptr<Component> component: components)
    {
        auto componentPtr = std::dynamic_pointer_cast<T>(component);
        if (componentPtr) return componentPtr;
    }

    return std::shared_ptr<T>{};
}

template<class T>
std::vector<std::shared_ptr<T>> GameObject::GetComponents() const {
    std::vector<std::shared_ptr<T>> typeComponents;

    for (std::shared_ptr<Component> component: components)
    {
        auto componentPtr = std::dynamic_pointer_cast<T>(component);
        if (componentPtr) typeComponents.push_back(componentPtr);
    }

    return typeComponents;
}

void GameObject::SetName(const std::string &name) { this->name = name; }

std::string GameObject::GetName() const { return name; }

int GameObject::GetTag() const { return tag; }

void GameObject::SetTag(int tag) { this->tag = tag; }

int GameObject::GetLayer() const { return layer; }

void GameObject::SetLayer(int layer) { this->layer = layer; }

const Transform &GameObject::GetTransform() const { return transform; }

void GameObject::SetTransform(const Transform &transform) { this->transform = transform; }

bool GameObject::IsActive() const { return active; }

void GameObject::SetActive(bool active) { this->active = active; }

bool GameObject::IsActiveInWorld() const { return active; }

bool GameObject::IsActiveSelf() const { return active; }
