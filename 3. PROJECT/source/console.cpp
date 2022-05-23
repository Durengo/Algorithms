#include "console.h"

#include <iostream>
#include <fstream>
#include <limits>

#include <fmt/format.h>

#define print fmt::print

console::console() {
  execute();
}

void console::execute() {
  print("This program will manage a database for a Hospital\n");
  print("A Hospital has a patient.\n");
  print("A patient has:\n*A Name\n*A Surname\n*A Date of Birth\n*A Gender\n"
		"*Symptom or Symptoms\n*A Phone Number\n*An Address\n*A Blood Type\n"
		"*A Height\n*A weight\n*A Healthcare Plan ID\n*An Insurance Cost\n");
  print("A dummy database will be created with a few filled out rows in order to test functionality.\n");

  if(!dbExists("database.db")){
	SQLWRAP::database DB("database.db");
	DB.createTable();
	HEALTHCARE::patient P1("IGOR", "ZOLNERCIK", "2001-05-17", HEALTHCARE::GENDER::MALE, "BRONCHITUS", 8655544, "VIRSULISKES", HEALTHCARE::BLOODTYPE::ABPLUS, 182, 87, 666, 4666.52);
	HEALTHCARE::patient P2("ZACK", "FOUGH", "1985-05-13", HEALTHCARE::GENDER::MALE, "COUGH, SORE TRHOAT", 869949, "AVE ST.", HEALTHCARE::BLOODTYPE::OPLUS, 180, 78, 555, 300);
	HEALTHCARE::patient P3("ELLIE", "MACKERY", "1980-01-21", HEALTHCARE::GENDER::FEMALE, "ABDOMINAL PAIN", 869547, "BROOD ST.", HEALTHCARE::BLOODTYPE::BMINUS, 172, 60, 666, 500);
	HEALTHCARE::patient P4("BILL", "JOE", "1987-09-16", HEALTHCARE::GENDER::MALE, "NUMBNESS, SHORT BREATH", 862135, "MARK AVE", HEALTHCARE::BLOODTYPE::ABMINUS, 187, 92, 333, 250);
	HEALTHCARE::patient P5("MARK", "BURROW", "1992-07-20", HEALTHCARE::GENDER::MALE, "URINARY PROBLEMS, SKIN RASH, WHEEZING, ANKLE PAIN, NAUSEA", 8677410, "LAKE AVE", HEALTHCARE::BLOODTYPE::ABMINUS, 179, 79, 555, 4000);
	HEALTHCARE::patient P6("DOROTHY", "ASGEIR", "1997-03-04", HEALTHCARE::GENDER::FEMALE, "HIP PAIN, LOW BACK PAIN", 869573, "JAKE ST.", HEALTHCARE::BLOODTYPE::ABPLUS, 172, 67, 666, 1500);
	DB.insert(P1);
	DB.insert(P2);
	DB.insert(P3);
	DB.insert(P4);
	DB.insert(P5);
	DB.insert(P6);
	loop(DB);
  }else{
	SQLWRAP::database DB("database.db");
	DB.createTable();
	loop(DB);
  }
}

void console::loop(SQLWRAP::database &DBinstance){
  while(true){
	print("0. Exit\n"
		  "1. Show All Patients\n"
		  "2. Add New Patient Record\n"
		  "3. Change Patient Insurance Cost\n"
		  "4. Modify Patient Records\n"
		  "5. Remove Patient Record\n");
	switch(Get_Input_By_INT(0,5)){
	  case 0:
		print("EXITING\n");
		return;
	  case 1:
		DBinstance.display();
		break;
	  case 2:
		createPatient(DBinstance);
		break;
	  case 3:
		changeinsurace(DBinstance);
		break;
	  case 4:
		modifyPatientRecord(DBinstance);
		break;
	  case 5:
		removePatientRecord(DBinstance);
		break;
	}
  }
}

void console::createPatient(SQLWRAP::database &DBinstance){
  std::string name;
  std::string surname;
  std::string dateofbirth;
  std::string gender;
  std::string symptoms;
  int phonenumber;
  std::string address;
  std::string bloodtype;
  int height;
  int weight;
  int healthcarePlanID;
  double insuranceCost;
  print("CREATING NEW PATIENT\nENTER PATIENTS NAME: ");
  name = GIBS();
  print("\nENTER PATIENTS SURNAME: ");
  surname = GIBS();
  print("\nENTER PATIENTS DATE OF BIRTH (DATE OF BIRTH FORMAT: YYYY-MM-DD): ");
  dateofbirth = GIBS();
  print("\nENTER PATIENTS GENDER (MALE OR FEMALE): ");
  while(true){
	gender = GIBS();
	if(gender == "MALE" || gender == "FEMALE"){
	  break;
	}
	else{
	  print("\nENTER PATIENTS GENDER (MALE OR FEMALE): ");
	}
  }
  print("\nENTER PATIENTS SYMPTOMS: ");
  symptoms = GIBSWW();
  print("\nENTER PATIENTS PHONE NUMBER: ");
  phonenumber = Get_Input_By_INT();
  print("\nENTER PATIENTS ADDRESS: ");
  address = GIBSWW();
  print("\nENTER PATIENTS BLOOD TYPE (A+;A-;B+;B-;AB+;AB-;O+;O-): ");
  while(true){
	bloodtype = GIBS();
	if(bloodtype == "A+" || bloodtype == "A-" || bloodtype == "B+" || bloodtype == "B-" ||
		bloodtype == "AB+" || bloodtype == "AB-" || bloodtype == "O+" || bloodtype == "O+"){
	  break;
	}
	else{
	  print("\nENTER PATIENTS BLOOD TYPE (A+;A-;B+;B-;AB+;AB-;O+;O-): ");
	}
  }
  print("\nENTER PATIENTS HEIGHT: ");
  height = Get_Input_By_INT();
  print("\nENTER PATIENTS WEIGHT: ");
  weight = Get_Input_By_INT();
  print("\nENTER PATIENTS HEALTHCARE PLAN ID: ");
  healthcarePlanID = Get_Input_By_INT();
  print("\nENTER PATIENTS INSURANCE COST: ");
  insuranceCost = Get_Input_By_DOUBLE();
  HEALTHCARE::patient NEWPATIENT(name, surname, dateofbirth, gender, symptoms, phonenumber,
								 address, bloodtype, height, weight, healthcarePlanID,
								 insuranceCost);
  DBinstance.insert(NEWPATIENT);
  print("NEW PATIENT RECORD CREATED:\n");
  DBinstance.displayLast();
}

void console::changeinsurace(SQLWRAP::database &DBinstance){
  DBinstance.display();
  print("\nSELECT PATIENT:\n");
  int input = Get_Input_By_INT();
  while(DBinstance.getPatient(input) == nullptr){
	DBinstance.display();
	print("\nSELECT PATIENT:\n");
	input = Get_Input_By_INT();
  }
  print("SELECTED PATIENT:\n");
  double insur = DBinstance.getPatient(input)->GetInsuranceCost();
  print("INSURANCE VALUE: ");
  std::cout << insur << "\n";
  while(true){
	double amount = 0;
	print("0. EXIT\n1. PAY\n2. INCREASE\n");
	switch(Get_Input_By_INT(0,2)){
	  case 0:
		return;
	  case 1:
		print("CURRENT INSURANCE VALUE: ");
		std::cout << insur << "\n";
		print("ENTER AMOUNT TO PAY: ");
		amount = Get_Input_By_INT();
		DBinstance.pay(input, amount);
		insur -= amount;
		print("NEW INSURANCE VALUE: ");
		std::cout << insur << "\n";
		break;
	  case 2:
		print("CURRENT INSURANCE VALUE: ");
		std::cout << insur << "\n";
		print("ENTER AMOUNT TO INCREASE: ");
		amount = Get_Input_By_INT();
		DBinstance.addCost(input, amount);
		insur += amount;
		print("NEW INSURANCE VALUE: ");
		std::cout << insur << "\n";
		break;
	}
  }
}

void console::modifyPatientRecord(SQLWRAP::database &DBinstance){
  DBinstance.display();
  print("\nSELECT PATIENT: \n");
  int input = Get_Input_By_INT();
  while(DBinstance.getPatient(input) == nullptr){
	DBinstance.display();
	print("\nSELECT PATIENT: \n");
	input = Get_Input_By_INT();
  }
  DBinstance.displayElement(input);
  HEALTHCARE::patient *temp = DBinstance.getPatient(input);
  while(true){
	int amount = 0;
	std::string newele = "";
	print("0. EXIT\n1. CHANGE WEIGHT\n2. CHANGE HEIGHT\n"
		  "3. PHONE NUMBER\n4. HEALTHCARE PLAN ID\n"
		  "5. SYMPTOMS\n6. ADDRESS\n");
	switch(Get_Input_By_INT(0,6)){
	  case 0:
		return;
	  case 1:
		print("CURRENT WEIGHT: \n");
		std::cout << temp->GetWeight() << "\n";
		print("ENTER AMOUNT TO CHANGE WEIGHT: ");
		amount = Get_Input_By_INT();
		DBinstance.changeRecordINT(input, SQLWRAP::COLUMN::WEIGHT, amount);
		temp->SetWeight(amount);
		print("NEW WEIGHT: \n");
		std::cout << temp->GetWeight() << "\n";
		break;
	  case 2:
		print("CURRENT HEIGHT: \n");
		std::cout << temp->GetHeight() << "\n";
		print("ENTER AMOUNT TO CHANGE HEIGHT: ");
		amount = Get_Input_By_INT();
		DBinstance.changeRecordINT(input, SQLWRAP::COLUMN::HEIGHT, amount);
		temp->SetHeight(amount);
		print("NEW HEIGHT: \n");
		std::cout << temp->GetHeight() << "\n";
		break;
	  case 3:
		print("CURRENT PHONE NUMBER: \n");
		std::cout << temp->GetPhonenumber() << "\n";
		print("ENTER NEW PHONE NUMBER: ");
		amount = Get_Input_By_INT();
		DBinstance.changeRecordINT(input, SQLWRAP::COLUMN::PHONENUMBER, amount);
		temp->SetPhonenumber(amount);
		print("NEW PHONE NUMBER: \n");
		std::cout << temp->GetPhonenumber() << "\n";
		break;
	  case 4:
		print("CURRENT HEALTHCARE PLAN ID: \n");
		std::cout << temp->GetHealthcarePlanId() << "\n";
		print("ENTER A NEW HEALTHCARE PLAN ID: ");
		amount = Get_Input_By_INT();
		DBinstance.changeRecordINT(input, SQLWRAP::COLUMN::HEALTHCAREPLANID, amount);
		temp->SetHealthcarePlanId(amount);
		print("NEW HEALTHCARE PLAN ID: \n");
		std::cout << temp->GetHealthcarePlanId() << "\n";
		break;
	  case 5:
		print("CURRENT SYMPTOMS: \n");
		std::cout << temp->GetSymptoms() << "\n";
		print("CHANGE SYMPTOMS: ");
		newele = GIBSWW();
		DBinstance.changeRecordSTRING(input, SQLWRAP::COLUMN::SYMPTOMS, newele);
		temp->SetSymptoms(newele);
		print("NEW SYMPTOMS: \n");
		std::cout << temp->GetSymptoms() << "\n";
		break;
	  case 6:
		print("CURRENT ADDRESS: \n");
		std::cout << temp->GetAddress() << "\n";
		print("CHANGE ADDRESS: ");
		newele = GIBSWW();
		DBinstance.changeRecordSTRING(input, SQLWRAP::COLUMN::ADDRESS, newele);
		temp->SetAddress(newele);
		print("NEW ADDRESS: \n");
		std::cout << temp->GetAddress() << "\n";
		break;
	}
  }
}

void console::removePatientRecord(SQLWRAP::database &DBinstance){
  DBinstance.display();
  print("\nSELECT PATIENT: \n");
  int input = Get_Input_By_INT();
  while(DBinstance.getPatient(input) == nullptr){
	DBinstance.display();
	print("\nSELECT PATIENT: \n");
	input = Get_Input_By_INT();
  }
  DBinstance.displayElement(input);
  while(true){
	print("ARE YOU SURE YOU WANT TO DELETE THIS PATIENT RECORD?\n");
	print("1. YES\n2. NO\n");
	switch(Get_Input_By_INT(1,2)){
	  case 1:
		DBinstance.displayElement(input);
		DBinstance.removeRecord(input);
		print("PATIENT RECORD REMOVED.\n");
		return;
	  case 2:
		return;
	}
  }
}

bool console::dbExists(const std::string &filepath){
	std::ifstream file(filepath);
	if(file.is_open()){
	  return true;
	}
	else{
	  return false;
	}
}

int console::Get_Input_By_INT() {
  std::string input;
  int converted;
  while (true) {
	std::cin >> input;
	try {
	  converted = std::stoi(input);
	  break;
	}
	catch (std::invalid_argument &i) {
	  std::cout << i.what();
	  print("\n!EXCEPTION!\n");
	  print("\n!EXCEPTION!\n !STOI INVALID ARGUMENT!: ", input, "\n");
	}
	catch (std::out_of_range &i) {
	  std::cout << i.what();
	  print("\n!EXCEPTION!\n");
	  print("\n!EXCEPTION!\n !STOI OUT OF RANGE!: ", input, "\n");
	}
  }
  return converted;
}

int console::Get_Input_By_INT(int min, int max) {
  while (true) {
	int input = Get_Input_By_INT();
	if (input >= min && input <= max) {
	  return input;
	} else {
	  print("!EXCEPTION!\n");
	  print("\n!EXCEPTION!\n !OUT OF RANGE INPUT: ", input, " in", min, " ", max);
	}
  }
}

double console::Get_Input_By_DOUBLE() {
  std::string input;
  double converted;
  while (true) {
	std::cin >> input;
	try {
	  converted = std::stod(input);
	  break;
	}
	catch (std::invalid_argument &i) {
	  std::cout << i.what();
	  print("\n!EXCEPTION!\n");
	  print("\n!EXCEPTION!\n !STOI INVALID ARGUMENT!: ", input, "\n");
	}
	catch (std::out_of_range &i) {
	  std::cout << i.what();
	  print("\n!EXCEPTION!\n");
	  print("\n!EXCEPTION!\n !STOI OUT OF RANGE!: ", input, "\n");
	}
  }
  return converted;
}

std::string console::GIBS(){
  std::string input;
  std::cin >> input;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  return input;
}
std::string console::GIBSWW(){
  std::string input;
  std::getline(std::cin >> std::ws, input);
  return input;
}

int console::Get_Input_Yes_Or_No() {
  while (true) {
	print("Answer with: (1) Yes; (0) No.\n");
	int input = Get_Input_By_INT(0, 1);

	switch (input) {
	  case 0:
		print("\nNo selected!\n");
		return input;
	  case 1:
		print("\nYes selected!\n");
		return input;
	  default:
		print("\n!EXCEPTION!\n");
		break;
	}
  }
}