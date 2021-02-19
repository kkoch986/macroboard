#ifndef HANDLER_CHATSEND
#define HANDLER_CHATSEND

#include <Keyboard.h>

/**
 * Chat send works the same as send text except:
 *   1. It will send the message on the key down
 *   2. It will send a "\n" on key up
 * It seems like, at least on slack, a short delay is needed 
 *  in order for it to pick up on things like emojis which need substitution.
 */
namespace button {
    namespace handler {
        class ChatSend : public button::Handler {
            public:
                ChatSend(const char *t) {
                    text = t;
                }

                void setup() { }
                void up() {
                    Keyboard.print("\n");
                }

                void down() {
                    Keyboard.print(text);
                }
            private:
                const char *text;
        };
    }
}

#endif
