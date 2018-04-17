#include "ccomputationformula.h"
#include "ccomputationdata.h"
#include "../globalfunction.h"

using namespace  std;
CComputationFormula::CComputationFormula()
{

}

void CComputationFormula::primitiveExpression(const std::__cxx11::string &strExpress, const std::__cxx11::string &strSplite)
{
    _strMathExpression = strExpress;
    _strSplite = strSplite;
}

void CComputationFormula::parseExpress(const std::__cxx11::string &strMathExpression)
{
    _vectParse = globalFun::spliteStr_g(_strMathExpression,_strSplite);
}

void CComputationFormula::calculate(const std::__cxx11::string &strOpt)
{
    if(strOpt == "#")
    {
        CComputationData opd = _opdStack.top();
        CComputationData opdTmp;
        CComputationData result = opdTmp - opd;
        _opdStack.pop();
        _opdStack.push(result);
        //cout << " "
    }
    else if(strOpt == "+")
    {
        CComputationData rOpd = _opdStack.top();
        _opdStack.pop();
        CComputationData lOpd =_opdStack.top();
        _opdStack.pop();
        CComputationData result = lOpd + rOpd;
        _opdStack.push(result);
    }
    else if(strOpt == "-")
    {
        CComputationData rOpd = _opdStack.top();
        _opdStack.pop();
        CComputationData lOpd =_opdStack.top();
        _opdStack.pop();
        CComputationData result = lOpd - rOpd;
        _opdStack.push(result);
    }
    else if(strOpt == "*")
    {
        CComputationData rOpd = _opdStack.top();
        _opdStack.pop();
        CComputationData lOpd =_opdStack.top();
        _opdStack.pop();
        CComputationData result = lOpd * rOpd;
        _opdStack.push(result);
    }
    else if(strOpt == "/")
    {
        std::cerr << " Don't support the operation!" << endl;
        /*
        CComputationData rOpd = _opdStack.top();
        _opdStack.pop();
        CComputationData lOpd =_opdStack.top();
        _opdStack.pop();
        CComputationData result = lOpd / rOpd;
        _opdStack.push(result);
        */
    }
}

CComputationData CComputationFormula::evaluateMiddleExpression()
{
    int i =0;
    int size = _vectParse.size();

    for(i =0;i<size;i++)
    {
       string  strToken = _vectParse[i];
        if(isOperation(strToken))
        {
            if(_optStack.size() == 0)
            {
                _optStack.push(strToken);
            }
            else
            {
                int tokenPriority = getPriority(strToken);
                string topOpt = _optStack.top();
                int topOptPriority = getPriority(topOpt);
                if(tokenPriority > topOptPriority)
                {
                    _optStack.push(strToken);
                }
                else
                {
                    while(tokenPriority <= topOptPriority)
                    {
                        _optStack.pop();
                        calculate(topOpt);
                        if(_optStack.size() >0)
                        {
                            topOpt = _optStack.top();
                            topOptPriority = getPriority(topOpt);
                        }
                        else
                            break;
                    }
                    _optStack.push(strToken);
                }
            }
        }
        else if(strToken == "(")
        {
            _optStack.push(strToken);
        }
        else if(strToken == ")")
        {
            while(_optStack.top() != "(")
            {
                string topOpt = _optStack.top();
                calculate(topOpt);
                _optStack.pop();
            }
            _optStack.pop();
        }
        else
        {
            CComputationData data;
            //
            _opdStack.push(data);
        }

    }
    while(_optStack.size()!=0)
    {
        string topOpt = _optStack.top();
        calculate(topOpt);
        _optStack.pop();
    }

    return _opdStack.top();
}

CComputationData CComputationFormula::getData(const string &strParam, const string strValueUrlParse)
{
    CComputationData retData;

    return retData;
}

int CComputationFormula::getPriority(const std::__cxx11::string &strOpt)
{
    int priority;
    if(strOpt=="#")
        priority = 3;
    else if(strOpt=="*"||strOpt=="/")
        priority = 2;
    else if(strOpt=="+"||strOpt=="-")
        priority = 1;
    else if(strOpt=="(")
        priority = 0;
    return priority;
}

bool CComputationFormula::isOperation(const std::__cxx11::string &strOpt)
{
    if(strOpt == "#" || strOpt == "-" || \
       strOpt == "*" || strOpt == "/" )
    {
        return true;
    }

    return false;
}
