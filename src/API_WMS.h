#ifndef WMSDATA_H
#define WMSDATA_H

#include <gdal_priv.h>
#include <string>
#include <vector>
#include <ogrsf_frmts.h>

class wmsdata {
public:
    wmsdata(const char* url);
    ~wmsdata() { close(); }

    // Ouvre un flux WMS
    void open(const char* url);

    // Liste les couches disponibles dans le flux
    void getLayers();

    //void wmsdata::displayMetadata();

    // Télécharge une tuile spécifique et la convertit en GeoTIFF
    void downloadTileToGeoTiff(const char* layerName, const char* outputFile, int zoom, int row, int col);

    // Charge une grille de tuiles autour d'une position donnée et les convertit en GeoTIFF
    void loadTileGridToGeoTiff(const char* layerName, int zoom, int centerRow, int centerCol, int gridSize, const char* outputPrefix);

    // Ferme le flux
    void close();

    //check if dataset is empty or not to avoid memory leak
    bool isEmpty();

    // Retourne le dataset actuel
    GDALDataset* GetDataset();

private:
    GDALDataset* m_dataset;
    std::string m_url;
    char** m_metada;
};

#endif // WMSDATA_H