// Converter

#include <iostream>

#include "convert.hpp"

int main(int argc, char** argv)
{
    std::string text = R"({
        "name": "Max",
        "age": 25,
        "active": true,
        "address": {
            "street": "123 Main St",
            "city": "New York"
        },
        "hobbies": ["reading", "traveling", "swimming"]
    })";

	std::string code = converter::json_to_code(text);
	std::cout << code << std::endl;
}
