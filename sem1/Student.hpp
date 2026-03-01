#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "Person.hpp"
#include "RecordBook.hpp"
using namespace std;

class Student : public Person {
private:
    RecordBook recordBook;

public:
    Student();
    explicit Student(const string& name);
    Student(const string& name, const string& recordNumber);

    void addGrade(double grade);
    double calculateAverage() const;
    void print() const override;
    string getRecordNumber() const;
    const RecordBook& getRecordBook() const;
};

#endif
