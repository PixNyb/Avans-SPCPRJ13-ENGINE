/**
 * @file engine.cpp
 * @author Melvin van Bree
 * @brief Implementation of the Engine class for the core game engine functionalities.
 * @version 0.1
 * @date 2023-11-10
 *
 * This file contains the implementation of the Engine class, which is central to the game engine's operation.
 * The Engine class manages the game loop, rendering process, and scene management. It also provides
 * utilities for frame timing and FPS calculation. The Engine ensures the cohesive operation of different
 * engine components, including IO and graphics, and manages the game's running state.
 *
 * Copyright Copyright (c) 2023
 *
 */

#include "engine.hpp"
#include "behaviour_script_manager.hpp"
#include "graphics_facade.hpp"
#include "render_manager.hpp"
#include "scene_manager.hpp"
#include "time.hpp"
#include <thread>

Engine* Engine::instancePtr = nullptr;

Engine::Engine() {
    container.registerInstance<SceneManager>(std::make_shared<SceneManager>());
    // TODO: Figure out the scope?
    container.registerInstance<IOFacade>(std::make_shared<GraphicsFacade>());
    container.registerInstance<RenderManager>(std::make_shared<RenderManager>(),InstanceScope::Engine);
    container.registerInstance<BehaviourScriptManager>(std::make_shared<BehaviourScriptManager>(),InstanceScope::Engine);
}

void Engine::Start()
{
    isRunning = true;
    int frameCount = 0;
    double lastFPSUpdateTime = Time::GetTotalTime();
    auto graphicsFacade = Get<IOFacade>();

    if (!graphicsFacade) {
        std::cerr << "GraphicsFacade instance is null" << std::endl;
        return;
    }

    graphicsFacade->Init();

    while (isRunning) {
        double deltaTime = Time::GetDeltaTime();

        // Start of the frame
        Time::StartFrame();

        // Game logic goes here


        // TODO: Remove
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
        }

        Get<SceneManager>()->Update(deltaTime);
        Get<BehaviourScriptManager>()->Update();

        // Render stuff goes here
        graphicsFacade->ClearScreen();
        Get<RenderManager>()->Render();
        graphicsFacade->PresentScreen();

        // End of the frame

        // Calculate FPS
        frameCount++;
        if (Time::GetTotalTime() - lastFPSUpdateTime >= 1.0f) {
            currentFPS = frameCount;
            frameCount = 0;
            lastFPSUpdateTime = Time::GetTotalTime();
        }

        // Frame limiting
        double elapsedMs = Time::GetElapsedTimeSinceFrameStart();
        double targetMs = 1000.0f / FPS_LIMIT;
        if (targetMs > elapsedMs)
        {
            graphicsFacade->Delay(static_cast<unsigned int>(targetMs - elapsedMs));
        }
    }
}

void Engine::Stop() {
    isRunning = false;
}

void Engine::Shutdown() {
    Stop();

    if(auto sceneManager = Get<SceneManager>(); sceneManager != nullptr)
        sceneManager->ClearScene();
}

int Engine::GetFPS() const {
    return currentFPS;
}

void Engine::SetFPSLimit(float fps) {
    FPS_LIMIT = fps;
}

Engine *Engine::GetInstance() {
    if (!instancePtr) {
        instancePtr = new Engine();
    }
    return instancePtr;
}