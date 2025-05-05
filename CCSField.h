#pragma once

enum cellState {
    WHITE, BLACK, NONE
};

enum cellSide {
    LEFT, RIGHT, TOP, BOTTOM
};

struct cell{
    cellState state;
    cellState lineIn;
    cellState lineOut;
    bool isLine;
};

class CCSField {
private:

    LinkedList<cell> values;
    LinkedList<int> LI;
    LinkedList<int> LJ;


};