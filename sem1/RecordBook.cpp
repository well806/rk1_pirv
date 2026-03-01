#include "RecordBook.hpp"
#include <iostream>
#include <numeric>
using namespace std;

RecordBook::RecordBook() : number("000000") {}

RecordBook::RecordBook(const string& number) : number(number) {}

void RecordBook::addGrade(double grade) {
    if (grade >= 0 && grade <= 5) {
        grades.push_back(grade);
    }
}

double RecordBook::calculateAverage() const {
    if (grades.empty()) return 0.0;

    double sum = 0.0;
    for (double g : grades) {
        sum += g;
    }
    return sum / grades.size();
}

void RecordBook::printGrades() const {
    cout << "Оценки: ";
    for (double g : grades) {
        cout << g << " ";
    }
    cout << endl;
}

string RecordBook::getNumber() const {
    return number;
}

const vector<double>& RecordBook::getGrades() const {
    return grades;
}

size_t RecordBook::getGradesCount() const {
    return grades.size();
}
