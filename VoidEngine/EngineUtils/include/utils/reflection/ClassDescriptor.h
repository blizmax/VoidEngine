#pragma once
//STD Headers
#include <span>
#include <optional>

//Library Headers

//Void Engine Headers
#include "utils/Name.h"
#include "utils/reflection/ClassDescriptorData.h"
#include "utils/reflection/TypeDescriptor.h"


namespace utils {
	//Forward declarations
	struct Property;
	struct Function;

	struct ClassDescriptor : public TypeDescriptor {
		/**
		 * Constructor
		 * @param type This class's type descriptor
		 * @param data The reflection data of this classes properties and functions
		 */
		ClassDescriptor(const TypeDescriptor& type, ClassDescriptorData& data);

		/**
		 * @return A recusively constructed list of all properties of this type, inherited or otherwise
		 */
		[[nodiscard]] 
		std::vector<Property> GetProperties() const;

		/**
		 * @param propertyName The hashed name of the property to retrieve
		 * @return The requested property from this type, or an invalid optional
		 */
		std::optional<Property> GetProperty(const utils::Name& propertyName) const;

		/**
		 * @tparam The type to use when attempting to set the property
		 * @param instance The instance to manipulate through reflection
		 * @param name The name of the property to set
		 * @param value The value to set the specified property to
		 */
		template<class T, class InstanceType>
		void SetPropertyData(InstanceType* instance, const utils::Name& name, const T& value);

		/**
		 * @tparam The type to use when attempting to get the property
		 * @param instance The instance to extract the value from
		 * @param name The name of the property to get
		 * @return The requested property from this type, or an invalid optional
		 */
		template<class T, class InstanceType> [[nodiscard]]
		std::optional<T> GetPropertyData(const InstanceType* instance, const utils::Name& name) const;

		/**
		 * @return Count of all properties for this class descriptor, inherited or otherwise
		 */
		[[nodiscard]] 
		std::size_t GetPropertyCount() const;

	private:
		/** Interface to generically access stack-allocated data arrays generated by VoidReflect */
		ClassDescriptorData& m_Data;
	};

	template<class T, class InstanceType>
	inline void ClassDescriptor::SetPropertyData(InstanceType* instance, const utils::Name& name, const T& value) {
		auto property = GetProperty(name);
		
		if (property.has_value()) {
			property.value().SetValue(instance, value);
		}
		return;
	}

	template<class T, class InstanceType>
	inline std::optional<T> ClassDescriptor::GetPropertyData (
		const InstanceType* instance,
		const utils::Name& name
	) const {
		auto property = GetProperty(name);
		return property.has_value() ? property.value().GetValue<T>(instance) : T{};
	}

	inline std::size_t ClassDescriptor::GetPropertyCount() const {
		std::size_t propertyCount = 0;

		//Recursively walk all parents and accumulate their property count 
		for (auto parentClassDesc : m_Data.GetParents()) {
			propertyCount += parentClassDesc->GetPropertyCount();
		}

		//Return the total 
		return m_Data.GetPropertyCount() + propertyCount;
	}
}