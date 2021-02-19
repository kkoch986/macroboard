#include <Arduino.h>
#include "./Button.h"

namespace button {

    Button::Button(Handler *k, uint8_t p, uint8_t li) {
        handler = k;
        buttonPin = p;
        ledIndex = li;
    }

    void Button::setup() {
        pinMode(buttonPin, INPUT_PULLUP);
        handler->setup();
    }

    void Button::down() {
        handler->down();
    }

    void Button::up() {
        handler->up();
    }

    unsigned long Button::pressedTime() {
        if( isDown == 0 ) {
            return 0;
        }
        return millis() - lastPressed;
    }

    void Button::update() {
        uint8_t state = digitalRead(buttonPin);

        // is the button down currently?
        if(state == LOW) {
            // if it was not down on the previous frame, start the debounce timer
            if(lastPressed == 0) {
                lastPressed = millis();
                isDown = 0;
            } else if(isDown == 0 && millis() - lastPressed > debounceTime) {
                isDown = 1;
                down();
            }
        } else if(isDown == 1) {
            // button is released, but down is still set meaning we havent sent a release event yet
            isDown = 0;
            up();
        }
    }
}
