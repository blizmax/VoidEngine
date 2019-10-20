//STD Headers

//Library Headers

//Void Engine Headers
#include "RunningState.h"

namespace core {
	void RunningState::Enter() {
		utils::Logger::LogDebug("Game Running");
	}

	void RunningState::Update(float deltaTime) {

	}

	void RunningState::Exit() {
		utils::Logger::LogDebug("Game Execution Halting");
	}
}