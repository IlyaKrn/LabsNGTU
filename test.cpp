#include <chrono>
#include "CCSMatrix.h"

using namespace std;

int unitTest(){
    LinkedList<LinkedList<int>> matrixTemplate = LinkedList<LinkedList<int>>();
    static int evenCount = 0;
    for (int i = 0; i < 10; ++i) {
        LinkedList<int> row = LinkedList<int>();
        for (int j = 0; j < 10; ++j) {
            if((i + j) % 2 == 0) {
                row.pushBack(2);
                evenCount++;
            } else{
                row.pushBack(0);
            }
        }
        matrixTemplate.pushBack(row);
    }


    CCSMatrix<int> matrix = CCSMatrix<int>(matrixTemplate, 10, 10, 0);

    cout.setstate(std::ios_base::failbit);
    static int allCount = evenCount;
    matrix.getEvenIndexElements([](int it){
        if (it == 2)
            evenCount--;
        allCount--;
    });
    cout.clear();

    return allCount == 0 && evenCount == 0 ? 0 : 1;
}

int stressTest(){
    LinkedList<LinkedList<int>> matrixTemplate = LinkedList<LinkedList<int>>();
    static int evenCount = 0;
    for (int i = 0; i < 250; ++i) {
        LinkedList<int> row = LinkedList<int>();
        for (int j = 0; j < 250; ++j) {
            if((i + j) % 2 == 0) {
                row.pushBack(2);
                evenCount++;
            } else{
                row.pushBack(0);
            }
        }
        matrixTemplate.pushBack(row);
    }


    auto start = chrono::system_clock::now();
    CCSMatrix<int> matrix = CCSMatrix<int>(matrixTemplate, 250, 250, 0);
    auto end = chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end-start;
    return elapsed_seconds.count();
}

int whiteBoxTest() {
    LinkedList<LinkedList<int>> matrixTemplate = LinkedList<LinkedList<int>>();
    static int evenCount = 0;
    for (int i = 0; i < 10; ++i) {
        LinkedList<int> row = LinkedList<int>();
        for (int j = 0; j < 10; ++j) {
            if((i + j) % 2 == 0) {
                row.pushBack(2);
                evenCount++;
            } else{
                row.pushBack(0);
            }
        }
        matrixTemplate.pushBack(row);
    }

    try {
        CCSMatrix<int> matrix = CCSMatrix<int>(matrixTemplate, 1, 1, 0);
        return 1;
    }catch (...){

    }

    try {
        CCSMatrix<int> matrix = CCSMatrix<int>(matrixTemplate, 100, 100, 0);
        return 1;
    }catch (...){

    }

    try {
        CCSMatrix<int> matrix = CCSMatrix<int>(matrixTemplate, 10, 10, 0);
    }catch (...){
        return 1;
    }
    return 0;
}

int loadTest() {
    const int ITERATIONS = 1000;
    const int MATRIX_SIZE = 100;

    auto start = std::chrono::high_resolution_clock::now();

    for (int iter = 0; iter < ITERATIONS; iter++) {
        LinkedList<LinkedList<int>> matrix;
        for (int i = 0; i < MATRIX_SIZE; i++) {
            LinkedList<int> row;
            for (int j = 0; j < MATRIX_SIZE; j++) {
                row.pushBack((i + j) % 5 == 0 ? 1 : 0); // Каждый 5й элемент ненулевой
            }
            matrix.pushBack(row);
        }

        CCSMatrix<int> ccs(matrix, MATRIX_SIZE, MATRIX_SIZE, 0);
    }

    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    return elapsed_seconds.count();
}

int stabilityTest() {
    const int seconds = 60;

    auto start = std::chrono::steady_clock::now();
    auto end_time = start + std::chrono::seconds (seconds);
    int iteration = 0;

    while (std::chrono::steady_clock::now() < end_time) {
        int size = 50 + (iteration % 50);
        LinkedList<LinkedList<int>> matrix;

        for (int i = 0; i < size; i++) {
            LinkedList<int> row;
            for (int j = 0; j < size; j++) {
                row.pushBack((i * j) % 7 == 0 ? 1 : 0);
            }
            matrix.pushBack(row);
        }

        {
            CCSMatrix<int> ccs(matrix, size, size, 0);

        }

        iteration++;
    }
    return 0;

}


int main(){
    cout << "unit test " << (unitTest() == 0 ? "passed" : "failed") << endl;
    cout << "stress test passed in " << stressTest() << " seconds" << endl;
    cout << "whitebox test " << (whiteBoxTest() == 0 ? "passed" : "failed") << endl;
    cout << "load test passed in " << loadTest() << " seconds" << endl;
    cout << "stability test " << (stabilityTest() == 0 ? "passed" : "failed") << endl;

    return 0;
}