#ifndef SMARTDEVICEMANAGER_H
#define SMARTDEVICEMANAGER_H

#include <QMainWindow>
#include "device.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class SmartDeviceManager;
}
QT_END_NAMESPACE

class SmartDeviceManager : public QMainWindow
{
    Q_OBJECT

public:
    SmartDeviceManager(QWidget *parent = nullptr);
    ~SmartDeviceManager();

    void updateDeviceList(const std::vector<std::unique_ptr<Device>>& list);

private slots:
    void on_btnAddDevice_clicked();
    void on_btnRemoveDevice_clicked();
    void on_DeviceSelected();

private:
    Ui::SmartDeviceManager *ui;

};
#endif // SMARTDEVICEMANAGER_H
