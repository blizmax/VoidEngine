//STD Headers

//Library Headers

//Void Engine Headers
#include "gameplay_framework/Component.h"

namespace core {

	TYPE_INFO_IMPL(Component)

	Component::Component() {
		Parent = nullptr;
	}

	Component::~Component() {
	}

	void Component::SetParent(Entity* parent) {
		Parent = parent;
	}

	Entity* Component::GetParent() {
		return Parent;
	}

	void Component::Input(const InputAction& input, float deltaTime) {
		;
	}

	void Component::Input(const AxisInputAction& input, float deltaTime) {
		;
	}

	void Component::Tick(float deltaTime) {
		;
	}

	void Component::Draw() {
		;
	}

	void Component::SetPosition(const math::Vector3& position) {
		Position = position;
	}

	math::Vector3 Component::GetPosition() const {
		return Position;
	}

	float Component::GetDistance(Component* other) const {
		return (Position - other->Position).Magnitude();
	}

	float Component::GetDistanceSquared(Component* other) const {
		return (Position - other->Position).Magnitude2();
	}

	void Component::SetRotation(const math::Rotator& rotation) {
		Rotation = rotation;
	}
}
