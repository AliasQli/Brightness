#include <unistd.h>
#include <string>
#include <list>

#include "include/device.h"
#include "include/brightness.h"

#define SLEEP_US 		50000U 	// 50ms or 1/20s
#define RESCAN_CYCLES 	20U 	// 1s

using namespace std;

int main() {
	list<string> devices;
	getDevices(devices);

	string path;
	getFolder(path);

	unsigned int maxBrightness = getMaxBrightness(path);
	unsigned int prevBrightness = getBrightness(path);
	unsigned int brightness;
	setDevicesBrightness(devices, (double)prevBrightness/maxBrightness);

	unsigned int i = RESCAN_CYCLES;
	
	while (true) {
		brightness = getBrightness(path);
		if (brightness != prevBrightness) {
			setDevicesBrightness(devices, (double)brightness/maxBrightness);
			prevBrightness = brightness;
		}

		if (i == 0) {
			getDevices(devices);
			i = RESCAN_CYCLES;
		}
		i--;

		usleep(SLEEP_US);
	}

	return 0;
}