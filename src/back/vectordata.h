#ifndef VECTORDATA_H
#define VECTORDATA_H

#include "abstractdata.h"

class VectorData : public AbstractData
{
public:
    VectorData();
    VectorData(const char* path);

};

#endif // VECTORDATA_H