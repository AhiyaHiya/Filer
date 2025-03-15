
#include <ftxui/component/screen_interactive.hpp>

#include <iostream>
#include <string>

constexpr auto noErrors = 0;
constexpr auto errorDetected = 1;

int main(int argc, char *argv[])
{
    // Get the home directory from the environment variable "HOME"
    const auto home = std::string(std::getenv("HOME"));
    if (home.empty())
    {
        std::cerr << "Error: HOME environment variable not set." << std::endl;
        return errorDetected;
    }

    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    return noErrors;
}
