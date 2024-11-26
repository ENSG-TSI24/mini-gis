#include "mainwindow.h"
#include "src/WMS_Geotiff.h"
#include <iostream>
#include "src/WMS_Geotiff.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    ///////////////////TEST WMS ///////////////////////////


    // URL du service WMS
    const char* wmsUrl = "WMS:https://data.geopf.fr/wms-r?SERVICE=WMS&VERSION=1.3.0&REQUEST=GetCapabilities";

    // Nom de la couche WMS que vous souhaitez télécharger
    const char* layerName = "OI.OrthoimageCoverage";

    // Crée une instance de la classe wmsdata
    wmsdata wms(wmsUrl);

    // Ouvre le flux WMS

    //std::cout << "Liste des couches disponibles :" << std::endl;
    //wms.getLayers();

    // Télécharge une tuile spécifique et la sauvegarde en GeoTIFF
    const char* outputFile = "/home/formation/Documents/mini_SIG/cute-gis/src/tile_orthoimage.tiff";
    wms.downloadTileToGeoTiff(layerName, outputFile, 1, 1, 0);

    // Ferme le flux
    wms.close();

    return 0;
}

