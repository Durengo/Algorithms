#pragma once

#include <iostream>

namespace HEALTHCARE {

enum BLOODTYPE { APLUS = 1, AMINUS = -1, BPLUS = 2, BMINUS = -2, ABPLUS = 3, ABMINUS = -3, OPLUS = 4, OMINUS = -4 };

enum GENDER { MALE = 1, FEMALE = 2 };

class patient {
 private:
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
 public:
  patient(const std::string &newname,
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
		  double newinsuranceCost);
  patient(const std::string &newname,
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
		  double newinsuranceCost);
  const std::string &GetName() const;
  void SetName(const std::string &name);
  const std::string &GetSurname() const;
  void SetSurname(const std::string &surname);
  const std::string &GetDateofbirth() const;
  void SetDateofbirth(const std::string &dateofbirth);
  const std::string &GetGender();
  void SetGender(const std::string &gender);
  const std::string &GetSymptoms() const;
  void SetSymptoms(const std::string &symptoms);
  int GetPhonenumber() const;
  void SetPhonenumber(int phonenumber);
  const std::string &GetAddress() const;
  void SetAddress(const std::string &address);
  const std::string &GetBloodtype() const;
  void SetBloodtype(const std::string &bloodtype);
  int GetHeight() const;
  void SetHeight(int height);
  int GetWeight() const;
  void SetWeight(int weight);
  int GetHealthcarePlanId() const;
  void SetHealthcarePlanId(int healthcare_plan_id);
  double GetInsuranceCost() const;
  void SetInsuranceCost(double insurance_cost);
};
}