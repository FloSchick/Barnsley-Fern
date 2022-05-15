#include <mutex>
#include <thread>
#include <iostream>
#include <exception>
#include <chrono>
#include <condition_variable>
#ifndef Buffer_H
#define Buffer_H

template <class T>
class Buffer
{
public:
    explicit Buffer(int size) : buf_(std::unique_ptr<T[]>(new T[size])),
                                max_size_(size)
    {
    }

    void put(T item)
    {

        std::unique_lock<std::mutex> lock(mutex_);
        //std::cout << "put in buffer" << std::endl;

        hasCapacity.wait(lock, [this] { if (this->full()) return false; else return true; });

        buf_[head_] = item;
        head_ = (head_ + 1) % max_size_;
        fill_++;
        full_ = head_ == tail_;
        hasData.notify_one();
        //std::cout << "put in buffer done" << std::endl;
    }
    T get()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        //std::cout << "read from buffer" << std::endl;
        hasData.wait_for(lock, std::chrono::seconds(2), [this] {if (this->empty()) return false; else return true; });
        if (empty())
        {
            throw std::runtime_error("Buffer timeout");
        }

        //Read data and advance the tail (we now have a free space)
        auto val = buf_[tail_];
        full_ = false;
        tail_ = (tail_ + 1) % max_size_;
        fill_--;
        hasCapacity.notify_one();
        //std::cout << "read from buffer done" << std::endl;
        return val;
    }
    void reset()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        head_ = tail_;
        full_ = false;
    }
    bool empty() const
    {
        //if head and tail are equal, we are empty
        return (!full_ && (head_ == tail_));
    }

    bool full() const
    {
        //If tail is ahead the head by 1, we are full
        return full_;
    }
    size_t capacity() const
    {
        return max_size_;
    }

    size_t size() const
    {
        size_t size = max_size_;

        if (!full_)
        {
            if (head_ >= tail_)
            {
                size = head_ - tail_;
            }
            else
            {
                size = max_size_ + head_ - tail_;
            }
        }

        return size;
    }

private:
    std::mutex mutex_;
    std::condition_variable hasCapacity, hasData;
    std::unique_ptr<T[]> buf_;
    size_t head_ = 0;
    size_t tail_ = 0;
    const size_t max_size_;
    bool full_ = false;
    size_t fill_ = 0;
    size_t empty_counter = 0;
};

#endif