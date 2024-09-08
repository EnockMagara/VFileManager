//main.cpp

#include<iostream>
#include<sstream>
#include<stdlib.h>
#include "vfs.hpp"
using namespace std;

// Main function
int main()
{
    // Creating an object of VFS class
    VFS vfs;
//     //Load the file system from a file
//    ifstream fin("vfs.dat");
//    vfs.load(fin);


    // Infinite loop to keep the program running until the user decides to exit
    while(true)
    {
        // Variables to store user input and parameters
        string user_input;
        string command;
        string parameter1;
        string parameter2;

        // Prompting the user for input
        cout<<">";
        // Reading the user input
        getline(cin,user_input);

        // Parsing user input into command and parameters
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,parameter1,' ');
        getline(sstr,parameter2);

        // Using a try-catch block to handle exceptions
        try
        {
            // Checking the command and calling the corresponding function
            if(command=="help")        {
                cout << "List of available Commands:" << endl
                     << "help               : Display the list of available commands" << endl
                     << "pwd                : Print the current working directory" << endl
                     << "ls                 : List the contents of the current directory" << endl
                     << "mkdir <dir_name>   : Create a new directory" << endl
                     << "touch <file_name> <file_size> : Create a new file with the specified name and size" << endl
                     << "cd <dir_name>      : Change the current directory" << endl
                     << "rm <name>          : Remove a file or directory" << endl
                     << "size <name>        : Display the size of a file or directory" << endl
                     << "showbin            : Show the contents of the recycle bin" << endl
                     << "emptybin           : Empty the recycle bin" << endl
                     << "exit               : Exit the program" << endl
                     << "find <file_name>   : Find a file in the VFS" << endl
                     << "mv <src> <dest>    : Move a file or directory to a new location" << endl
                     << "recover            : Recover the last deleted file or directory" << endl
                     << "clear              : Clear the terminal screen" << endl;
            }
            else if(command=="pwd")            cout<<vfs.pwd()<<endl;
            else if(command=="ls")             vfs.ls();
            else if(command=="mkdir")        vfs.mkdir(parameter1);
            else if(command=="touch")        {
                   unsigned int size = stoi(parameter2);
                   vfs.touch(parameter1, &size);
               }
            else if(command=="cd")            vfs.cd(parameter1);
            else if(command=="rm")            vfs.rm(parameter1);
            else if(command=="size")        vfs.size(parameter1);
            else if(command=="showbin")        vfs.showbin();
            else if(command=="emptybin")    vfs.emptybin();
            else if(command=="exit")        {vfs.exit(); return(EXIT_SUCCESS);}
            else if(command=="find")        vfs.find(parameter1);
            else if(command=="mv")            vfs.mv(parameter1, parameter2);
            else if(command=="recover")        vfs.recover();
            else if(command=="clear")        system("clear");
            else                             cout<<command<<": command not found"<<endl;
        }
        catch(exception &e)
        {
            // Printing the exception message
            cout<<"Exception: "<<e.what()<<endl;
        }

    }
}


