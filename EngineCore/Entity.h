#pragma once
//STD Headers
#include <string>

//Library headers

//Void Engine Headers
#include "Name.h"
#include "Vector.h"
#include "Rotator.h"
#include "InputEvent.h"
#include "InputAxis.h"

namespace EngineCore {
	//Forward class declarations
	class Component;

	/**
	 * @class Entity 
	 * @brief The Entity class provides the basic definition of what it takes to partake in the simulation
	 */
	class Entity {
	public:
		/**
		 * Constructor
		 * @param name The entity's name
		 */
		Entity(const EngineUtils::Name& name);

		/**
		 * Constructor
		 * @param name The entity's name
		 */
		Entity(const std::string& name);

		/**
		 * Destructor
		 */
		virtual ~Entity();

		/**
		 * Function to allow this component to process input events
		 * @param input Input fromt the keyboard to process
		 */
		virtual void Input(const InputEvent& input, float deltaTime);

		/**
		 * Function to allow this component to process input axis data
		 * @param input Input fromt the keyboard to process
		 */
		virtual void Input(const InputAxis& input, float deltaTime);

		/**
		 * Pure virtual function that defines what the entity does once a level begins.
		 * @note This function largely acts like an initialization function
		 */
		virtual void BeginPlay() = 0;

		/**
		 * Pure virtual function that defines how an entity processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 * @note This function should be called by the derived class tick function
		 */
		virtual void Tick(float deltaTime);

		/**
		 * Defines entity death behaviors
		 */
		virtual void Terminate() = 0;

		/**
		 * Command for the renderer to draw the entity
		 */
		virtual void Draw() const;
		
		/**
		 * Function to request position of this entity
		 * @return The entity's position
		 */
		EngineMath::Vector3 GetPostion();

		/**
		 * Setter for object's position
		 */
		void SetPosition(const EngineMath::Vector3& newPosition);

		/**
		 * Function to request position of this entity
		 * @return The entity's position
		 */
		EngineMath::Rotator GetRotation();

		/**
		 * Setter for object's position
		 */
		void SetRotation(const EngineMath::Rotator& newRotation);

		/**
		 * Gives ownership of a component to this entity
		 * @param component The component to add
		 */
		void AddComponent(Component* component);
	
	protected:
		/** The entity's position in 3D space */
		EngineMath::Vector3 Position;

		/** The entity's rotation in 3D space */
		EngineMath::Rotator Rotation;
		
		/** The entity's velocity */
		float Velocity;

		/** Entity's name */
		EngineUtils::Name ID;

		/** All of the components for this entity */
		std::vector<Component*> Components;
	};
}