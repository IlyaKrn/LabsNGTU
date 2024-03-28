#pragma once
#include<string>
#include<iostream>

class Patient
{
private:
	int _id;
	int _age;
	std::string _name;
	std::string _diagnosis;

public:

	Patient();
	Patient(int id, int age, std::string name, std::string diagnosis);

	void setId(int id);
	void setAge(int age);
	void setName(std::string name);
	void setDiagnosis(std::string diagnosis);

	int getId();
	int getAge();
	std::string getName();
	std::string getDiagnosis();

	};

	std::ostream& operator<<(std::ostream& os, Patient& dt);
	std::istream& operator>> (std::istream& is, Patient& dt);
