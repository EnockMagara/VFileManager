# VFileManager


## Description
The VFileManager is a simulated file system implemented in C++. It provides a command-line interface for users to interact with a virtual directory structure, allowing them to create, delete, move, and manage files and directories. The VFS also includes features such as a recycle bin for deleted items, file recovery, and persistent storage.

## Features
- **Directory and File Management**: Create, delete, and move files and directories.
- **Navigation**: Change the current working directory and print the current path.
- **Recycle Bin**: Deleted files and directories are moved to a recycle bin, allowing for recovery.
- **Persistent Storage**: Save and load the state of the file system to and from a file.
- **Size Calculation**: Calculate and display the size of files and directories.
- **Search**: Find files and directories by name.
- **Custom Data Structures**: Implementation of custom `Vector` and `Queue` classes.

## Commands
- `help`: Display the list of available commands.
- `pwd`: Print the current working directory.
- `ls`: List the contents of the current directory.
- `mkdir <dir_name>`: Create a new directory.
- `touch <file_name> <file_size>`: Create a new file with the specified name and size.
- `cd <dir_name>`: Change the current directory.
- `rm <name>`: Remove a file or directory.
- `size <name>`: Display the size of a file or directory.
- `showbin`: Show the contents of the recycle bin.
- `emptybin`: Empty the recycle bin.
- `exit`: Exit the program.
- `find <file_name>`: Find a file in the VFS.
- `mv <src> <dest>`: Move a file or directory to a new location.
- `recover`: Recover the last deleted file or directory.
- `clear`: Clear the terminal screen.

## Files
- `main.cpp`: Contains the main function and command-line interface logic.
- `vfs.hpp`: Defines the `VFS` class and its methods.
- `inode.hpp`: Defines the `Inode` class representing files and directories.
- `queue.hpp`: Defines a template `Queue` class used for the recycle bin.
- `vector.hpp`: Defines a template `Vector` class used for dynamic arrays.
- `Makefile`: Contains the build instructions for the project.

## Build and Run
1. **Build the project**:
    ```sh
    make
    ```

2. **Run the executable**:
    ```sh
    ./vfs
    ```

3. **Clean the build**:
    ```sh
    make clean
    ```

