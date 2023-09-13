#include <iostream>
#include <format>
#include <optional>

import Setting;
import Utils;

using std::cout, std::endl, std::format;
using std::string;

auto main (int argc, char** argv) -> int
{
	Setting MySettingList({"One", "Two", "Three"}, 8U);
	MySettingList.AddValue("Four");

	cout << "Elements: " << join_with_separator(MySettingList.GetAllValues().begin(), MySettingList.GetAllValues().end(), ", ") << endl;

	if (MySettingList.Contains("Four"))
		cout << "Setting Contains El" << endl;
	else
		cout << "Setting Not Contains El" << endl;

	if (MySettingList == "One")
		cout << "Setting Default Is El" << endl;
	else
		cout << "Setting Default Is Not El" << endl;

	cout << "Default is: " << MySettingList.GetDefaultValue() << endl;
}
