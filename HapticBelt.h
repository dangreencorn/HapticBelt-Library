#ifndef HAPTIC_BELT
#define HAPTIC_BELT

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class HapticBelt {
private:
	Adafruit_NeoPixel* strip;
    int motors[];
    float angularDistanceLights;
    float angularDistanceMotors;

public:
    HapticBelt(Adafruit_NeoPixel* pixelStrip, int vibrationMotors[]);
    ~HapticBelt();
    void setDirection(float dir, float err);
    void vibrateDirection(float dir, float err);
    void lightDirection(float dir, float err);
    void clear();
    void clearVibration();
    void clearLight();
    float getDirectionFromCompass(float heading);
};

#endif