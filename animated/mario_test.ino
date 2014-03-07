// #define FORCE_SOFTWARE_SPI
// #define FORCE_SOFTWARE_PINS
#include <FastLED.h>
#include <SD.h>
#include <LowPower.h>

///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a color dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel on and then off, moving down the line of pixels.
//

// How many leds are in the strip?
#define NUM_LEDS 256

// Data pin that led data will be written out over
#define DATA_PIN 6

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];
File root;
File animation;

// Error, not animated
PROGMEM uint8_t warning[768] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 175, 127, 0, 255, 163, 71, 255, 163, 71, 255, 163, 71, 0, 0, 0, 0, 0, 0, 175, 127, 0,
    175, 127, 0, 175, 127, 0, 0, 0, 0, 255, 163, 71, 255, 163, 71, 255, 163, 71, 175, 127, 0, 175, 127, 0, 0, 0, 0, 0, 0, 0, 175, 127, 0, 175, 127, 0, 175, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 248, 56, 0, 175, 127, 0, 255, 163, 71, 255, 163, 71, 175, 127, 0, 0, 0, 0, 175, 127, 0, 175, 127, 0, 175, 127, 0, 175, 127, 0, 255, 163, 71, 248, 56, 0, 248, 56, 0, 175, 127, 0, 175, 127, 0,
    175, 127, 0, 175, 127, 0, 248, 56, 0, 248, 56, 0, 248, 56, 0, 248, 56, 0, 175, 127, 0, 175, 127, 0, 175, 127, 0, 255, 163, 71, 255, 163, 71, 175, 127, 0, 175, 127, 0, 175, 127, 0, 248, 56, 0, 248, 56, 0,
    248, 56, 0, 248, 56, 0, 175, 127, 0, 255, 163, 71, 175, 127, 0, 255, 163, 71, 255, 163, 71, 248, 56, 0, 248, 56, 0, 248, 56, 0, 255, 163, 71, 248, 56, 0, 248, 56, 0, 248, 56, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 56, 0, 248, 56, 0, 248, 56, 0, 248, 56, 0, 175, 127, 0, 175, 127, 0, 255, 163, 71, 255, 163, 71, 255, 163, 71, 255, 163, 71, 255, 163, 71, 248, 56, 0, 248, 56, 0,
    248, 56, 0, 248, 56, 0, 255, 163, 71, 255, 163, 71, 255, 163, 71, 255, 163, 71, 255, 163, 71, 175, 127, 0, 175, 127, 0, 248, 56, 0, 248, 56, 0, 248, 56, 0, 248, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 248, 56, 0, 248, 56, 0, 248, 56, 0, 255, 163, 71, 248, 56, 0, 248, 56, 0, 175, 127, 0, 255, 163, 71, 175, 127, 0, 255, 163, 71, 175, 127, 0, 175, 127, 0, 248, 56, 0, 248, 56, 0,
    0, 0, 0, 248, 56, 0, 255, 163, 71, 255, 163, 71, 175, 127, 0, 175, 127, 0, 255, 163, 71, 0, 0, 0, 175, 127, 0, 175, 127, 0, 248, 56, 0, 248, 56, 0, 248, 56, 0, 248, 56, 0, 175, 127, 0, 175, 127, 0,
    175, 127, 0, 175, 127, 0, 248, 56, 0, 248, 56, 0, 255, 163, 71, 175, 127, 0, 175, 127, 0, 175, 127, 0, 0, 0, 0, 255, 163, 71, 175, 127, 0, 255, 163, 71, 255, 163, 71, 0, 0, 0, 248, 56, 0, 0, 0, 0,
    0, 0, 0, 248, 56, 0, 0, 0, 0, 255, 163, 71, 255, 163, 71, 175, 127, 0, 0, 0, 0, 0, 0, 0, 175, 127, 0, 175, 127, 0, 255, 163, 71, 255, 163, 71, 255, 163, 71, 0, 0, 0, 175, 127, 0, 175, 127, 0,
    175, 127, 0, 0, 0, 0, 0, 0, 0, 255, 163, 71, 255, 163, 71, 255, 163, 71, 175, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 163, 71, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


void setup() {
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(2000);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(1);
    for (int led = 0; led < NUM_LEDS; led++) {
        leds[led] = CRGB::Black;
    }
    FastLED.show();
    SD.begin();
    root = SD.open("/");
    File animation = root.openNextFile();
    if (! animation) {
        display_warning();
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    }
}

void loop() {
    while (animation.available() >= 768) {
        for(int active_led = 0; active_led < NUM_LEDS; active_led++) {
            leds[active_led].r = animation.read();
            leds[active_led].g = animation.read();
            leds[active_led].b = animation.read();
        }
        FastLED.show();
        LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
    }
    // TODO: randomize
    File animation = root.openNextFile();
    if (! animation) {
        root.rewindDirectory();
        animation = root.openNextFile();
    }
}

void display_warning() {
    for(int active_led = 0; active_led < 32; active_led++) {
        leds[active_led].r = warning[(3*active_led)];
        leds[active_led].g = warning[(3*active_led)+1];
        leds[active_led].b = warning[(3*active_led)+2];
    }
    FastLED.show();
}
