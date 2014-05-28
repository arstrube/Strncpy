#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include <cstring>

extern "C" {
#include "strncpy_s_custom.h"
void ignore_handler_s() {}
}


/** Macro to effectively ignore buffer_size in strncpy_s() */

#define _IGNORE ((size_t)-1)

/** Macros to "normalize" strncpy() function signature */

#define STRNCPY(buffer, dummy, string_to_copy, size_to_copy) \
{ \
    __pragma(warning(push)) __pragma(warning(disable:4996)) \
	strncpy(buffer, string_to_copy, size_to_copy); \
    __pragma(warning(pop)) \
}

/** Macros to facilitate comparing results at one glance*/

#define TEST_STRNCPY_FUNC(strncpy_func, string_to_copy, size_to_copy, string_result)\
{ \
	strncpy_func(buffer, _IGNORE, string_to_copy, size_to_copy); \
	STRCMP_EQUAL(string_result, buffer); \
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

TEST(alltests, does_it_zero_terminate) {
	TEST_STRNCPY_FUNC(STRNCPY,        "womanizer",  5, "womanxxxxxxx");
	TEST_STRNCPY_FUNC(strncpy_s,      "womanizer",  5, "woman"       ); // safer
	TEST_STRNCPY_FUNC(strncpy_s_wine, "womanizer",  5, "woman"       ); // safer
	TEST_STRNCPY_FUNC(strncpy_s_safe, "womanizer",  5, "woman"       ); // safer
}

TEST(alltests, does_it_overwrite_buffer_boundary) {
	TEST_STRNCPY_FUNC(STRNCPY,        "womanizer",  9, "womanizerxxx");
	TEST_STRNCPY_FUNC(strncpy_s,      "womanizer",  9, "womanizer"   ); // safer
	TEST_STRNCPY_FUNC(strncpy_s_wine, "womanizer",  9, "womanizer"   ); // safer
	TEST_STRNCPY_FUNC(strncpy_s_safe, "womanizer",  9, "womanizer"   ); // safer
}

TEST(alltests, will_it_zeroterminate_if_size_is_big_enough) {
	TEST_STRNCPY_FUNC(STRNCPY,        "womanizer", 10, "womanizer"   );
	TEST_STRNCPY_FUNC(strncpy_s,      "womanizer", 10, "womanizer"   );
	TEST_STRNCPY_FUNC(strncpy_s_wine, "womanizer", 10, "womanizer"   );
	TEST_STRNCPY_FUNC(strncpy_s_safe, "womanizer", 10, "womanizer"   );
}

TEST(alltests, will_it_behave_properly_if_length_of_string_is_smaller_than_size) {
	TEST_STRNCPY_FUNC(STRNCPY,        "woman",      6, "woman"       );
	TEST_STRNCPY_FUNC(strncpy_s,      "woman",      6, "woman"       );
	TEST_STRNCPY_FUNC(strncpy_s_wine, "womanizer", 10, "womanizer"   );
	TEST_STRNCPY_FUNC(strncpy_s_safe, "womanizer", 10, "womanizer"   );
}

TEST(alltests, strncpy_does_nothing_if_size_is_zero) {
	TEST_STRNCPY_FUNC(STRNCPY,        "woman",      0, "xxxxxxxxxxxx");
	TEST_STRNCPY_FUNC(strncpy_s,      "woman",      0, ""            ); // safer
	TEST_STRNCPY_FUNC(strncpy_s_wine, "woman",      0, ""            ); // safer
	TEST_STRNCPY_FUNC(strncpy_s_safe, "woman",      0, ""            ); // safer
}

TEST(alltests, strncpy_copies_empty_string_if_string_is_empty) {
	TEST_STRNCPY_FUNC(STRNCPY,        "",      1,     ""             );
	TEST_STRNCPY_FUNC(strncpy_s,      "",      1,     ""             );
	TEST_STRNCPY_FUNC(strncpy_s_wine, "",      1,     ""             );
	TEST_STRNCPY_FUNC(strncpy_s_safe, "",      1,     ""             );
}


int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}

