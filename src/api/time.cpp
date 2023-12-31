/**
 * @file time.cpp
 * @author Robin Pijnappels
 * @brief This file contains the Time class implementation.
 * @version 0.1
 * @date 2023-11-08
 *
 * Copyright Copyright (c) 2023
 *
 */

#include "time.hpp"
#include "performance_utility.hpp"

uint64_t Time::startTime = 0;
uint64_t Time::prevTime = 0;
uint64_t Time::currentTime = 0;
double Time::deltaTime = 0.0f;
double Time::timeScale = 1.0f;

double Time::GetTotalTime()
{
    return static_cast<float>(currentTime - startTime) /
           static_cast<float>(PerformanceUtility::GetPerformanceFrequency());
}

double Time::GetElapsedTimeSinceFrameStart()
{
    return static_cast<float>(PerformanceUtility::GetPerformanceCounter() - currentTime) /
           static_cast<float>(PerformanceUtility::GetPerformanceFrequency()) * 1000.0f;
}

double Time::GetDeltaTime() { return deltaTime; }

void Time::StartFrame()
{
    prevTime = prevTime == 0 ? PerformanceUtility::GetPerformanceCounter() : currentTime;

    currentTime = PerformanceUtility::GetPerformanceCounter();
    deltaTime = static_cast<double>(currentTime - prevTime) /
                static_cast<double>(PerformanceUtility::GetPerformanceFrequency());
}

double Time::TimeScale() { return timeScale; }

void Time::TimeScale(double newTimeScale) { timeScale = newTimeScale; }
