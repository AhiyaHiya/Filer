
#include "last_file_path.hpp"

#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <cstdlib>
#include <filesystem>
#include <iostream>

auto get_last_path() -> std::filesystem::path
{
#if defined(_WIN32)
    const char *homeEnv = std::getenv("USERPROFILE");
    if (!homeEnv)
    {
        const char *drive = std::getenv("HOMEDRIVE");
        const char *path = std::getenv("HOMEPATH");
        if (drive && path)
        {
            std::string home = std::string(drive) + std::string(path);
            if (!home.empty())
            {
                return std::filesystem::path(home) / ".filer_last_path";
            }
        }
        std::cerr << "Error: USERPROFILE or HOMEDRIVE/HOMEPATH environment variables not set.\n";
        return {};
    }
    const auto home = std::string(homeEnv);
#else
    const char *homeEnv = std::getenv("HOME");
    if (!homeEnv)
    {
        std::cerr << "Error: HOME environment variable not set.\n";
        return {};
    }
    const auto home = std::string(homeEnv);
#endif
    if (home.empty())
    {
        std::cerr << "Error: Home directory environment variable contains empty path.\n";
        return {};
    }
    return std::filesystem::path(home);// / ".filer_last_path";
}
