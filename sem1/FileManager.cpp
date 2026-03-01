#include "FileManager.hpp"
#include <iostream>
using namespace std;

bool FileManager::saveGroup(const Group& group, const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        return false;
    }

    FileHeader header;
    header.signature[0] = 'G';
    header.signature[1] = 'R';
    header.signature[2] = 'P';
    header.signature[3] = '1';
    header.version = 1;
    header.studentCount = group.getSize();

    string groupName = group.getName();
    for (size_t i = 0; i < 49 && i < groupName.length(); ++i) {
        header.groupName[i] = groupName[i];
    }
    header.groupName[49] = '\0';

    file.write(reinterpret_cast<char*>(&header), sizeof(header));

    const auto& students = group.getStudents();
    for (const auto& student : students) {
        string name = student->getName();
        int nameLength = name.length();
        file.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        file.write(name.c_str(), nameLength);

        string recordNumber = student->getRecordNumber();
        int recordLength = recordNumber.length();
        file.write(reinterpret_cast<char*>(&recordLength), sizeof(recordLength));
        file.write(recordNumber.c_str(), recordLength);

        const auto& grades = student->getRecordBook().getGrades();
        int gradeCount = grades.size();
        file.write(reinterpret_cast<char*>(&gradeCount), sizeof(gradeCount));
        file.write(reinterpret_cast<const char*>(grades.data()), gradeCount * sizeof(double));
    }

    file.close();
    return true;
}

bool FileManager::loadGroup(Group& group, const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        return false;
    }

    FileHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if (header.signature[0] != 'G' || header.signature[1] != 'R' ||
        header.signature[2] != 'P' || header.signature[3] != '1') {
        file.close();
        return false;
    }

    group = Group(string(header.groupName));

    for (int i = 0; i < header.studentCount; ++i) {
        int nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        char* nameBuffer = new char[nameLength + 1];
        file.read(nameBuffer, nameLength);
        nameBuffer[nameLength] = '\0';
        string name(nameBuffer);
        delete[] nameBuffer;

        int recordLength;
        file.read(reinterpret_cast<char*>(&recordLength), sizeof(recordLength));
        char* recordBuffer = new char[recordLength + 1];
        file.read(recordBuffer, recordLength);
        recordBuffer[recordLength] = '\0';
        string recordNumber(recordBuffer);
        delete[] recordBuffer;

        Student* student = new Student(name, recordNumber);

        int gradeCount;
        file.read(reinterpret_cast<char*>(&gradeCount), sizeof(gradeCount));
        for (int j = 0; j < gradeCount; ++j) {
            double grade;
            file.read(reinterpret_cast<char*>(&grade), sizeof(grade));
            student->addGrade(grade);
        }

        group.addStudent(student);
    }

    file.close();
    return true;
}

void FileManager::printHeaderSize() {
    cout << "Размер структуры заголовка: " << sizeof(FileHeader) << " байт" << endl;
}
