
add_executable(filer "Source/cli.cpp")
find_package(ftxui CONFIG REQUIRED)

target_link_libraries(filer
    PRIVATE
        ftxui::dom
        ftxui::screen
        ftxui::component
)
