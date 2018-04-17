#ifndef CCOMPUTATIONFORMULA_H
#define CCOMPUTATIONFORMULA_H
#include <string>
#include <vector>
#include <stack>

class CComputationData;
class CComputationFormula
{
public:
    CComputationFormula();

public:
    void primitiveExpression(const std::string &strExpress,const std::string &strSplite);

    void parseExpress(const std::string &strMathExpression);

    void calculate(const std::string &strOpt);

    CComputationData evaluateMiddleExpression();

    CComputationData getData(const std::string& strParam,const std::string strValueUrlParse);


protected:
    int getPriority(const std::string &strOpt);

    bool isOperation(const std::string &strOpt);


private:
    std::string _strSplite;
    std::string _strMathExpression;
    std::vector<std::string> _vectParse;
    std::stack<CComputationData> _opdStack;
    std::stack<std::string> _optStack;
};

#endif // CCOMPUTATIONFORMULA_H
