/*==============================================================================
 Name        : krtest.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : Compare SM solutions to C Answer Book

 See README at the root of this project.

 Naming Convention:
 Base_* functions are close to literal C Answer Book solutions. Some
 small tweaks were needed to build cleanly with cpp.  Also, rather than depend
 on the user for scanf type input, we have the programs parse existing files.

 Test_* functions are SM implementations.

 Most of the time, we pass back tuples for comparisons. Sometimes it is just
 easier to write out to log files and diff them.

Subdirectories:
 ./parsefiles (various files to parse for test data, e.g. from linux kernel.)
 ./basefiles  (output of the C Answer Book captured in a log file.
 ./test files (output of SM implementations).
==============================================================================*/
#include "ch01.cpp"
#include <gtest/gtest.h>
#include <string>
#include <fstream>

/* for cases like remove comments that you have to parse log files */
std::string log2str(const char *log)
{
	std::ifstream t(log);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}
TEST(Cmp_1_8, Default)
{
	auto test = Test_1_8();
	auto base = Base_1_8();

	ASSERT_EQ(std::get<0>(test), std::get<0>(base));
	ASSERT_EQ(std::get<1>(test), std::get<1>(base));
	ASSERT_EQ(std::get<2>(test), std::get<2>(base));
}
TEST(Cmp_1_11, Default)
{
	auto test = Test_1_11();
	auto base = Base_1_11();

	ASSERT_EQ(std::get<0>(test), std::get<0>(base));
	ASSERT_EQ(std::get<1>(test), std::get<1>(base));
	ASSERT_EQ(std::get<2>(test), std::get<2>(base));
}
int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
