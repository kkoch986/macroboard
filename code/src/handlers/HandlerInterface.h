#ifndef HANDLER_INTERFACE
#define HANDLER_INTERFACE

namespace button {
    
    class Handler {
        public:
            virtual void setup() = 0;
            virtual void up() = 0;
            virtual void down() = 0;
    };
}

#endif
