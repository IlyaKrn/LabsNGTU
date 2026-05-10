#include <iostream>
#include <cmath>
#include "build/libs/sdl2/include/SDL.h"
#include "include/SLAU.h"

using namespace std;

int main(int argc, char** argv) {

    auto fi = [](long double x){
        return x*x*x*(1-x);
    };

    auto g1 = [](long double t){
        return 0;
    };

    auto g2 = [](long double t){
        return 0;
    };

    auto f = [](long double x, long double t){
        return 0;
    };

    vector<vect_t> result = explicitSchema(fi, f, g1, g2, 1, 0, 2, 0, 2, 1000);

    int HEIGHT = 800;
    int WIDTH = 1000;
    long double SCALE_W = ((long double)WIDTH) / (result[0].X.back() - result[0].X[0]);
    long double umin = result[0].U[0], umax = result[0].U[0];
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].U.size(); ++j) {
            if(umax < result[i].U[j])
                umax = result[i].U[j];
            if(umin > result[i].U[j])
                umin = result[i].U[j];
        }
    }
    long double SCALE_H = ((long double)HEIGHT) / (umax - umin);

    // Пиксельные координаты центра мировых координат
    int centerX = ((result[0].X[0] + result[0].X.back()) / 2 - result[0].X[0]) * SCALE_W;
    int centerY = HEIGHT - ((umin + umax) / 2 - umin) * SCALE_H;

    SDL_Window* window = SDL_CreateWindow("ДУЧП", 0, 0, WIDTH, HEIGHT , 0);
    Uint32* pixels = (Uint32*) SDL_GetWindowSurface(window)->pixels;

    int curTimeLayer = 0;
    while (curTimeLayer < result.size()) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                SDL_Quit();
                return 0;
            }
        }
        //отрисовка поля
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                pixels[i * WIDTH + j] = 0xFFFFFFFF;
            }
        }


        //оси координат
        for (int j = 0; j < HEIGHT; ++j) {
            pixels[j * WIDTH + centerX] = 0x000000;
        }
        for (int j = 0; j < WIDTH; ++j) {
            pixels[centerY * WIDTH + j] = 0x000000;
        }

        //стрелки
        for (int i = 0; i < 40; ++i) {
            pixels[(centerY + i) * WIDTH + WIDTH - i] = 0x000000;
            pixels[(centerY - i) * WIDTH + WIDTH - i] = 0x000000;
        }

        //стрелки
        for (int i = 0; i < 40; ++i) {
            pixels[i * WIDTH + WIDTH - centerX + i] = 0x000000;
            pixels[i * WIDTH + WIDTH - centerX - i] = 0x000000;
        }

        //буква X (снизу под стрелкой OX, отступ 10 пикселей)
        int xPos = WIDTH - 80;
        int yPos = centerY + 80;
        for (int i = -20; i <= 20; i++) {
            if(xPos + i >= 0 && xPos + i < WIDTH && yPos + i >= 0 && yPos + i < HEIGHT)
                pixels[(yPos + i) * WIDTH + (xPos + i)] = 0x000000;
            if(xPos + i >= 0 && xPos + i < WIDTH && yPos - i >= 0 && yPos - i < HEIGHT)
                pixels[(yPos - i) * WIDTH + (xPos + i)] = 0x000000;
        }

        //буква U (справа от края стрелки OY, отступ 10 пикселей)
        int uX = WIDTH - centerX + 50;
        int uY = 50;
        for (int i = 0; i <= 40; i++) {
            if(uY + i >= 0 && uY + i < HEIGHT) {
                if(uX >= 0 && uX < WIDTH)
                    pixels[(uY + i) * WIDTH + uX] = 0x000000;
                if(uX + 30 >= 0 && uX + 30 < WIDTH)
                    pixels[(uY + i) * WIDTH + (uX + 30)] = 0x000000;
            }
        }
        for (int i = 0; i <= 30; i++) {
            if(uY + 40 >= 0 && uY + 40 < HEIGHT && uX + i >= 0 && uX + i < WIDTH)
                pixels[(uY + 40) * WIDTH + (uX + i)] = 0x000000;
        }

        //сетка
        for (int i = centerX+SCALE_W; i < WIDTH; i+= SCALE_W) {
            for (int j = 0; j < HEIGHT; ++j) {
                pixels[j * WIDTH + i] = 0xAAAAAA;
            }
        }
        for (int i = centerX-SCALE_W; i >= 0; i-= SCALE_W) {
            for (int j = 0; j < HEIGHT; ++j) {
                pixels[j * WIDTH + i] = 0xAAAAAA;
            }
        }
        for (int i = centerY+SCALE_H; i < HEIGHT; i+= SCALE_H) {
            for (int j = 0; j < WIDTH; ++j) {
                pixels[i * WIDTH + j] = 0xAAAAAA;
            }
        }
        for (int i = centerY-SCALE_H; i >= 0; i-= SCALE_H) {
            for (int j = 0; j < WIDTH; ++j) {
                pixels[i * WIDTH + j] = 0xAAAAAA;
            }
        }

        //отрисовка функций
        for (int j = 1; j < result[curTimeLayer].X.size(); ++j) {
            int x = (result[curTimeLayer].X[j] - result[curTimeLayer].X[0]) * SCALE_W;
            int y = HEIGHT - (result[curTimeLayer].U[j] - umin) * SCALE_H;
            int lastX = (result[curTimeLayer].X[j-1] - result[curTimeLayer].X[0]) * SCALE_W;
            int lastY = HEIGHT - (result[curTimeLayer].U[j-1] - umin) * SCALE_H;

            for (int l = -1; l < 2; ++l) {
                for (int m = -1; m < 2; ++m) {
                    //отрисовываем линию к предыдущей точке
                    for (int xl = lastX; xl < x; ++xl) {
                        int yl = lastY + (lastX-xl)*(lastY-y)/(x-lastX);
                        if((int)xl+l >= 0 && (int)xl+l < WIDTH && (int)yl+m >= 0 && (int)yl+m < HEIGHT)
                            pixels[((int)yl+m) * WIDTH + (int)xl+l] = 0x0;
                    }

                }
            }
        }

        curTimeLayer++;
        SDL_Delay(10);




        SDL_UpdateWindowSurface(window);
    }

    return 0;
}