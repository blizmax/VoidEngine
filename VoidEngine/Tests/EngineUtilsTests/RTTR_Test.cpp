//STD Headers
#include <cstddef>

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "utils/reflection/TypeInfo.h"

namespace rttr_test {
	CLASS()
		class User {
		public:
			PROPERTY()
			int m_ID;

			PROPERTY()
			double m_Money;

			CTOR()
			User() {
				m_ID = 0;
			}

			FUNCTION()
			bool Modify() {
				m_ID++;
			}

		private:
			int m_PrivateProperty;
	};
}

// Sample reflection data format, to be generated by VoidReflect
namespace utils {
	template<>
	const Class& utils::GetClass<rttr_test::User>() {
		static Class classDescriptor;

		classDescriptor.m_Properties.emplace_back(
			Property { 
				GetType<int>(), 
				"m_ID", 
				offsetof(rttr_test::User, m_ID) 
			}
		);

		classDescriptor.m_Properties.emplace_back(
			Property{
				GetType<double>(),
				"m_ID",
				offsetof(rttr_test::User, m_Money)
			}
		);

		return classDescriptor;
	}
}

using namespace utils;

namespace utils_tests {
	
	TEST(RTTR_Tests, PrimitiveReflectionTest) {
		auto intRefl = GetType<int>();
		ASSERT_EQ(intRefl.m_Name, utils::Name("int"));
		ASSERT_EQ(intRefl.m_Size, sizeof(int));

		auto uintRefl = GetType<unsigned int>();
		ASSERT_EQ(uintRefl.m_Name, utils::Name("unsigned int"));
		ASSERT_EQ(uintRefl.m_Size, sizeof(unsigned int));

		auto doubleRefl = GetType<double>();
		ASSERT_EQ(doubleRefl.m_Name, utils::Name("double"));
		ASSERT_EQ(doubleRefl.m_Size, sizeof(double));
		
		auto boolRefl = GetType<bool>();
		ASSERT_EQ(boolRefl.m_Name, utils::Name("bool"));
		ASSERT_EQ(boolRefl.m_Size, sizeof(bool));
	}

	TEST(RTTR_Tests, ClassPropertyAccessTest) {
		rttr_test::User instance;

		auto userRefl = GetClass<rttr_test::User>();
		ASSERT_EQ(2, userRefl.m_Properties.size());

		instance.m_ID = 0;
		userRefl.SetProperty(&instance, utils::Name("m_ID"), 12345);
		ASSERT_EQ(12345, instance.m_ID);

		instance.m_ID = 123456;

		ASSERT_EQ(123456, userRefl.GetProperty<int>(&instance, utils::Name("m_ID")));
	}

}