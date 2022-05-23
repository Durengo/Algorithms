#include <iostream>
#include <sstream>
#include <fstream>

#include "../CSV/CSV.h"

namespace DTYPES {

class CSVLL;

int readCSV(const std::string &FILEPATH, DTYPES::CSVLL* LIST);
void parseCSV(std::fstream &CSVFILE, DTYPES::CSVLL* LIST);
void parseColumns(const std::string &line, DTYPES::CSVLL* LIST);
void parseElements(const std::string &line, DTYPES::CSVLL* LIST);

class CSVLL {
 private:
  CSV::CSV *head;
 public:
  CSVLL(const std::string &FILEPATH);

  int length();

  void displayTable(bool neatly);

  void displayColumn(int index);

  void displayRow(int index);

  CSV::CSV *getHead();

  CSV::CSV *getPTR(int index);

  CSV::CSV *get(int index);

  void addCSVelement(int index, const std::string &element);

  void add(const std::string &category);

  void addFront(const std::string &category);

  void add(int index, const std::string &category);

  void remove();

  void remove(int index);

  void removeFront();
};

}