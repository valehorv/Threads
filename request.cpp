#include"request.h"

void Request::process()
{
    out_func("Process request: " + std::to_string(value));
}
