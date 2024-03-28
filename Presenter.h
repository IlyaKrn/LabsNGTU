#pragma once
#include "PatientRepository.h"
#include<string>

class Presenter
{

private:
	PatientRepository _repo;

public:
	Presenter(std::string filePath);

	void createPatient();
	void editPatient();
	void deletePatient();
	void searchPatient();
	void getAllPatients();

};

