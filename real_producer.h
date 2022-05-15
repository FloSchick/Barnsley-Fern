#include <mutex>
#include "producer.h"
#include "buffer.h"
#ifndef RPRODUCER_H
#define RPRODUCER_H

typedef std::pair<double, double> pair;

class real_producer : public Producer<pair>
{
public:
    real_producer(Buffer<pair> &buffer, size_t iterations_, pair start_point)
        : Producer(buffer, start_point), iterations(iterations_)
    {
    }

private:
    size_t iterations;

    int randomNumber();
    bool calcFarn(pair *data);
    bool produce(pair &data) override;
};
#endif