#ifndef CCOMPUTATIONMODEL_H
#define CCOMPUTATIONMODEL_H
class CBaseObject;
class CComputationResult;
class CComputationFormula;
class CComputationData;
class CComputationModel : public CBaseObject
{
public:
    CComputationModel();

private:
    CComputationData* _pData;
    CComputationFormula* _pFormula;
    CComputationResult* _pResult;
};

#endif // CCOMPUTATIONMODEL_H
