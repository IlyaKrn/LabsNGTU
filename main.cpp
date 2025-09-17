#include <iostream>
#include <unordered_map>
#include "include/TaylorSeries.h"
#include "SDL.h"

using namespace std;

int main(int argc, char** argv) {

    int COLOR_WHITE = 2147483647;
    int COLOR_GRAY = 1002159035;
    int COLOR_BLACK = 0;

    //размеры окна и размер клетки
    int HEIGHT = 1000;
    int WIDTH = 1000;
    int SCALE = 50;

    //перезаписываем параметры окна из аргументов программы
    if(argc == 3){
        try{ HEIGHT = stoi(argv[0]); } catch(...) {}
        try{ WIDTH = stoi(argv[1]);  } catch(...) {}
        try{ SCALE = stoi(argv[2]);  } catch(...) {}
    }
    cout << "field: " << HEIGHT << "x" << WIDTH << "\n1 cell= " << SCALE << endl;

    //открываем окно и получаем матрицу пикселей
    SDL_Window* window = SDL_CreateWindow("Численные методы лаб. 0", 0, 0, HEIGHT, WIDTH , 0);
    Uint32* pixels = (Uint32*) SDL_GetWindowSurface(window)->pixels;

    //регулируемые значения
    int members = 1;        //количество членов частичной суммы ряда Тейлора (1-10)
    float k = 1;            //параметр в формуле
    float x0 = 0;           //точка, в которой раскладываем функцию
    float EPS = 0.1;        //максимальная разница между значениями функции и частичной суммы ряда Тейлора

    //массивы значений функции и частичной суммы ряда Тейлора для оптимизации отрисовки
    float* funcVals = new float[WIDTH];
    float* taylorVals = new float[WIDTH];

    //рисуем белый фон на поле
    for (int i = 0; i < HEIGHT * WIDTH; ++i) {
        pixels[i] = COLOR_WHITE;
    }

    //рисуем графики и считываем действия пользователя
    while (true){
        //читаем действия пользователя
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        //изменяем параметр k (стрелки вверх-вниз)
                        case SDLK_UP:       k += 0.05; break;
                        case SDLK_DOWN:     k -= 0.05; break;
                        //изменяем точку для разложения в ряд Тейлора (стрелки вправо-влево)
                        case SDLK_RIGHT:    x0 += 0.1; break;
                        case SDLK_LEFT:     x0 -= 0.1; break;
                        //меняем количество членов частичной суммы ряда Тейлора (цифры 0-9)
                        case SDLK_0: members = 1;  break;
                        case SDLK_1: members = 2;  break;
                        case SDLK_2: members = 3;  break;
                        case SDLK_3: members = 4;  break;
                        case SDLK_4: members = 5;  break;
                        case SDLK_5: members = 6;  break;
                        case SDLK_6: members = 7;  break;
                        case SDLK_7: members = 8;  break;
                        case SDLK_8: members = 9;  break;
                        case SDLK_9: members = 10; break;
                    }
                    break;
                //завершение программы при закрытии окна
                case SDL_QUIT:
                    SDL_Quit();
                    return 0;
            }
            //выводим значения переменных в консоль
            cout << "================\nmembers: " << members << "\nk: " << k << "\nx0: " << x0 << endl;
        }

        //рисуем клетки
        for (int i = 1; i < HEIGHT / 2 - 1; ++i) {
            if(i % SCALE == 0) {
                for (int j = 0; j < WIDTH; ++j) {
                    pixels[(i + HEIGHT / 2) * WIDTH + j] = COLOR_GRAY;
                    pixels[(-i + HEIGHT / 2) * WIDTH + j] = COLOR_GRAY;
                }
            }
        }
        for (int i = 1; i < WIDTH / 2 - 1; ++i) {
            if(i % SCALE == 0) {
                for (int j = 0; j < HEIGHT; ++j) {
                    pixels[j * WIDTH + ((i + WIDTH / 2 - 1))] = COLOR_GRAY;
                    pixels[j * WIDTH + ((-i + WIDTH / 2 - 1))] = COLOR_GRAY;
                }
            }
        }

        //рисуем оси
        for (int i = 0; i < HEIGHT; ++i) {
            pixels[i * WIDTH + WIDTH / 2] = COLOR_BLACK;
        }
        for (int i = 0; i < WIDTH; ++i) {
            pixels[(HEIGHT / 2 - 1) * WIDTH + i] = COLOR_BLACK;
        }


        //отрисовка графиков
        for (int x = 0; x < WIDTH; ++x) {
            //считаем текущую координату x с поправкой на смещение осей
            float curX = x - WIDTH / 2;

            //вычисляем значения функции и частичной суммы ряда Тейлора для текущего x с поправкой на смещение и переворот осей
            float funcVal = - sin(k * curX / SCALE) * SCALE + HEIGHT / 2;
            float taylorVal = - taylorSerial(curX / SCALE, x0, k, members) * SCALE + HEIGHT / 2;

            //сравниваем новое значение функций с предыдущими и удаляем его при необходимости
            if(funcVal != funcVals[x])
                pixels[((int)funcVals[x]) * WIDTH + x] = COLOR_WHITE;
            if(taylorVal != taylorVals[x])
                pixels[((int)taylorVals[x]) * WIDTH + x] = COLOR_WHITE;

            //чистим промежуток с предыдущей допустимой погрешностью
            if(abs(funcVals[x] - taylorVals[x]) <= EPS * SCALE){
                for (int i = min(funcVals[x], taylorVals[x]) + 1; i < max(funcVals[x], taylorVals[x]); ++i) {
                    pixels[i * WIDTH + x] = COLOR_WHITE;
                }
            }

            //рисуем новый промежуток с допустимой погрешностью
            if(abs(funcVal - taylorVal) <= EPS * SCALE){
                for (int i = min(funcVal, taylorVal) + 1; i < max(funcVal, taylorVal); ++i) {
                    pixels[i * WIDTH + x] = COLOR_BLACK;
                }
            }

            //рисуем функции
            if(funcVal >= 0 && funcVal < HEIGHT){
                pixels[((int) funcVal) * WIDTH + x] = COLOR_BLACK;
                funcVals[x] = funcVal;
            }
            if(taylorVal >= 0 && taylorVal < HEIGHT){
                pixels[((int) taylorVal) * WIDTH + x] = COLOR_BLACK;
                taylorVals[x] = taylorVal;
            }

        }
        SDL_UpdateWindowSurface(window);
    }

}