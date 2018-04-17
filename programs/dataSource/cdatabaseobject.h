#ifndef CDATABASEOBJECT_H
#define CDATABASEOBJECT_H
#include <string>
struct sqlite3;
class CDatabaseObject
{
public:
    CDatabaseObject();
    ~CDatabaseObject();
    void openDB(const std::string &file,bool create = false);
    //
    void execSQL(const std::string& strSQL);

    void addDataToTable(const std::string& strValue,const std::string &strSplite,const std::string strTable);

    void modifyDataToTable(const std::string&strModify,const std::string strTable);

    void deleteDataToTable(const std::string &strDel,const std::string &strTable);

    void dropTable(const std::string strtable);

    void selectData(const std::string &strSelect,const std::string &strFrom,const std::string &strWhere,std::string &strValue);

    void clearDB();

    void listTable(std::string &strtable);
private:
    sqlite3* _db;
};

#endif // CDATABASEOBJECT_H
