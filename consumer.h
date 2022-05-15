#include "buffer.h"
#include "worker.h"
#include <exception>
#include <iostream>

#ifndef CONSUMER_H
#define CONSUMER_H
template <class T>
class Consumer : public Worker
{

public:
    Consumer(Buffer<T> &buff_) : m_buffer(buff_), Worker()
    {
    }

private:
    Buffer<T> &m_buffer;
    T data;
    bool step() override
    {
        bool result;
        try
        {
            data = m_buffer.get();
        }
        catch (const std::runtime_error &err)
        {
            std::cout << "quitting consumer" << std::endl;
            save_img();
            return false;
        }
        result = consume(data);

        return result;
    }

protected:
    virtual bool consume(T &data) = 0;
    virtual void save_img() = 0;
};
#endif