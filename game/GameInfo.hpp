//
// Created by robcholz on 3/11/23.
//

#ifndef RUNCRAFT_GAMEINFO_HPP
#define RUNCRAFT_GAMEINFO_HPP

#pragma once

#include "Render/Render.hpp"
#include "util/GameLogger.hpp"
#include "Log.h"
#include "Initializers/RollingFileInitializer.h"
#include "Appenders/ColorConsoleAppender.h"

namespace game_data {
	enum Biome : unsigned short {
		SNOWY_PLAINS,
		PLAINS,
		FOREST,
		DESERT,
		BIRCH_FOREST
	};

	typedef unsigned short SoundLevel;
}

struct GameGlobalData {
	game_data::Biome biome;
	game_data::SoundLevel soundLevel;
	game_data::SoundLevel playerSoundLevel;
};

struct InputState {
	sf::Vector2i mousePosition;
	bool isPressed{};
};

class GameInfo {
private:
	Render *renderInstance{};
	InputState inputState;
	GameGlobalData gameGlobalData;
public:
	GameInfo() = default;

	GameInfo &setRenderer(Render *renderer) {
		renderInstance = renderer;

		PLOG_DEBUG << "Successfully set the renderer";
		return *this;
	}

	void listen(sf::Vector2i mousePosition, bool isPressed) {
		this->inputState.isPressed = isPressed;
		this->inputState.mousePosition = mousePosition;
	}

	InputState *getInputState() { return &inputState; }

	GameGlobalData *getGameGlobalData() { return &gameGlobalData; }

	[[nodiscard]] unsigned int getScreenWidth() const { return renderInstance->getScreenWidth(); }

	[[nodiscard]] unsigned int getScreenHeight() const { return renderInstance->getScreenHeight(); }

	Render *getRender() { return renderInstance; }
};

GameInfo GameInfo;

#endif //RUNCRAFT_GAMEINFO_HPP
