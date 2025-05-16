
#include "last_file_path.hpp"

#include <ftxui/component/screen_interactive.hpp>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <iostream>
#include <string>

constexpr auto noErrors = 0;
constexpr auto errorDetected = 1;

int main(int argc, char *argv[])
{
    spdlog::init_thread_pool(8192, 1); // Queue size and thread count
    auto async_logger = spdlog::create_async<spdlog::sinks::stdout_color_sink_mt>("async_console");
    async_logger->info("Async logging enabled!");

    // We are going to use the last know path to open the app to that folder
    const auto lastPath = get_last_path();

    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    return noErrors;
}
