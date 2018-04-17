#ifndef CIPFSHANDLEDATA_H
#define CIPFSHANDLEDATA_H
#include "cipfsbase.h"

class CipfsHandleData : public CipfsBase
{
public:

    CipfsHandleData();
    virtual void setIpfsGateway(const std::string &strIpfsGateway);
    virtual void getIpfsGateway(std::string &strIpfsGateway);

    void encodeData(const std::string & strData,std::string &strCode);
    void decodeData(const std::string&strCode,std::string strData);

    void uploadCode(const std::string &strCode,std::string &ipfsHash);
    void dowmloadCode(const std::string&ipfsHash,std::string &strCode);
private:
    std::string _strGateway;
};

#endif // CIPFSHANDLEDATA_H
