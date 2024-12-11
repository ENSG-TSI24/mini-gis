#include "addFluxData.h"
#include "ui_addFluxData.h"

addFluxData::addFluxData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFluxData) {
    ui->setupUi(this);
    connect(ui->url, &QComboBox::currentIndexChanged, this, &addFluxData::onUrlSelected);
}

addFluxData::~addFluxData() {
    delete ui;
}

QString addFluxData::getLayerName() const {
    return ui->layer->currentText();
}

QString addFluxData::getLayerURL() const {
    return ui->url->currentText();
}




void addFluxData::loadLayersFromURL(const QString& url, QComboBox* comboBox_Layer) {
    comboBox_Layer->clear();  // Efface les couches précédentes

    try {
        API_WFS wfs(url.toStdString().c_str());
        wfs.loadDataset();

        if (!wfs.isEmpty()) {
            char** layers = wfs.displayMetadata();  // Récupérer les couches depuis l'URL WFS
            for (int i = 0; layers[i] != nullptr; ++i) {
                QString layerName = QString::fromStdString(layers[i]);
                qDebug() << "Layer ajoutée : " << layerName;
                comboBox_Layer->addItem(layerName);  // Ajouter chaque couche à la combo box
            }
        } else {
            QMessageBox::warning(this, "Warning", "No layers found for this URL.");
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to load layers: %1").arg(e.what()));
    }
}

void addFluxData::addItemToComboBox_url(QString item) {
    ui->url->addItem(item);  // Ajoute l'élément à la combo box
}
void addFluxData::addItemToComboBox_layer(QString item) {
    ui->layer->addItem(item);  // Ajoute l'élément à la combo box
}

void addFluxData::populateComboBox(QComboBox* comboBox, const QStringList& items) {
    comboBox->clear();
    comboBox->addItems(items);
}



void addFluxData::onUrlSelected(int index) {
    QString selectedUrl = ui->url->itemText(index);
    if (!selectedUrl.isEmpty()) {
        loadLayersFromURL(selectedUrl, ui->layer); // Charger les couches pour l'URL sélectionnée
    }
}

