#pragma once

#include "database.h"

class console {
 public:
  console();
  void execute();

  void loop(SQLWRAP::database &DBinstance);
  void createPatient(SQLWRAP::database &DBinstance);
  void changeinsurace(SQLWRAP::database &DBinstance);
  void modifyPatientRecord(SQLWRAP::database &DBinstance);
  void removePatientRecord(SQLWRAP::database &DBinstance);

  bool dbExists(const std::string &filepath);

  int Get_Input_By_INT();
  int Get_Input_By_INT(int min, int max);
  double Get_Input_By_DOUBLE();
  std::string GIBS();
  std::string GIBSWW();
  int Get_Input_Yes_Or_No();
};
