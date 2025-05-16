
#include "last_file_path.hpp"

#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <iostream>

auto get_last_path() -> std::filesystem::path
{
    // Get the home directory from the environment variable "HOME"
    const auto homeEnv = std::getenv("HOME");
    if (homeEnv == nullptr)
    {
        std::cerr << "Error: HOME environment variable not set.\n";
        return {};
    }
    const auto home = std::string(homeEnv);
    if (home.empty())
    {
        std::cerr << "Error: HOME variable contains empty path.\n";
        return {};
    }
    return std::filesystem::path();
}
