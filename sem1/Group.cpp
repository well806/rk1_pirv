#include "Group.hpp"
#include <iomanip>
using namespace std;

Group::Group() : name("Unknown") {}

Group::Group(const string& name) : name(name) {}

Group::~Group() {}

void Group::addStudent(Student* student) {
    if (student != nullptr) {
        students.push_back(student);
    }
}

bool Group::removeStudent(const string& studentName) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if ((*it)->getName() == studentName) {
            students.erase(it);
            return true;
        }
    }
    return false;
}

void Group::printAllStudents() const {
    cout << "\n=== Группа: " << name << " ===\n";
    cout << "Количество студентов: " << students.size() << "\n\n";

    for (size_t i = 0; i < students.size(); ++i) {
        cout << "Студент #" << (i + 1) << ":\n";
        students[i]->print();
        cout << "------------------------\n";
    }
}

double Group::calculateGroupAverage() const {
    if (students.empty()) return 0.0;

    double sum = 0.0;
    for (const auto& student : students) {
        sum += student->calculateAverage();
    }
    return sum / students.size();
}

void Group::sortByAverage() {
    vector<pair<int, double>> studentAverages;
    for (size_t i = 0; i < students.size(); ++i) {
        studentAverages.push_back({i, students[i]->calculateAverage()});
    }

    sort(studentAverages.begin(), studentAverages.end(),
        [](const pair<int, double>& a, const pair<int, double>& b) {
            if (a.second != b.second)
                return a.second > b.second;
            return a.first < b.first;
        });

    vector<Student*> sortedStudents;
    for (const auto& item : studentAverages) {
        sortedStudents.push_back(students[item.first]);
    }
    students = sortedStudents;
}

void Group::filterByThreshold(double threshold) {
    auto newEnd = remove_if(students.begin(), students.end(),
        [threshold](Student* s) {
            return s->calculateAverage() < threshold;
        });
    students.erase(newEnd, students.end());
}

int Group::countExcellent() const {
    int count = 0;
    for (const auto& s : students) {
        if (s->calculateAverage() >= 4.5) {
            count++;
        }
    }
    return count;
}

int Group::countAtRisk() const {
    int count = 0;
    for (const auto& s : students) {
        if (s->calculateAverage() < 3.0) {
            count++;
        }
    }
    return count;
}

Student* Group::findStudent(const string& name) const {
    for (const auto& s : students) {
        if (s->getName() == name) {
            return s;
        }
    }
    return nullptr;
}

size_t Group::getSize() const {
    return students.size();
}

string Group::getName() const {
    return name;
}

const vector<Student*>& Group::getStudents() const {
    return students;
}
