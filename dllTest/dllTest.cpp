#include "pch.h"
#include "../intersect/core.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dllTest
{
	TEST_CLASS(dllTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			core c;
			c.add_component("L 0 0 1 1");
			c.add_component("L 0 0 1 -1");
			int count = c.get_all_intersection(true).size();

			Assert::AreEqual(1, count);
		}

		TEST_METHOD(TestDeleteLine) {
			core c;
			c.add_component("L 0 0 1 1");
			c.add_component("L 0 0 1 -1");
			c.add_component("R 0 0 1 -2");

			Assert::AreEqual(3, (int)c.get_all_line().size());

			int id = c.get_all_line().at(0).id;
			c.delete_line_component(id);

			Assert::AreEqual(2, (int)c.get_all_line().size());
		}

		TEST_METHOD(TestDeleteRay) {
			core c;
			c.add_component("R 0 0 1 1");
			c.add_component("R 0 0 1 -1");
			c.add_component("L 0 0 1 -2");

			Assert::AreEqual(3, (int)c.get_all_line().size());

			int id = c.get_all_line().at(0).id;
			c.delete_line_component(id);

			Assert::AreEqual(2, (int)c.get_all_line().size());
		}

		TEST_METHOD(TestDeleteSegment) {
			core c;
			c.add_component("S 0 0 1 1");
			c.add_component("S 0 0 1 -1");
			c.add_component("L 0 0 1 -2");

			Assert::AreEqual(3, (int)c.get_all_line().size());

			int id = c.get_all_line().at(0).id;
			c.delete_line_component(id);

			Assert::AreEqual(2, (int)c.get_all_line().size());
		}

		TEST_METHOD(TestDeleteCircle) {
			core c;
			c.add_component("C 0 0 1");
			c.add_component("C 0 0 2");

			Assert::AreEqual(2, (int)c.get_all_circle().size());

			int id = c.get_all_circle().at(0).id;
			c.delete_circle_component(id);

			Assert::AreEqual(1, (int)c.get_all_circle().size());
		}
	};
}
