#include <iostream>
#include <cmath>
#include "build/libs/sdl2/include/SDL.h"
#include "include/SLAU.h"

using namespace std;

const int COLOR_WHITE = 2147483647;
const int COLOR_GRAY = 1002159035;
const int COLOR_RED = 16711680;
const int COLOR_BLACK = 0;

//рисуем клетки и оси
void drawField(Uint32* pixels, int h, int w, int s){
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            pixels[i * w + j] = COLOR_WHITE;
        }
    }

    for (int i = 0; i < h / 2 - 1; ++i) {
        if(i % s == 0) {
            for (int j = 0; j < w; ++j) {
                pixels[(i + h / 2) * w + j] = COLOR_GRAY;
                pixels[(-i + h / 2) * w + j] = COLOR_GRAY;
            }
        }
    }
    for (int i = 0; i < w / 2 - 1; ++i) {
        if(i % s == 0) {
            for (int j = 0; j < h; ++j) {
                pixels[j * w + ((i + w / 2 - 1))] = COLOR_GRAY;
                pixels[j * w + ((-i + w / 2 - 1))] = COLOR_GRAY;
            }
        }
    }
    for (int k = 0; k < 2; ++k) {
        for (int i = 0; i < w; ++i) {
            pixels[(h / 2 + k) * w + i] = COLOR_BLACK;
        }
        for (int i = 0; i < h; ++i) {
            pixels[i * w + (w / 2 + k)] = COLOR_BLACK;
        }
    }

    //рисуем стрелки
    for (int k = -1; k < 2; ++k) {
        for (int i = 0; i < s / 16; i++) {
            pixels[(h / 2 + i + k) * w + (w - i)] = COLOR_BLACK;
            pixels[(h / 2 - i + k) * w + (w - i)] = COLOR_BLACK;
            pixels[(i) * w + (w / 2 + i + k)] = COLOR_BLACK;
            pixels[(i) * w + (w / 2 - i + k)] = COLOR_BLACK;
        }
    }

    //рисуем буквы
    int size = s / 6;
    int x1x = w - size - size / 5;
    int x1y = h / 2 + size / 5 + size / 4;
    int x2x = w / 2 - size - size / 10 - size / 4 - size / 5 - size / 4;
    int x2y = size / 5;

    for(int l = 0; l  < 2; l++){
        for (int k = 0; k < 2; ++k) {
            int x1_x = x1x + k;
            int x2_x = x2x + k;
            int x1_y = x1y + l;
            int x2_y = x2y + l;

            for (int i = 0; i < size; i++) {
                pixels[(x1_y + i) * w + (x1_x + i)] = COLOR_BLACK;
                pixels[(x1_y + i) * w + (x1_x + size - 1 - i)] = COLOR_BLACK;
                if(i >= size / 2){
                    pixels[(x1_y + i) * w + x1_x + size + size / 10] = COLOR_BLACK;
                }
            }
            for (int i = 0; i < size; i++) {
                pixels[(x2_y + i) * w + (x2_x + i)] = COLOR_BLACK;
                pixels[(x2_y + i) * w + (x2_x + size - 1 - i)] = COLOR_BLACK;
                if(i >= size - size / 4)
                    pixels[(x2_y + i) * w + x2_x + size + size / 10] = COLOR_BLACK;
                else if(i >= size / 2)
                    pixels[(x2_y + i) * w + x2_x + size + size / 10 + size / 4] = COLOR_BLACK;
                if(i < size / 4 ){
                    pixels[(x2_y + size / 2) * w + x2_x + size + size / 10 + i] = COLOR_BLACK;
                    pixels[(x2_y + size * 3 / 4) * w + x2_x + size + size / 10 + i] = COLOR_BLACK;
                    pixels[(x2_y - 1 + size) * w + x2_x + size + size / 10 + i] = COLOR_BLACK;
                }
            }
        }
    }
}

void drawPoint(int x, int y, int mx, int my, Uint32* pixels){
    int r = 15;
    for (int i = -r; i < r; ++i) {
        for (int j = -r; j < r; ++j) {
            if(y+i >= 0 && y+i < my && x+j >= 0 && x+j < mx && sqrt(i*i + j*j) < r && (sqrt(i*i + j*j) > r*0.7 || sqrt(i*i + j*j) < r*0.5))
                pixels[(y+i) * mx + x+j] = COLOR_RED;
        }
    }
}

int main(int argc, char** argv) {

    cout << "Исходные уравнения:" << endl;
    cout << "cos(0.4 * x2 + x1^2) + x2^2 + x1^2 - 1.6" << endl;
    cout << "1.5 * x1^2 - (x2^2) / 0.36 - 1" << endl;

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

    //рисуем поле
    drawField(pixels, HEIGHT, WIDTH, SCALE);
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
                    pixels[i * WIDTH + j] = COLOR_BLACK;
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