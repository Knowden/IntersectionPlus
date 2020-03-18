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

	TEST_METHOD(NormalTest1) {
		Solution s;
		s.add_component("S -1 3 2 -1");
		s.add_component("L -2 2 3 0");
		s.add_component("R -3 0 4 2");

		s.count_result();
		Assert::AreEqual(1, s.count_result());
		int a = 0;
	}

	TEST_METHOD(NormalTest2) {
		Solution s;
		s.add_component("C 3 3 3");
		s.add_component("L -1 4 5 2");
		s.add_component("R 2 5 -1 2");

		Assert::AreEqual(5, s.count_result());
	}

	TEST_METHOD(TestDeleteLine) {
		Solution s;
		s.add_component("L 0 0 1 1");
		s.add_component("L 0 0 1 -1");
		s.add_component("R 0 0 1 -2");

		Assert::AreEqual(3, (int)s.line_list.size());

		int id = s.line_list.at(0).id;
		s.delete_line_component(id);

		Assert::AreEqual(2, (int)s.line_list.size());
	}

	TEST_METHOD(TestDeleteRay) {
		Solution s;
		s.add_component("R 0 0 1 1");
		s.add_component("R 0 0 1 -1");
		s.add_component("L 0 0 1 -2");

		Assert::AreEqual(3, (int)s.line_list.size());

		int id = s.line_list.at(0).id;
		s.delete_line_component(id);

		Assert::AreEqual(2, (int)s.line_list.size());
	}

	TEST_METHOD(TestDeleteSegment) {
		Solution s;
		s.add_component("S 0 0 1 1");
		s.add_component("S 0 0 1 -1");
		s.add_component("L 0 0 1 -2");

		Assert::AreEqual(3, (int)s.line_list.size());

		int id = s.line_list.at(0).id;
		s.delete_line_component(id);

		Assert::AreEqual(2, (int)s.line_list.size());
	}

	TEST_METHOD(TestDeleteCircle) {
		Solution s;
		s.add_component("C 0 0 1");
		s.add_component("C 0 0 2");

		Assert::AreEqual(2, (int)s.circle_list.size());

		int id = s.circle_list.at(0).id;
		s.delete_circle_component(id);

		Assert::AreEqual(1, (int)s.circle_list.size());
	}

	};
}
