#define cimg_display 0
#include "CImg.h"
#include <iostream>
#include "buffer.h"
#include "consumer.h"
#ifndef RCONSUMER_H
#define RCONSUMER_H

typedef std::pair<double, double> pair;

class real_consumer : public Consumer<pair>
{
public:
    real_consumer(Buffer<pair> &buffer) : Consumer(buffer) {}

private:
    static cimg_library::CImg<unsigned char> *jpg;
    bool consume(pair &data) override;
    void save_img();
};
#endif