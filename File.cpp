#include <iomanip>
#include "File.h"

int File::_inode_counter = 0;
const int MAX_FILE_NAME_CHARACTERS = 20;

/**
 * Constructor, sequentially generate inodes.
 * @param name
 * @param isDir
 */
File::File(std::string name, bool isDir) : _inode(_inode_counter++), _name(name), _isDir(isDir)
{}
/**
 * @return File data size in bytes
 */
size_t File::getDataBytes() const {
    return _data.empty() ? 0 : _data.size() + 1;
}
/**
 * Prints the relevant file data into an ostream
 * @param os ostream
 * @param file File
 * @return os after writing on it
 */
std::ostream &operator<<(std::ostream &os, const File &file) {
    os << std::setw(MAX_FILE_NAME_CHARACTERS) << std::left <<file._name << " " << file.getDataBytes() << std::endl;
    return os;
}
/**
 * @return file name
 */
std::string File::getName() const {
    return _name;
}
/**
 *  Sets the file's data while overriding the existing data
 */
void File::setData(std::string data) {
    _data = data;
}
/**
 * @return file's data
 */
std::string File::getData() const {
    return _data;
}
/**
 * @return file's inode
 */
int File::getInode() const {
    return _inode;
}
/**
 * @return true when the file is a directory, false otherwise.
 */
bool File::getIsDir() const {
    return _isDir;
}
