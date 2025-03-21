#include <format>
#include <string>
#include <sstream>
#include <string_view>
#include <cstdio>

template<typename... Args>
void print(const std::string_view fmt_str, Args&&... args)
{
	auto fmt_args{ std::make_format_args(args...) };
	std::string outstr{ std::vformat(fmt_str, fmt_args) };
	std::fputs(outstr.c_str(), stdout);
}

template<typename... Args>
void print_nl(const std::string_view fmt_str, Args&&... args)
{
	auto fmt_args{ std::make_format_args(args...) };
	std::string outstr{ std::vformat(fmt_str, fmt_args) };
	outstr.append("\n");
	std::fputs(outstr.c_str(), stdout);
}

template<typename T>
std::string join_with_sep(T beg_it, T end_it, std::string separator)
{
	std::ostringstream outstr;

	if(beg_it != end_it)
		outstr << *beg_it++;

	while(beg_it != end_it)
		outstr << separator.c_str() << *beg_it++;

	return outstr.str();
}

template<typename T>
std::string join_wrap_with_sep(T beg_it, T end_it, std::string separator, std::string wrapper)
{
	std::ostringstream outstr;

	if(beg_it != end_it)
		outstr << wrapper << *beg_it++ << wrapper;

	while(beg_it != end_it)
		outstr << separator.c_str() << wrapper << *beg_it++ << wrapper;

	return outstr.str();
}
