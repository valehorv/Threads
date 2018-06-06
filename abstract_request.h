#ifndef ABSTRACT_REQUEST_H
#define ABSTRACT_REQUEST_H

class AbstractRequest{
public:
    virtual void set_value(int value) = 0;
    virtual void process() = 0;
};

#endif // ABSTRACT_REQUEST_H
