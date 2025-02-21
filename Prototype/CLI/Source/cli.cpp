#include <iostream>
#include <string>

constexpr auto noErrors = 0;
constexpr auto errorDetected = 1;
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::cout << "Arguments:" << std::endl;
        for (int i = 1; i < argc; ++i)
        {
            std::cout << argv[i] << std::endl;
        }
    }
    else
    {
        std::cout << "No arguments provided." << std::endl;
    }

    // Get the home directory from the environment variable "HOME"
    const auto home = std::getenv("HOME");
    if (home.empty())
    {
        std::cerr << "Error: HOME environment variable not set." << std::endl;
        return errorDetected;
    }
    return noErrors;
}