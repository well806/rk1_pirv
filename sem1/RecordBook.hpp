#ifndef RECORDBOOK_HPP
#define RECORDBOOK_HPP

#include <vector>
#include <string>
using namespace std;

class RecordBook {
private:
    string number;
    vector<double> grades;

public:
    RecordBook();
    explicit RecordBook(const string& number);

    void addGrade(double grade);
    double calculateAverage() const;
    void printGrades() const;
    string getNumber() const;
    const vector<double>& getGrades() const;
    size_t getGradesCount() const;
};

#endif
