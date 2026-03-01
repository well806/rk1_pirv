#include "Teacher.hpp"
using namespace std;

Teacher::Teacher() : Person(), discipline("Unknown") {}

Teacher::Teacher(const string& name, const string& discipline)
    : Person(name), discipline(discipline) {}

void Teacher::print() const {
    cout << "Преподаватель: " << name << endl;
    cout << "Дисциплина: " << discipline << endl;
}

string Teacher::getDiscipline() const {
    return discipline;
}
