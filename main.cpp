#include <iostream>

#include "LinkedList.h"


using namespace std;



int main() {

    LinkedList<int> linkedList = LinkedList<int>();

    linkedList.print([](int item){
        cout << item;
    });

    linkedList.pushBack(1);
    linkedList.pushBack(2);
    linkedList.pushBack(3);
    linkedList.pushBack(4);
    linkedList.pushBack(5);

    linkedList.print([](int item){
        cout << item;
    });

}