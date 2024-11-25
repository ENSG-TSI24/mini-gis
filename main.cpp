#include "mainwindow.h"
#include "src/WMS_Load.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    ///////////////////TEST WMS ///////////////////////////

    std::string wms_url = "https://data.geopf.fr/wms-r?"
                              "LAYERS=OI.OrthoimageCoverage&EXCEPTIONS=text/xml&"
                              "FORMAT=image/jpeg&SERVICE=WMS&"
                              "VERSION=1.3.0&REQUEST=GetMap&STYLES=&CRS=EPSG:4326&"
                              "BBOX=47.34956960,3.25167353,47.38545104,3.30486151&WIDTH=256&HEIGHT=256";

        std::string output_file = "/home/formation/Documents/mini_SIG/cute-gis/src/output.png";

        WMSLoader loader(wms_url, output_file);

        if (loader.performRequest()) {
            std::cout << "Requête WMS réussie, fichier sauvegardé dans : " << output_file << std::endl;
        } else {
            std::cerr << "Erreur lors de la requête WMS." << std::endl;
        }

    return a.exec();
}
