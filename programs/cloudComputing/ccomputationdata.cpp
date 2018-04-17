#include "ccomputationdata.h"
#include "../fheconfig.h"
CComputationData::CComputationData()
{

}

CComputationData::CComputationData(const std::__cxx11::string &strParam, Ctxt *pCtxtVaule)
{
    _strParam = strParam;
    _pCtxtValue = pCtxtVaule;
}

void CComputationData::InitValue(const std::__cxx11::string &strParams, const std::__cxx11::string &strValueUrlParse)
{
    _strParam = strParams;

}

const CComputationData CComputationData::operator +(const CComputationData &rData)
{
    return CComputationData(_strParam + "+" + rData._strParam , &(*_pCtxtValue += *rData._pCtxtValue));

}
const CComputationData CComputationData::operator -(const CComputationData &rData)
{
    return CComputationData(_strParam + "-" + rData._strParam , &(*_pCtxtValue -= *rData._pCtxtValue));
}

const CComputationData CComputationData::operator *(const CComputationData &rData)
{
    return CComputationData(_strParam + "+" + rData._strParam , &(*_pCtxtValue *= *rData._pCtxtValue));
}

