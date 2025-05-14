
#include <ftxui/component/screen_interactive.hpp>

#include <iostream>
#include <string>

constexpr auto noErrors = 0;
constexpr auto errorDetected = 1;

int main(int argc, char *argv[])
{
    // Get the home directory from the environment variable "HOME"
    const auto homeEnv = std::getenv("HOME");
    if (homeEnv == nullptr)
    {
        std::cerr << "Error: HOME environment variable not set.\n";
        return errorDetected;
    }
    const auto home = std::string(homeEnv);
    if (home.empty())
    {
        std::cerr << "Error: HOME variable contains empty path.\n";
        return errorDetected;
    }

    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    return noErrors;
}
