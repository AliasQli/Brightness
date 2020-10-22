#include <string.h>

#include "include/device.h"
#include "include/util.h"

using namespace std;

char* initBuffer(size_t size){
	char *buff = (char*)malloc(RES_SIZE);

	if( buff == NULL) {
		error("malloc", -1);
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
		if (buff[i] == ' ') { // replace the first ' ' with '\0'
			buff[i] = '\0';
			break;
		}
		i++;
	}
}

void getDevices(list<string>& devices) {

	char *buff = initBuffer(RES_SIZE);

	FILE *fp = popen("xrandr --query | grep \" connected \"", "r"); //exec `xrandr --query | grep " connected "`
	
	if (fp == NULL) {
		free(buff);
		error("popen error", -2);
	}

	devices.clear(); // the function would be executed multiple times
	log("devices: ");
    while (true) {
        fgets(buff, RES_SIZE, fp);
		getFstWd(buff, RES_SIZE);
		string str = buff;
		if (devices.size() > 0 && str == devices.back()) { // when having reached the last line of output, it will repeatedly read in the same
			break;
		}
		log(str + " ");
	    devices.push_back(buff); // enque them in the scanned order
    }
	log("\n");

	pclose(fp);
	free(buff);
}

void setDevicesBrightness(list<string>& devices, float brightness) {
	string&& strBrightness = to_string(brightness);

	// exec `xrandr --output <device> --brightness <num>` for each device
	for (auto it = devices.begin(); it != devices.end(); it++) {
		log("set brightness of device " + *it + " to " + strBrightness + "\n");
		system(("xrandr --output " + *it + " --brightness " + strBrightness).c_str());
	}
}