#ifndef MATH_UTIL
#define MATH_UTIL

#include <string>
#include <vector>

class MathUtil {
public:
	static bool d_equal(long double num1, long double num2) {
		bool result = abs(num1 - num2) < 1e-6;
		return result;
	}
};

#endif // !MATH_UTIL

