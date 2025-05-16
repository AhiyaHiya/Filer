
#include "last_file_path.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <iostream>
#include <string>
#include <vector>

constexpr auto noErrors = 0;
constexpr auto errorDetected = 1;

int main(int argc, char *argv[])
{
    spdlog::init_thread_pool(8192, 1); // Queue size and thread count
    auto async_logger = spdlog::create_async<spdlog::sinks::stdout_color_sink_mt>("async_console");
    async_logger->info("Async logging enabled!");

    // We are going to use the last know path to open the app to that folder
    //const auto lastPath = get_last_path();
    //(void)lastPath;
    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    // Menu options
    const auto entries = std::vector<std::string>{
        "Option 1: Start Game",
        "Option 2: Settings",
        "Option 3: About"};
    auto selected = 0;

    // Create a menu component
    auto menu = ftxui::Menu(&entries, &selected);

    // Button to quit
    auto quit_button = ftxui::Button("Quit", [&] { screen.ExitLoopClosure()(); });

    // Combine components in a vertical container
    auto container = ftxui::Container::Vertical({menu, quit_button});

    // Renderer with a header and layout
    auto renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({ftxui::text("Welcome to FTXUI Demo") | ftxui::bold | ftxui::color(ftxui::Color::Blue),
                            ftxui::separator(),
                            ftxui::text("Select an option:"),
                            menu->Render(),
                            ftxui::separator(),
                            quit_button->Render()}) | ftxui::border;
    });

    // Start the event loop
    screen.Loop(renderer);
    return noErrors;
}
