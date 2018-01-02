#pragma once
#include <vector>
#include <string>
#include <functional>

class Command {
public:
	Command(const std::string& _identifier, std::function<bool(const std::vector<std::string>&)> _execute) :
        identifier(_identifier), execute(_execute) {};

    std::string identifier;
	std::function<bool(const std::vector<std::string>&)> execute;
};
