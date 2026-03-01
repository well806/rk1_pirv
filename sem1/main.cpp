#include <iostream>
#include <limits>
#include <vector>
#include "Student.hpp"
#include "Teacher.hpp"
#include "Group.hpp"
#include "FileManager.hpp"
using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double inputGrade() {
    double grade;
    while (true) {
        cout << "Введите оценку (0-5): ";
        cin >> grade;

        if (cin.fail()) {
            cout << "Ошибка! Введите число.\n";
            clearInput();
        } else if (grade < 0 || grade > 5) {
            cout << "Ошибка! Оценка должна быть от 0 до 5.\n";
        } else {
            return grade;
        }
    }
}

void printMenu() {
    cout << "\n========== МЕНЮ ==========\n";
    cout << "1. Добавить студента\n";
    cout << "2. Добавить оценку студенту\n";
    cout << "3. Показать всех студентов\n";
    cout << "4. Показать статистику группы\n";
    cout << "5. Сортировать студентов по среднему баллу\n";
    cout << "6. Фильтровать студентов (удалить ниже порога)\n";
    cout << "7. Найти студента по имени\n";
    cout << "8. Сохранить группу в файл\n";
    cout << "9. Загрузить группу из файла\n";
    cout << "10. Показать размер заголовка файла\n";
    cout << "0. Выход\n";
    cout << "==========================\n";
    cout << "Выберите действие: ";
}

int main() {
    Group group("ИУ1-42Б");
    vector<Student*> allStudents;

    int choice;
    do {
        printMenu();
        cin >> choice;

        if (cin.fail()) {
            cout << "Ошибка ввода!\n";
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: {
                string name;
                cout << "Введите имя студента: ";
                clearInput();
                getline(cin, name);

                string recordNumber;
                cout << "Введите номер зачётки: ";
                getline(cin, recordNumber);

                Student* student = new Student(name, recordNumber);

                int gradeCount;
                cout << "Сколько оценок добавить? ";
                cin >> gradeCount;

                for (int i = 0; i < gradeCount; ++i) {
                    double grade = inputGrade();
                    student->addGrade(grade);
                }

                allStudents.push_back(student);
                group.addStudent(student);
                cout << "Студент добавлен!\n";
                break;
            }

            case 2: {
                if (group.getSize() == 0) {
                    cout << "Нет студентов!\n";
                    break;
                }

                string name;
                cout << "Введите имя студента: ";
                clearInput();
                getline(cin, name);

                Student* student = group.findStudent(name);
                if (student) {
                    double grade = inputGrade();
                    student->addGrade(grade);
                    cout << "Оценка добавлена!\n";
                } else {
                    cout << "Студент не найден!\n";
                }
                break;
            }

            case 3:
                group.printAllStudents();
                break;

            case 4: {
                cout << "\n=====ИУ1-42Б=====\n";
                cout << "Средний балл группы: " << group.calculateGroupAverage() << endl;
                cout << "Количество отличников (>=4.5): " << group.countExcellent() << endl;
                cout << "Количество студентов с риском отчисления (<3.0): " << group.countAtRisk() << endl;
                break;
            }

            case 5:
                group.sortByAverage();
                cout << "Студенты отсортированы по среднему баллу!\n";
                group.printAllStudents();
                break;

            case 6: {
                double threshold;
                cout << "Введите пороговое значение: ";
                cin >> threshold;
                group.filterByThreshold(threshold);
                cout << "Фильтрация выполнена!\n";
                break;
            }

            case 7: {
                string name;
                cout << "Введите имя студента: ";
                clearInput();
                getline(cin, name);

                Student* student = group.findStudent(name);
                if (student) {
                    cout << "\nНайден студент:\n";
                    student->print();
                } else {
                    cout << "Студент не найден!\n";
                }
                break;
            }

            case 8: {
                string filename;
                cout << "Введите имя файла: ";
                cin >> filename;

                if (FileManager::saveGroup(group, filename)) {
                    cout << "Группа сохранена в файл " << filename << endl;
                } else {
                    cout << "Ошибка сохранения!\n";
                }
                break;
            }

            case 9: {
                string filename;
                cout << "Введите имя файла: ";
                cin >> filename;

                Group newGroup;
                if (FileManager::loadGroup(newGroup, filename)) {
                    group = newGroup;
                    cout << "Группа загружена из файла " << filename << endl;
                } else {
                    cout << "Ошибка загрузки или неверный формат файла!\n";
                }
                break;
            }

            case 10:
                FileManager::printHeaderSize();
                break;

            case 0:
                cout << "Выход из программы...\n";
                break;

            default:
                cout << "Неверный выбор!\n";
        }

    } while (choice != 0);


    for (Student* s : allStudents) {
        delete s;
    }

    return 0;
}
