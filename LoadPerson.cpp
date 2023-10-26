#include <string_view>
#include <vector>


using namespace std;

struct DbParams
{
    string_view db_name;
    bool db_allow_exceptions;
    int db_connection_timeout;
    DBLogLevel db_log_level;
};

struct PersonParams
{
    int min_age;
    int max_age;
    string_view name_filter;
};

DBHandler DBConnect(const DbParams& db_params)
{
    DBConnector connector(DbParams.db_allow_exceptions, DbParams.db_log_level);
    DBHandler db;
    if (db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(DbParams.db_name, DbParams.db_connection_timeout);
    } else {
        db = connector.Connect(DbParams.db_name, DbParams.db_connection_timeout);
    }
    return db;
}

DBQuery MakePersonQuery(const PersonParams& person_params)
{
    ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << person_params.min_age << " and "s << person_params.max_age << " "s
              << "and Name like '%"s << db.Quote(person_params.name_filter) << "%'"s;
    return {query_str.str()};
}

vector<Person> LoadPersons(const DbParams& db_params, const PersonParams& person_params) 
{
    DBHandler db = DBConnect(db_params);
    // Если запрещены исключения, проверим корректность хэндлера БД
    if (!db.IsOK()) 
    {
        return {};
    }

    DBQuery query = MakePersonQuery(const PersonParams& person_params)

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) 
    {
        persons.push_back({move(name), age});
    }
    return persons;
}