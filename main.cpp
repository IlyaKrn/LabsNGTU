#include <iostream>
#include <cmath>
#include "build/libs/sdl2/include/SDL.h"
#include "include/SLAU.h"

using namespace std;

void drawPoint(int x, int y, int mx, int my, Uint32* pixels){
    int r = 15;
    for (int i = -r; i < r; ++i) {
        for (int j = -r; j < r; ++j) {
            if(y+i >= 0 && y+i < my && x+j >= 0 && x+j < mx && sqrt(i*i + j*j) < r && (sqrt(i*i + j*j) > r*0.7 || sqrt(i*i + j*j) < r*0.5))
                pixels[(y+i) * mx + x+j] = 0;
        }
    }
}

int main(int argc, char** argv) {

    //вычисляем точки
    vector<long double> start1 = {1, -1};
    vector<long double> start2 = {-1, 1};
    vector<long double> appr1 = solveSNAU(start1);
    vector<long double> appr2 = solveSNAU(start2);

    //размеры окна и размер клетки
    int HEIGHT = 1000;
    int WIDTH = 1000;
    int SCALE = 250;


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
                long double x = (long double) (j - WIDTH / 2) / SCALE;
                long double y = (long double) -(i - HEIGHT / 2) / SCALE;
                long double f1 = cos(0.4 * y + x * x) + y * y + x * x - 1.6;
                long double f2 = 1.5 * x * x - ((y * y) / 0.36) - 1;

                if(abs(f1) < 0.004 || abs(f2) < 0.015)
                    pixels[i * WIDTH + j] = 0;
                else
                    pixels[i * WIDTH + j] = 2147483647;
            }
        }

        //отрисовка точек
        drawPoint(start1[0] * SCALE + WIDTH / 2, -start1[1] * SCALE + HEIGHT / 2, WIDTH, HEIGHT, pixels);
        drawPoint(start2[0] * SCALE + WIDTH / 2, -start2[1] * SCALE + HEIGHT / 2, WIDTH, HEIGHT, pixels);
        drawPoint(appr1[0] * SCALE + WIDTH / 2, -appr1[1] * SCALE + HEIGHT / 2, WIDTH, HEIGHT, pixels);
        drawPoint(appr2[0] * SCALE + WIDTH / 2, -appr2[1] * SCALE + HEIGHT / 2, WIDTH, HEIGHT, pixels);
        SDL_UpdateWindowSurface(window);
    }


}