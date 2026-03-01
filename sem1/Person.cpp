#include "Person.hpp"

Person::Person() : name("Unknown") {}

Person::Person(const string& name) : name(name) {}

Person::~Person() {}

void Person::print() const {
    cout << "Имя: " << name;
}

string Person::getName() const {
    return name;
}
