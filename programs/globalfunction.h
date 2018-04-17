#ifndef GLOBALFUNCTION_H
#define GLOBALFUNCTION_H
#include <iostream>
#include <string>
#include <vector>
namespace  globalFun {

static std::vector<std::string>  spliteStr_g(const std::string &strTol,const std::string &strSplite)
{
    std::vector<std::string> retVect;
    if("" == strTol)
    {
        return retVect;
    }

    std::string strTmp = strTol+strSplite;
    size_t pos = strTmp.find(strSplite);
    size_t size = strTmp.size();
    while(pos != std::string::npos)
    {
        std::string strSpliteTmp = strTmp.substr(0,pos);
        retVect.push_back(strSpliteTmp);
        strTmp = strTmp.substr(pos+1,size);
        pos =  strTmp.find(strSplite);
    }
    return retVect;
}

}

#endif // GLOBALFUNCTION_H
