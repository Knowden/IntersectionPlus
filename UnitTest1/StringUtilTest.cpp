#include "pch.h"
#include "CppUnitTest.h"
#include "../intersect/StringUtil.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StringUtilTest {
	TEST_CLASS(StringUtilTest) {
public:

	TEST_METHOD(TestRemoveDupSpace) {
		std::string input = "1231 1231     123";
		std::vector<std::string> infos = StringUtil::split(input, " ");

		Assert::IsTrue("1231" == infos.at(0));
		Assert::IsTrue("1231" == infos.at(1));
		Assert::IsTrue("123" == infos.at(2));
	}

	};
}
