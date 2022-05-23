#pragma once

#include <string>

#include "../DataTypes/CSVLL.h"
#include "../Algorithms/ALGO.h"

class console {
 private:
  bool firstset = false;
  std::string filepath = "";
  DTYPES::CSVLL *parser = nullptr;
  ALGO::CSVQUEUE *QUEUE = nullptr;
  bool neatly = false;

 public:
  console();
  void execute();
  void displayPart();
  void search();
  void sort();
  void queueUp();

  void loop();
  void selectFile();
  void createPatient();
  void changeinsurace();
  void modifyPatientRecord();
  void removePatientRecord();

  bool Exists(const std::string &filepath);

  int GIBI();
  int GIBI(int min, int max);
  double GIBD();
  std::string GIBS();
  std::string GIBSWW();
  int Get_Input_Yes_Or_No();
};
