#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;
  std::vector<T> data;

private:
  /// Add whatever helper functions and data members you need below
  PComparator comp;
  size_t heap_size;
  size_t num_child;

  void heapify(size_t i);
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : comp(c), num_child(m), heap_size(0) {
  if (m < 2) {
    throw std::invalid_argument("heap needs at least 2 children");
  }
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return heap_size;
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
  return heap_size == 0;
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T &item){
  heap_size++;
  data.push_back(item);
  size_t i = data.size() - 1;

  while (i > 0) {
    size_t parentIdx = (i - 1) / num_child;
    if (!comp(data[i], data[parentIdx])) {
      break;
    }
    std::swap(data[i], data[parentIdx]);
    i = parentIdx;
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const {
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::out_of_range("heap empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop() {
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::out_of_range("heap empty");

  }
  
  std::swap(data[0], data[data.size() - 1]);
  data.pop_back();
  heap_size--;
  heapify(0);
}


template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify(size_t i) {
  size_t n = data.size();
  while (true){
    size_t best = i;

    for (size_t j = num_child * i + 1; j < num_child * i + 1 + num_child; j++) {
      if (j < n && comp(data[j], data[best])) {
        best = j;
      }
    }
    // if not, swap
    if (best != i) {
      std::swap(data[i], data[best]);
      i = best;
    } else {
      break;
    }
  }
}


#endif

