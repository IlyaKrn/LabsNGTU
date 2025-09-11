#include <iostream>
#include <unordered_map>
#include "include/TaylorSeries.h"
#include "SDL.h"

using namespace std;

int main(int argc, char** argv) {

    //размеры окна и размер клетки
    int HEIGHT = 300;
    int WIDTH = 300;
    int SCALE = 15;


    //открываем окно и получаем матрицу пикселей
    SDL_Window* window = SDL_CreateWindow("Численные методы лаб. 0", 0, 0, HEIGHT, WIDTH , 0);
    Uint32* pixels = (Uint32*) SDL_GetWindowSurface(window)->pixels;


    //регулируемые переменные
    int members = 1;
    float k = 1;
    float x0 = 0;
    float EPS = 0.1;

    //рисуем изображение и считываем действия пользователя
    while (true){
        //читаем события
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            k += 0.05;
                            break;
                        case SDLK_DOWN:
                            k -= 0.05;
                            break;
                        case SDLK_RIGHT:
                            x0 += 0.1;
                            break;
                        case SDLK_LEFT:
                            x0 -= 0.1;
                            break;
                        case SDLK_0: members = 1;
                            break;
                        case SDLK_1: members = 2;
                            break;
                        case SDLK_2: members = 3;
                            break;
                        case SDLK_3: members = 4;
                            break;
                        case SDLK_4: members = 5;
                            break;
                        case SDLK_5: members = 6;
                            break;
                        case SDLK_6: members = 7;
                            break;
                        case SDLK_7: members = 8;
                            break;
                        case SDLK_8: members = 9;
                            break;
                        case SDLK_9: members = 10;
                            break;
                    }
                    break;
                case SDL_QUIT:
                    SDL_Quit();
                    return 0;
            }
            cout << "members: " << members << endl;
            cout << "k: " << k << endl;
            cout << "x0: " << x0 << endl;
            cout << endl;
        }

        //отрисовка функций
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                //считаем координаты с поправкой на смещение осей и переворот
                float fixX = x - WIDTH/2;
                float fixY = - y + HEIGHT/2;
                //вычисляем значения функций для текущего x
                float funcVal = sin(k * fixX / (float) SCALE) * SCALE;
                float taylorVal = taylorSerial(fixX / (float) SCALE, x0, k, members) * SCALE;

                //красим пиксель в нужный цвет
                pixels[y * WIDTH + x] =
                        fixX == 0 ||
                        fixY == 0 ||
                        (fixX + 2 > x0 * SCALE && fixX - 2 < x0 * SCALE) ||
                        (fixY + 2 > funcVal && fixY - 2 < funcVal) ||
                        (fixY + 2 > taylorVal && fixY - 2 < taylorVal)
                        ? (abs(funcVal - taylorVal) < EPS * SCALE ? 555555 : 0) : 2147483647;

            }
        }
        SDL_UpdateWindowSurface(window);
    }

}