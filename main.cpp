#include <iostream>
#include "Presenter.h"
#include "Utils.h"
#include<string>


using namespace std;
using namespace utils;

int main()
{
	try {
		//сщздание презентера
		Presenter p("database.txt");
		//бесконечный цикл
		while (true) {
			cout << "=============================" << endl;
			cout << "select action:" << endl;
			cout << "1. create patient" << endl;
			cout << "2. edit patient" << endl;
			cout << "3. delete patient" << endl;
			cout << "4. search patient" << endl;
			cout << "5. get all patients" << endl;
			cout << "6. close program" << endl;

			//обработка действий пользователя
			string action;
			cin >> action;
			try {
				switch (getIntFromString(action)) {
				case 1:
					p.createPatient();
					break;
				case 2:
					p.editPatient();
					break;
				case 3:
					p.deletePatient();
					break;
				case 4:
					p.searchPatient();
					break;
				case 5:
					p.getAllPatients();
					break;
				case 6:
					return 0;
				default:
					cout << "action \'" << action << "\' not found" << endl;
					break;
				}
			}
			catch (string s) {
				cout << s << endl;
			}
			cout << endl;
		}
	}
	catch (string s) {
		cout << s << endl;
	}
	return 0;
}

