//inode.hpp

#ifndef INODE_H
#define INODE_H
#include<cstdlib>
#include<string>
#include<ctime>
#include "vector.hpp"

using namespace std;
enum {File=0,Folder=1};

class Inode
{
    private:
        string name;
        bool type;
        unsigned int size;
        string cr_time;
        Vector<Inode*> children;
        Inode* parent;

    public:
        Inode(string name, Inode* parent, bool type, int size, string cr_time) : name(name),type(type),size(size),cr_time(cr_time),parent(parent)
        { }

        string getName() const {
            return name;
        }

        friend class VFS;
};
#endif
