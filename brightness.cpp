#include <unistd.h>
#include <fstream>

#include "include/brightness.h"
#include "include/util.h"

using namespace std;

string backlightPath = "/sys/class/backlight/";

vector<string> backlights = {"dell_backlight", "intel_backlight"};

bool isExist(const string& path) {
    return access(path.c_str(), 4) == 0;
}

void getFolder(string& path) {

	if (!isExist(backlightPath)) {
		error(backlightPath + " does not exist");
	}

	for (vector<string>::const_iterator iter = backlights.begin(); iter != backlights.end(); iter++) {
        path = backlightPath + *iter;
		if (isExist(path)) {
            log("find path: " + path + "\n");
			return;
		}
	}
    // else
	error("no available backlight folder");
}

unsigned int readNum(const string& path) {
    if (!isExist(path)) {
        error(path + " does not exist");
    }

    ifstream srcFile(path, ios::in);

    if(!srcFile) {
        error("open " + path + " failed");
    }
    unsigned int num;
    srcFile >> num;
    srcFile.close();
    return num;
}

unsigned int getMaxBrightness(const string& path) {
	return readNum(path + "/max_brightness");
}

unsigned int getBrightness(const string& path) {
	return readNum(path + "/actual_brightness");
}