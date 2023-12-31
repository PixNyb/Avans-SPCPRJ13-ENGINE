/**
 * @file audio_facade.cpp
 * @author "Melvin van Bree"
 * @brief A facade for the audio library.
 * @version 0.1
 * @date 22/11/2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "audio_facade.hpp"
#include "sfml_sound.hpp"

std::unique_ptr<ISound> AudioFacade::CreateAudioInstance(const std::string &filePath)
{
    return std::make_unique<SFMLSound>(filePath);
}
