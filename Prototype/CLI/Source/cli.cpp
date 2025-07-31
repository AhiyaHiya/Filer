
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
        std::sort(entries.begin(), entries.end(), [](const fs::directory_entry &a, const fs::directory_entry &b)
        {
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
    auto asyncLogger = spdlog::create_async<spdlog::sinks::stdout_color_sink_mt>("async_console");
    asyncLogger->info("Async logging enabled!");

    const auto lastPath = get_last_path();
    if (lastPath.empty() || !fs::exists(lastPath) || !fs::is_directory(lastPath))
    {
        const auto message = "Invalid or missing last path: " + lastPath.string();
        asyncLogger->error(message);
        return errorDetected;
    }

    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    // Menu bar state
    auto menuEntries = std::vector<std::string>{"File"};
    auto submenus = std::vector<std::vector<std::string>>{{"Quit"}};
    auto menuSelected = 0;
    auto submenuSelected = 0;
    auto menuActive = false;

    // Miller columns state
    auto columnPaths = std::vector<fs::path>{lastPath};
    auto selectedIndexes = std::vector<int>{0};

    // Menu component
    auto menu = ftxui::Menu(&menuEntries, &menuSelected);
    auto submenu = ftxui::Menu(&submenus[0], &submenuSelected);

    auto renderer = ftxui::Renderer([&] {
        auto menuBar = ftxui::hbox({
            ftxui::text(" File ") | (menuActive && menuSelected == 0 ? ftxui::inverted : ftxui::nothing)
        }) | ftxui::border;

        ftxui::Element submenuBox;
        if (menuActive && menuSelected == 0) {
            submenuBox = ftxui::vbox({
                ftxui::text(" Quit ") | (submenuSelected == 0 ? ftxui::inverted : ftxui::nothing)
            }) | ftxui::border;
        } else {
            submenuBox = ftxui::text("");
        }

        auto columns = std::vector<ftxui::Element>();

        // For each column, build a vertical list of entries
        for (size_t col = 0; col < columnPaths.size(); ++col)
        {
            auto entries = GetEntries(columnPaths[col]);
            auto items = std::vector<ftxui::Element>();
            for (size_t i = 0; i < entries.size(); ++i)
            {
                const auto name = entries[i].path().filename().string();
                const auto isDir = entries[i].is_directory();
                auto elem = ftxui::text(name) | (isDir ? ftxui::bold : ftxui::nothing);
                if (i == selectedIndexes[col])
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

        auto mainContent = ftxui::hbox(std::move(columns)) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 60);

        if (menuActive && menuSelected == 0)
            return ftxui::vbox({menuBar, submenuBox, mainContent});
        else
            return ftxui::vbox({menuBar, mainContent});
    });

    // Keyboard navigation
    auto component = ftxui::CatchEvent(renderer, [&](const ftxui::Event &event) {
        // Menu bar navigation
        if (event == ftxui::Event::Character('f')) {
            menuActive = !menuActive;
            return true;
        }
        if (menuActive) {
            if (event == ftxui::Event::ArrowDown) {
                submenuSelected = (submenuSelected + 1) % submenus[0].size();
                return true;
            }
            if (event == ftxui::Event::ArrowUp) {
                submenuSelected = (submenuSelected + submenus[0].size() - 1) % submenus[0].size();
                return true;
            }
            if (event == ftxui::Event::Return) {
                if (menuSelected == 0 && submenuSelected == 0) {
                    screen.Exit();
                    return true;
                }
            }
            if (event == ftxui::Event::Escape) {
                menuActive = false;
                return true;
            }
            return false;
        }

        const auto col = columnPaths.size() - 1;
        auto entries = GetEntries(columnPaths[col]);
        if (event == ftxui::Event::ArrowDown)
        {
            if (!entries.empty())
                selectedIndexes[col] = (selectedIndexes[col] + 1) % entries.size();
            return true;
        }
        if (event == ftxui::Event::ArrowUp)
        {
            if (!entries.empty())
                selectedIndexes[col] = (selectedIndexes[col] + entries.size() - 1) % entries.size();
            return true;
        }
        if (event == ftxui::Event::ArrowRight || event == ftxui::Event::Return)
        {
            if (!entries.empty() && entries[selectedIndexes[col]].is_directory())
            {
                columnPaths.push_back(entries[selectedIndexes[col]].path());
                selectedIndexes.push_back(0);
            }
            return true;
        }
        if (event == ftxui::Event::ArrowLeft)
        {
            if (columnPaths.size() > 1)
            {
                columnPaths.pop_back();
                selectedIndexes.pop_back();
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
