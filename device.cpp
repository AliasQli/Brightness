#include <string.h>

#include "include/device.h"
#include "include/util.h"

using namespace std;

char* initBuffer(size_t size){
	char *buff = (char*)malloc(RES_SIZE);

	if( buff == NULL) {
		perror("malloc");
		exit(-1);
	}

	memset(buff, 0, RES_SIZE);

	return buff;
}

void getFstWd(char* buff, size_t size) {
	size_t i = 0;
	while(true) {
		if (buff[i] == '\0' || i >= size) {
			break;
		}
		if (buff[i] == ' ') {
			buff[i] = '\0';
			break;
		}
		i++;
	}
}

void getDevices(list<string>& devices) {
	// init buff
	char *buff = initBuffer(RES_SIZE);

	// init fp
	FILE *fp = popen("xrandr --query | grep \" connected \"", "r");
	
	if (fp == NULL) {
		perror("popen error");
		free(buff);
		exit(-1);
	}

	// get devices
	devices.clear();
	log("devices: ");
    while (true) {
        fgets(buff, RES_SIZE, fp);
		getFstWd(buff, RES_SIZE);
		string str = buff;
		if (devices.size() > 0 && str == devices.back()) {
			break;
		}
		log(str + " ");
	    devices.push_back(buff);
    }
	log("\n");

	// release
	pclose(fp);
	free(buff);
}

void setDevicesBrightness(list<string>& devices, double brightness) {
	char* buff = initBuffer(RES_SIZE);

	for (list<string>::const_iterator iter = devices.begin(); iter != devices.end(); iter++) {
		string&& strBrightness = to_string(brightness);
		log("set brightness of device " + *iter + " to " + strBrightness + "\n");
		system(("xrandr --output " + *iter + " --brightness " + strBrightness).c_str());
	}
}