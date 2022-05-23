#include "patient.h"

namespace HEALTHCARE {

patient::patient(const std::string &newname,
				 const std::string &newsurname,
				 const std::string &newdateofbirth,
				 GENDER newgender,
				 const std::string &newsymptoms,
				 int newphonenumber,
				 const std::string &newaddress,
				 BLOODTYPE newbloodtype,
				 int newheight,
				 int newweight,
				 int newhealthcarePlanID,
				 double newinsuranceCost) {
  if (newdateofbirth.at(4) != '-' || newdateofbirth.at(7) != '-') {
	std::cout << "INVALID DATE FORMAT: " << newdateofbirth << "\n";
	std::cout << "DATE FORMAT: YYYY-MM-DD";
	delete (this);
	return;
  }
  if (newheight <= 0) {
	std::cout << "INVALID HEIGHT!\n";
	delete (this);
	return;
  }
  if (newweight <= 0) {
	std::cout << "INVALID WEIGHT!\n";
	delete (this);
	return;
  }
  if (newinsuranceCost <= 0) {
	std::cout << "INVALID INSURANCE COST!\n";
	delete (this);
	return;
  }
  name = newname;
  surname = newsurname;
  dateofbirth = newdateofbirth;
  if (newgender == GENDER::MALE) {
	gender = "MALE";
  } else {
	gender = "FEMALE";
  }
  symptoms = newsymptoms;
  phonenumber = newphonenumber;
  address = newaddress;
  switch (newbloodtype) {
	case BLOODTYPE::APLUS:
	  bloodtype = "A+";
	  break;
	case BLOODTYPE::AMINUS:
	  bloodtype = "A-";
	  break;
	case BLOODTYPE::BPLUS:
	  bloodtype = "B+";
	  break;
	case BLOODTYPE::BMINUS:
	  bloodtype = "B-";
	  break;
	case BLOODTYPE::ABPLUS:
	  bloodtype = "AB+";
	  break;
	case BLOODTYPE::ABMINUS:
	  bloodtype = "AB-";
	  break;
	case BLOODTYPE::OPLUS:
	  bloodtype = "O+";
	  break;
	case BLOODTYPE::OMINUS:
	  bloodtype = "O-";
	  break;
  }
  height = newheight;
  weight = newweight;
  healthcarePlanID = newhealthcarePlanID;
  insuranceCost = newinsuranceCost;
}

patient::patient(const std::string &newname,
				 const std::string &newsurname,
				 const std::string &newdateofbirth,
				 const std::string &newgender,
				 const std::string &newsymptoms,
				 int newphonenumber,
				 const std::string &newaddress,
				 const std::string &newbloodtype,
				 int newheight,
				 int newweight,
				 int newhealthcarePlanID,
				 double newinsuranceCost)
	: name(newname), surname(newsurname), dateofbirth(newdateofbirth), gender(newgender), symptoms(newsymptoms), phonenumber(newphonenumber), address(newaddress), bloodtype(newbloodtype),
	  height(newheight), weight(newweight), healthcarePlanID(newhealthcarePlanID), insuranceCost(newinsuranceCost) {

}

const std::string &patient::GetName() const {
  return name;
}

void patient::SetName(const std::string &name) {
  patient::name = name;
}

const std::string &patient::GetSurname() const {
  return surname;
}

void patient::SetSurname(const std::string &surname) {
  patient::surname = surname;
}

const std::string &patient::GetDateofbirth() const {
  return dateofbirth;
}

void patient::SetDateofbirth(const std::string &dateofbirth) {
  patient::dateofbirth = dateofbirth;
}

const std::string &patient::GetGender() {
  return gender;
}

void patient::SetGender(const std::string &gender) {
  patient::gender = gender;
}

const std::string &patient::GetSymptoms() const {
  return symptoms;
}

void patient::SetSymptoms(const std::string &symptoms) {
  patient::symptoms = symptoms;
}

int patient::GetPhonenumber() const {
  return phonenumber;
}

void patient::SetPhonenumber(int phonenumber) {
  patient::phonenumber = phonenumber;
}

const std::string &patient::GetAddress() const {
  return address;
}

void patient::SetAddress(const std::string &address) {
  patient::address = address;
}

const std::string &patient::GetBloodtype() const {
  return bloodtype;
}

void patient::SetBloodtype(const std::string &bloodtype) {
  patient::bloodtype = bloodtype;
}

int patient::GetHeight() const {
  return height;
}

void patient::SetHeight(int height) {
  patient::height = height;
}

int patient::GetWeight() const {
  return weight;
}

void patient::SetWeight(int weight) {
  patient::weight = weight;
}

int patient::GetHealthcarePlanId() const {
  return healthcarePlanID;
}

void patient::SetHealthcarePlanId(int healthcare_plan_id) {
  healthcarePlanID = healthcare_plan_id;
}

double patient::GetInsuranceCost() const {
  return insuranceCost;
}

void patient::SetInsuranceCost(double insurance_cost) {
  insuranceCost = insurance_cost;
}

}