#pragma once
#include <iostream>
#include <string>


class File {
public:
    File(std::string, bool);
    size_t getDataBytes() const;
    std::string getName() const;
    std::string getData() const;
    int getInode() const;
    bool getIsDir() const;
    void setData(std::string);
    friend std::ostream& operator<<(std::ostream& os, const File& file);
private:
    int _inode;
    std::string _name;
    std::string _data;
    bool _isDir;
    static int _inode_counter;
};

