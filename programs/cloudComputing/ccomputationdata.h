#ifndef CCOMPUTATIONDATA_H
#define CCOMPUTATIONDATA_H
#include<string>
class Ctxt;
class CComputationData
{
public:
    CComputationData();
    CComputationData(const std::string & strParam,Ctxt*pCtxtVaule);
    void InitValue(const std::string &strParams,const std::string&strValueUrlParse);

    const CComputationData operator + (const CComputationData&rData);
    const CComputationData operator - (const CComputationData&rData);
    const CComputationData operator * (const CComputationData&rData);

private:
    Ctxt*_pCtxtValue;
    std::string _strParam;
};

#endif // CCOMPUTATIONDATA_H
