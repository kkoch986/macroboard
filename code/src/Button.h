#ifndef BUTTON
#define BUTTON

#include <Arduino.h>
#include "./handlers/HandlerInterface.h"

namespace button {
    // TODO: make buttson work / program some macros!
    // Button helper class for handling press/release and debouncing
    class Button {
      public:
      uint8_t ledIndex;
      Button(Handler *k, uint8_t p, uint8_t li);
      void setup();
      void update();
      unsigned long pressedTime();

      private:
      Handler *handler;
      uint8_t buttonPin;
      unsigned long debounceTime = 30;
      unsigned long lastPressed = 0;
      boolean isDown = 0;

      void up();
      void down();
    };
}

#endif
