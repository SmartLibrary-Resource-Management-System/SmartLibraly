#pragma once
#include <string>
#include <vector>

namespace FieldCodec {
std::string escape(const std::string& field);
std::string join(const std::vector<std::string>& fields);
std::vector<std::string> split(const std::string& line);
}  
