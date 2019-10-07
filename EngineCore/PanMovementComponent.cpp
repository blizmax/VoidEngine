//STD Headers

//Library Headers

//Void Engine Headers
#include "PanMovementComponent.h"

namespace core {

	core::PanMovementComponent::PanMovementComponent(Entity* parent) 
		: MovementComponent(parent) {


	}

	void PanMovementComponent::Input(const InputEvent& input, float deltaTime) {

	}

	void PanMovementComponent::Input(const InputAxis& axis, float deltaTime) {
		auto speed = MoveSpeed * deltaTime;
		auto up = math::Vector3(0, 1, 0);
		auto right = math::Vector3(1, 0, 0);

		if (axis.AxisName == "UpAxis") {
			Parent->SetPosition(
				Parent->GetPostion() + up * axis.Value * speed
			);
		}
		else if (axis.AxisName == "RightAxis") {
			Parent->SetPosition(
				Parent->GetPostion() + right * axis.Value * speed
			);
		}
	}

}