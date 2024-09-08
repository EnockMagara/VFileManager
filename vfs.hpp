
//vfs.hpp
#ifndef VFS_H
#define VFS_H
#include<iostream>
#include <regex>
#include<iomanip>
#include<cstdlib>
#include<string>
#include<ctime>
#include <numeric>
#include<fstream>
#include<chrono>
#include<sstream>
#include "inode.hpp"
#include "stack.hpp"
#include "queue.hpp"
using namespace std;

class VFS
{
    private:
        Inode *root;
        Inode *curr_inode;
        Inode *prev_inode;
        Queue<Inode*> bin;
        Queue<string> bin_paths;
    
    public:
        // Constructor for the VFS class
        VFS() {
            // Initialize the root inode with the root directory ("/")
            root = new Inode("/", nullptr, Folder, 0, getTime());
            // Set the current and previous inodes to the root
            curr_inode = root;
            prev_inode = nullptr;
            // Initialize the bin and bin_paths queues with a capacity of 100
            bin = Queue<Inode*>(100);
            bin_paths = Queue<string>(100);
        }
        // Method to display the available commands
        void help() {
            //Implemented in main.cpp
        }
  
    string pwd() {
            // Set the current inode to the current working directory
            Inode* current = curr_inode;
            // Create an empty string path
            string path = "";
            //  Loop until the current inode is the root directory or null
            while (current != root && current != nullptr) {
                
                //  Prepend the name of the current inode to the path
                path = current->name + (path.empty() ? "" : "/") + path;
                //  Set the current inode to its parent
                current = current->parent;
            }
            //  If the current inode is not null
            if (current != nullptr) {
                //  Append the root directory symbol ("/") to the path
                path = "/" + path;
            }
            //  Return the path
            return path;
        }

    void mkdir(string folder_name) {
        // If the folder_name is empty, throw an error
        if (folder_name.empty()) {
            throw runtime_error("Folder name cannot be empty");
        }
        // Check if a child with the same name and type Folder already exists
        Inode* existing_folder = getChild(curr_inode, folder_name);
        if (existing_folder != nullptr && existing_folder->type == Folder) {
            throw runtime_error("Folder already exists");
        }
        // If no such folder exists, create a new Inode for the folder
        Inode* new_folder = new Inode(folder_name, curr_inode, Folder, 10, getTime());
        // Add the new folder to the children of the current inode
        curr_inode->children.push_back(new_folder);
       
    }
    void touch(string file_name, unsigned int* size = nullptr) {
        // If the file_name is empty, throw an error
        if (file_name.empty()) {
            throw runtime_error("File name cannot be empty");
        }
        // Check if the file_name is alphanumeric with optional periods
        if (!regex_match(file_name, regex("^[a-zA-Z0-9.]+$"))) {
            throw runtime_error("File name must be alphanumeric and may only contain a period");
        }
        // If the size is not provided, throw an error
            if (size == nullptr) {
                throw runtime_error("File size must be specified");
            }
        // Check if a child with the same name and type File already exists
        Inode* existing_file = getChild(curr_inode, file_name);
        if (existing_file != nullptr && existing_file->type == File) {
            throw runtime_error("File already exists");
        }
        // If no such file exists, create a new Inode for the file
        Inode* new_file = new Inode(file_name, curr_inode, File, *size, getTime());
        // Add the new file to the children of the current inode
        curr_inode->children.push_back(new_file);
    }

    
    Vector<string> split(const string &str, char delim) {
        Vector<string> result;
        stringstream ss(str);
        string item;
        while (getline(ss, item, delim)) {
            result.push_back(item);
        }
        return result;
    }
    void cd(string path = "") {
           // If no path is provided, change the current inode to the root
           if (path == "") {
               prev_inode = curr_inode;
               curr_inode = root;
               return;
           }
           // If path is "..", change the current inode to its parent
           if (path == "..") {
               if (curr_inode->parent != nullptr) {
                   prev_inode = curr_inode;
                   curr_inode = curr_inode->parent;
               }
               return;
           }
           // If path is "-", change the current inode to the previous inode
           if (path == "-") {
               if (prev_inode != nullptr) {
                   Inode* temp = curr_inode;
                   curr_inode = prev_inode;
                   prev_inode = temp;
               }
               return;
           }
           // Get the inode at the given path
           Inode* target = (path[0] == '/' ? getNode(path.substr(1), true, root) : getNode(path, true));
           // Check if the target inode is a folder
           if (target != nullptr && target->type == Folder) {
               // If it is a folder, change the current inode to the target
               prev_inode = curr_inode;
               curr_inode = target;
           } else {
               // If the target inode does not exist or is not a folder, throw an error
               throw runtime_error("Directory does not exist or not in current working directory");
           }
       }


        void rm(string path) {
    // Get the inode at the given path
    Inode* target = getNode(path, true);
    // If the target inode does not exist, throw an error
    if (target == nullptr) {
        throw runtime_error("File or folder does not exist");
    }
    // Check if the target inode is the root directory
    if (target == root) {
        throw runtime_error("Cannot delete the root directory");
        }
    // Get the parent of the target inode
    Inode* parent = target->parent;
    // Remove the target from the children of its parent
    for (int i = 0; i < parent->children.size(); i++) {
        if (parent->children[i] == target) {
            parent->children.erase(parent->children.begin() + i);
            break;
        }
    }
   
    // If the bin is full, dequeue the oldest inode and delete it
    if (bin.isFull()) {
        delete bin.dequeue();
    }
    // Add the target to the bin
    bin.enqueue(target);
    // If the bin_paths is full, dequeue the oldest path
    if (bin_paths.isFull()) {
        bin_paths.dequeue();
    }
    // Add the full path to the bin paths
    bin_paths.enqueue(pwd() + "/" + path);
}
        void size(string path) {
            // Get the inode at the given path
            Inode* target = getNode(path, true);
            // Check if the target inode exists
            if (target != nullptr) {
                // If it exists, calculate the total size of the folder or file
                int totalSize = 0;
                if (target->type == Folder) {
                    totalSize = calculateFolderSize(target);
                } else {
                    totalSize = target->size;
                }
                // Print the size of the target
                cout << path << "\n" << totalSize << " bytes" << endl;
            } else {
                // If it does not exist, throw a runtime error
                throw runtime_error("Cannot calculate size: Path does not exist or not absolute path.");
            }
        }
    int calculateFolderSize(Inode* folder) {
        // Start with the size of the folder itself
        int totalSize = folder->size;
        for (Inode* child : folder->children) {
            if (child->type == Folder) {
                totalSize += calculateFolderSize(child);
            } else {
                totalSize += child->size;
            }
        }
     
        return totalSize;
    }

        void showbin() {
            // Check if the bin is empty
            if (!bin.isEmpty()) {
                // If it is not empty, print the oldest inode in the bin and its path
                Inode* oldestInode = bin.front_element();
                string path = bin_paths.front_element();
                cout << "Next Element to remove: " << path;
                cout << " (" << (oldestInode->type == Folder ? calculateFolderSize(oldestInode) : oldestInode->size) << " bytes, ";
                cout << oldestInode->cr_time << ")" << endl;
            } else {
                // If it is empty, print a message indicating that the bin is empty
                cout << "Bin is empty" << endl;
            }
        }
        void emptybin() {
            // While the bin is not empty, dequeue each inode and delete it
            while(!bin.isEmpty()) {
                delete bin.dequeue();
            }
            // While the bin_paths is not empty, dequeue each path
            while(!bin_paths.isEmpty()) {
                bin_paths.dequeue();
            }
        }
        void exit() {
            // Create an output file stream object to save the current state of the file system
            ofstream fout("vfs.dat");
            // Check if the file is open, if not, throw a runtime error
            if (!fout.is_open()) {
                throw runtime_error("Failed to open the file");
            }
            
            // Call the write function to recursively write the data of each inode starting from the root to the file
            write(fout, root);
            
            // Close the output file stream
            fout.close();
            
            // Deallocate the memory occupied by the root inode
            delete root;
            
            // Deallocate the memory occupied by each inode in the bin by dequeuing each inode and deleting it until the bin is empty
            while (!bin.isEmpty()) {
                delete bin.dequeue();
            }
            
            // Terminate the program
            ::exit(0);
        }
        // Method to find a file or directory by name
        void find(string name) {
            // Pass an empty string as the initial path
            find_helper(root, name, "");
        }

        void find_helper(Inode *ptr, string name, string path) {


            // Check if the current inode's name matches the target name
            if (ptr->name == name) {
                // If it does, print the path
                // If the inode is a folder, append a '/' to the path
                cout << path << (ptr->type == Folder ? "/" : "") << endl;
            }
            // If it doesn't, iterate over the children of the current inode
            for (int i = 0; i < ptr->children.size(); i++) {
                Inode* child = ptr->children[i];
                // Recursively call find_helper on each child with the updated path
                // The updated path includes the current path, a '/' separator, and the child's name
                // string newPath = path + "/" + child->name;
                string newPath = path + (path.empty() ? "" : "/") + child->name;
                find_helper(child, name, newPath);
            }
        }


        void mv(string filename, string foldername) {
            // Find the file and folder among the children of the current inode
            Inode* fileNode = getChild(curr_inode, filename);
            Inode* folderNode = getChild(curr_inode, foldername);
            
            // If the file or folder does not exist, or the folder is not a directory, print an error message and return
            if (fileNode == nullptr) {
                cout << "File '" << filename << "' does not exist in the current directory." << endl;
                return;
            }
            if (folderNode == nullptr || folderNode->type != Folder) {
                cout << "Folder '" << foldername << "' does not exist in the current directory, or is not a directory." << endl;
                return;
            }
            
            // Remove the file from its current parent's children
            for (int i = 0; i < fileNode->parent->children.size(); i++) {
                if (fileNode->parent->children[i] == fileNode) {
                    fileNode->parent->children.erase(fileNode->parent->children.begin() + i);
                    break;
                }
            }
            
            // Change the parent of the file to the new folder
            fileNode->parent = folderNode;
            
            // Add the file to the new folder's children
            folderNode->children.push_back(fileNode);
            // Update the size of the new parent inode and its parents
            updateSize(folderNode);
            
            // Print a success message
            cout << "Moved '" << filename << "' to '" << foldername << "'." << endl;
        }
        void recover() {
            // Check if the bin is empty
            if (bin.isEmpty()) {
                // If the bin is empty, print a message and return
                cout << "Bin is empty. Nothing to recover." << endl;
                return;
            }
            
            // Get the last deleted inode and its path from the bin
            Inode* deletedNode = bin.dequeue();
            string deletedPath = bin_paths.dequeue();
            
            // Get the parent inode of the deleted inode
            Inode* parentNode = getNode(deletedPath.substr(0, deletedPath.find_last_of('/')), false);
            
            // Check if the parent node exists
            if (parentNode == nullptr) {
                // If the parent node does not exist, print an error message and return
                cout << "Parent directory does not exist. Cannot recover." << endl;
                return;
            }
            
            // Add the deleted inode back to its parent's children
            parentNode->children.push_back(deletedNode);
            
            // Set the parent of the deleted inode to its original parent
            deletedNode->parent = parentNode;
            
            // Print a success message
            cout << "Recovered '" << deletedNode->name << "' to '" << deletedPath << "'." << endl;
        }
    
    void load(ifstream& fin) {
                // Check if the file is open
                if (!fin.is_open()) {
                    cout << "Failed to open the file." << endl;
                    return;
                }

                // Helper function to check if a string is a valid integer
                auto isInteger = [](const string& s) {
                    return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
                };

                // Read the file line by line
                string line;
                while (getline(fin, line)) {
                    // Split the line into tokens
                    istringstream iss(line);
                    vector<string> tokens;
                    string token;
                    while (getline(iss, token, ' ')) {
                        tokens.push_back(token);
                    }

                    // The first token is the full path of the inode
                    string fullPath = tokens[0];

                    // The second token is the size of the inode
                    string sizeStr = tokens[1];
                    if (!isInteger(sizeStr)) {
                        cout << "Invalid size: " << sizeStr << endl;
                        continue;
                    }
                    unsigned int size = stoi(sizeStr);

                    // The third token is the creation time of the inode
                    string time = tokens[2];

                    // Extract the parent path and the name of the inode from the full path
                    string parentPath, name;
                    if (fullPath == "/") {
                        parentPath = "";
                        name = "/";
                    } else {
                        parentPath = fullPath.substr(0, fullPath.find_last_of('/'));
                        name = fullPath.substr(fullPath.find_last_of('/') + 1);
                    }

                    // Handle the root directory as a special case
                    if (fullPath == "/") {
                        root = new Inode(name, nullptr, Folder, size, time);
                        continue;
                    }

                    // Get the parent inode, create directories if they don't exist
                    Inode* parentNode = getNode(parentPath, true);

                    // Check if the parent node is null (error case)
                    if (parentNode == nullptr) {
                        cout << "Failed to create parent directories for '" << fullPath << "'." << endl;
                        continue;
                    }
                    // Check if a child with the same name and type Folder already exists
                    Inode* existingFolder = getChild(parentNode, name);
                    if (existingFolder != nullptr && existingFolder->type == Folder) {
                        cout << "Folder already exists: " << fullPath << endl;
                        continue;
                    }

                    // Create a new Inode for the folder
                    Inode* newFolder = new Inode(name, parentNode, Folder, size, time);

                    // Check if the new folder is null (error case)
                    if (newFolder == nullptr) {
                        cout << "Failed to create inode for '" << fullPath << "'." << endl;
                        continue;
                    }

                    // Add the new folder to the children of the parent inode
                    parentNode->children.push_back(newFolder);
                }

                // Close the file
                fin.close();

                // Print a success message
                cout << "Loaded the file system from the file." << endl;
            }

    Inode* getNode(string path, bool createIfNotExist, Inode* startNode = nullptr) {
            // If no startNode is provided, use the current inode
            if (startNode == nullptr) {
                startNode = curr_inode;
            }

            // Split the path into tokens
            istringstream iss(path);
            Vector<string> tokens;
            string token;
            while (getline(iss, token, '/')) {
                if (!token.empty()) {
                    tokens.push_back(token);
                }
            }

            // Start from the root inode if the path is absolute, or from the startNode if the path is relative
            Inode* temp = (path[0] == '/') ? root : startNode;

            // Iterate over the tokens
            for (const auto& token : tokens) {
                // If the token is "..", move up to the parent inode
                if (token == "..") {
                    temp = (temp->parent != nullptr) ? temp->parent : temp;
                }
                // Otherwise, find the child with the same name as the token
                else {
                    Inode* child = getChild(temp, token);
                    if (child == nullptr) {
                        // If the child does not exist, return nullptr
                        return nullptr;
                    }
                    temp = child;
                }
            }

            // Return the found inode
            return temp;
        }
        Inode* getChild(Inode *ptr, string childname) {
            // Get the number of children
            int numChildren = ptr->children.size();

            // Iterate over the children of the given inode
            for (int i = 0; i < numChildren; i++) {
                Inode* child = ptr->children[i];

                // If a child with the same name is found, return it
                if (child->name == childname) {
                    return child;
                }
            }

            // If no child with the same name is found, return nullptr
            return nullptr;
        }




    void updateSize(Inode* node, bool updateParent = true) {
        // Initialize the size to 0
        unsigned int size = 0;

        // If the inode is a file, set the size to the file's size
        if (node->type == File) {
            size = node->size;
        }
        // If the inode is a folder, recursively call updateSize on each child and add their sizes
        else if (node->type == Folder) {
            for (auto &child : node->children) {
                updateSize(child, false);
                size += child->size;
            }
        }

        // Update the inode's size
        node->size = size;

        // Only update the parent's size if updateParent is true
        if (node->parent && updateParent) {
            updateSize(node->parent, false);
        }
    }
        
     
 
        string getTime() {
            // Create a time_t object to hold the current time
            time_t now = time(0);

            // Convert the time_t object to a tm struct
            tm *ltm = localtime(&now);

            // Create a stringstream to format the time
            stringstream ss;

            // Add the hour, minute, and second to the stringstream
            // Use setw and setfill to ensure two digits for each
            ss << setw(2) << setfill('0') << ltm->tm_hour << ":";
            ss << setw(2) << setfill('0') << ltm->tm_min << ":";
            ss << setw(2) << setfill('0') << ltm->tm_sec;

            // Return the formatted time as a string
            return ss.str();
        }
        void write(ofstream &fout, Inode *ptr) {
            if (!fout.is_open()) {
                throw runtime_error("File is not open");
            }

            if (!fout.good()) {
                throw runtime_error("Error writing to file");
            }


            fout << ptr->name << " " << ptr->type << " " << ptr->size << " " << ptr->cr_time << "\n";

            if (ptr->type == Folder) {
                for (Inode* child : ptr->children) {
                    write(fout, child);
                }
            }
        }
        void ls() {
            // Check if the current directory is empty
            if (curr_inode->children.empty()) {
                cout << "Directory is empty" << endl;
            } else {
                // If it is not empty, print the details of each child
                for (Inode* child : curr_inode->children) {
                    cout << (child->type == Folder ? "dir " : "file ") << child->name << " ";
                    // If the child is a folder, calculate its total size
                    if (child->type == Folder) {
                        cout << calculateFolderSize(child) << " ";
                    } else {
                        // If the child is a file, print its size
                        cout << child->size << " ";
                    }
                    // Print the creation time of the child
                    cout << child->cr_time << endl;
                }
            }
        }
};
#endif
