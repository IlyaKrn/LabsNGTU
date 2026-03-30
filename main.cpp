#include <iostream>
#include <cmath>
#include "build/libs/sdl2/include/SDL.h"
#include "include/SLAU.h"

using namespace std;

const int COLOR_WHITE = 2147483647;
const int COLOR_GRAY = 1002159035;
const int COLOR_RED = 16711680;
const int COLOR_BLACK = 0;

int main(int argc, char** argv) {
    //открываем окно и получаем матрицу пикселей
    int HEIGHT = 1000;
    int WIDTH = 1000;
    int SCALE = 250;
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
        auto u1 = eulerExplicit({{0.1}, 0}, 90, 0.01, 0.01, [](vect_t cur){
            vector<long double> res = {cur.vect[0]*(2-cur.vect[0]*0.1)};
            return res;
        });

        auto u2 = eulerNonExplicit({{0.1}, 0}, 90, 0.01, 0.01, 1, [](vect_t cur){
            vector<long double> res = {cur.vect[0]*(2-cur.vect[0]*0.1)};
            return res;
        }, [](vect_t cur){
            vector<vector<long double>> res = {{2-2*cur.vect[0]*0.1}};
            return res;
        });

        auto u3 = shikhman({{0.1}, 0}, 90, 0.01, 0.01, 1, [](vect_t cur){
            vector<long double> res = {cur.vect[0]*(2-cur.vect[0]*0.1)};
            return res;
        }, [](vect_t cur){
            vector<vector<long double>> res = {{2-2*cur.vect[0]*0.1}};
            return res;
        });

        for (int i = 0; i < u1.size(); ++i) {
            if(u1[i].vect[0] >= 0 && u1[i].vect[0] < HEIGHT)
                pixels[((int)(u1[i].vect[0]*30)) * WIDTH + (int)(u1[i].t*9)] = COLOR_WHITE;
        }

        for (int i = 0; i < u2.size(); ++i) {
            if(u2[i].vect[0] >= 0 && u2[i].vect[0] < HEIGHT)
                pixels[((int)(u2[i].vect[0]*30)) * WIDTH + (int)(u2[i].t*9)] = COLOR_WHITE;
        }

        for (int i = 0; i < u3.size(); ++i) {
            if(u3[i].vect[0] >= 0 && u3[i].vect[0] < HEIGHT)
                pixels[((int)(u3[i].vect[0]*30)) * WIDTH + (int)(u3[i].t*9)] = COLOR_RED;
        }



        SDL_UpdateWindowSurface(window);
    }


}