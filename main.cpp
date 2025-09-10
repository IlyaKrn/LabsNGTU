#include <iostream>
#include <unordered_map>
#include "include/TaylorSeries.h"
#include "SDL.h"

using namespace std;

int main(int argc, char** argv) {

    //размеры окна и размер клетки
    int HEIGHT = 1000;
    int WIDTH = 1000;
    int SCALE = 50;


    //открываем окно и получаем матрицу пикселей
    SDL_Window* window = SDL_CreateWindow("Численные методы лаб. 0", 0, 0, HEIGHT, WIDTH , 0);
    Uint32* pixels = (Uint32*) SDL_GetWindowSurface(window)->pixels;


    //отрисовываем изображение и считываем действия пользователя
    while (true){
        //читаем события
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    break;
                case SDL_QUIT:
                    SDL_Quit();
                    return 0;
            }
        }

        //отрисовка функций
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                //считаем координаты с поправкой на смещение осей и переворот
                int fixX = x - WIDTH/2;
                int fixY = - y + HEIGHT/2;
                //вычисляем значения функций для текущего x с поправкой на перевернутую ось OY и смещение осей
                float funcVal = sin((float) fixX / SCALE) * SCALE;
                float taylorVal = taylorSerial((float) fixX / SCALE, 0, 1, 10) * SCALE;

                //красим пиксель в нужный цвет
                pixels[y * WIDTH + x] =
                        fixX == 0 ||
                        fixY == 0 ||
                        (fixY + 2 > funcVal && fixY - 2 < funcVal) ||
                        (fixY + 2 > taylorVal && fixY - 2 < taylorVal)
                        ? 0 : 2147483647;

            }
        }
        SDL_UpdateWindowSurface(window);
    }

}