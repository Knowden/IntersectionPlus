#include "pch.h"
#include "CppUnitTest.h"
#include  <unordered_set>
#include "../intersect/Point.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PointTest {
	TEST_CLASS(PointTest) {
public:

	TEST_METHOD(TestRemoveDup) {
		auto* set = new std::unordered_set<Point>();
		Point p1(1, 1);
		Point p2(1, 1);

		set->insert(p1);
		set->insert(p2);

		Assert::AreEqual(1, (int) set->size());
	}

	TEST_METHOD(TestSaveUniq) {
		auto* set = new std::unordered_set<Point>();

		Point p1(1, 1);
		Point p2(1, 2);

		set->insert(p1);
		set->insert(p2);

		Assert::AreEqual(2, (int)set->size());
	}
	};
}
