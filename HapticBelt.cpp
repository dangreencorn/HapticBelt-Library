#include "HapticBelt.h"

HapticBelt::HapticBelt(Adafruit_NeoPixel *pixelStrip, int *vibrationMotors) {
	motors = vibrationMotors;
	strip = pixelStrip;

	angularDistanceLights = 360 / strip->numPixels();
    angularDistanceMotors = 90;//360 / sizeof(motors);
}

HapticBelt::~HapticBelt() {

}

void HapticBelt::setDirection(float dir, float err) {
	this.vibrateDirection(dir, err);
	this.lightDirection(dir, err);
}

void HapticBelt::vibrateDirection(float dir, float err) {
//	for (int i = 0; i < sizeof(motors); i++) {
//		if (abs(i*angularDistanceMotors - dir) < (err + 2/3 * angularDistanceMotors)) {
//			digitalWrite(motors[i], HIGH);
//		} else {
//			digitalWrite(motors[i], LOW);
//		}
//	}
    // fromt - motor[0]
    if (dir >= 300 || dir <= 60) {
        digitalWrite(motors[0], HIGH);
    } else {
        digitalWrite(motors[0], LOW);
    }
    // right - motor[1]
    if (dir >= 30 && dir <= 210) {
        digitalWrite(motors[1], HIGH);
    } else {
        digitalWrite(motors[1], LOW);
    }
    // left - motor[2]
    if (dir >= 150 && dir <= 330) {
        digitalWrite(motors[2], HIGH);
    } else {
        digitalWrite(motors[2], LOW);
    }
}

void HapticBelt::lightDirection(float dir, float err) {
	for (int i = 0; i < strip->numPixels(); i++) {
		if (abs(i*angularDistanceLights - dir) < (err + 2/3 * angularDistanceLights)) {
			if (abs(i*angularDistanceLights - dir) < (2/3 * angularDistanceLights)) {
				strip->setPixelColor(i, 255,0,0);
			} else {
				strip->setPixelColor(i, 0,255,0);	
			}
		} else {
			strip->setPixelColor(i, 0,0,255);
		}
	}
	strip->show();
}

void HapticBelt::signalLeft() {
    for(int i = 0; i < 5; i++) {
        this.setDirection(270, 90);
        delay(1000);
        this.clear();
        delay(500);
    }
}

void HapticBelt::signalRight() {
    for(int i = 0; i < 5; i++) {
        this.setDirection(90, 90);
        delay(1000);
        this.clear();
        delay(500);
    }
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
		strip->setPixelColor(i, 0,0,255);
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