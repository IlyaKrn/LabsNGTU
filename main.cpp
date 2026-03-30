#include <iostream>
#include <cmath>
#include "build/libs/sdl2/include/SDL.h"
#include "include/SLAU.h"

using namespace std;

//задача
struct task{
    function<vector<long double>(vect_t)> rhs;
    function<vector<vector<long double>>(vect_t)> rhsJ;
    vect_t start;
    long double maxTime;
    long double tau_min;
    long double tau_max;
};

//список задач
vector<task>tasks={};

int main(int argc, char** argv) {

    //значения для подстановки в методы
    task selectedTask;
    int methodNumber;
    long double eps_i;

    //выбираем задачу
    cout << "Выберите задачу:" << endl;
    cout << "1. Уравнение Ван-дер-Поля" << endl;
    cout << "2. Уравнение Рэлея" << endl;
    cout << "3. Система трех уравнений" << endl;
    cout << "4. Система с матрицей A" << endl;

    int taskNumber;
    try{cin >> taskNumber;}catch (...){taskNumber=0;}
    if(taskNumber <= 0 || taskNumber > 4){
        cout << "Неверный ввод. Выбрана задача 1" << endl;
        taskNumber = 1;
    }
    selectedTask = tasks[taskNumber];

    //todo("задаем значения коэффициентов в задаче")

    // выбираем eps_i
    cout << "Выберите погрешность:" << endl;
    cout << "1. 1e-3" << endl;
    cout << "2. 1e-5" << endl;
    int eps_i_Number;
    try{cin >> eps_i_Number;}catch (...){eps_i_Number=0;}
    if(eps_i_Number <= 0 || eps_i_Number > 2){
        cout << "Неверный ввод. Выбрана погрешность 1" << endl;
        eps_i_Number = 1;
    }
    eps_i = eps_i_Number == 1 ? 1e-3 : 1e-5;

    // выбираем метод
    cout << "Выберите метод:" << endl;
    cout << "1. явный м. Эйлера" << endl;
    cout << "2. неявный м. Эйлера" << endl;
    cout << "3. неявный м. Шихмана" << endl;
    try{cin >> methodNumber;}catch (...){methodNumber=0;}
    if(methodNumber <= 0 || methodNumber > 3){
        cout << "Неверный ввод. Выбран метод 1" << endl;
        methodNumber = 1;
    }
    vector<vect_t> result;

    switch(methodNumber) {
        case 1:
            result = eulerExplicit(selectedTask.start, selectedTask.maxTime, eps_i, selectedTask.tau_max, selectedTask.rhs);
            break;
        case 2:
            result = eulerNonExplicit(selectedTask.start, selectedTask.maxTime, eps_i, selectedTask.tau_min, selectedTask.tau_max, selectedTask.rhs, selectedTask.rhsJ);
            break;
        case 3:
            result = shikhman(selectedTask.start, selectedTask.maxTime, eps_i, selectedTask.tau_min, selectedTask.tau_max, selectedTask.rhs, selectedTask.rhsJ);
            break;
    }

    return 0;
}