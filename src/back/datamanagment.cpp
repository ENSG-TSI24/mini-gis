#include "datamanagment.h"
#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>

DataManagment::DataManagment() {
    filePath = nullptr;
    sessionvisitor = nullptr;
}

DataManagment::DataManagment(const char* Path) {
    GDALAllRegister();
    filePath = Path;
    sessionvisitor = new SessionVisitor();
}

DataManagment::~DataManagment() {
    // GDALClose(data);
}

const char* DataManagment::GetPath() const {
    return filePath;
}

/*
GDALDriver* DataManagment::GetDriver() {
    return data->GetDriver();
}

GDALDataset* DataManagment::GetDATA() {
    return data;
}
*/
