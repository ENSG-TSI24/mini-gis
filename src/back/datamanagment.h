#ifndef DATAMANAGMENT_H
#define DATAMANAGMENT_H

#include <gdal_priv.h>
#include "dataextract/datavisitor.h"


class DataManagment {
public:
    DataManagment();
    DataManagment(const char* Path);
    virtual void accept(DataVisitor& visitor) = 0;
    ~DataManagment();
    const char* GetPath();
protected:
    const char* filePath;
};

#endif
