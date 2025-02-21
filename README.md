# Filer

Filer is a cross-platform file explorer that works on Linux and Windows. It is written in C++ and provides a user-friendly interface for navigating and managing files and directories.

## Features

- Browse files and directories
- Create new directories
- Copy, move, and delete files and directories
- Search for files by name
- Sort files and directories by various criteria
- View file and directory details

## Prerequisites

- C++ compiler (clang++ or MSVC)
- Qt framework (version X.X.X or higher)
- FTXUI framework, for terminal UI (https://github.com/ArthurSonzogni/FTXUI)
- Operating system: Linux or Windows

## Build for Windows

1. Clone the repository: `git clone https://github.com/AhiyaHiya/Filer.git`
2. Navigate to the project directory: `cd Filer`
3. Build the project: `cmake -S . -B build -G "Visual Studio 2022"`
4. Run the executable: `./Filer` or `Filer.exe`

## Build using Ninja, for macOS
To build the project using Ninja, follow these steps:

1. Clone the repository: `git clone https://github.com/AhiyaHiya/Filer.git`
2. Navigate to the project directory: `cd Filer`
3. Build the project with Ninja:
    ```sh
    cmake -S . -B build -G Ninja -DCMAKE_CXX_FLAGS="-L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib"
    cmake --build build
    ```
4. Run the executable: `./Filer` or `Filer.exe`

## Usage

- Upon launching Filer, you will see the main window with the file explorer interface.
- Use the navigation pane on the left to browse through directories.
- Double-click on a file or directory to open it.
- Right-click on a file or directory to access context menu options.
- Use the toolbar at the top for common actions such as creating new directories or searching for files.

## Contributing

Contributions are welcome! If you would like to contribute to Filer, please follow these steps:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/your-feature-name`
3. Make your changes and commit them: `git commit -m 'Add some feature'`
4. Push to the branch: `git push origin feature/your-feature-name`
5. Submit a pull request.

## License

This project is licensed under the lesser-GPL license.

