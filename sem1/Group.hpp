#ifndef GROUP_HPP
#define GROUP_HPP

#include "Student.hpp"
#include <vector>
#include <algorithm>
using namespace std;

class Group {
private:
    string name;
    vector<Student*> students;

public:
    Group();
    explicit Group(const string& name);
    ~Group();

    void addStudent(Student* student);
    bool removeStudent(const string& studentName);
    void printAllStudents() const;
    double calculateGroupAverage() const;
    void sortByAverage();
    void filterByThreshold(double threshold);
    int countExcellent() const;
    int countAtRisk() const;
    Student* findStudent(const string& name) const;
    size_t getSize() const;
    string getName() const;
    const vector<Student*>& getStudents() const;
};

#endif
