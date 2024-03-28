#include "PatientRepository.h"
#include <fstream>
#include<string>

using namespace std;

//конструктор
PatientRepository::PatientRepository(std::string filePath)
{
	//инициализация бд
	this->_filePath = filePath;
	ofstream out(_filePath, ios_base::app);
	out.close();
	ifstream in(_filePath);
	if (in.is_open()) {
		if(in.peek() == ifstream::traits_type::eof()){
			ofstream out2(_filePath, ios_base::app);
			if (out2.is_open()) {
				out << "0" << endl;
			}
			else {
				throw string("cant init database");
			}
			out2.close();
		}
	}
	else {
		throw string("cant init database");
	}

	in.close();
}

//метод получения всех элементов
Patient* PatientRepository::getPatientList(int* size){
	ifstream in(_filePath);
	if (in.is_open()) {
		try {
			//чтение файла
			in >> *size;
			Patient* ps = new Patient[*size];
			for (int i = 0; i < *size; i++) {
				in >> ps[i];
			}
			return ps;
		}
		catch (...) {
			// если некорректные данные в файле
			in.close();
			throw string("cant convert file to list");
		}
		in.close();
	}
	else {
		//если не удалось открыть файл
		throw string("cant open file " + _filePath);
	}
}

//метод добавления/изменения элемента
int PatientRepository::setPatient(Patient p){
	//id созданного/измененного элемента
	int id = p.getId();
	//получение элементов
	int size = 0;
	Patient* ps = getPatientList(&size);
	//конечный массив элементов
	Patient* pEnd;
	//если создание нового элемента
	if (p.getId() == -1) {
		//генерация нового id
		p.setId(0);
		for (int i = 0; i < size; i++) {
			if (ps[i].getId() >= p.getId()) {
				p.setId(ps[i].getId() + 1);
			}
		}
		id = p.getId();
		//добавление старого списка и нового элемента в новый список
		size++;
		pEnd = new Patient[size];
		for (int i = 0; i < size - 1; i++) {
			pEnd[i] = ps[i];
		}
		pEnd[size - 1] = p;
	}
	//если изменение элемента
	else {
		pEnd = new Patient[size];
		bool edited = false;
		//добавление старого массива в новый с измененным элементом
		for (int i = 0; i < size; i++) {
			if (ps[i].getId() == p.getId()) {
				pEnd[i] = p;
				edited = true;
			}
			else {
				pEnd[i] = ps[i];
			}
		}
		//если нет элемента с нужным id
		if (!edited) {
			id = -1;
		}
	}

	//запись нового массива в файл
	ofstream out(_filePath);
	if (out.is_open()) {
		out.clear();
		out << size << endl;
		for (int i = 0; i < size; i++) {
			out << pEnd[i];
		}
	}
	else {
		//если не удалось открыть файл
		throw string("cant open file " + _filePath);
	}
	out.close();
	//очистка памяти
	delete[] pEnd;
	delete[] ps;
	return id;
}

Patient PatientRepository::getPatientById(int id)
{
	int size = 0;
	Patient* p = getPatientList(&size);
	for (int i = 0; i < size; i++) {
		if (p[i].getId() == id)
			return p[i];
	}
	throw string("cant find patient");
	delete[] p;
}

//метод удаления элемента
int PatientRepository::deletePatientById(int id){
	int idEnd = id;
	int size = 0;
	Patient* ps = getPatientList(&size);
	//новый массив
	Patient* pEnd;

	//проверка на наличие элемента
	bool edited = false;
	for (int i = 0; i < size; i++) {
		if (ps[i].getId() == id) {
			edited = true;
		}
	}
	//если элеменьта нет
	if (!edited) {
		//копирование старого массива в новый
		pEnd = new Patient[size];
		for (int i = 0; i < size; i++) {
			pEnd[i] = ps[i];
		}
		idEnd = -1;
	}
	//если элемент есть
	else {
		//копирование старого массива в новый без элемента
		size--;
		pEnd = new Patient[size];
		int count = 0;
		for (int i = 0; i < size + 1; i++) {
			if (ps[i].getId() != id) {
				pEnd[count] = ps[i];
				count++;
			}
		}
	}
	//запись нового массивы
	ofstream out(_filePath);
	if (out.is_open()) {
		out.clear();
		out << size << endl;
		for (int i = 0; i < size; i++) {
			out << pEnd[i];
		}
	}
	else {
		//если не удалось открыть файл
		throw string("cant open file " + _filePath);
	}
	out.close();
	//очистка памяти
	delete[] pEnd;
	delete[] ps;
	return idEnd;
	
}
