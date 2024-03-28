#include "Patient.h"
#include "Utils.h"
#include<string>

using namespace std;
using namespace utils;

//конструктор по умолчанию
Patient::Patient(): _id(-1), _name("no data"), _diagnosis("no data"), _age(-1){}

//конструктор
Patient::Patient(int id, int age, std::string name, std::string diagnosis)
{
	this->_id = id;
	this->_name = name;
	this->_diagnosis = diagnosis;;
	this->_age = age;
}

//геттеры и сеттеры
void Patient::setId(int id) {
	this->_id = id;
}
void Patient::setAge(int age) {
	this->_age = age;
}
void Patient::setName(std::string name) {
	this->_name = name;
}
void Patient::setDiagnosis(std::string diagnosis) {
	this->_diagnosis = diagnosis;;
}

int Patient::getId() {
	return this->_id;
}
int Patient::getAge() {
	return this->_age;
}
string Patient::getName() {
	return this->_name;
}
string Patient::getDiagnosis() {
	return this->_diagnosis;
}

// операторы ввода/вывода
ostream& operator<<(ostream& os, Patient& dt)
{
	os << dt.getId() << '\n' << dt.getAge() << '\n' << dt.getName() << '\n' << dt.getDiagnosis() << '\n';
	return os;
}
istream& operator>> (istream& is, Patient& dt)
{
	string idStr = "";
	string ageStr = "";
	string name = "";
	string diagnosis = "";
	char c = '\n';
	is >> idStr;
	is >> ageStr;
	is >> name;
	is >> diagnosis;
	
	//установка значений и проверка на int
	dt.setId(getIntFromString(idStr));
	dt.setAge(getIntFromString(ageStr));
	dt.setName(name);
	dt.setDiagnosis(diagnosis);
	return is;
}