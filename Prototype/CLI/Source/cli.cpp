#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

using namespace ftxui;
namespace fs = std::filesystem;

// Structure to hold file/folder info
struct DirEntry
{
    std::string Name;
    bool IsDirectory;
};

// Function to get directory contents
std::vector<DirEntry> GetDirectoryContents(const std::string &path)
{
    auto entries = std::vector<DirEntry>{};
    try
    {
        for (const auto &entry : fs::directory_iterator(path))
        {
            entries.push_back({entry.path().filename().string(),
                               entry.IsDirectory()});
        }
        // Sort entries (directories first, then files)
        std::sort(entries.begin(), entries.end(),
                  [](const DirEntry &a, const DirEntry &b) {
                      if (a.IsDirectory != b.IsDirectory)
                      {
                          return a.IsDirectory > b.IsDirectory;
                      }
                      return a.Name < b.Name;
                  });
    }
    catch (const fs::filesystem_error &e)
    {
        // Handle error gracefully
        entries.push_back({"Error accessing directory", false});
    }
    return entries;
}

int main()
{
    auto screen = ScreenInteractive::TerminalOutput();

    // Get current directory
    const auto currentPath = fs::current_path().string();
    auto pathHistory = std::vector<std::string>{currentPath};
    auto selectedColumn = 0;

    // Main component loop
    auto component = Container::Horizontal({});

    auto updateColumns = [&](int selected)
    {
        component->DetachAllChildren();
        std::vector<Component> columns;

        // Generate columns based on path history
        for (auto i = 0; i <= selected; ++i)
        {
            auto entries = GetDirectoryContents(pathHistory[i]);
            std::vector<Element> column_entries;

            for (const auto &entry : entries)
            {
                std::string display_name = (entry.is_directory ? "📁 " : "📄 ") + entry.Name;
                column_entries.push_back(text(display_name));
            }

            auto menu = Menu(&column_entries, &selectedColumn, MenuOption{.on_enter = [&]() {
                if (selectedColumn >= 0 && selectedColumn < entries.size() &&
                    entries[selectedColumn].is_directory)
                {
                    std::string new_path = fs::path(pathHistory[i]) /
                                           entries[selectedColumn].Name;
                    if (selected < pathHistory.size() - 1)
                    {
                        pathHistory.resize(selected + 1);
                    }
                    pathHistory.push_back(new_path);
                    selected++;
                    updateColumns(selected);
                }
                screen.PostEvent(Event::Custom);
            }});

            columns.push_back(menu);
            component->Add(menu);
        }
    };

    // Initial column setup
    updateColumns(0);

    // Add navigation controls
    auto renderer = Renderer(component, [&] {
        std::vector<Element> columns;
        for (int i = 0; i < component->ChildCount(); ++i)
        {
            columns.push_back(
                vbox({text(" " + pathHistory[i] + " ") | border,
                      component->ChildAt(i)->Render()}) |
                size(WIDTH, LESS_THAN, 40));
        }
        return hbox(columns) | border;
    });

    // Handle keyboard input
    auto controls = CatchEvent(renderer, [&](Event event) {
        if (event == Event::Escape)
        {
            screen.ExitLoopClosure()();
            return true;
        }
        if (event == Event::Backspace && pathHistory.size() > 1)
        {
            pathHistory.pop_back();
            updateColumns(pathHistory.size() - 1);
            return true;
        }
        return false;
    });

    screen.Loop(controls);
    return 0;
}