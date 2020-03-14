#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <set>
#include <iostream>
#include "../intersect/Circle.h"
#include "../intersect/Point.h"
#include "../intersect/Line.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ImpossiblePointTest {
	TEST_CLASS(ImpossiblePointTest) {
public:
	TEST_METHOD(TestLwithS1) {
		std::string input1 = "L 1 1 2 2";
		std::string input2 = "S -1 0 1 0";
		Line line1(input1);
		Line line2(input2);

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(1, (int)result.size());
	}

	TEST_METHOD(TestLwithS2) {
		std::string input1 = "L 1 1 2 2";
		std::string input2 = "S -2 0 -1 0";
		Line line1(input1);
		Line line2(input2);

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(0, (int)result.size());
	}

	TEST_METHOD(TestSwithS1) {
		std::string input1 = "S 1 1 2 2";
		std::string input2 = "S -2 0 -1 0";
		Line line1(input1);
		Line line2(input2);

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(0, (int)result.size());
	}

	TEST_METHOD(TestSwithS2) {
		std::string input1 = "S 1 1 2 2";
		std::string input2 = "S 0 1 1 1";
		Line line1(input1);
		Line line2(input2);

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(1, (int)result.size());
	}

	TEST_METHOD(TestRwithS1) {
		std::string input1 = "R 1 1 2 2";
		std::string input2 = "S 0 0 0 1";
		Line line1(input1);
		Line line2(input2);

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(0, (int)result.size());
	}

	TEST_METHOD(TestRwithS2) {
		std::string input1 = "R 2 2 1 1";
		std::string input2 = "S 0 0 0 1";
		Line line1(input1);
		Line line2(input2);

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(1, (int)result.size());
	}

	TEST_METHOD(TestLwithR1) {
		std::string input1 = "R 1 1 2 2";
		std::string input2 = "L 0 0 0 1";
		Line line1(input1);
		Line line2(input2);

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(0, (int)result.size());
	}

	TEST_METHOD(TestLwithR2) {
		std::string input1 = "R 2 2 1 1";
		std::string input2 = "L 0 0 0 1";
		Line line1(input1);
		Line line2(input2);

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(1, (int)result.size());
	}

	TEST_METHOD(TestRwithR1) {
		std::string input1 = "R 1 1 2 2";
		std::string input2 = "R 0 0 0 1";
		Line line1(input1);
		Line line2(input2);

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(0, (int)result.size());
	}

	TEST_METHOD(TestRwithR2) {
		std::string input1 = "R 2 2 1 1";
		std::string input2 = "R 0 0 0 1";
		Line line1(input1);
		Line line2(input2);

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(1, (int)result.size());
	}
	};
}