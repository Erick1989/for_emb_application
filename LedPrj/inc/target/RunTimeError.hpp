#include <string>
#include <stdint.h>

class RuntimeError{
    public:
    void log_error(uint8_t * error_msg, uint8_t * file,  uint32_t line);
};