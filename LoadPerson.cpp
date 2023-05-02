
#include <vector>
#include <sstream>


using namespace std;


class DBLogLevel;
class DBConnector;
class DBHandler;


enum DBStatus {
    FAILED,
    SUCCESS
};

class DBConnect {


public:

    enum DBStatus {
        FAILED,
        SUCCESSFUL
    };
    
      DBConnect(bool db_allow_exceptions,
          DBLogLevel db_log_level):
          connector_(db_allow_exceptions, db_log_level), 
          db_allow_exceptions_(db_allow_exceptions), 
          db_log_level_(db_log_level)
      {}

      bool ConnectToDB(string_view db_name, int db_connection_timeout) {
          
          if (db_name.starts_with("tmp."s)) {
              db_ = connector_.ConnectTmp(db_name, db_connection_timeout);
          }
          else {
              db_ = connector_.Connect(db_name, db_connection_timeout);
          }
          if (!db_allow_exceptions_ && !db_.IsOK()) {
              return FAILED;
          }
          else return SUCCESSFUL;


      }

private:
    string_view db_name_;
    int db_connection_timeout_;

    bool db_allow_exceptions_;
    DBLogLevel db_log_level_;

    DBConnector connector_;
    DBHandler db_;
};


vector<Person> LoadPersons(int min_age, int max_age, string_view name_filter, const DBConnect db) {

    ostringstream query_str;
    query_str << "from Persons "s
        << "select Name, Age "s
        << "where Age between "s << min_age << " and "s << max_age << " "s
        << "and Name like '%"s << db.Quote(name_filter) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({ move(name), age });
    }
    return persons;
}