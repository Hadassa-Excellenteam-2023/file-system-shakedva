#include "myfs.h"
#include <string.h>
#include <iostream>
#include <math.h>
#include <sstream>

const char *MyFs::MYFS_MAGIC = "MYFS";
const std::string WHITESPACES(" \t\f\v\n\r");


MyFs::MyFs(BlockDeviceSimulator *blkdevsim_) : blkdevsim(blkdevsim_) {
    myfs_header header;
    blkdevsim->read(0, sizeof(header), (char *) &header);

    if (strncmp(header.magic, MYFS_MAGIC, sizeof(header.magic)) != 0 ||
        (header.version != CURR_VERSION)) {
        std::cout << "Did not find myfs instance on blkdev" << std::endl;
        std::cout << "Creating..." << std::endl;
        format();
        std::cout << "Finished!" << std::endl;

    }
    else { // file system instance exists, load it
        int dataSize = BlockDeviceSimulator::DEVICE_SIZE - sizeof(header);
        char blkdevData[dataSize];
        blkdevsim->read(sizeof(header), dataSize, blkdevData);
        _blkdevData = blkdevData;
        parseBlockDevice();
    }
}

void MyFs::format() {

    // put the header in place
    myfs_header header;
    strncpy(header.magic, MYFS_MAGIC, sizeof(header.magic));
    header.version = CURR_VERSION;
    blkdevsim->write(0, sizeof(header), (const char *) &header);
    blkdevsim->write(sizeof(header), _blkdevData.size(), _blkdevData.data());
}

void MyFs::create_file(std::string path_str, bool directory) {
    File f = File(path_str, directory);
    _files.push_back(f);

}

std::string MyFs::get_content(std::string path_str) {
    for (const auto &file: _files) {
        if (file.getName() == path_str) {
            return file.getData();
        }
    }
    return "";
}

void MyFs::set_content(std::string path_str, std::string content) {
    for (auto &file: _files) {
        if (file.getName() == path_str) {
            file.setData(content);
            return;
        }
    }
}

std::vector<File> MyFs::list_dir(std::string path_str) {
    return _files;
}

void MyFs::updateBlockDevice() {
    _blkdevData = "\n";
    for (auto file: _files) {
        char type = file.getIsDir() ? 'd' : 'f';
        _blkdevData +=
                std::to_string(file.getInode()) + " " + file.getName() + " " + type + " " + file.getData() + "\n";
    }
    format();
}

void MyFs::parseBlockDevice() {
    std::istringstream f(_blkdevData);
    std::string line;
    int inode;
    std::string name;
    std::string data;
    char type;

    while(std::getline(f, line))
    {
        f >> inode >> name >> type;
        std::getline(f, data);
        data = ltrim(data);
        File file = File(name, type == 'd');
        file.setData(data);
        _files.push_back(file);
    }
}

std::string MyFs::ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACES);
    return (start == std::string::npos) ? "" : s.substr(start);
}