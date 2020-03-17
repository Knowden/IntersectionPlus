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
	};
}
