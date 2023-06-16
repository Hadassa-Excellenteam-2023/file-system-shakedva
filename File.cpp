#include <iomanip>
#include "File.h"

int File::_inode_counter = 0;
const int MAX_FILE_NAME_CHARACTERS = 20;

File::File(std::string name, bool isDir) : _inode(_inode_counter++), _name(name), _isDir(isDir)
{}

size_t File::getDataBytes() const {
    return _data.empty() ? 0 : _data.size() + 1;
}

std::ostream &operator<<(std::ostream &os, const File &file) {
    os << std::setw(MAX_FILE_NAME_CHARACTERS) << std::left <<file._name << " " << file.getDataBytes() << std::endl;
    return os;
}

std::string File::getName() const {
    return _name;
}

void File::setData(std::string data) {
    _data = data;
}

std::string File::getData() const {
    return _data;
}
