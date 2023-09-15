module;

#include <string>
#include <vector>
#include <concepts>
#include <format>

export module Setting;

template <typename T>
concept IntegerType = std::integral<T> && !std::signed_integral<T>;

template <typename T>
concept ConvertsToString = std::constructible_from<std::string, T>;

export template <typename T = std::string, class V = std::vector<T>>
class Setting {

	public:
		T PrintSeparator{", "};

		template <ConvertsToString U>
		Setting(std::initializer_list<U> values, U default_value)
		{
			static_assert(std::constructible_from<T, U>);
			for (auto& el : values)
			{
				_content.emplace_back(el);
			}
			_default_val = T{default_value};
		}

		template <ConvertsToString U>
		Setting(std::initializer_list<U> values, IntegerType auto default_index) : Setting(values,
			[](auto values, auto default_index) {
				return *(values.begin() + (default_index < values.size() ? default_index : 0));
			} (values, default_index)) {}

		template <ConvertsToString U>
		Setting(std::initializer_list<U> values) : Setting(values, 0U) {}

		void AddValue(ConvertsToString auto& value) { _content.emplace_back(value); }
		void SetDefaultValue(IntegerType auto default_index)
		{
			if (default_index < _content.size())
				_default_val = _content.at(default_index);
		}

		void SetDefaultValue(ConvertsToString auto& value)
		{
			for (const auto& el : _content)
			{
				if (value == el)
					_default_val = value;
			}
		}

		auto GetDefaultValue() const -> T const& { return _default_val; }
		auto GetAllValues() const -> V const& { return _content; };

		auto Contains(ConvertsToString auto& value) const -> bool
		{
			for (const auto& el : _content)
			{
				if (value == el)
					return true;
			}
			return false;
		}

		auto operator==(ConvertsToString auto& value) const -> bool
		{
			return value == _default_val ? true : false;
		}

	private:
		T _default_val{};
		V _content{};
};

template <>
struct std::formatter<Setting<>> : std::formatter<string_view>
{
	auto format(const Setting<>& setting, std::format_context& ctx)
	{
		std::string str;
		for (const auto& el : setting.GetAllValues())
		{
			std::format_to(std::back_inserter(str), "{}{}", el, setting.PrintSeparator);
		}
		if (!str.empty())
		{
			std::string separ{setting.PrintSeparator};
			if (str.length() >= separ.length())
				str.resize(str.length() - separ.length());
		}

		return std::formatter<string_view>::format(str, ctx);
	}
};
