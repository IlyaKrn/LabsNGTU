#include <iostream>
#include <unordered_map>
#include "include/TaylorSeries.h"
#include "SDL.h"

using namespace std;

int main() {

    //размеры окна
    int HEIGHT = 600;
    int WIDTH = 600;
    //окно
    SDL_Window* window = SDL_CreateWindow("Численные методы лаб. 1", 0, 0, HEIGHT, WIDTH , 0);
    Uint32* pixels = (Uint32*) SDL_GetWindowSurface(window)->pixels;


    //отрисовываем функции
    while (true){
        //читаем события
//        int x;
//        int y;
//        SDL_Event event;
//        while (SDL_PollEvent(&event)) {
//            switch (event.type) {
//                case SDL_MOUSEBUTTONDOWN:
//                    break;
//                case SDL_QUIT:
//                    SDL_Quit();
//                    return 0;
//            }
//        }
        //отрисовка функций
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                double funcVal = -100*sin(j*3.14*2/WIDTH) + HEIGHT/2;
                double taylorVal = -100*taylorSerial(j*3.14*2/WIDTH, 3.14, 1, 5) + HEIGHT/2;
                pixels[i * WIDTH + j] = (funcVal + 1 > i && funcVal - 1 < i) || i == HEIGHT/2 || j == WIDTH/2 || (taylorVal + 2 > i && taylorVal - 2 < i) || abs(taylorVal - funcVal) > 10? 0 : 2147483647;
            }
        }
        SDL_UpdateWindowSurface(window);
    }

}