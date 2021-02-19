#ifndef HANDLER_SENDTEXT
#define HANDLER_SENDTEXT

#include <Keyboard.h>

namespace button {
    namespace handler {
        class SendText : public button::Handler {
            public:
                SendText(const char *t) {
                    text = t;
                }

                void setup() { }
                void up() {}

                void down() {
                    Keyboard.print(text);
                }
            private:
                const char *text;
        };
    }
}

#endif
