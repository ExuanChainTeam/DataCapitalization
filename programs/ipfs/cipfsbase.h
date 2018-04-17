#ifndef CIPFSBASE_H
#define CIPFSBASE_H
#include <string>

class CipfsBase
{
public:
    CipfsBase();
    virtual void setIpfsGateway(const std::string &strIpfsGateway)=0;
    virtual void getIpfsGateway(std::string &strIpfsGateway)=0;

};

#endif // CIPFSBASE_H
