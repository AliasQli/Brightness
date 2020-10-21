#pragma once

#include <string>
#include <list>

#define RES_SIZE 1024

void getDevices(std::list<std::string>& devices);

void setDevicesBrightness(std::list<std::string>& devices, double brightness);