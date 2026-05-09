#include <iostream>
#include <cmath>
#include "build/libs/sdl2/include/SDL.h"
#include "include/SLAU.h"

using namespace std;

int main(int argc, char** argv) {

    auto fi = [](long double x){
        return cos(x);
    };

    auto g1 = [](long double t){
        return cos(-3);
    };

    auto g2 = [](long double t){
        return cos(3);
    };

    vector<vect_t> result = explicitSchema(fi, g1, g2, 1, 0, 10, -3, 3, 100);

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

    cout << SCALE_W << endl;
    cout << SCALE_H << endl;
    cout << umin << endl;
    cout << umax << endl;

    SDL_Window* window = SDL_CreateWindow("ДУЧП", 0, 0, WIDTH, HEIGHT , 0);
    Uint32* pixels = (Uint32*) SDL_GetWindowSurface(window)->pixels;

    int curTimeLayer = 0;
    while (true) {
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

        //отрисовка функций
        for (int j = 0; j < result[curTimeLayer].X.size(); ++j) {
            long double x = (result[curTimeLayer].X[j] - result[curTimeLayer].X[0]) * SCALE_W;
            long double y = HEIGHT - (result[curTimeLayer].U[j] - umin) * SCALE_H;

            for (int l = -1; l < 2; ++l) {
                for (int m = -1; m < 2; ++m) {
                    if((int)x+l >= 0 && (int)x+l < WIDTH && (int)y+m >= 0 && (int)y+m < HEIGHT)
                        pixels[((int)y+m) * WIDTH + (int)x+l] = 0x0;
                }
            }
        }
        curTimeLayer++;
        SDL_Delay(1);




        SDL_UpdateWindowSurface(window);
    }

    return 0;
}
