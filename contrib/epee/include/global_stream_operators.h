#pragma once

std::stringstream& operator<<(std::stringstream& out, const std::wstring& ws)
{
	std::string as = string_encoding::convert_to_ansii(ws);
	out << as;
	return out;
}
