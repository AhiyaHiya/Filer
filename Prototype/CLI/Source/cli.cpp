#include <iostream>

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::cout << "Arguments:" << std::endl;
        for (int i = 1; i < argc; ++i)
        {
            std::cout << argv[i] << std::endl;
        }
    } else {
        std::cout << "No arguments provided." << std::endl;
    }
    return 0;
}