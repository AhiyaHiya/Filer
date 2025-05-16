
find_package(ftxui CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(filer
    "Include/last_file_path.hpp"
    "Source/cli.cpp"
    "Source/last_file_path.cpp"
)

target_include_directories(filer PRIVATE "Include")

target_link_libraries(filer
    PRIVATE
        ftxui::dom
        ftxui::screen
        ftxui::component
        spdlog::spdlog
)
