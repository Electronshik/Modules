#include <iostream>
#include <format>

#include <gtest/gtest.h>

import Setting;
import Utils;

using std::cout, std::endl, std::format;
using std::string;

struct ModulesTest : public testing::Test
{
	void SetUp() {}
	void TearDown() {}
};

TEST_F(ModulesTest, ConstructorBasic)
{
	std::initializer_list<const char*> test_list{"One", "Two", "Three"};
	Setting MySettingTestList(test_list, 8U);

	for (const auto& el : test_list)
		EXPECT_TRUE(MySettingTestList.Contains(el));

	std::string new_added_value{"Four"};
	MySettingTestList.AddValue(new_added_value);
	EXPECT_TRUE(MySettingTestList.Contains(new_added_value));

	EXPECT_FALSE(MySettingTestList.Contains("Some random string"));
	EXPECT_STREQ(MySettingTestList.GetDefaultValue().c_str(), *(test_list.begin()));
	EXPECT_TRUE(MySettingTestList == *(test_list.begin()));

	size_t default_outrange_index = 20000U;
	MySettingTestList.SetDefaultValue(default_outrange_index);
	EXPECT_STREQ(MySettingTestList.GetDefaultValue().c_str(), *(test_list.begin()));

	size_t default_index = 2;
	EXPECT_TRUE(default_index < test_list.size());
	MySettingTestList.SetDefaultValue(default_index);
	EXPECT_STREQ(MySettingTestList.GetDefaultValue().c_str(), *(test_list.begin() + default_index));

	std::string new_default_value{"five"};
	MySettingTestList.AddValue(new_default_value);
	MySettingTestList.SetDefaultValue(new_default_value);
	EXPECT_STREQ(MySettingTestList.GetDefaultValue().c_str(), new_default_value.c_str());
}

TEST_F(ModulesTest, FormatCompare)
{
	std::initializer_list<const char*> test_list{"One", "Two", "Three"};
	Setting MySettingTestList(test_list);

	EXPECT_STREQ(MySettingTestList.GetDefaultValue().c_str(), *(test_list.begin()));
	EXPECT_STREQ(
		std::format("{}", MySettingTestList).c_str(),
		join_with_sep(MySettingTestList.GetAllValues().begin(), MySettingTestList.GetAllValues().end(), MySettingTestList.PrintSeparator).c_str()
	);
	EXPECT_STREQ(
		join_with_sep(MySettingTestList.GetAllValues().begin(), MySettingTestList.GetAllValues().end(), MySettingTestList.PrintSeparator).c_str(),
		join_wrap_with_sep(MySettingTestList.GetAllValues().begin(), MySettingTestList.GetAllValues().end(), MySettingTestList.PrintSeparator, "").c_str()
	);

	std::vector<std::string> test_content{"El1", "El2", "El3"};
	std::string test_outstr{"'El1','El2','El3'"};
	EXPECT_STREQ(
		test_outstr.c_str(),
		join_wrap_with_sep(test_content.begin(), test_content.end(), ",", "'").c_str()
	);
}

auto main (int argc, char** argv) -> int
{
	Setting MySettingList({"One", "Two", "Three"}, 8U);
	MySettingList.AddValue("Four");

	cout << "Elements: " << join_with_sep(MySettingList.GetAllValues().begin(), MySettingList.GetAllValues().end(), ", ") << endl;
	cout << "Elements: " << join_wrap_with_sep(MySettingList.GetAllValues().begin(), MySettingList.GetAllValues().end(), ", ", ",") << endl;

	if (MySettingList.Contains("Four"))
		cout << "Setting Contains El" << endl;
	else
		cout << "Setting Not Contains El" << endl;

	if (MySettingList == "One")
		cout << "Setting Default Is El" << endl;
	else
		cout << "Setting Default Is Not El" << endl;

	cout << "Default is: " << MySettingList.GetDefaultValue() << endl;
	cout << std::format("Settings Formatted: {}", MySettingList) << endl;

	::testing::InitGoogleTest(&argc, argv); 
	return RUN_ALL_TESTS();
}
