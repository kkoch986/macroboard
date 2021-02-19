#include "./HandlerInterface.h"

namespace button {
    namespace handler {
        class NoOp: public button::Handler {
            void setup() {}
            void up() {}
            void down() {}
        };
    }
}
