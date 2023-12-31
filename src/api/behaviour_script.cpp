/**
 * @file behaviour_script.cpp
 * @author Robin Pijnappels
 * @brief This file contains the BehaviourScript class implementation.
 * @version 0.1
 * @date 2023-11-08
 *
 * Copyright Copyright (c) 2023
 *
 */

#include "behaviour_script.hpp"
#include "component.hpp"

void BehaviourScript::OnStart() { hasStarted = true; }
void BehaviourScript::OnUpdate() {}
void BehaviourScript::OnTriggerEnter2D(Collider &collider) {}
void BehaviourScript::OnTriggerExit2D(Collider &collider) {}
void BehaviourScript::OnTriggerStay2D(Collider &collider) {}
bool BehaviourScript::HasStarted() const { return hasStarted; }
