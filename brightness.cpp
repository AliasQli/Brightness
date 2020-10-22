#include <unistd.h>
#include <fstream>

#include "include/brightness.h"
#include "include/util.h"

using namespace std;

string backlightPath = "/sys/class/backlight/";

vector<string> backlights = {"dell_backlight", "intel_backlight"}; // the folders to scan under the backlightPath folder

bool isExist(const string& path) { // if it exists and can be read
    return access(path.c_str(), 4) == 0;
}

void getFolder(string& path) {

	if (!isExist(backlightPath)) {
		error(backlightPath + " does not exist or cannot be read", -3);
	}

	for (auto it = backlights.begin(); it != backlights.end(); it++) {
        path = backlightPath + *it;
		if (isExist(path)) {
            log("find path: " + path + "\n");
			return;
		}
	}
    // else
	error("no available backlight folder", -4);
}

unsigned int readNum(const string& path) {
    if (!isExist(path)) {
        error(path + " does not exist or cannot be read", -5);
    }

    ifstream srcFile(path, ios::in);

    if(!srcFile) {
        error("open " + path + " failed", -6);
    }
    unsigned int num;
    srcFile >> num; // warning: the program may stuck if the file is empty
    srcFile.close();
    return num;
}

unsigned int getMaxBrightness(const string& path) {
	return readNum(path + "/max_brightness");
}

unsigned int getBrightness(const string& path) {
	return readNum(path + "/actual_brightness"); // if it doesn't work, change "/actual_brightness" to "/brightness" may fix it
}