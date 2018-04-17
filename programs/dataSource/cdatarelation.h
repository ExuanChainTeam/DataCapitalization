#ifndef CDATARELATION_H
#define CDATARELATION_H
#include <string>
#include <vector>
#include <map>
struct DataInformation
{
    std::string strMetadata;//This maybe file in path or database or content
    std::string strCiphertext;
    //They are the hashindex  from url of ipfs.
    //They can be retrieved the metadata or ciphertext  or FHlib content
    std::string strMetadataIpfsHash;//This shouldn't tell others but youself,if you upload ipfs.
    std::string strCiphertextIpfsHash;
    std::string strHelibContentIpfsHash;

    std::string strSecKey;//This  shouldn't  be saved on a machine other than you.
};

struct DataOperateRule
{
    enum IpfsHashType
    {
        eAny =0,
        eMetadata=1,
        eCiphertextx=2,
        eHelibContent =3

    };
    int eIpfsHash;
    std::string strIpfs;
    bool bSameSecKey;
    std::string strSecKey;

};

typedef std::map<std::string ,DataInformation*>  MapHash2Data;
class CDataRelation
{
public:
    CDataRelation();

    void addDataRelation(const std::string & strIpfsHash, const DataInformation *pDataInfo);

    void modifyDataRelation(const std::string &strIpfsHash, const DataInformation *pDataInfo);

    void deleteDataRelation(const DataOperateRule&deleteRule);

    void selectDataRelation(const DataOperateRule &selectRule,std::vector<DataInformation>& vectDataInfo);

    void saveDataRelationToFile(const std::string &file);

    void readDataRelationFromFile(const std::string &file);
private:
    MapHash2Data _mapIpfs2data;
};

#endif // CDATARELATION_H
