#include "devicemanager.h"

std::unique_ptr<deviceManager> deviceManager::instance = nullptr;

// deviceManager Constructor
deviceManager::deviceManager() {
    qDebug() << "deviceManager Constructor Called";
}

// static method to create/get instance
deviceManager& deviceManager::getInstance()
{
    if(nullptr == instance)
    {
        instance = std::unique_ptr<deviceManager>(new deviceManager());
    }

    return *instance;
}

void deviceManager::addDevice(std::unique_ptr<Device> dev)
{
    devices.push_back(std::move(dev));
}


const std::vector<std::unique_ptr<Device>>& deviceManager::getDevices()
{
    return devices;
}
