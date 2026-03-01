#include "Student.hpp"
#include <iomanip>
using namespace std;

Student::Student() : Person(), recordBook() {}

Student::Student(const string& name) : Person(name), recordBook() {}

Student::Student(const string& name, const string& recordNumber)
    : Person(name), recordBook(recordNumber) {}

void Student::addGrade(double grade) {
    recordBook.addGrade(grade);
}

double Student::calculateAverage() const {
    return recordBook.calculateAverage();
}

void Student::print() const {
    cout << "Студент: " << name << endl;
    cout << "Номер зачётки: " << recordBook.getNumber() << endl;
    cout << "Средний балл: " << fixed << setprecision(2) << calculateAverage() << endl;
    recordBook.printGrades();
}

string Student::getRecordNumber() const {
    return recordBook.getNumber();
}

const RecordBook& Student::getRecordBook() const {
    return recordBook;
}
