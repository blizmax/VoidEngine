#pragma once
//STD Headers
#include <cstddef>
#include <memory>

//Library Headers

//Coati Headers
#include "EngineUtilities.h"
#include "TimeUtils.h"

namespace EngineCore {
	enum class ButtonState : unsigned {
		Released = 0,
		Pressed = 1,
		Held = 2,
		Any = 4
	};

	class GenericInput {

	protected:
		unsigned Button;
		ButtonState State;
		EngineCore::GameTime TimeStamp;

	public:
		GenericInput(unsigned button, ButtonState state, EngineCore::GameTime time);
		~GenericInput() = default;

		virtual bool operator==(const GenericInput& other) const;

	public:

		template<typename T>
		T GetButton() const;
		ButtonState GetButtonState() const;
		EngineCore::GameTime GetTimeStamp() const;

		virtual std::size_t Hash() const;
	};

	template<typename T>
	T GenericInput::GetButton() const {
		return static_cast<T>(Button);
	}


	using GenericInputPtr = std::shared_ptr<GenericInput>;
}