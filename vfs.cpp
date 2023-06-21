#include "vfs.h"

#include <iostream>
#include <sstream>


const std::string FS_NAME = "myfs";

const std::string LIST_CMD = "ls";
const std::string CONTENT_CMD = "cat";
const std::string CREATE_FILE_CMD = "touch";
const std::string EDIT_CMD = "edit";
const std::string REMOVE_CMD = "rm";
const std::string HELP_CMD = "help";
const std::string EXIT_CMD = "exit";

const std::string HELP_STRING = "The following commands are supported: \n"
                                + LIST_CMD + " [<directory>] - list directory content. \n"
                                + CONTENT_CMD + " <path> - show File content. \n"
                                + CREATE_FILE_CMD + " <path> - create empty File. \n"
                                + EDIT_CMD + " <path> - re-set File content. \n"
                                + REMOVE_CMD + " <path> - remove File. \n"
                                + HELP_CMD + " - show this help messege. \n"
                                + EXIT_CMD + " - gracefully exit. \n";


std::string getCmdContent(std::vector<std::string>);

std::string getPath(std::vector<std::string>);

std::vector<std::string> split_cmd(std::string cmd) {
    std::stringstream ss(cmd);
    std::string part;
    std::vector<std::string> ans;

    while (std::getline(ss, part, ' '))
        ans.push_back(part);

    return ans;
}

void run_vfs(MyFs &fs) {
    std::cout << "Welcome to " << FS_NAME << std::endl;
    std::cout << "To get help, please type 'help' on the prompt below." << std::endl;
    std::cout << std::endl;

    bool exit = false;
    while (!exit) {
        try {
            std::string cmdline;
            std::cout << FS_NAME << "$ ";
            std::getline(std::cin, cmdline, '\n');
            if (cmdline == std::string(""))
                continue;

            std::vector<std::string> cmd = split_cmd(cmdline);

            if (cmd[0] == EXIT_CMD) {
                exit = true;
            }
            else if (cmd[0] == HELP_CMD) {
                std::cout << HELP_STRING;
            }
            else if (cmd[0] == LIST_CMD) {
                std::vector<File> all_files = fs.list_dir(getPath(cmd));
                for (const File &file: all_files) {
                    std::cout << file;
                }
            }
            else if (cmd[0] == CREATE_FILE_CMD) {
                fs.create_file(getPath(cmd), false);
            }
            else if (cmd[0] == CONTENT_CMD) {
                std::cout << fs.get_content(getPath(cmd)) << std::endl;
            }
            else if (cmd[0] == EDIT_CMD) {
                fs.set_content(getPath(cmd), getCmdContent(cmd));
            }
            else if (cmd[0] == REMOVE_CMD) {
                fs.remove_file(getPath(cmd));
            }
            else {
                std::cout << "unknown command: " << cmd[0] << std::endl;
            }
        } catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        }
    }
}
/**
 * Checks if command line received file path and returns it
 * @param cmd command line string
 * @return the file path
 */
std::string getPath(std::vector<std::string> cmd) {
    if (cmd.size() > 1)
        return cmd[1];
    return "";
}
/**
 * Checks if command line received content and returns it
 * @param cmd
 * @return content received from the user via the cmd
 */
std::string getCmdContent(std::vector<std::string> cmd) {
    std::string content;
    for (size_t i = 2; i < cmd.size(); i++)
        content += cmd[i] + " ";
    if (!content.empty())
        content.pop_back(); //remove last whitespace
    return content;
}