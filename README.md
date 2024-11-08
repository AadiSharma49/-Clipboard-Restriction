# Clipboard Restriction Tool for Windows

This Windows application monitors the clipboard for file copy-paste actions. It restricts any attempt to paste files outside a designated "root" folder, displaying a warning message if the operation is unauthorized.

## Features
- Monitors the clipboard for file transfer attempts.
- Restricts copy-pasting files outside a defined "root" folder.
- Displays a warning message when restriction rules are violated.

## Prerequisites
- MinGW Compiler (for g++) to build the project.
- Visual Studio Code or any other text editor.
- Windows operating system (preferably Windows 10/11).
  
## Installation

1. **Install MinGW**:
   - Download MinGW from [MinGW website](https://sourceforge.net/projects/mingw/).
   - During installation, select the `mingw32-gcc-g++` package.

2. **Set Up Environment**:
   - Add MinGW's `bin` directory (e.g., `C:\MinGW\bin`) to your system's PATH environment variable.

3. **Download and Set Up Project**:
   - Clone the repository:
     ```bash
     git clone https://github.com/yourusername/clipboard-restriction-tool.git
     ```
   - Navigate into the project directory:
     ```bash
     cd clipboard-restriction-tool
     ```

## Building the Project

1. Open the project folder in Visual Studio Code or your editor of choice.
2. Ensure the `tasks.json` file is correctly configured for MinGW.
3. Build the project:
   - Press `Ctrl+Shift+B` in Visual Studio Code to execute the build task.

## Running the Application

1. **Run as Administrator**:
   - Locate the compiled `main.exe` file in your project directory.
   - Right-click on `main.exe` and select **Run as Administrator** (administrator privileges may be required for clipboard access).

2. **Test Clipboard Restrictions**:
   - Copy a file from the specified `C:\root` folder.
   - Attempt to paste it outside `C:\root`. If the file is outside the designated folder, a warning message will be displayed.

## Debugging and Logs

For debugging:
- Check console output for clipboard event logs.
- Additional logging statements have been added to monitor file paths and system messages.

## Contributing
Contributions are welcome. Feel free to fork the project and submit pull requests.

## License
This project is licensed under the MIT License.


