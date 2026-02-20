#include <iostream>
#include <cmath>
#include "build/libs/sdl2/include/SDL.h"
#include "include/SLAU.h"

using namespace std;

int main(int argc, char** argv) {

    //вычисляем точки
    vector<long double> start1 = {1, -1};
    vector<long double> start2 = {-1, 1};
    vector<long double> appr1 = solveSNAU(start1);
    vector<long double> appr2 = solveSNAU(start2);

    //размеры окна и размер клетки
    int HEIGHT = 1000;
    int WIDTH = 1000;
    int SCALE = 50;


    //открываем окно и получаем матрицу пикселей
    SDL_Window* window = SDL_CreateWindow("СНАУ", 0, 0, HEIGHT, WIDTH , 0);
    Uint32* pixels = (Uint32*) SDL_GetWindowSurface(window)->pixels;


    //отрисовываем функции
    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                SDL_Quit();
                return 0;
            }
        }

        //отрисовка функций
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                pixels[i * WIDTH + j] = 125454;
            }
        }
        SDL_UpdateWindowSurface(window);
    }


}