#pragma once

#include <filesystem>

// This will get the last path that the program was open to
auto get_last_path() -> std::filesystem::path;
