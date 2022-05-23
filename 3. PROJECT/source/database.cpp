#include "database.h"

namespace SQLWRAP {

database::database(const std::string &path)
	: FILEPATH(path.c_str()), fpath(path) {
  sqlite3_open(FILEPATH, &SQLDB);
  if (SQLDB == nullptr) {
	std::cout << "COULD NOT ESTABLISH LINK WITH DATABASE\n";
	delete (this);
  } else {
	std::cout << "DATABASE LINK ESTABLISHED\n";
	return;
  }
  this->close();
}

database::~database() {

}

const std::string &database::getFPath(){
  return fpath;
}

void database::open() {
  if (sqlite3_open(fpath.c_str(), &SQLDB)) {
	std::cout << "\nFAILED TO OPEN DATABASE\n";
  } else {
	return;
  };
}

void database::close() {
  sqlite3_close(SQLDB);
}

int database::rc() {
  if (sqlite3_open(fpath.c_str(), &SQLDB)) {
	std::cout << "\nFAILED TO OPEN DATABASE\n";
	return 1;
  } else {
	std::cout << "\nDATABASE OPENED SUCCESSFULLY\n";
	return sqlite3_open(fpath.c_str(), &SQLDB);
  };
}

void database::clear() {
  /*std::string app = "rm ";
  app.append(fpath);
  system(app.c_str());
  system("ls");*/
  remove(fpath.c_str());
}

void database::createTable() {
  std::string sql;
  char *zErrMsg = nullptr;

  int rc = this->rc();

  /* Create SQL statement */
  sql = "CREATE TABLE IF NOT EXISTS HOSPITAL("  \
      "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
      "NAME           TEXT    NOT NULL," \
      "SURNAME        TEXT    NOT NULL," \
      "DATE_OF_BIRTH  TEXT    NOT NULL," \
      "GENDER    	  TEXT    NOT NULL," \
      "SYMPTOMS    	  TEXT    NOT NULL," \
      "PHONE_NUMBER   INT     NOT NULL," \
      "ADDRESS    	  TEXT    NOT NULL," \
      "BLOOD_TYPE     TEXT    NOT NULL," \
      "HEIGHT     	  REAL," \
      "WEIGHT     	  REAL," \
      "HEALTHCARE_PLAN_ID	TEXT	NOT NULL," \
      "HEALTH_INSURANCE_COST	DOUBLE );";

  /* Execute SQL statement */
  rc = sqlite3_exec(SQLDB, sql.c_str(), callback, nullptr, &zErrMsg);

  if (rc != SQLITE_OK) {
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	sqlite3_free(zErrMsg);
  } else {
	fprintf(stdout, "Table created successfully\n");
  }
  this->close();
}

int database::callback(void *NotUsed, int argc, char **argv, char **azColName) {

  for (int i = 0; i < argc; i++) {
	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  /*for (int i = 0; i < argc; i++) {
	std::cout << argv[i] << " ";
  }*/

  std::cout << std::endl;

  return 0;
}

void database::insert(HEALTHCARE::patient patient) {
  this->open();
  //12ELE
  const char *sql = "INSERT INTO HOSPITAL VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)";

  if (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
	printf("\nCould not execute insert func.\n");
	return;
  }
  if (sqlite3_bind_null(stmt, 1) != SQLITE_OK) {
	printf("\nCould not bind null.\n");
	return;
  }
  if (sqlite3_bind_text(stmt, 2, patient.GetName().c_str(), patient.GetName().length(), SQLITE_STATIC) != SQLITE_OK) {
	printf("\nCould not bind text.\n");
	return;
  }
  if (sqlite3_bind_text(stmt, 3, patient.GetSurname().c_str(), patient.GetSurname().length(), SQLITE_STATIC) != SQLITE_OK) {
	printf("\nCould not bind text.\n");
	return;
  }
  if (sqlite3_bind_text(stmt, 4, patient.GetDateofbirth().c_str(), patient.GetDateofbirth().length(), SQLITE_STATIC) != SQLITE_OK) {
	printf("\nCould not bind text.\n");
	return;
  }
  if (sqlite3_bind_text(stmt, 5, patient.GetGender().c_str(), patient.GetGender().length(), SQLITE_STATIC) != SQLITE_OK) {
	printf("\nCould not bind text.\n");
	return;
  }
  if (sqlite3_bind_text(stmt, 6, patient.GetSymptoms().c_str(), patient.GetSymptoms().length(), SQLITE_STATIC) != SQLITE_OK) {
	printf("\nCould not bind text.\n");
	return;
  }
  if (sqlite3_bind_int(stmt, 7, patient.GetPhonenumber()) != SQLITE_OK) {
	printf("\nCould not bind int.\n");
	return;
  }
  if (sqlite3_bind_text(stmt, 8, patient.GetAddress().c_str(), patient.GetAddress().length(), SQLITE_STATIC) != SQLITE_OK) {
	printf("\nCould not bind text.\n");
	return;
  }
  if (sqlite3_bind_text(stmt, 9, patient.GetBloodtype().c_str(), patient.GetBloodtype().length(), SQLITE_STATIC) != SQLITE_OK) {
	printf("\nCould not bind text.\n");
	return;
  }
  if (sqlite3_bind_int(stmt, 10, patient.GetHeight()) != SQLITE_OK) {
	printf("\nCould not bind int.\n");
	return;
  }
  if (sqlite3_bind_int(stmt, 11, patient.GetWeight()) != SQLITE_OK) {
	printf("\nCould not bind int.\n");
	return;
  }
  if (sqlite3_bind_int(stmt, 12, patient.GetHealthcarePlanId()) != SQLITE_OK) {
	printf("\nCould not bind int.\n");
	return;
  }
  if (sqlite3_bind_double(stmt, 13, patient.GetInsuranceCost()) != SQLITE_OK) {
	printf("\nCould not bind double.\n");
	return;
  }
  if (sqlite3_step(stmt) != SQLITE_DONE) {
	printf("\nCould not step (execute) stmt.\n");
	return;
  }
  this->close();

}

void database::display() {

  this->open();

  char *zErrMsg = nullptr;
  const char *data = "Callback function called";
  const char *sql = "SELECT * from HOSPITAL";
  int rc = sqlite3_exec(SQLDB, sql, callback, (void *) data, &zErrMsg);

  if (rc != SQLITE_OK) {
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	sqlite3_free(zErrMsg);
  } else {
	fprintf(stdout, "Operation done successfully\n");
  }

  this->close();
}

void database::displayElement(int index) {
  if(this->getPatient(index)== nullptr){
	std::cout << "INVALID INDEX\n";
	return;
  }
  this->open();
  char *zErrMsg = nullptr;
  const char *data = "Callback function called";
  const char *sql = "SELECT * FROM HOSPITAL WHERE ID=?";
  int rc = (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr));
  if (sqlite3_bind_int(stmt, 1, index) != SQLITE_OK) {
	printf("\nCould not bind int in ID\n");
	return;
  }
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
	auto name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
	auto surname = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
	auto dateofbirth = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
	auto gender = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
	auto symptoms = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5)));
	auto phonenumber = sqlite3_column_int(stmt, 6);
	auto address = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7)));
	auto bloodtype = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8)));
	auto height = sqlite3_column_int(stmt, 9);
	auto weight = sqlite3_column_int(stmt, 10);
	auto healthcarePlanID = sqlite3_column_int(stmt, 11);
	double insuranceCost = sqlite3_column_int(stmt, 12);
	std::cout << "NAME = " << name << "\n";
	std::cout << "SURNAME = " << surname << "\n";
	std::cout << "DATE_OF_BIRTH = " << dateofbirth << "\n";
	std::cout << "GENDER = " << gender << "\n";
	std::cout << "SYMPTOMS = " << symptoms << "\n";
	std::cout << "PHONE_NUMBER = " << phonenumber << "\n";
	std::cout << "ADDRESS = " << address << "\n";
	std::cout << "BLOOD_TYPE = " << bloodtype << "\n";
	std::cout << "HEIGHT = " << height<< "\n";
	std::cout << "WEIGHT = " << weight << "\n";
	std::cout << "HEALTHCARE_PLAN_ID = " << healthcarePlanID << "\n";
	std::cout << "HEALTH_INSURANCE_COST = " << insuranceCost << "\n";
  };
  //sqlite3_finalize(stmt);
  this->close();
}

void database::displayLast() {
  this->open();
  char *zErrMsg = nullptr;
  const char *data = "Callback function called";
  const char *sql = "SELECT * FROM HOSPITAL WHERE ID=(SELECT MAX(ID)  FROM HOSPITAL)";
  int rc = (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr));
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
	auto name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
	auto surname = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
	auto dateofbirth = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
	auto gender = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
	auto symptoms = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5)));
	auto phonenumber = sqlite3_column_int(stmt, 6);
	auto address = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7)));
	auto bloodtype = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8)));
	auto height = sqlite3_column_int(stmt, 9);
	auto weight = sqlite3_column_int(stmt, 10);
	auto healthcarePlanID = sqlite3_column_int(stmt, 11);
	double insuranceCost = sqlite3_column_int(stmt, 12);
	std::cout << "NAME = " << name << "\n";
	std::cout << "SURNAME = " << surname << "\n";
	std::cout << "DATE_OF_BIRTH = " << dateofbirth << "\n";
	std::cout << "GENDER = " << gender << "\n";
	std::cout << "SYMPTOMS = " << symptoms << "\n";
	std::cout << "PHONE_NUMBER = " << phonenumber << "\n";
	std::cout << "ADDRESS = " << address << "\n";
	std::cout << "BLOOD_TYPE = " << bloodtype << "\n";
	std::cout << "HEIGHT = " << height<< "\n";
	std::cout << "WEIGHT = " << weight << "\n";
	std::cout << "HEALTHCARE_PLAN_ID = " << healthcarePlanID << "\n";
	std::cout << "HEALTH_INSURANCE_COST = " << insuranceCost << "\n";
  };
  //sqlite3_finalize(stmt);
  this->close();
}

//PATIENT CLASS

void database::changeRecordDOUBLE(int index, double amount) {
  this->open();
  const char *sql = "UPDATE HOSPITAL SET HEALTH_INSURANCE_COST=? WHERE ID=?";

  if (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
	std::cout << "COULD NOT EXECUTE CHANGE INSURANCE COST\n";
	return;
  }
  if (sqlite3_bind_double(stmt, 1, amount) != SQLITE_OK) {
	std::cout << "COULD NOT BIND DOUBLE IN INSURANCE COST\n";
	return;
  }
  if (sqlite3_bind_int(stmt, 2, index) != SQLITE_OK) {
	std::cout << "COULD NOT BIND INT IN ID\n";
	return;
  }
  if (sqlite3_step(stmt) != SQLITE_DONE) {
	std::cout << "COULD NOT EXECUTE STEP IN CHANGE INSURANCE COST\n";
	return;
  }
  sqlite3_finalize(stmt);
  this->close();
}

void database::changeRecordINT(int index, COLUMN category, int amount) {
  if (this->getPatient(index) == nullptr) {
	std::cout << "INVALID INDEX\n";
	return;
  }
  this->open();
  const char *sql = "";
  switch (category) {
	case COLUMN::HEIGHT:
	  sql = "UPDATE HOSPITAL SET WEIGHT=? WHERE ID=?";
	  if (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cout << "COULD NOT EXECUTE CHANGE WEIGHT\n";
		return;
	  }
	  if (sqlite3_bind_int(stmt, 1, amount) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN WEIGHT\n";
		return;
	  }
	  if (sqlite3_bind_int(stmt, 2, index) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN ID\n";
		return;
	  }
	  if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cout << "COULD NOT EXECUTE STEP IN CHANGE WEIGHT\n";
		return;
	  }
	  sqlite3_finalize(stmt);
	  this->close();
	  return;
	case COLUMN::WEIGHT:
	  sql = "UPDATE HOSPITAL SET HEIGHT=? WHERE ID=?";
	  if (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cout << "COULD NOT EXECUTE CHANGE WEIGHT\n";
		return;
	  }
	  if (sqlite3_bind_int(stmt, 1, amount) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN WEIGHT\n";
		return;
	  }
	  if (sqlite3_bind_int(stmt, 2, index) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN ID\n";
		return;
	  }
	  if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cout << "COULD NOT EXECUTE STEP IN CHANGE WEIGHT\n";
		return;
	  }
	  sqlite3_finalize(stmt);
	  this->close();
	  return;
	case COLUMN::PHONENUMBER:
	  sql = "UPDATE HOSPITAL SET PHONE_NUMBER=? WHERE ID=?";
	  if (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cout << "COULD NOT EXECUTE CHANGE WEIGHT\n";
		return;
	  }
	  if (sqlite3_bind_int(stmt, 1, amount) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN WEIGHT\n";
		return;
	  }
	  if (sqlite3_bind_int(stmt, 2, index) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN ID\n";
		return;
	  }
	  if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cout << "COULD NOT EXECUTE STEP IN CHANGE WEIGHT\n";
		return;
	  }
	  sqlite3_finalize(stmt);
	  this->close();
	  return;
	case COLUMN::HEALTHCAREPLANID:
	  sql = "UPDATE HOSPITAL SET HEALTHCARE_PLAN_ID=? WHERE ID=?";
	  if (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cout << "COULD NOT EXECUTE CHANGE HEALTHCARE PLAN ID\n";
		return;
	  }
	  if (sqlite3_bind_int(stmt, 1, amount) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN HEALTHCARE PLAN ID\n";
		return;
	  }
	  if (sqlite3_bind_int(stmt, 2, index) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN ID\n";
		return;
	  }
	  if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cout << "COULD NOT EXECUTE STEP IN CHANGE HEALTHCARE PLAN ID\n";
		return;
	  }
	  sqlite3_finalize(stmt);
	  this->close();
	  return;
	default:
	  std::cout << "WRONG COLUMN SELECTED: INT DOES NOT EXIST.\n";
	  this->close();
	  return;
  }
}

void database::changeRecordSTRING(int index, COLUMN category, const std::string &argument) {
  if (this->getPatient(index) == nullptr) {
	std::cout << "INVALID INDEX\n";
	return;
  }
  this->open();
  const char *sql = "";
  switch (category) {
	case COLUMN::SYMPTOMS:
	  sql = "UPDATE HOSPITAL SET SYMPTOMS=? WHERE ID=?";
	  if (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cout << "COULD NOT EXECUTE CHANGE SYMPTOMS\n";
		return;
	  }
	  if (sqlite3_bind_text(stmt, 1, argument.c_str(), argument.length(), SQLITE_STATIC) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN SYMPTOMS\n";
		return;
	  }
	  if (sqlite3_bind_int(stmt, 2, index) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN ID\n";
		return;
	  }
	  if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cout << "COULD NOT EXECUTE STEP IN CHANGE SYMPTOMS\n";
		return;
	  }
	  sqlite3_finalize(stmt);
	  this->close();
	  return;
	case COLUMN::ADDRESS:
	  sql = "UPDATE HOSPITAL SET ADDRESS=? WHERE ID=?";
	  if (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cout << "COULD NOT EXECUTE CHANGE ADDRESS\n";
		return;
	  }
	  if (sqlite3_bind_text(stmt, 1, argument.c_str(), argument.length(), SQLITE_STATIC) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN ADDRESS\n";
		return;
	  }
	  if (sqlite3_bind_int(stmt, 2, index) != SQLITE_OK) {
		std::cout << "COULD NOT BIND INT IN ID\n";
		return;
	  }
	  if (sqlite3_step(stmt) != SQLITE_DONE) {
		std::cout << "COULD NOT EXECUTE STEP IN CHANGE ADDRESS\n";
		return;
	  }
	  sqlite3_finalize(stmt);
	  this->close();
	  return;
	default:
	  std::cout << "WRONG COLUMN SELECTED: INT DOES NOT EXIST.\n";
	  this->close();
	  return;
  }
}

HEALTHCARE::patient *database::getPatient(int ID) {
  this->open();
  HEALTHCARE::patient *temp = nullptr;
  const char *sql = "SELECT * FROM HOSPITAL WHERE ID=?";
  int rc = (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr));

  if (sqlite3_bind_int(stmt, 1, ID) != SQLITE_OK) {
	printf("\nCould not bind int in ID\n");
	return nullptr;
  }

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
	auto name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
	auto surname = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
	auto dateofbirth = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
	auto gender = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
	auto symptoms = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5)));
	int phonenumber = sqlite3_column_int(stmt, 6);
	auto address = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7)));
	auto bloodtype = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8)));
	int height = sqlite3_column_int(stmt, 9);
	int weight = sqlite3_column_int(stmt, 10);
	int healthcarePlanID = sqlite3_column_int(stmt, 11);
	double insuranceCost = sqlite3_column_int(stmt, 12);

	temp = new HEALTHCARE::patient(name, surname, dateofbirth, gender, symptoms, phonenumber, address, bloodtype, height, weight, healthcarePlanID, insuranceCost);
  }
  sqlite3_finalize(stmt);
  this->close();
  return temp;
}

void database::pay(int index, double amount) {
  if (amount <= 0) {
	std::cout << "INVALID AMOUNT\n";
  }
  HEALTHCARE::patient *temp = getPatient(index);

  if (temp != nullptr) {
	if (amount > temp->GetInsuranceCost()) {
	  std::cout << "Cannot pay more than needed.\n";
	} else {
	  temp->SetInsuranceCost(temp->GetInsuranceCost() - amount);
	  this->changeRecordDOUBLE(index, temp->GetInsuranceCost());
	}
  } else {
	std::cout << "INDEX OUT OF BOUNDS\n";
  }
}

void database::addCost(int index, double amount) {
  if (amount <= 0) {
	std::cout << "INVALID AMOUNT\n";
  }
  HEALTHCARE::patient *temp = getPatient(index);

  if (temp != nullptr) {
	temp->SetInsuranceCost(temp->GetInsuranceCost() + amount);
	this->changeRecordDOUBLE(index, temp->GetInsuranceCost());
  } else {
	std::cout << "INDEX OUT OF BOUNDS\n";
  }
}

void database::removeRecord(int ID) {
  this->open();
  char *zErrMsg = nullptr;
  const char *data = "Callback function called";
  const char *sql = "DELETE FROM HOSPITAL WHERE ID=?";

  if (sqlite3_prepare_v2(SQLDB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
	std::cout << "COULD NOT EXECUTE REMOVE STATEMENT\n";
	return;
  }
  if (sqlite3_bind_int(stmt, 1, ID) != SQLITE_OK) {
	std::cout << "COULD NOT BIND INT TO ID\n";
	return;
  }
  int rc = sqlite3_exec(SQLDB, sql, callback, (void *) data, &zErrMsg);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
	std::cout << "COULD NOT EXECUTE STEP\n";
	return;
  }
  if (rc != SQLITE_OK) {
	std::cerr << "SQL error: " << zErrMsg << std::endl;
	sqlite3_free(zErrMsg);
  } else {
	std::cout << "PATIENT WITH ID: " << ID << " WAS REMOVED.\n";
  }
  sqlite3_finalize(stmt);
  this->close();
}

}