#ifndef TEACHER_HPP
#define TEACHER_HPP

#include "Person.hpp"
using namespace std;

class Teacher : public Person {
private:
    string discipline;

public:
    Teacher();
    Teacher(const string& name, const string& discipline);

    void print() const override;
    string getDiscipline() const;
};

#endif
