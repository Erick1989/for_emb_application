#include <string>
#include <stdint.h>

class iRuntimeError{
    public:
    virtual void log_error(uint8_t * error_msg, uint8_t * file,  uint32_t line)=0;
};

class RuntimeError:iRuntimeError
{
public:
    void log_error(uint8_t * error_msg, uint8_t * file,  uint32_t line);
    uint8_t num_errors;
};