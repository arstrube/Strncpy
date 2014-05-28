#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include <cstring>

extern "C" 
{
}

TEST_GROUP(alltests) {

	char buffer[6];
	char safe_space[6];
	char safe_terminator[1];

	void setup() {
		memset(buffer, 'x', 6);
		memset(safe_space, 'x', 6);
		*safe_terminator = 0;
	}
};

#pragma warning(push)
#pragma warning(disable:4996)

TEST(alltests, strncpy_does_not_zero_terminate) {
	strncpy(buffer, "womanizer", 4);
	STRCMP_EQUAL("womaxxxxxxxx", buffer);
}

TEST(alltests, strncpy_overwrites_buffer_boundary) {
	strncpy(buffer, "womanizer", 9);
	STRCMP_EQUAL("womanizerxxx", buffer);
}

TEST(alltests, strncpy_will_terminate_if_size_is_big_enough) {
	strncpy(buffer, "womanizer", 10);
	STRCMP_EQUAL("womanizer", buffer);
}

TEST(alltests, strncpy_behaves_properly_if_sizeof_string_is_smaller_than_size) {
	strncpy(buffer, "woman", 6);
	STRCMP_EQUAL("woman", buffer);
	STRCMP_EQUAL("xxxxxx", safe_space);
}

TEST(alltests, strncpy_does_nothing_if_size_is_zero) {
	strncpy(buffer, "woman", 0);
	STRCMP_EQUAL("xxxxxxxxxxxx", buffer);
}

TEST(alltests, strncpy_copies_empty_string_if_string_is_empty) {
	strncpy(buffer, "", 1);
	STRCMP_EQUAL("", buffer);
	STRCMP_EQUAL("xxxxxx", safe_space);
}

#pragma warning(pop)

#define _ALL ((size_t)-1)

TEST(alltests, strncpy_s_does_zero_terminate) {
	strncpy_s(buffer, _ALL, "womanizer", 4);
	STRCMP_EQUAL("woma", buffer);
}

TEST(alltests, strncpy_s_overwrites_buffer_boundary) {
	strncpy_s(buffer, _ALL, "womanizer", 9);
	STRCMP_EQUAL("womanizer", buffer);
}

TEST(alltests, strncpy_s_will_terminate_if_size_enough) {
	strncpy_s(buffer, _ALL, "womanizer", 10);
	STRCMP_EQUAL("womanizer", buffer);
}

TEST(alltests, strncpy_s_behaves_properly_if_length_of_string_is_smaller_than_size) {
	strncpy_s(buffer, _ALL, "woman", 6);
	STRCMP_EQUAL("woman", buffer);
	STRCMP_EQUAL("xxxxxx", safe_space);
}

TEST(alltests, strncpy_s_truncates_to_empty_string_if_size_is_zero) {
	strncpy_s(buffer, _ALL, "woma", 0);
	STRCMP_EQUAL("", buffer);
}

TEST(alltests, strncpy_s_copies_empty_string_if_string_is_empty) {
	strncpy_s(buffer, _ALL, "", 1);
	STRCMP_EQUAL("", buffer);
	STRCMP_EQUAL("xxxxxx", safe_space);
}

int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}

