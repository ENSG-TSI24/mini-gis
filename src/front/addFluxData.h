#ifndef ADDFLUXDATA_H
#define ADDFLUXDATA_H

#include <QDialog>
#include <QComboBox>
#include "../back/API_WFS.h"
#include <QMessageBox>

namespace Ui {
class addFluxData;
}

class addFluxData : public QDialog {
    Q_OBJECT

public:
    explicit addFluxData(QWidget *parent = nullptr);
    ~addFluxData();

    QString getLayerName() const;  // Getter for Layer Name
    QString getLayerURL() const;   // Getter for URL
    void loadLayersFromURL(const QString& url, QComboBox* comboBox_Layer);
    void  addItemToComboBox_url( QString  item);
    void  addItemToComboBox_layer( QString  item);
    void onUrlSelected(int index);
    void populateComboBox(QComboBox* comboBox, const QStringList& items);
private:
    Ui::addFluxData *ui;
};

#endif // ADDFLUXDATA_H

