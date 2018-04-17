#include "chelibio.h"

using namespace std;
CHElibIO::CHElibIO()
{

}

int CHElibIO::setContextToFile(const FHEcontext *context, const char *file, ios_base::openmode mode)
{

    int  eRet = eNoError;
    if(!context)
    {
       eRet = eContentNull;
       errorInfo(eRet);
       return eRet;
    }

    ofstream fileOut;
    fileOut.open(file,mode);
    if(!fileOut)
    {
        eRet = eFileFault;
         errorInfo(eRet);
        return eRet;
    }

    writeContextBase(fileOut,*context);
    writeContextBase(cout ,*context);
    fileOut  << *context << endl;
    fileOut.close();
    return eRet;
}

int CHElibIO::getContextFromFile(FHEcontext *context, const char *file)
{
    int eRet = eNoError;
    ifstream fileIn;
    fileIn.open(file,ios_base::in );
    if(!fileIn)
    {
        eRet = eFileFault;
        errorInfo(eRet);
        return eRet;
    }

    unsigned long m ,p,r;
    vector<long>  gens,ords;
    readContextBase(fileIn,m,p,r,gens,ords);
    fileIn.close();

    if(context)
    {
        delete context;
        context = NULL;
    }
    context = new FHEcontext(m,p,r,gens,ords);
    return eRet;
}

int CHElibIO::setSecKeyToFile(const FHESecKey *skey, const char *file, ios_base::openmode mode)
{
    ofstream fileOut;
    int eRet = eNoError;
    fileOut.open(file,mode);
    if(!fileOut)
    {
        eRet = eFileFault;
        errorInfo(eRet);
        return eRet;
    }

    if(!skey)
    {
        eRet = eContentNull;
        errorInfo(eRet);
        return eRet;
    }

    fileOut << *skey << endl;
    fileOut.close();
    return eRet;

}

int CHElibIO::getSecKeyFromFile(FHESecKey *skey, const char *file)
{
    int eRet = eNoError;

    ifstream filein ;
    filein.open(file,ios_base::in);
    if(!filein)
    {
        eRet = eFileFault;
        errorInfo(eRet);
        return eRet;
    }

    filein >>  *skey ;
    filein.close();
    return eRet;
}

int CHElibIO::setPubKeyToFile(const FHEPubKey *pkey, const char *file, ios_base::openmode mode)
{
    int eRet = eNoError;

    if(!pkey)
    {
        eRet = eContentNull;
        errorInfo(eRet);
        return eRet;
    }

    ofstream fileOut;
    fileOut.open(file,mode);
    if(!fileOut)
    {
        eRet = eFileFault;
        errorInfo(eRet);
        return eRet;
    }
    fileOut << *pkey << endl;
    fileOut.close();

    return eRet;
}

int CHElibIO::getPubKeyFromFile(FHEPubKey *pkey, const char *file)
{
    int eRet = eNoError;

    ofstream fileIn;
    fileIn.open(file,fstream::in);
    if(!fileIn)
    {
        eRet = eFileFault;
        errorInfo(eRet);
        return eRet;
    }

    Ctxt text(*pkey);
   // fileIn >> *pkey;
    fileIn.close();
    return eRet;

}

int CHElibIO::setCtxtToFile(const Ctxt *txts, const char *file, ios_base::openmode mode)
{
    int eRet = eNoError;
    if(!txts)
    {
        eRet = eContentNull;
        errorInfo(eRet);
        return eRet;
    }

    ofstream fileOut;
    fileOut.open(file,mode);
    if(!fileOut)
    {
        eRet = eFileFault;
        errorInfo(eRet);
        return eRet;
    }

    fileOut << *txts <<endl;
    fileOut.close();
    //writeCtxtToFile(txts,eRet,mode);
    return eRet;
}

int CHElibIO::getCtxtFromFile(Ctxt *txts, const char *file)
{
    int eRet = eNoError;
    if(!txts)
    {
        eRet = eContentNull;
        errorInfo(eRet);
        return eRet;
    }

    ifstream fileIn;
    fileIn.open(file,ios_base::in);
    if(!fileIn)
    {
        eRet = eFileFault;
        errorInfo(eRet);
        return eRet;
    }

    fileIn >> *txts ;
    return eRet;
}

int CHElibIO::setZZXToFile(const ZZX &poly, const char *file, ios_base::openmode mode)
{
    int eRet = eNoError;

    ofstream fileOut;
    fileOut.open(file,mode);
    if(!fileOut)
    {
        eRet = eFileFault;
        errorInfo(eRet);
        return eRet;
    }

    fileOut << poly <<endl;

    return eRet;
}

int CHElibIO::getZZXFromFile(ZZX &poly, const char *file)
{
    int eRet = eNoError;

    ifstream fileIn;
    fileIn.open(file,ios_base::in);
    if(!fileIn)
    {
        eRet = eFileFault;
        errorInfo(eRet);
        return eRet;
    }

    fileIn >> poly;
    return eRet;
}

void CHElibIO::errorInfo(int errorType)
{
    switch (errorType)
    {
    case eFileFault:
        cerr << "Can't open file!" << endl;
        break;
    case eContentNull:
        cerr << "Content to file is NULL!" << endl;
        break;
    default:
        break;
    }
}

