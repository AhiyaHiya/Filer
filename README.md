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

- C++ compiler (clang++ or MSVC or similar)
- FTXUI framework, for terminal UI (https://github.com/ArthurSonzogni/FTXUI)
- GTK framework (gtk.org)
- Operating system: Linux, macOS, Windows

## Building...

### For all platforms

```sh
git clone https://github.com/AhiyaHiya/Filer.git
cd Filer
python3 -m venv venv_filer
```

### Linux

```sh
source venv_filer/bin/activate
pip install conan
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_CXX_STANDARD=23
cmake --build ./build
```

### Windows

```sh
venv_filer\Scripts\activate.bat
pip install conan
cmake -S . -B build -G "Visual Studio 2022"
cmake --build .\build
```

### macOS
#### Ninja

```sh
cmake -S . -B build -G Ninja -DCMAKE_CXX_FLAGS="-L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib"
cmake --build ./build
```

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

