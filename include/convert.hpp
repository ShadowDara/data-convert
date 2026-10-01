#pragma once

#include <iostream>

#include <more/json.hpp>

#include <string>

namespace converter
{
    inline void generate(
        const nlohmann::json& j,
        std::string& result,
        const std::string& key = "")
    {
        if (j.is_object())
        {
            if (!key.empty())
            {
                result += "namespace "
                    + key
                    + " {\n";
            }
            
            for (auto& [key, value] : j.items())
            {
                generate(value, result, key);
            }

            if (!key.empty())
            {
                result += "}\n";
            }
        }
        else if (j.is_array())
        {
            /*std::size_t length = j.size();

            for (const auto& value : j)
            {
                generate(value, result);
            }*/

            std::cerr << "array is not supported in this implementation\n";
        }
        else if (j.is_string())
        {
            auto value = j.get<std::string>();

            result += "constexpr const char* "
                + key
                + " = \""
                + value
                + "\";\n";
        }
        else if (j.is_number_integer())
        {
            int value = j.get<int>();

            result += "constexpr int "
                + key
                + " = "
                + std::to_string(value)
                + ";\n";
        }
        else if (j.is_boolean())
        {
            bool value = j.get<bool>();

            result += "constexpr bool "
                + key
                + " = "
                + (value ? "true" : "false")
                + ";\n";
        }
    }

    inline std::string json_to_code(const std::string& input)
    {
        nlohmann::json j = nlohmann::json::parse(input);

        std::string result;
		result.reserve(1024); // Reserve some space to avoid multiple allocations

        result += "namespace converted_data {\n";
        generate(j, result);
		result += "}\n";

        return result;
    }
}
