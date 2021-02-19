#include <Arduino.h>
#include <FastLED.h>
#include <Keyboard.h>
#include "./Button.h"
#include "./handlers/NoOp.h"
#include "./handlers/SendText.h"
#include "./handlers/ChatSend.h"

#define NEOPIXEL_PIN 10
#define NUM_PIXELS 12
#define NUM_BUTTONS 12
#define PIXEL_TYPE WS2812
#define COLOR_ORDER GRB


// TODO: break the classes out into separate files
// TODO: support different kinds of lighting
// TODO: take all the constants as args
// Lights Helper for managing the entire set of LEDs
class Lights {
  public:
    void setup() {
        FastLED.addLeds<PIXEL_TYPE,A3,COLOR_ORDER>(leds, NUM_PIXELS);
        FastLED.setBrightness(100);
        cycleEach(50); 
        cycleEachReverse(50);
    }

    void update(button::Button buttons[]) {
        // paint the base color
        fill_rainbow(leds, NUM_PIXELS, step, NUM_PIXELS);
        // fill_solid(leds, NUM_PIXELS, CRGB::Red);
        
        // update all the lights with keys pressed
        for(int x = 0 ; x < NUM_BUTTONS ; x++) {
            if(buttons[x].pressedTime() > 0) {
               leds[buttons[x].ledIndex] = CRGB::White;
            }
        }

        // show and advance th ts
        FastLED.show();
        step += 0.025;
        if(step >= 1024) {
            step = 0;
        }
    }
  private:
    CRGB leds[NUM_PIXELS];
    double step = 0;

    void cycleEachReverse(int d) {
        for(int a = NUM_PIXELS-1 ; a >= 0 ; a--) {
            for(int x = 0 ; x < NUM_PIXELS ; x++) {
                if(a == x) {
                    leds[x] = CRGB::White;
                } else {
                    leds[x] = CRGB::Black;
                }
            }
            FastLED.show();
            delay(d);
        }
    }


    void cycleEach(int d) {
        for(int a = 0 ; a < NUM_PIXELS ; a++) {
            for(int x = 0 ; x < NUM_PIXELS ; x++) {
                if(a == x) {
                    leds[x] = CRGB::White;
                } else {
                    leds[x] = CRGB::Black;
                }
            }
            FastLED.show();
            delay(d);
        }
    }
};

button::handler::NoOp noop;
button::handler::SendText plus("+ ");
button::handler::SendText minus("- ");
button::handler::ChatSend thumbsUp(":thumbsup:");
button::handler::ChatSend sendX(":x:");
button::handler::ChatSend joy(":joy:");
button::handler::ChatSend rofl(":rolling_on_the_floor_laughing:");
button::Button buttons[] = {
    { &plus,      7,  6 },
    { &minus,     6,  7 },
    { &thumbsUp,  8,  5 },
    { &sendX,    15, 11 },
    { &joy,      14,  8 },
    { &rofl,      5,  0 },
    { &noop,      9,  4 },
    { &noop,     10, 10 },
    { &noop,     16,  9 },
    { &noop,      4,  1 },
    { &noop,      2,  3 },
    { &noop,      3,  2 },
};
Lights lights;

void setup() {
    Keyboard.begin();
    lights.setup();

    for(int x = 0 ; x < NUM_BUTTONS ; x++) {
        buttons[x].setup();
    }
}

void loop() {
    for(int x = 0 ; x < NUM_BUTTONS ; x++) {
        buttons[x].update();
    }
    lights.update(buttons);    
}

