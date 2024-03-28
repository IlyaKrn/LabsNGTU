#include "Presenter.h"
#include "Utils.h"
#include<string>

using namespace std;
using namespace utils;

Presenter::Presenter(std::string filePath): _repo(PatientRepository(filePath)){}

//создание элемента
void Presenter::createPatient(){
	try {
		string age;
		string name;
		string diagnosis;

		cout << "enter name" << endl;
		cin >> name;
		cout << "enter age" << endl;
		cin >> age;
		cout << "enter diagnosis" << endl;
		cin >> diagnosis;
		int id = _repo.setPatient(Patient(-1, getIntFromString(age), name, diagnosis));
		cout << "patient with id " << id << " created" << endl;
	} catch (string s) {
		cout << s << endl;
	}
}

//изменение элемента
void Presenter::editPatient(){
	try {
		string id;
		string age;
		string name;
		string diagnosis;

		cout << "enter id" << endl;
		cin >> id;
		cout << "enter new name or -1 to skip" << endl;
		cin >> name;
		cout << "enter new age or -1 to skip" << endl;
		cin >> age;
		cout << "enter new diagnosis or -1 to skip" << endl;
		cin >> diagnosis;
		Patient p = _repo.getPatientById(getIntFromString(id));
		if (name != "-1")
			p.setName(name);
		if (age != "-1")
			p.setAge(getIntFromString(age));
		if (diagnosis != "-1")
			p.setDiagnosis(diagnosis);
		int idEnd = _repo.setPatient(p);
		if(idEnd != -1)
			cout << "patient with id " << id << " edited" << endl;
		else
			cout << "patient not found" << endl;
	} catch (string s) {
		cout << s << endl;
	}
}

//удаление элемента
void Presenter::deletePatient(){
	try {
		string id;
		cout << "enter id" << endl;
		cin >> id;
		int idEnd = _repo.deletePatientById(getIntFromString(id));
		if (idEnd != -1)
			cout << "patient with id " << id << " deleted" << endl;
		else
			cout << "patient not found" << endl;
	}
	catch (string s) {
		cout << s << endl;
	}
}

//поиск элемента
void Presenter::searchPatient(){
	try {
		//обработка действий пользователя
		int size = 0;
		Patient* p = _repo.getPatientList(&size);
		cout << "select search field:" << endl;
		cout << "1. id" << endl;
		cout << "2. name" << endl;
		cout << "3. age" << endl;
		cout << "4. diagnosis" << endl;
		string action;
		cin >> action;
		string param;
		//поиск по выбранному полю
		switch (getIntFromString(action)) {
		case 1:
			cout << "enter id" << endl;
			cin >> param;
			cout << "patients:" << endl;
			for (int i = 0; i < size; i++) {
				if (p[i].getId() == getIntFromString(param)) {
					cout << "id: " << p[i].getId();
					cout << " name: " << p[i].getName();
					cout << " age: " << p[i].getAge();
					cout << " diagnosis: " << p[i].getDiagnosis() << endl;
				}
			}
			break;
		case 2:
			cout << "enter name" << endl;
			cin >> param;
			cout << "patients:" << endl;
			for (int i = 0; i < size; i++) {
				if (p[i].getName() == param) {
					cout << "id: " << p[i].getId();
					cout << " name: " << p[i].getName();
					cout << " age: " << p[i].getAge();
					cout << " diagnosis: " << p[i].getDiagnosis() << endl;
				}
			}
			break;
		case 3:
			cout << "enter age" << endl;
			cin >> param;
			cout << "patients:" << endl;
			for (int i = 0; i < size; i++) {
				if (p[i].getAge() == getIntFromString(param)) {
					cout << "id: " << p[i].getId();
					cout << " name: " << p[i].getName();
					cout << " age: " << p[i].getAge();
					cout << " diagnosis: " << p[i].getDiagnosis() << endl;
				}
			}
			break;
		case 4:
			cout << "enter diagnosis" << endl;
			cin >> param;
			cout << "patients:" << endl;
			for (int i = 0; i < size; i++) {
				if (p[i].getName() == param) {
					cout << "id: " << p[i].getId();
					cout << " name: " << p[i].getName();
					cout << " age: " << p[i].getAge();
					cout << " diagnosis: " << p[i].getDiagnosis() << endl;
				}
			}
			break;
		default:
			cout << "search field \'" << action << "\' not found" << endl;
			break;
		}
	} catch (string s) {
		cout << s << endl;
	}
}

//вывод всех элементов
void Presenter::getAllPatients(){
	try {
		
		cout << "patients:" << endl;
		int size = 0;
		Patient* p = _repo.getPatientList(&size);
		for (int i = 0; i < size; i++) {
			cout << "id: " << p[i].getId();
			cout << " name: " << p[i].getName();
			cout << " age: " << p[i].getAge();
			cout << " diagnosis: " << p[i].getDiagnosis() << endl;
		}
	} catch (string s) {
		cout << s << endl;
	}
}
