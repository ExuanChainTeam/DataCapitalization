#ifndef CBASEOPERATE_H
#define CBASEOPERATE_H
#include "intraSlot.h"

class CBaseOperate
{
public:
    CBaseOperate();

    /*brief:
    * d  is the size of degree .like  long d = ea.getDegree();

    */
    void unpackedToSlot(const EncryptedArray&ea ,);
};

     unpackSlots(std::vector<unsigned long> &value, ZZX &pa, const EncryptedArray &ea);

#endif // CBASEOPERATE_H
