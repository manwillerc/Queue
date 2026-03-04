#include <stdexcept>
#include <utility>

using namespace std;

//Default constructor
template <typename T>
Queue<T>::Queue() {}

//Destructor
template <typename T>
Queue<T>::~Queue() {}

//Copy Constructor
template <typename T>
Queue<T>::Queue(const Queue &rhs) {
    container = rhs.container;
}

//Move Constructor
template <typename T>
Queue<T>::Queue(Queue<T>&& rhs) {
    container = std::move(rhs.container);
    rhs.container.clear();

}

//operator= override (copy)
template <typename T>
Queue<T>& Queue<T>::operator= (const Queue<T>& rhs) {
    if(this != &rhs) {
        container = rhs.container;
    }
    return *this;
}

//operator= override(move)
template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T> &&rhs) {
    if(this != &rhs) {
        container = std::move(rhs.container);
        rhs.container.clear();
    }
    return *this;
}

//check if queue is empty
template <typename T>
bool Queue<T>::empty() const{
    return container.empty();
}

//return size of queue
template <typename T>
int Queue<T>::size() const{
    return container.size();
}

//return value at front of queue
template <typename T>
T& Queue<T>::front() {
    if (container.empty()==true) {
        throw std::out_of_range("Queue::front() called on empty queue");
    }
    return container.front();
}

//return value at back of queue
template <typename T>
T& Queue<T>::back() {
    if (container.empty() == true) {
        throw std::out_of_range("Queue::back() called on empty queue");
    }
    return container.back();
}

//add argument to back of queue(copy)
template <typename T>
void Queue<T>::push(const T& val) {
    container.push_back(val);
}

//add argument to back of queue(move)
template <typename T>
void Queue<T>::push(T&& val) {
    container.push_back(std::move(val));
}

//remove value at fron of queue
template <typename T>
void Queue<T>::pop() {
    if (container.empty()==true) {
        throw std::out_of_range("Queue::pop() called on empty queue");
    }
    container.pop_front();
}

