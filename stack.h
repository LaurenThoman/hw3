#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T> {
public:
  // constructor
  Stack() : std::vector<T>() {}

  // destructor
  ~Stack() {}

  // true if the stack empty
  bool empty() const {
    return std::vector<T>::empty();
  }

  // return num of elements in stack
  size_t size() const {
    return std::vector<T>::size();
  }

  // push onto the stack O(1)
  void push(const T& item) {
    std::vector<T>::push_back(item);
  }

  // remove top element from stack
  // throws std::underflow_error if stack empty
  void pop() {
    if (empty()) {
      throw std::underflow_error("pop() called on an empty stack");
    }
    std::vector<T>::pop_back();
  }

  // returns const ref to top element
  // throws std::underflow_error if stack empt
  const T& top() const {
    if (empty()) {
      throw std::underflow_error("top() called on an empty stack");
    }
    return std::vector<T>::back();
  }
};


#endif