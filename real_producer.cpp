#include <random>
#include <mutex>
#include <iostream>
#include "real_producer.h"

typedef std::pair<double, double> pair;

std::random_device dev;                          // get random number from hardware
std::mt19937 engine(dev());                      // init random seed
std::uniform_int_distribution<int> dist(1, 100); //set ranges

bool real_producer::produce(pair &data)
{
    return calcFarn(&data);
}
int real_producer::randomNumber()
{

    return dist(engine);
}

bool real_producer::calcFarn(pair *data)
{
    if (iterations != 0)
    {
        int r = randomNumber();
        double x1, y1;
        pair start = *data;
        double x = start.first;
        double y = start.second;

        if (r == 1)
        {
            x1 = 0;
            y1 = 0.16 * y;
        }
        else if (r <= 86)
        {
            x1 = 0.85 * x + 0.04 * y;
            y1 = -0.04 * x + 0.85 * y + 1.6;
        }
        else if (r <= 93)
        {
            x1 = 0.2 * x - 0.26 * y;
            y1 = 0.23 * x + 0.22 * y + 1.6;
        }
        else
        {
            x1 = -0.15 * x + 0.28 * y;
            y1 = 0.26 * x + 0.24 * y + 0.44;
        }

        pair result(x1, y1);
        *data = result;
        iterations--;
        return true;
    }
    else
    {
        std::cout << "quitting producer" << std::endl;
        return false;
    }
}