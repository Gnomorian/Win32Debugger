#include "conversion.h"
#include <memory>

std::string wchar_to_char(const std::wstring& from)
{
	std::string buffer;
	buffer.reserve(from.length());

	wchar_t* in{ const_cast<wchar_t*>(from.data()) };
	auto out{ std::make_unique<char[]>(MB_CUR_MAX) };
	std::mbstate_t state{};
	for (auto& wc : from)
	{
		const auto result{ std::wcrtomb(out.get(), wc, &state) };
		buffer.append(out.get(), result);
	}

	return buffer;
}

std::wstring char_to_wchar(const std::string& from)
{
	std::wstring buffer;
	buffer.reserve(from.length());
	
	char* in{ const_cast<char*>(from.data()) };
	wchar_t out{0};
	size_t maxLen{from.length()};
	size_t result{};
	size_t& numChars{ result };
	std::mbstate_t state{};
	do
	{
		if (out != 0)
		{
			buffer += out;
			in += numChars;
			maxLen -= numChars;
		}
		result = std::mbrtowc(&out, in, maxLen, &state);
	} 
	while (result > 0);
	return buffer;
}
