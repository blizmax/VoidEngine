#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "MovementComponent.h"

namespace core {
	
	/**
	 * @class FlyingMovementComponent
	 * @brief The FlyingMovementComponent allows actors (primarily the player actor)
	 *        to respond to player inputs like a flying FPS camera 
	 */
	class FlyingMovementComponent :	public MovementComponent {
	public:
		/**
		 * Constructor
		 */
		FlyingMovementComponent(Entity* parent);

		/**
		 * Function to allow the component to update it's parent's position in accordance with 
		 * the player's input
		 * @param input The player's input
		 */
		void Input(const InputEvent& input, float deltaTime) override;

		/**
		 * Function to allow the component to update it's parent's position in accordance with
		 * the player's input
		 * @param input The player's input
		 */
		void Input(const InputAxis& axis, float deltaTime) override;
	};
}