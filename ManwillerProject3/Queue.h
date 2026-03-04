#ifndef COP4530_QUEUE_H
#define COP4530_QUEUE_H

#include <deque>

namespace cop4530 {

    template <typename T>
    class Queue {
    public: 
        //constructors and destructors
        Queue();
        ~Queue();
        Queue(const Queue &rhs);
        Queue(Queue &&rhs);

        Queue& operator=(const Queue &rhs);
        Queue& operator=(Queue &&rhs);

        //Accessor functions
        bool empty() const;
        int size() const;

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        //Modifier functions
        void push(const T& value);
        void push(T&& val);
        void pop();

    private:
        std::deque<T> container;
    };

    #include "Queue.hpp"
}

#endif
