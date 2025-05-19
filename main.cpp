#include "include/FieldMatrix.h"
#include "include/GameLogic.h"
#include <iostream>
#include "SDL.h"

using namespace std;

void printField(FieldMatrix* fieldMatrix, SDL_Window* window, int height, int width, int pixelSize){
    unsigned char* pixels = (unsigned char*)SDL_GetWindowSurface(window)->pixels;
    for (int startX = 0; startX < width * pixelSize; startX += pixelSize) {
        for (int startY = 0; startY < height * pixelSize; startY += pixelSize) {
            for (int pxX = 0; pxX < pixelSize; pxX++) {
                for (int pxY = 0; pxY < pixelSize; pxY++) {

                    bool isFill = false;

                    if (pxX < 4 || pxY < 4) {
                        isFill = true;
                    }
                    else if (fieldMatrix->getPtr(startX / pixelSize, startY / pixelSize) != nullptr) {
                        cell* curCell = fieldMatrix->getPtr(startX / pixelSize, startY / pixelSize);
                        switch (curCell->state) {
                            case WHITE:
                                if ((pxX >= 10 && pxX < pixelSize - 6) && (pxY >= 10 && pxY < pixelSize - 6))
                                    isFill = true;
                                if((pxX >= 16 && pxX < pixelSize - 12) && (pxY >= 16 && pxY < pixelSize - 12))
                                    isFill = false;
                                break;
                            case BLACK:
                                if ((pxX >= 10 && pxX < pixelSize - 6) && (pxY >= 10 && pxY < pixelSize - 6))
                                    isFill = true;
                                break;
                            default:
                                isFill = false;
                        }
                        if (curCell->isLine){

                        }
                    }

                    pixels[4 * ((startY + pxY) * width * pixelSize + (startX + pxX)) + 0] = isFill ? 0 : 255;
                    pixels[4 * ((startY + pxY) * width * pixelSize + (startX + pxX)) + 1] = isFill ? 0 : 255;
                    pixels[4 * ((startY + pxY) * width * pixelSize + (startX + pxX)) + 2] = isFill ? 0 : 255;
                    pixels[4 * ((startY + pxY) * width * pixelSize + (startX + pxX)) + 3] = 255;

                }
            }
        }
    }
    SDL_UpdateWindowSurface(window);

}

int main() {

    int height = 6;
    int width = 6;
    int pxSize = 50;

    SDL_Window* window = SDL_CreateWindow("Ожерелье", 0, 0, height * pxSize, width * pxSize, 0);

    FieldMatrix* field = new FieldMatrix();
    field->insert(cell(BLACK, RIGHT, RIGHT, false), 0, 0);
    field->insert(cell(WHITE, RIGHT, RIGHT, false), 2, 2);
    field->insert(cell(BLACK, RIGHT, RIGHT, false), 4, 4);

    printField(field, window, height, width, pxSize);

//    GameLogic gl(field, 5, 5);
//    gl.getSolution();

    while (true){}

    delete field;
    return 0;
}