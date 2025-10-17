#include "smartdevicemanager.h"
#include "./ui_smartdevicemanager.h"
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include "devicemanager.h"
#include "adddevicedialog.h"


SmartDeviceManager::SmartDeviceManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartDeviceManager)
{
    ui->setupUi(this);
    connect(ui->listWidget,&QListWidget::itemSelectionChanged,this,&SmartDeviceManager::on_DeviceSelected);
}

void SmartDeviceManager::updateDeviceList(const std::vector<std::unique_ptr<Device>>& list)
{
    ui->listWidget->clear();
    for(auto& device:list)
    {
        ui->listWidget->addItem(QString::fromStdString(device->getDevName()));
    }
}

SmartDeviceManager::~SmartDeviceManager()
{
    delete ui;
}


void SmartDeviceManager::on_btnAddDevice_clicked()
{

    addDeviceDialog diaglog(this);

    int result = diaglog.exec();

    if(result == QDialog::Accepted)
    {
        auto device  = DeviceFactory::createDevice(diaglog.getDeviceName().toStdString(),
                                                  diaglog.getDeviceId().toStdString(),
                                                  diaglog.getDeviceLocation().toStdString(),
                                                  diaglog.getDeviceType());
        if(device)
        {
            deviceManager::getInstance().addDevice(std::move(device));
            updateDeviceList(deviceManager::getInstance().getDevices());
        }

        ui->txtLogging->appendPlainText("");
        ui->txtLogging->appendPlainText("Thêm thiết bị mới:");
        ui->txtLogging->appendPlainText("    Tên Thiết Bị: " + diaglog.getDeviceName());
        ui->txtLogging->appendPlainText("    ID Thiết Bị: " + diaglog.getDeviceId());
        ui->txtLogging->appendPlainText("    Vị Trí Thiết Bị: " + diaglog.getDeviceLocation());
        ui->txtLogging->appendPlainText("    Kiểu Thiết Bị: " + QString::number(diaglog.getDeviceType()));
        qDebug() << "Diaglog nhan OK";
        qDebug() << diaglog.getDeviceName();
        qDebug() << diaglog.getDeviceId();
        qDebug() << diaglog.getDeviceLocation();
        qDebug() << diaglog.getDeviceType();
    }
    else
    {
        qDebug() << "Dialog bị từ chối/đóng.";
    }
}


void SmartDeviceManager::on_btnRemoveDevice_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  "Remove Device",
                                  "Are you sure you want to remove this device?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        int itemIdx = ui->listWidget->row(ui->listWidget->currentItem());
        auto deviceId = deviceManager::getInstance().getDevices().at(itemIdx)->getDevId();

        // Gọi hàm xóa thiết bị ở đây

        ui->txtLogging->appendPlainText("");
        ui->txtLogging->appendPlainText("Xóa Thiết Bị Có ID: "+ QString::fromStdString(deviceId));
        qDebug() << "Remove Device ID: " << QString::fromStdString(deviceId);
    } else {
        qDebug() << "User clicked No";
    }
}

void SmartDeviceManager::on_DeviceSelected()
{
    int itemIdx = ui->listWidget->row(ui->listWidget->currentItem());
    auto deviceName = deviceManager::getInstance().getDevices().at(itemIdx)->getDevName();
    auto deviceId = deviceManager::getInstance().getDevices().at(itemIdx)->getDevId();
    auto deviceLocation = deviceManager::getInstance().getDevices().at(itemIdx)->getDevLocation();
    auto deviceType = deviceManager::getInstance().getDevices().at(itemIdx)->getDevType();

    auto deviceValue = deviceManager::getInstance().getDevices().at(itemIdx)->getValue();

    // CLear Text Infor
    ui->txtDevInfo->clear();

    ui->txtDevInfo->appendPlainText("Tên Thiết Bị:      " + QString::fromStdString(deviceName));
    ui->txtDevInfo->appendPlainText("ID Thiết Bị:      " + QString::fromStdString(deviceId));
    ui->txtDevInfo->appendPlainText("Vị Trí Thiết Bị:      " + QString::fromStdString(deviceLocation));

    if(Device::TEMPERATURE_SENSOR == deviceType)
    {
        ui->txtDevInfo->appendPlainText("Nhiệt Độ:      " + QString::number(deviceValue,'f',2) + " °C");
    }
    else if(Device::PRESSURE_SENSOR == deviceType)
    {
        ui->txtDevInfo->appendPlainText("Áp Suất:      " + QString::number(deviceValue,'f',2) + " Bar");
    }
    else if(Device::HUMIDITY_SENSOR == deviceType)
    {
        ui->txtDevInfo->appendPlainText("Độ Ẩm:      " + QString::number(deviceValue,'f',2) + " %%");
    }
    else if(Device::LIGHT_SWITCH == deviceType)
    {
        ui->txtDevInfo->appendPlainText("Ligh State:      " );
    }
    else
    {
        ui->txtDevInfo->appendPlainText("================= Invalid Device Selected ================= ");
    }

    qDebug() << "Selected Item " << itemIdx << " --- " << deviceName;
}

