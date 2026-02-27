#include "build/libs/sdl2/include/SDL.h"
#include "include/SLAU.h"
#include <iostream>
#include <cmath>

using namespace std;

const int COLOR_WHITE = 2147483647;
const int COLOR_GRAY = 1002159035;
const int COLOR_RED = 16711680;
const int COLOR_BLACK = 0;

int main(int argc, char** argv) {


    auto m = solveSLAU(getInterpolationMatrix(1000, 1, 0, 0, 0, [](long double x) -> long double {
        return x == 500 || x == 50 ? 1 : (x == 100 ? -10 : 0);
    }));

    //размеры окна и размер клетки
    int HEIGHT = 1000;
    int WIDTH = 1000;
    int SCALE = 100;

    //открываем окно и получаем матрицу пикселей
    SDL_Window* window = SDL_CreateWindow("ГРАФИК ТЕМПЕРАТУРЫ", 0, 0, HEIGHT, WIDTH , 0);
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
        for (int i = 0; i < HEIGHT * WIDTH; ++i) {
            pixels[i] = COLOR_WHITE;
        }
        for (int i = 0; i < WIDTH; ++i) {
            pixels[HEIGHT / 2 * WIDTH + i] = COLOR_BLACK;
        }

        for (int i = 0; i < m.size(); ++i) {
            int y = -m[i] + HEIGHT / 2;
            if(y >= 0 && y < HEIGHT && i < WIDTH){
                pixels[y * WIDTH + i] = COLOR_BLACK;
            }
            else{
                cout << m[i] << endl;
            }
        }

        SDL_UpdateWindowSurface(window);
    }


}