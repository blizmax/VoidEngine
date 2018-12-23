#pragma once

//STD Headers
#include <chrono>
#include <memory>

//Project-Coati Headers
#include "Level.h"

//Forward Class declarations
class MessageBus;

class World{
private:
	//Private Class Members
	std::shared_ptr<MessageBus> GameMessageBus;

	Level currentLevel = Level(1);

public:
	//CTORS
	World(std::shared_ptr<MessageBus> GameMessageBus);
	~World();

private:
	//Private Class Methods

public:
	//Public Class Methods
	void Update(double deltaSeconds);
};

