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
    long double snauE1;
    long double snauE2;
    int snauMaxIter;
};

//коэффициенты
long double a, k, w, lambda1, lambda2, lambda3, T;

//список задач
vector<task> tasks = {
    {
        [](vect_t cur) {
            vector<long double> res = {
                -cur.vect[0]*cur.vect[1] + sin(cur.t)/cur.t,
                -cur.vect[1]*cur.vect[1] + a*cur.t/(1+cur.t*cur.t)
            };
            return res;
        },
        [](vect_t cur) {
            vector<vector<long double>> res = {{
                -cur.vect[1],
                -cur.vect[0]
            },{
                0,
                -2*cur.vect[1]
            }};
            return res;
        },
        {{0, -0.412}, 0}, 1, 0.01, 0.1, 1e-3, 1e-3, 10000
    },{
        [](vect_t cur) {
            vector<long double> res = {
                cur.vect[1] - (a*cur.vect[0] + k*cur.vect[1])*cur.vect[0],
                exp(cur.vect[0]) - (cur.vect[0] + a*cur.vect[1])*cur.vect[0]
            };
            return res;
        },
        [](vect_t cur) {
            vector<vector<long double>> res = {{
                - (a)*cur.vect[0] - (a*cur.vect[0] + k*cur.vect[1]),
                1 - (k)*cur.vect[0]
            },{
                exp(cur.vect[0]) - cur.vect[0] - (cur.vect[0] + a*cur.vect[1]),
                - (a)*cur.vect[0]
            }};
            return res;
        },
        {{1, 0}, 0}, 1, 0.01, 0.1, 1e-3, 1e-3, 10000
    },{
        [](vect_t cur) {
            vector<long double> res = {
                (k-a)/a * cur.vect[1]*cur.vect[2],
                (a+k)/k * cur.vect[0]*cur.vect[2],
                (a-k)/a * cur.vect[0]*cur.vect[1]
            };
            return res;
        },
        [](vect_t cur) {
            vector<vector<long double>> res = {{
                0,
                (k-a)/a * cur.vect[2],
                (k-a)/a * cur.vect[1]
            },{
                (a+k)/k * cur.vect[2],
                0,
                (a+k)/k * cur.vect[0]
            },{
                (a-k)/a * cur.vect[1],
                (a-k)/a * cur.vect[0],
                0
            }};
            return res;
        },
        {{1, 1, 1}, 0}, 1, 0.01, 0.1, 1e-3, 1e-3, 10000
    },{
        [](vect_t cur) {
            vector<long double> res = {
                -cur.vect[0]*cur.vect[1] + sin(cur.t)/cur.t,
                -cur.vect[1]*cur.vect[1] + a*cur.t/(1+cur.t*cur.t)
            };
            return res;
        },
        [](vect_t cur) {
            vector<vector<long double>> res = {{
                -cur.vect[1],
                -cur.vect[0]
            },{
                0,
                -2*cur.vect[1]
            }};
            return res;
        },
        {{10, 22, 9}, 0}, T, 0.01, 0.1, 1e-3, 1e-3, 10000
    }
};

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
    selectedTask = tasks[taskNumber - 1];

    //получаем значения коэффициентов
    switch(taskNumber) {
        case 1:
            cout << "Введите параметр w: ";
            cin >> w;
            a = 2.5 + w / 40;
            break;
        case 2:
            cout << "Введите параметр a: ";
            cin >> a;
            cout << "Введите параметр k: ";
            cin >> k;
            break;
        case 3:
            cout << "Введите параметр a: ";
            cin >> a;
            cout << "Введите параметр k: ";
            cin >> k;
            break;
        case 4:
            cout << "Введите lambda1: ";
            cin >> lambda1;
            cout << "Введите lambda2: ";
            cin >> lambda2;
            cout << "Введите lambda3: ";
            cin >> lambda3;
            cout << "Введите конечное время T: ";
            cin >> T;
            break;
    }

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
            result = eulerNonExplicit(selectedTask.start, selectedTask.maxTime, eps_i, selectedTask.tau_min, selectedTask.tau_max, selectedTask.rhs, selectedTask.rhsJ, selectedTask.snauE1, selectedTask.snauE2, selectedTask.snauMaxIter);
            break;
        case 3:
            result = shikhman(selectedTask.start, selectedTask.maxTime, eps_i, selectedTask.tau_min, selectedTask.tau_max, selectedTask.rhs, selectedTask.rhsJ, selectedTask.snauE1, selectedTask.snauE2, selectedTask.snauMaxIter);
            break;
    }

    int HEIGHT = 800;
    int WIDTH = 1000;
    long double SCALE_W = ((long double)WIDTH) / (result.back().t - result[0].t);
    long double umin = result[0].vect[0], umax = result[0].vect[0];
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].vect.size(); ++j) {
            if(umax < result[i].vect[j])
                umax = result[i].vect[j];
            if(umin > result[i].vect[j])
                umin = result[i].vect[j];
        }
    }
    long double SCALE_H = ((long double)HEIGHT) / (umax - umin);

    SDL_Window* window = SDL_CreateWindow("СОДУ", 0, 0, WIDTH, HEIGHT , 0);
    Uint32* pixels = (Uint32*) SDL_GetWindowSurface(window)->pixels;

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                SDL_Quit();
                return 0;
            }
        }
        //отрисовка поля
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                pixels[i * WIDTH + j] = 0xFFFFFFFF;
            }
        }

        int zeroX = -result[0].t * SCALE_W;
        int zeroY = HEIGHT + umin * SCALE_H;
        int gridX = SCALE_W/2;
        int gridY = SCALE_H/2;
        int curStep = 0;

        if(zeroY >= 0 && zeroY < HEIGHT){
            for (int i = 0; i < WIDTH; ++i) {
                pixels[zeroY * WIDTH + i] = 0x0;
            }
        }
        while (true){
            curStep += gridY;
            bool stop = true;
            int r = zeroY + curStep;
            int l = zeroY - curStep;
            if(r >= 0 && r < HEIGHT){
                stop = false;
                for (int i = 0; i < WIDTH; ++i) {
                    pixels[r * WIDTH + i] = 0x88888888;
                }
            }
            if(l >= 0 && l < HEIGHT){
                stop = false;
                for (int i = 0; i < WIDTH; ++i) {
                    pixels[l * WIDTH + i] = 0x88888888;
                }
            }
            if (stop) break;
        }

        curStep = 0;
        if(zeroX >= 0 && zeroX < WIDTH){
            for (int i = 0; i < HEIGHT; ++i) {
                pixels[i * WIDTH + zeroX] = 0x0;
            }
        }
        while (true){
            curStep += gridX;
            bool stop = true;
            int r = zeroX + curStep;
            int l = zeroX - curStep;
            if(r >= 0 && r < WIDTH){
                stop = false;
                for (int i = 0; i < HEIGHT; ++i) {
                    pixels[i * WIDTH + r] = 0x88888888;
                }
            }
            if(l >= 0 && l < WIDTH){
                stop = false;
                for (int i = 0; i < HEIGHT; ++i) {
                    pixels[i * WIDTH + l] = 0x88888888;
                }
            }
            if (stop) break;
        }

        //отрисовка функций
        for (int i = 0; i < result.size(); ++i) {
            for (int j = 0; j < result[i].vect.size(); ++j) {
                long double x = (result[i].t - result[0].t) * SCALE_W;
                long double y = HEIGHT - (result[i].vect[j] - umin) * SCALE_H;

                for (int l = -1; l < 2; ++l) {
                    for (int m = -1; m < 2; ++m) {
                        if((int)x+l >= 0 && (int)x+l < WIDTH && (int)y+m >= 0 && (int)y+m < HEIGHT)
                            pixels[((int)y+m) * WIDTH + (int)x+l] = 0x0;
                    }
                }
            }
        }




        SDL_UpdateWindowSurface(window);
    }

    return 0;
}
