#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "Group.hpp"
#include <string>
#include <fstream>
using namespace std;

#pragma pack(push, 1)
struct FileHeader {
    char signature[4];
    int version;
    int studentCount;
    char groupName[50];
};
#pragma pack(pop)

class FileManager {
public:
    static bool saveGroup(const Group& group, const string& filename);
    static bool loadGroup(Group& group, const string& filename);
    static void printHeaderSize();
};

#endif
