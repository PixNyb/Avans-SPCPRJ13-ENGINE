//
// Created by Robin on 30-10-2023.
//

#include "GameObject.hpp"
#include "Component.hpp"

GameObject::GameObject()
        : name(""), active(true), tag(0), layer(0) {
    // Constructor default initialization
}

GameObject::GameObject(const std::string& name)
        : name(name), active(true), tag(0), layer(0) {
    // Constructor with name initialization
}

void GameObject::AddComponent(Component* component) {
    contents.push_back(component);

}

bool GameObject::IsActiveInWorld() const {

    return active;
}

bool GameObject::IsActiveSelf() const {
    return active;
}


