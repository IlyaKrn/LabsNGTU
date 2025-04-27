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


int main(){
    cout << "unit test " << (unitTest() == 0 ? "passed" : "failed") << endl;
    cout << "unit test passed in " << stressTest() << " seconds" << endl;

    return 0;
}