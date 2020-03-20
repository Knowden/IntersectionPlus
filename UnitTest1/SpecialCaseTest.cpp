#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <set>
#include <iostream>
#include "../intersect/Circle.h"
#include "../intersect/Point.h"
#include "../intersect/Line.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*
这个测试文件专门用于测试一些特殊的边界情况
因为都是特殊case，所以一定记得写注释解释case的含义

根据TDD的规范，想到特殊测试就写上，不用管能不能通过
把测试作为笔记本，记下所有可能的特殊点
*/
namespace SpecialCaseTest {
	TEST_CLASS(SpecialCaseTest) {
public:

	/*
	两个线段，他们可能只有一个端点相交
	*/
	TEST_METHOD(TestTwoSegmentIntersecInEnd) {
		Line line1("S 0 0 1 1");
		Line line2("S 0 0 1 -1");

		std::vector<Point> result = line1.get_intersection_with(line2);
		Assert::AreEqual(1, (int)result.size());
	}

	/*
	两线段共线，且有一个公共交点（端点）
	*/
	TEST_METHOD(TestTwoSegmentInSameLineHaveOneIntersection) {
		Line line1("S 0 0 1 1");
		Line line2("S 1 1 2 2");

		std::vector<Point> result = line1.get_intersection_with(line2);
		Assert::AreEqual(1, (int)result.size());
	}

	/*
	两线段共线，且无交点
	*/
	TEST_METHOD(TestTwoSegmentInSameLineHaveNoIntersection) {
		Line line1("S 0 0 1 1");
		Line line2("S 2 2 3 3");

		std::vector<Point> result = line1.get_intersection_with(line2);
		Assert::AreEqual(0, (int)result.size());
	}

	/*
	两线段共线，且有多个交点（部分重合），期望抛出异常，这里异常尚未定义，但是必须有异常抛出
	*/
	TEST_METHOD(TestTwoSegmentCoverPart) {
		auto func = [] {
			Line line1("S 0 0 3 3");
			Line line2("S 1 1 5 5");
			line1.get_intersection_with(line2);
		};

		Assert::ExpectException<std::exception>(func);
	}

	/*
	两射线共线，且有一个公共交点（端点）
	*/
	TEST_METHOD(TestTwoRayInSameLineHaveOneIntersection) {
		Line line1("R 1 1 2 2");
		Line line2("R 1 1 -1 -1");

		std::vector<Point> result = line1.get_intersection_with(line2);
		Assert::AreEqual(1, (int)result.size());
	}

	/*
	两射线共线，且无交点
	*/
	TEST_METHOD(TestTwoRayInSameLineHaveNoIntersection) {
		Line line1("R 0 0 1 1");
		Line line2("R -1 -1 -2 -2");

		std::vector<Point> result = line1.get_intersection_with(line2);
		Assert::AreEqual(0, (int)result.size());
	}

	/*
	两射线共线，且有多个交点（部分重合），期望抛出异常，这里异常尚未定义，但是必须有异常抛出
	*/
	TEST_METHOD(TestTwoRayCoverPart) {
		auto func = [] {
			Line line1("S 0 0 3 3");
			Line line2("S 1 1 5 5");
			line1.get_intersection_with(line2);
		};

		Assert::ExpectException<std::exception>(func);
	}
	};
}