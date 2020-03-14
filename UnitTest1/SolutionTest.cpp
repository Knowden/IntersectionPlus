#include "pch.h"
#include "CppUnitTest.h"
#include "../intersect/Solution.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SolutionTest {
	TEST_CLASS(SolutionTest) {
public:

	TEST_METHOD(BasicTest) {
		Solution s;
		s.add_component("C 1 0 2");
		s.add_component("C 2 2 1");
		s.add_component("C 3 -2 6");
		s.add_component("L -1 4 4 -1");

		Assert::AreEqual(6, s.count_result());
	}

	TEST_METHOD(TestParrlleLines) {
		Solution s;
		s.add_component("L 0 0 1 1");
		s.add_component("L 0 1 1 2");
		s.add_component("L 0 0 1 -1");
		s.add_component("L 0 10 3 0");

		Assert::AreEqual(5, s.count_result());
	}
	};
}
