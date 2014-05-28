#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include <cstring>

extern "C" 
{
}

TEST_GROUP(strncpy) {

	char buf1[5];
	char buf2[5];
	char safeguard;

	void setup() {
		memset(buf1, 'x', 5);
		memset(buf2, 'x', 5);
		safeguard = 0;
	}
};

#pragma warning(push)
#pragma warning(disable:4996)

TEST(strncpy, does_not_zero_terminate) {
	strncpy(buf1, "womanizer", 4);
	STRCMP_EQUAL("womaxxxxxx", buf1);
}

TEST(strncpy, overwrites_buffer_boundary) {
	strncpy(buf1, "womanizer", 9);
	STRCMP_EQUAL("womanizerx", buf1);
}

TEST(strncpy, will_terminate_if_size_enough) {
	strncpy(buf1, "womanizer", 10);
	STRCMP_EQUAL("womanizer", buf1);
}

TEST(strncpy, behaves_itself_if_size_is_alright) {
	strncpy(buf1, "woma", 5);
	STRCMP_EQUAL("woma", buf1);
	STRCMP_EQUAL("xxxxx", buf2);
}

TEST(strncpy, size_is_zero) {
	strncpy(buf1, "woma", 0);
	STRCMP_EQUAL("xxxxxxxxxx", buf1);
	STRCMP_EQUAL("xxxxx", buf2);
}

TEST(strncpy, string_is_empty) {
	strncpy(buf1, "", 1);
	STRCMP_EQUAL("", buf1);
	STRCMP_EQUAL("xxxxx", buf2);
}

#pragma warning(pop)

#define _ALL ((size_t)-1)

TEST_GROUP(strncpy_s) {

	char buf1[5];
	char buf2[5];
	char safeguard;

	void setup() {
		memset(buf1, 'x', 5);
		memset(buf2, 'x', 5);
		safeguard = 0;
	}
};

TEST(strncpy_s, does_not_zero_terminate) {
	strncpy_s(buf1, _ALL, "womanizer", 4);
	STRCMP_EQUAL("womaxxxxxx", buf1);
}

TEST(strncpy_s, overwrites_buffer_boundary) {
	strncpy_s(buf1, _ALL, "womanizer", 9);
	STRCMP_EQUAL("womanizerx", buf1);
}

TEST(strncpy_s, will_terminate_if_size_enough) {
	strncpy_s(buf1, _ALL, "womanizer", 10);
	STRCMP_EQUAL("womanizer", buf1);
}

TEST(strncpy_s, behaves_itself_if_size_is_alright) {
	strncpy_s(buf1, _ALL, "woma", 5);
	STRCMP_EQUAL("woma", buf1);
	STRCMP_EQUAL("xxxxx", buf2);
}

TEST(strncpy_s, size_is_zero) {
	strncpy_s(buf1, _ALL, "woma", 0);
	STRCMP_EQUAL("xxxxxxxxxx", buf1);
	STRCMP_EQUAL("xxxxx", buf2);
}

TEST(strncpy_s, string_is_empty) {
	strncpy_s(buf1, _ALL, "", 1);
	STRCMP_EQUAL("", buf1);
	STRCMP_EQUAL("xxxxx", buf2);
}

int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}

