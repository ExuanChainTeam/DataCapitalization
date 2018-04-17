#ifndef CDATASOURCE_H
#define CDATASOURCE_H
#include <memory>
#include "../ipfs/cipfsbase.h"
#include "../fheconfig.h"
#include <string>

class CDataTransfer
{
public:
    enum LoadType
    {
        eNo = 0 ,
        eFromDataBase =1 ,
        eFromFile =2 ,
        eFromContent = 3
    };

    enum DownloadSaveType
    {
        eSaveMemory =0,// Not Recommended, only if you know that you  do.
        eInputConsole = 1,
        eSaveFile = 2,
        eSaveDatabase = 3
    };

public:
    CDataTransfer();

    void initIpfs();

//Metadata upload and download

    //Metadata upload
    void uploadMetadata(const std::string&strUrl,int eLoadType = eFromContent);
    //Metadata download
    void downloadMetadata(const std::string&strIpfsHash,int eDownloadSaveType = eSaveDatabase);


//ciphertext upload and download

    //ciphertext upload
    void uploadCiphertext(const std::string&strUrl,int eLoadType = eFromContent);
    //ciphertext download
    void downloadCiphertext(const std::string&strIpfsHase,int eDownloadSaveType = eSaveDatabase);


//FHlib  content upload and download

    //FHlib context upload
    void uploadFhlibContent(const FHEcontext *context,const FHEPubKey*pkey);
    //FHlib context download
    void downloadFhlibContent(FHEcontext*context,FHEPubKey*pkey,const std::string &strIpfsHash);
private:
    shared_ptr<CipfsBase> _pIpfs;
 };

#endif // CDATASOURCE_H
