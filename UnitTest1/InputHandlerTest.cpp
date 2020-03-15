#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <set>
#include <iostream>
#include "../intersect/Circle.h"
#include "../intersect/Point.h"
#include "../intersect/Line.h"
#include "../intersect/Solution.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace InputHandlerTest {
	TEST_CLASS(InputHandlerTest) {
public:
	/*
	��׼�������
	*/
	TEST_METHOD(AccpectInputTest1) {
		Solution s;
		s.add_component("L 0 0 1 1");
		s.add_component("S 0 1 1 2");
		s.add_component("R 0 2 1 3");
		s.add_component("C 0 0 1");
	}

	/*
	���пɽ��ܵĿո�����
	*/
	TEST_METHOD(AccpectInputTest2) {
		Solution s;
		s.add_component("L   0 0 1 1");
		s.add_component("  S 0 1 1 2");
		s.add_component("R  0  2 1  3 ");
		s.add_component("C  0	 0  1");
	}

	/*
	�Ƿ��ַ����루Сд��ĸ��������ţ�
	*/
	TEST_METHOD(IllegalCharacterInput1) {
		auto func = [] {
			Solution s;
			s.add_component("l 0 0 1 1");
		};

		Assert::ExpectException<std::exception>(func);
	}

	TEST_METHOD(IllegalCharacterInput2) {
		auto func = [] {
			Solution s;
			s.add_component("l - 0 0 1 1");
		};

		Assert::ExpectException<std::exception>(func);
	}

	TEST_METHOD(IllegalCharacterInput3) {
		auto func = [] {
			Solution s;
			s.add_component("l 0 0 1 1$");
		};

		Assert::ExpectException<std::exception>(func);
	}

	TEST_METHOD(IllegalCharacterInput4) {
		auto func = [] {
			Solution s;
			s.add_component("^l 0 0 1 1");
		};

		Assert::ExpectException<std::exception>(func);
	}

	TEST_METHOD(IllegalCharacterInput5) {
		auto func = [] {
			Solution s;
			s.add_component("L 00 1 1 1");
		};

		Assert::ExpectException<std::exception>(func);
	}

	/*
	Բ�뾶�쳣
	*/
	TEST_METHOD(IllegalCircleRedix1) {
		auto func = [] {
			Solution s;
			s.add_component("C 0 0 0");
		};

		Assert::ExpectException<std::exception>(func);
	}

	TEST_METHOD(IllegalCircleRedix2) {
		auto func = [] {
			Solution s;
			s.add_component("C 0 0 -1");
		};

		Assert::ExpectException<std::exception>(func);
	}

	/*
	�������곬��
	*/
	TEST_METHOD(ArgumentOutOfBound1) {
		auto func = [] {
			Solution s;
			s.add_component("C 100001 0 1");
		};

		Assert::ExpectException<std::exception>(func);
	}

	TEST_METHOD(ArgumentOutOfBound2) {
		auto func = [] {
			Solution s;
			s.add_component("C -100001 0 1");
		};

		Assert::ExpectException<std::exception>(func);
	}

	TEST_METHOD(ArgumentOutOfBound3) {
		auto func = [] {
			Solution s;
			s.add_component("C 1 0 100001");
		};

		Assert::ExpectException<std::exception>(func);
	}

	TEST_METHOD(ArgumentOutOfBound4) {
		auto func = [] {
			Solution s;
			s.add_component("C 1 0 -100001");
		};

		Assert::ExpectException<std::exception>(func);
	}

	TEST_METHOD(ArgumentOutOfBound5) {
		auto func = [] {
			Solution s;
			s.add_component("L 200000 0 0 0");
		};

		Assert::ExpectException<std::exception>(func);
	}
	TEST_METHOD(ArgumentOutOfBound6) {
		auto func = [] {
			Solution s;
			s.add_component("R -100001 0 0 0");
		};

		Assert::ExpectException<std::exception>(func);
	}
	TEST_METHOD(ArgumentOutOfBound7) {
		auto func = [] {
			Solution s;
			s.add_component("S 0 0 -100001 0");
		};

		Assert::ExpectException<std::exception>(func);
	}

	/*
	������غ�
	*/
	TEST_METHOD(PointCollision1) {
		auto func = [] {
			Solution s;
			s.add_component("L 0 0 0 0");
		};

		Assert::ExpectException<std::exception>(func);
	}

	TEST_METHOD(PointCollision2) {
		auto func = [] {
			Solution s;
			s.add_component("S 0 0 0 0");
		};

		Assert::ExpectException<std::exception>(func);
	}

	TEST_METHOD(PointCollision3) {
		auto func = [] {
			Solution s;
			s.add_component("R 0 0 0 0");
		};

		Assert::ExpectException<std::exception>(func);
	}
	};
}