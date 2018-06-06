#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include"abstract_request.h"

using namespace std;

typedef void (*log_function)(string text);

class Request : public AbstractRequest
{
    int value;
    log_function out_func;
public:
    void set_value(int value){this->value = value;}
    void set_output(log_function func){out_func = func;}
    void process();
    void finish();
};

#endif // REQUEST_H
