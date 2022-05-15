
#include <chrono>
#include <iostream>
#include "real_consumer.h"
#include "real_producer.h"

typedef std::pair<double, double> pair;

int main()
{
    auto start_time = std::chrono::steady_clock::now();

    Buffer<pair> circle(10000);
    pair start(0, 0);
    real_producer producer1(circle, 10000000, start);
    real_producer producer2(circle, 10000000, start);
    real_producer producer3(circle, 10000000, start);

    real_consumer consumer1(circle);
    real_consumer consumer2(circle);
    real_consumer consumer3(circle);
    real_consumer consumer4(circle);
    real_consumer consumer5(circle);

    producer1.start_thread();
    producer2.start_thread();
    producer3.start_thread();

    consumer1.start_thread();
    consumer2.start_thread();
    consumer3.start_thread();
    consumer4.start_thread();
    consumer5.start_thread();

    consumer1.join_thread();
    consumer2.join_thread();
    consumer3.join_thread();
    consumer4.join_thread();
    consumer5.join_thread();

    producer1.join_thread();
    producer2.join_thread();
    producer3.join_thread();

    auto end = std::chrono::steady_clock::now();

    // Store the time difference between start and end
    auto diff = end - start_time;
    std::cout << std::chrono::duration<double>(diff).count() << " s" << std::endl;
}