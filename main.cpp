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
        auto u = eulerExplicit({{0.1}, 0}, 90, 0.01, 0.01, [](vect_t cur){
            vector<long double> res = {cur.vect[0]*(2-cur.vect[0]*0.1)};
            return res;
        });

        for (int i = 0; i < u.size(); ++i) {
            if(u[i].vect[0] >= 0 && u[i].vect[0] < HEIGHT)
                pixels[((int)(u[i].vect[0]*30)) * WIDTH + i] = COLOR_WHITE;
            pixels[((int)((       1/(9.95/pow(2.7182818284590452353602874713527, i*0.2)+1)          ) * 600.0)) * WIDTH + i + 20-3] = COLOR_RED;
            pixels[((int)(20*10)) * WIDTH + i] = COLOR_WHITE;
        }



        SDL_UpdateWindowSurface(window);
    }


}