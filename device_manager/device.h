#ifndef DEVICE_H
#define DEVICE_H

#include <String>
#include <QDebug>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time() to seed srand()
#include <bits/stdc++.h>
#include <random>
#include <memory>


class Device
{

private:
    std::string _devName;
    std::string _devId;
    std::string _devLocation;
    int _devType;
public:
    Device(std::string name, std::string id, std::string location);
    const std::string getDevName();
    const std::string getDevId();
    const std::string getDevLocation();
    virtual const int getDevType() = 0;
    virtual const float getValue() = 0;

    enum {
        TEMPERATURE_SENSOR = 0 ,
        PRESSURE_SENSOR ,
        HUMIDITY_SENSOR ,
        LIGHT_SWITCH ,
        NUM_OF_SENSOR_TYPE
    };

    static bool isGenSeed;
    static std::default_random_engine gen;
    static std::uniform_real_distribution<double> distribution;
};


/* Class for Temperature Sensor */
class TemperatureSensor: public Device
{
private:

public:
    TemperatureSensor(std::string name, std::string id, std::string location);
    const int getDevType() override;

    const float getValue() override;
};

/* Class for Pressure Sensor */


/* Class for Humidity Sensor */


/* Class for Light Switch */



/* Simple Factory */
class DeviceFactory {
public:
   static std::unique_ptr<Device> createDevice(std::string name,std::string id, std::string location, int type);
};

#endif // DEVICE_H
