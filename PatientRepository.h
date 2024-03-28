#pragma once
#include<fstream>
#include<string>
#include"Patient.h"

class PatientRepository
{
private:
	std::string _filePath;
public:

	PatientRepository(std::string filePath);

	Patient* getPatientList(int* size);
	int setPatient(Patient p);
	Patient getPatientById(int id);
	int deletePatientById(int id);

};

