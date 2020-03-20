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
��������ļ�ר�����ڲ���һЩ����ı߽����
��Ϊ��������case������һ���ǵ�дע�ͽ���case�ĺ���

����TDD�Ĺ淶���뵽������Ծ�д�ϣ����ù��ܲ���ͨ��
�Ѳ�����Ϊ�ʼǱ����������п��ܵ������
*/
namespace SpecialCaseTest {
	TEST_CLASS(SpecialCaseTest) {
public:

	/*
	�����߶Σ����ǿ���ֻ��һ���˵��ཻ
	*/
	TEST_METHOD(TestTwoSegmentIntersecInEnd) {
		Line line1("S 0 0 1 1");
		Line line2("S 0 0 1 -1");

		std::vector<Point> result = line1.get_intersection_with(line2);
		Assert::AreEqual(1, (int)result.size());
	}

	/*
	���߶ι��ߣ�����һ���������㣨�˵㣩
	*/
	TEST_METHOD(TestTwoSegmentInSameLineHaveOneIntersection) {
		Line line1("S 0 0 1 1");
		Line line2("S 1 1 2 2");

		std::vector<Point> result = line1.get_intersection_with(line2);
		Assert::AreEqual(1, (int)result.size());
	}

	/*
	���߶ι��ߣ����޽���
	*/
	TEST_METHOD(TestTwoSegmentInSameLineHaveNoIntersection) {
		Line line1("S 0 0 1 1");
		Line line2("S 2 2 3 3");

		std::vector<Point> result = line1.get_intersection_with(line2);
		Assert::AreEqual(0, (int)result.size());
	}

	/*
	���߶ι��ߣ����ж�����㣨�����غϣ��������׳��쳣�������쳣��δ���壬���Ǳ������쳣�׳�
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
	�����߹��ߣ�����һ���������㣨�˵㣩
	*/
	TEST_METHOD(TestTwoRayInSameLineHaveOneIntersection) {
		Line line1("R 1 1 2 2");
		Line line2("R 1 1 -1 -1");

		std::vector<Point> result = line1.get_intersection_with(line2);
		Assert::AreEqual(1, (int)result.size());
	}

	/*
	�����߹��ߣ����޽���
	*/
	TEST_METHOD(TestTwoRayInSameLineHaveNoIntersection) {
		Line line1("R 0 0 1 1");
		Line line2("R -1 -1 -2 -2");

		std::vector<Point> result = line1.get_intersection_with(line2);
		Assert::AreEqual(0, (int)result.size());
	}

	/*
	�����߹��ߣ����ж�����㣨�����غϣ��������׳��쳣�������쳣��δ���壬���Ǳ������쳣�׳�
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