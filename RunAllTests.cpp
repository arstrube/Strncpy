#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include <cstring>

extern "C" {
#include "strncpy_s_custom.h"
}

extern "C" void ignore_handler_s() {
}

/** Macro to effectively ignore buffer_size in strncpy_s() */

#define _IGNORE ((size_t)-1)

/** Wrapper to "normalize" strncpy() function signature */

int STRNCPY(char* buffer, size_t dummy, const char* string_to_copy, size_t size_to_copy) {
    __pragma(warning(push)) __pragma(warning(disable:4996))
	strncpy(buffer, string_to_copy, size_to_copy);
    __pragma(warning(pop))
    return 0;
}

/** Macro to facilitate comparing results at one glanc e*/

#define TEST_STRNCPY_FUNC(strncpy_func, string_to_copy, size_to_copy, string_result, error_code)\
{ \
	int result = strncpy_func(buffer, _IGNORE, string_to_copy, size_to_copy); \
	STRCMP_EQUAL(string_result, buffer); \
	LONGS_EQUAL(error_code, result); \
}

TEST_GROUP(alltests) {

	char buffer[6];
	char safe_space[6];
	char safe_eos[1];

	void setup() {
		memset(buffer, 'x', 6);
		memset(safe_space, 'x', 6);
		*safe_eos = 0;
	}
};

TEST(alltests, how_does_it_handle_NULL_source) {
//	TEST_STRNCPY_FUNC(STRNCPY,        NULL,         5, "xxxxxxxxxxxx", 0      ); // crash!
//	TEST_STRNCPY_FUNC(strncpy_libc,   NULL,         5, "xxxxxxxxxxxx", 0      ); // crash!
//	TEST_STRNCPY_FUNC(strncpy_s     , NULL,         5, "xxxxxxxxxxxx", 0      ); // assertion error
	TEST_STRNCPY_FUNC(strncpy_s_wine, NULL,         5, "xxxxxxxxxxxx", EINVAL ); // error
	TEST_STRNCPY_FUNC(strncpy_s_safe, NULL,         5, "xxxxxxxxxxxx", ESLEMAX);
// 	TEST_STRNCPY_FUNC(strncpy_s_v8,   NULL,         5, "xxxxxxxxxxxx", 0      ); // assertion error
}

TEST(alltests, does_it_zero_terminate) {
	TEST_STRNCPY_FUNC(STRNCPY,        "womanizer",  5, "womanxxxxxxx", 0      );
	TEST_STRNCPY_FUNC(strncpy_libc,   "womanizer",  5, "womanxxxxxxx", 0      );
	TEST_STRNCPY_FUNC(strncpy_s,      "womanizer",  5, "woman",        0      ); // safer
	TEST_STRNCPY_FUNC(strncpy_s_wine, "womanizer",  5, "woman",        0      ); // safer
	TEST_STRNCPY_FUNC(strncpy_s_safe, "womanizer",  5, "woman",        ESLEMAX); // safer
	TEST_STRNCPY_FUNC(strncpy_s_v8,   "womanizer",  5, "woman",        0      ); // safer
}

TEST(alltests, does_it_overwrite_buffer_boundary) {
	TEST_STRNCPY_FUNC(STRNCPY,        "womanizer",  9, "womanizerxxx", 0      );
	TEST_STRNCPY_FUNC(strncpy_libc,   "womanizer",  9, "womanizerxxx", 0      );
	TEST_STRNCPY_FUNC(strncpy_s,      "womanizer",  9, "womanizer",    0      ); // safer
	TEST_STRNCPY_FUNC(strncpy_s_wine, "womanizer",  9, "womanizer",    0      ); // safer
	TEST_STRNCPY_FUNC(strncpy_s_safe, "womanizer",  9, "womanizer",    ESLEMAX); // safer
	TEST_STRNCPY_FUNC(strncpy_s_v8,   "womanizer",  9, "womanizer",    0      ); // safer
}

TEST(alltests, will_it_zeroterminate_if_size_is_big_enough) {
	TEST_STRNCPY_FUNC(STRNCPY,        "womanizer", 10, "womanizer",    0      );
	TEST_STRNCPY_FUNC(strncpy_libc,   "womanizer", 10, "womanizer",    0      );
	TEST_STRNCPY_FUNC(strncpy_s,      "womanizer", 10, "womanizer",    0      );
	TEST_STRNCPY_FUNC(strncpy_s_wine, "womanizer", 10, "womanizer",    0      );
	TEST_STRNCPY_FUNC(strncpy_s_safe, "womanizer", 10, "womanizer",    ESLEMAX);
	TEST_STRNCPY_FUNC(strncpy_s_v8,   "womanizer", 10, "womanizer",    0      );
}

TEST(alltests, will_it_behave_properly_if_length_of_string_is_smaller_than_size) {
	TEST_STRNCPY_FUNC(STRNCPY,        "woman",      6, "woman",        0      );
	TEST_STRNCPY_FUNC(strncpy_libc,   "woman",      6, "woman",        0      );
	TEST_STRNCPY_FUNC(strncpy_s,      "woman",      6, "woman",        0      );
	TEST_STRNCPY_FUNC(strncpy_s_wine, "woman",      6, "woman",        0      );
	TEST_STRNCPY_FUNC(strncpy_s_safe, "woman",      6, "woman",        ESLEMAX);
	TEST_STRNCPY_FUNC(strncpy_s_v8,   "woman",      6, "woman",        0      );
}

TEST(alltests, strncpy_does_nothing_if_size_is_zero) {
	TEST_STRNCPY_FUNC(STRNCPY,        "woman",      0, "xxxxxxxxxxxx", 0);
	TEST_STRNCPY_FUNC(strncpy_libc,   "woman",      0, "xxxxxxxxxxxx", 0);
	TEST_STRNCPY_FUNC(strncpy_s,      "woman",      0, "",             0); // safer
	TEST_STRNCPY_FUNC(strncpy_s_wine, "woman",      0, "",             0); // safer
	TEST_STRNCPY_FUNC(strncpy_s_safe, "woman",      0, "",             ESLEMAX); // safer
	TEST_STRNCPY_FUNC(strncpy_s_v8,   "woman",      0, "",             0);
}

TEST(alltests, strncpy_copies_empty_string_if_string_is_empty) {
	TEST_STRNCPY_FUNC(STRNCPY,        "",      1,     "",             0);
	TEST_STRNCPY_FUNC(strncpy_libc,   "",      1,     "",             0);
	TEST_STRNCPY_FUNC(strncpy_s,      "",      1,     "",             0);
	TEST_STRNCPY_FUNC(strncpy_s_wine, "",      1,     "",             0);
	TEST_STRNCPY_FUNC(strncpy_s_safe, "",      1,     "",             ESLEMAX);
	TEST_STRNCPY_FUNC(strncpy_s_v8,   "",      1,     "",             0);
}


int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}

