#ifndef SHARED_PTR_SHARED_PTR_H
#define SHARED_PTR_SHARED_PTR_H

template<typename T>
class shared_ptr {
public:

    explicit shared_ptr(T * t = nullptr): data_(t), counter_(new int(1)) {
        std::cout << "SP ctor" << std::endl;
    }

    // creates new shared_ptr with the same underlying raw pointer, sets counter to 1
    shared_ptr(const shared_ptr & other): data_(other.data_), counter_(other.counter_) {
        ++*counter_;
        std::cout << "SP copy ctor" << *counter_ << std::endl;
    }

    // decrements the counter for the old raw pointer, assigns the new one from 'other'
    shared_ptr & operator=(const shared_ptr &other) {
        if (other.data_ != data_) {
            --*counter_;
            if (*counter_ == 0) {
                delete data_;
                delete counter_;
            }
            data_ = other.data_;
            counter_ = other.counter_;
        }
        return *this;
    }

    // destructs underlying raw pointer if there're no other shared_ptr that owns it
    // otherwise decrements the counter
    ~shared_ptr() {
        --*counter_;
        if (*counter_ == 0) {
            delete data_;
            delete counter_;
        }
    }

    // releases stored pointer, replaces it with nullptr.
    // counter is decremented, but raw pointer is not deleted (even if it was the last shared_ptr).
    T * release() {
        T *tmp = data_;
        data_ = nullptr;
        --counter_;
        return tmp;
    }

    // replaces current raw pointer with a new one
    // counter is decremented, raw pointer is deleted if it was the last shared_ptr
    void reset(T * other) {
        std::cout << "reset" << std::endl;
        if (other == data_)
            return;

        --*counter_;
        if (*counter_ == 0) {
            delete data_;
        }
        data_ = other;
        *counter_ = 1;
    }

    // get the underlying raw pointer. counter is not changed
    T * get() {
        return data_;
    }

    // dereference underlying pointer
    T operator*() {
        return *data_;
    }

    // returns underlying pointer in order to access one of its members
    T * operator->() {
        return data_;
    }

private:
    T *data_;
    int *counter_ = nullptr;
};

#endif //SHARED_PTR_SHARED_PTR_H
