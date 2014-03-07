// #define FORCE_SOFTWARE_SPI
// #define FORCE_SOFTWARE_PINS
#include "FastLED.h"

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

// This function sets up the ledsand tells the controller about them
void setup() {
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(2000);
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(16);
    for (int led = 0; led < NUM_LEDS; led++) {
      leds[led] = CRGB::Black;
    }
    FastLED.show();
    delay(3000);
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
   for (int run = 0; run < 4 ; run++) {
      // Move a single led at a predefined color
      for(int active_led = 0; active_led < NUM_LEDS; active_led++) {
         switch (run) {
             case 0:
               leds[active_led] = CRGB::White;
               break;
             case 1:
               leds[active_led] = CRGB::Red;
               break;
             case 2:
               leds[active_led] = CRGB::Green;
               break;
             case 3:
               leds[active_led] = CRGB::Blue;
               break;
             default:
               leds[active_led] = CRGB::Black;
         }
         // Turn our current led on to predefined color, then show the leds
         //leds[active_led] = CRGB::White;

         // Show the leds (only one of which is set to predefined color, from above)
         FastLED.show();

         // Wait a little bit
         delay(50);

         // Turn our current led back to black for the next loop around
         leds[active_led] = CRGB::Black;
      }
   }
}
