#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <functional>
#include <stdexcept>


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

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data_;
  size_t m_;
  PComparator c_;
  void heapify(bool direction, size_t index);

};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m_(m), c_(c)
{
  if (m_ < 1)
  {
    throw std::invalid_argument("Invalid Value");
  }
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{
  
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T &item)
{
  data_.push_back(item);
  heapify(false, data_.size() - 1);
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
  return data_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const
{
  return data_.size();
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify(bool direction, size_t index)
{
  if (direction) //up
  {
    size_t size = data_.size();
    while (true)
    {
      size_t smallerChildIndex = m_ * index + 1;
      if (smallerChildIndex >= size) //no children
      {
        return;
      }
      for (size_t i = 1; i < m_; i++) //check all children of the node
      {
        size_t largerChildIndex = m_ * index + 1 + i;
        if(largerChildIndex < size && c_(data_[largerChildIndex], data_[smallerChildIndex]))
        {
          smallerChildIndex = largerChildIndex;
        }
      }
      if(!c_(data_[smallerChildIndex], data_[index]))
      {
        break;
      } 
      std::swap(data_[index], data_[smallerChildIndex]); //swap child and parent
      index = smallerChildIndex;
    }
  }
  else //down
  {
    while(index > 0)
    {
      size_t parent = (index - 1) / m_;

      if (c_(data_[index], data_[parent]))
      {
        std::swap(data_[index], data_[parent]);
        index = parent;
      }
      else
      {
        break;
      }
    }
  }
}
// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty())
  {
    throw std::underflow_error("Heap is empty");
  }
  return data_.front();
  
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty())
  {
    throw std::underflow_error("Heap is empty");
  }
  std::swap(data_.front(), data_.back());
  data_.pop_back();
  if (!empty())
  {
    heapify(true, 0);
  }
}
#endif

