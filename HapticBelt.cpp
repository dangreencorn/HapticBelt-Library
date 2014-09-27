#include "HapticBelt.h"

HapticBelt::HapticBelt(Adafruit_NeoPixel *pixelStrip, int vibrationMotors[]) {
	motors = vibrationMotors;
	strip = pixelStrip;

	angularDistanceLights = 360 / strip->numPixels();
	angularDistanceMotors = 360 / sizeof(motors);
}

HapticBelt::~HapticBelt() {

}

void HapticBelt::setDirection(float dir, float err) {
	this.vibrateDirection(dir, err);
	this.lightDirection(dir, err);
}

void HapticBelt::vibrateDirection(float dir, float err) {
	for (int i = 0; i < sizeof(motors); i++) {
		if (abs(i*angularDistanceMotors - dir) < (err + 2/3 * angularDistanceMotors)) {
			digitalWrite(motors[i], HIGH);
		} else {
			digitalWrite(motors[i], LOW);
		}
	}
}

void HapticBelt::lightDirection(float dir, float err) {
	for (int i = 0; i < strip->numPixels(); i++) {
		if (abs(i*angularDistanceLights - dir) < (err + 2/3 * angularDistanceLights)) {
			if (abs(i*angularDistanceLights - dir) < (2/3 * angularDistanceLights)) {
				strip->setPixelColor(i, keyColor);
			} else {
				strip->setPixelColor(i, washColor);	
			}
		} else {
			strip->setPixelColor(i, backgroundColor);
		}
	}
	strip->show();
}

void HapticBelt::clear() {
	this.clearVibration();
	this.clearLight();
}

void HapticBelt::clearVibration() {
	for (int i = 0; i < sizeof(motors); i++) {
		digitalWrite(motors[i], LOW);
	}
}

void HapticBelt::clearLight() {
	for (int i = 0; i < strip->numPixels(); i++) {
		strip->setPixelColor(i, backgroundColor);
	}
	strip->show();
}
// gets the desired position on the belt
// for the given orientation (heading of the belt wearer)
// relative to magnetic compass bearing
float HapticBelt::getDirectionFromCompass(float heading, float compassDirection) {
	float positionOnBelt = compassDirection - heading;

	if (positionOnBelt < 0) {
		positionOnBelt += 360;
	} else if (positionOnBelt >= 360) {
		positionOnBelt -= 360;
	}
}