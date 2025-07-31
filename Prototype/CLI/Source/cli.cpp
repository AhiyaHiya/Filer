
#include "last_file_path.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

constexpr auto noErrors = 0;
constexpr auto errorDetected = 1;

namespace fs = std::filesystem;

// Helper to get directory entries (files and folders)
std::vector<fs::directory_entry> GetEntries(const fs::path &path)
{
    std::vector<fs::directory_entry> entries;
    try
    {
        for (const auto &entry : fs::directory_iterator(path))
        {
            entries.push_back(entry);
        }
        std::sort(entries.begin(), entries.end(), [](const fs::directory_entry &a, const fs::directory_entry &b) {
            // Folders first, then files, both alphabetically
            if (a.is_directory() != b.is_directory())
                return a.is_directory() > b.is_directory();
            return a.path().filename().string() < b.path().filename().string();
        });
    } catch (...)
    {
        // Ignore errors (e.g., permission denied)
    }
    return entries;
}

int main(int argc, char *argv[])
{
    spdlog::init_thread_pool(8192, 1); // Queue size and thread count
    auto async_logger = spdlog::create_async<spdlog::sinks::stdout_color_sink_mt>("async_console");
    async_logger->info("Async logging enabled!");

    const auto lastPath = get_last_path();
    if (lastPath.empty() || !fs::exists(lastPath) || !fs::is_directory(lastPath))
    {
        std::cerr << "Invalid or missing last path: " << lastPath << std::endl;
        return errorDetected;
    }

    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    // Miller columns state
    auto column_paths = std::vector<fs::path>{lastPath};
    auto selected_indices = std::vector<int>{0};

    auto renderer = ftxui::Renderer([&] {
        auto columns = std::vector<ftxui::Element>();

        // For each column, build a vertical list of entries
        for (size_t col = 0; col < column_paths.size(); ++col)
        {
            auto entries = GetEntries(column_paths[col]);
            auto items = std::vector<ftxui::Element>();
            for (size_t i = 0; i < entries.size(); ++i)
            {
                auto name = entries[i].path().filename().string();
                bool is_dir = entries[i].is_directory();
                auto elem = ftxui::text(name) | (is_dir ? ftxui::bold : ftxui::nothing);
                if (i == selected_indices[col])
                    elem = elem | ftxui::inverted;
                items.push_back(elem);
            }
            if (items.empty())
                items.push_back(ftxui::text("(empty)") | ftxui::dim);
            columns.push_back(ftxui::vbox(std::move(items)) | ftxui::border);
        }

        // Pad to always show at least 3 columns
        while (columns.size() < 3)
            columns.push_back(ftxui::vbox({ftxui::text("")}) | ftxui::border);

        return ftxui::hbox(std::move(columns)) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 60);
    });

    // Keyboard navigation
    auto component = ftxui::CatchEvent(renderer, [&](const ftxui::Event &event) {
        size_t col = column_paths.size() - 1;
        auto entries = GetEntries(column_paths[col]);
        if (event == ftxui::Event::ArrowDown)
        {
            if (!entries.empty())
                selected_indices[col] = (selected_indices[col] + 1) % entries.size();
            return true;
        }
        if (event == ftxui::Event::ArrowUp)
        {
            if (!entries.empty())
                selected_indices[col] = (selected_indices[col] + entries.size() - 1) % entries.size();
            return true;
        }
        if (event == ftxui::Event::ArrowRight || event == ftxui::Event::Return)
        {
            if (!entries.empty() && entries[selected_indices[col]].is_directory())
            {
                column_paths.push_back(entries[selected_indices[col]].path());
                selected_indices.push_back(0);
            }
            return true;
        }
        if (event == ftxui::Event::ArrowLeft)
        {
            if (column_paths.size() > 1)
            {
                column_paths.pop_back();
                selected_indices.pop_back();
            }
            return true;
        }
        if (event == ftxui::Event::Character('q'))
        {
            screen.Exit();
            return true;
        }
        return false;
    });

    screen.Loop(component);
    return noErrors;
}
