#include "myfs.h"
#include <string.h>
#include <iostream>
#include <math.h>
#include <sstream>

const char *MyFs::MYFS_MAGIC = "MYFS";

MyFs::MyFs(BlockDeviceSimulator *blkdevsim_):blkdevsim(blkdevsim_) {
	myfs_header header;
	blkdevsim->read(0, sizeof(header), (char *)&header);

	if (strncmp(header.magic, MYFS_MAGIC, sizeof(header.magic)) != 0 ||
	    (header.version != CURR_VERSION)) {
		std::cout << "Did not find myfs instance on blkdev" << std::endl;
		std::cout << "Creating..." << std::endl;
		format();
		std::cout << "Finished!" << std::endl;
	}
    //todo create root dir
}

void MyFs::format() {

	// put the header in place
	myfs_header header;
	strncpy(header.magic, MYFS_MAGIC, sizeof(header.magic));
	header.version = CURR_VERSION;
	blkdevsim->write(0, sizeof(header), (const char*)&header);

	// TODO: put your format code here
}

void MyFs::create_file(std::string path_str, bool directory) {
    //todo check there arent directories like /..../...
    File f = File(path_str, directory);
    _files.push_back(f);

}
std::string MyFs::get_content(std::string path_str) {
    for(const auto& file: _files)
    {
        if(file.getName() == path_str) {
            return file.getData();
        }
    }
    return "";
}

void MyFs::set_content(std::string path_str, std::string content) {
    for(auto& file: _files)
    {
        if(file.getName() == path_str) {
            file.setData(content);
            return;
        }
    }
}

std::vector<File> MyFs::list_dir(std::string path_str) {
    //todo - check it is under the root path only (there aren't any dirs currently)
    return _files;
}
