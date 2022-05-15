#include "buffer.h"
#include "worker.h"
template <class T>
class Producer : public Worker
{

public:
    Producer(Buffer<T> &buff_, T data_) : m_buffer(buff_), data(data_), Worker()
    {
    }

private:
    Buffer<T> &m_buffer;
    T data;
    bool step() override
    {
        bool result;
        //return false;
        // produce new value par and give to buffer
        result = produce(data);
        m_buffer.put(data);
        return result;
    }

protected:
    virtual bool produce(T &data) = 0;
};