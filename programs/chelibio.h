#ifndef CHELIBIO_H
#define CHELIBIO_H
#include<fstream>
#include<unistd.h>

#include <NTL/ZZX.h>
#include <NTL/vector.h>

#include "FHE.h"
#include "timing.h"
#include "EncryptedArray.h"

class CHElibIO
{
public:
    CHElibIO();
    enum errorType
    {
        eNoError =0,
        eFileFault =1,
        eContentNull =2,
    };

// IO for file

    //write
    int setContextToFile(const FHEcontext* context,const char*file,ios_base::openmode mode = ios_base::in | ios_base::out);
    //read
    int getContextFromFile(FHEcontext* context,const char*file);

    //write
    int setSecKeyToFile(const FHESecKey*skey,const char* file,ios_base::openmode mode = ios_base::in | ios_base::out);
    //read
    int getSecKeyFromFile(FHESecKey*skey,const char*file);

    //write
    int setPubKeyToFile(const FHEPubKey*pkey,const char*file ,ios_base::openmode mode = ios_base::in| ios_base::out);
    //read
    int getPubKeyFromFile(FHEPubKey*pkey,const char*file);

    //write
    int setCtxtToFile(const Ctxt*txts,const char*file,ios_base::openmode mode = ios_base::in | ios_base::out);
    //read
    int getCtxtFromFile(Ctxt*txts,const char*file);

    //write
    int setZZXToFile(const ZZX &poly,const char*file,ios_base::openmode mode = ios_base::in | ios_base::out);
    //read
    int getZZXFromFile(ZZX&poly,const char*file);

// IO for net


public:


protected:
     void errorInfo(int errorType);

     int writeCtxtToFile(const Ctxt*txts ,const char* file,int& eRet,ios_base::openmode mode = ios_base::in | ios_base::out);

     void readCtxtToFile(Ctxt*txts,const char*file ,int&eRet);

/*
private:
    const char* _fileContextIn;
    const char* _fileContextOut;
*/


};

#endif // CHELIBIO_H
