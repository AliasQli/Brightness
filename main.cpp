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
	unsigned int prevBrightness, brightness;

	unsigned int i = 0;
	
	while (true) {
		brightness = getBrightness(path);

		if (i == 0) {
			getDevices(devices);
			setDevicesBrightness(devices, (float)brightness/maxBrightness);
			prevBrightness = brightness;
			i = RESCAN_CYCLES;
		} else if (brightness != prevBrightness) {
			setDevicesBrightness(devices, (float)brightness/maxBrightness);
			prevBrightness = brightness;
		}
		
		i--;

		usleep(SLEEP_US);
	}

	return 0;
}