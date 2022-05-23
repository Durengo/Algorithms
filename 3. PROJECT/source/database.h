#pragma once

#include "sqlite3.h"
#include "patient.h"
#include <iostream>
#include <vector>

namespace SQLWRAP {

enum COLUMN {
  NAME = 1, SURNAME = 2, DATEOFBIRTH = 3,
  GENDER = 4, SYMPTOMS = 5, PHONENUMBER = 6,
  ADDRESS = 7, BLOODTYPE = 8, HEIGHT = 9,
  WEIGHT = 10, HEALTHCAREPLANID = 11,
  INSURANCECOST = 12
};

class database {
 private:
  sqlite3 *SQLDB;
  sqlite3_stmt *stmt;

  const char *FILEPATH;
  std::string fpath;

  //std::vector<int> rows;
  //std::vector<int> columns;
  //int rows = 0;
  //int columns = 0;

 public:
  //THIS
  database(const std::string &path);
  ~database();
  const std::string &getFPath();
  void open();
  void close();
  int rc();
  void clear();
  void createTable();
  static int callback(void *context, int columnCount, char **columnValues, char **columnName);
  void display();
  void displayElement(int index);
  void displayLast();
  //PATIENT CLASS
  void insert(HEALTHCARE::patient patient);
  HEALTHCARE::patient *getPatient(int ID);
  void removeRecord(int ID);
  //Index = Patient Index;
  void changeRecordDOUBLE(int index, double amount);
  void changeRecordINT(int index, COLUMN category, int amount);
  void changeRecordSTRING(int index, COLUMN category, const std::string &argument);
  void pay(int index, double amount);
  void addCost(int index, double amount);
};
}