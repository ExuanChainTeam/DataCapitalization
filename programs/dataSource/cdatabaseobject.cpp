#include "cdatabaseobject.h"
#include <sqlite3.h>
#include <unistd.h>
#include <assert.h>
using namespace std;
CDatabaseObject::CDatabaseObject()
{
    _db= NULL;
}

CDatabaseObject::~CDatabaseObject()
{
   sqlite3_close(_db);
}

void CDatabaseObject::openDB(const std::string &file, bool create)
{
    if(_db)
    {
        sqlite3_close(_db);
    }

    if(!create)
    {
        if(!access(file.c_str(),F_OK))
            return ;
    }

    int rc = sqlite3_open(file.c_str(),&_db);
    assert(!rc);
}

void CDatabaseObject::execSQL(const std::string &strSQL)
{
    assert(_db);
    char* zErrMsg;
    sqlite3_exec(_db,strSQL.c_str(),0,0,&zErrMsg);

}

void CDatabaseObject::addDataToTable(const std::string &strValue, const std::__cxx11::string &strSplite, const std::__cxx11::string strTable)
{
    std::string strSQL = "INSERT INTO ";
    strSQL += strTable ;
    strSQL += "VALUES (";
    //format strValue;

    strSQL += strValue;
    strSQL += ");";
    execSQL(strSQL);
}

void CDatabaseObject::modifyDataToTable(const std::string &strModify, const std::__cxx11::string strTable)
{
     string strSQL =  "UPDATE ";
     strSQL += strTable;
     strSQL += "  SET ";
     strSQL +=  strModify;
     strSQL += ";";
     execSQL(strSQL);
}

void CDatabaseObject::deleteDataToTable(const std::string &strDel, const std::__cxx11::string &strTable)
{
    string strSQL = "DELETE FROM";
    strSQL  += strTable;
    strSQL  += "  WHERE ";
    strSQL  += strDel;
    execSQL(strSQL);
}

void CDatabaseObject::dropTable(const std::string strtable)
{
    string strSQL = "DROP ";
    strSQL += strtable;
    execSQL(strSQL);
}

void CDatabaseObject::selectData(const std::string &strSelect, const std::__cxx11::string &strFrom,const std::string &strWhere, std::string &strValue)
{
    string  strSQL = "SELECT  ";
    strSQL += strSelect;
    strSQL += " FROM ";
    strSQL += strFrom;
    strSQL += " WHERE ";
    strSQL += strWhere;
    char** azResult;

    int nrow = 0;
    int ncolumn = 0;
    char* zErrMsg;

    sqlite3_get_table(_db,strSQL.c_str(),&azResult,&nrow,&ncolumn,&zErrMsg);
    int i =0;
    for(;i<(nrow +1)*ncolumn ;i++)
    {
        strValue += azResult[i] ;
        strValue += ";";
    }
    sqlite3_free_table(azResult);
}

void CDatabaseObject::clearDB()
{
    sqlite3_close(_db);
    _db = NULL;
}

void CDatabaseObject::listTable(std::string &strtable)
{

}
