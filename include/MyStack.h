// Copyright 2021 Dev-will-work
#ifndef INCLUDE_MYSTACK_H_
#define INCLUDE_MYSTACK_H_
#include <iostream>
#include <utility>
template <typename T>
class MyStack {
 public:
  explicit MyStack(int size) {
    try {
     if (size <= 0) throw 0;
     max_size = size;
      container = new T[size]{0};
    } catch (int low) {
      std::cerr << "Wrong size for stack\n";
      exit(1);
    } catch (...) {
      std::cerr << "Not enough memory for stack\n";
      exit(2);
    }
  }

  MyStack(const MyStack& that) {
    T* temp;
    if (this->container == nullptr) this->container = new T[that.max_size]{0};
    if (this->max_size == 0) this->max_size = that.max_size;
    if (that.top != nullptr) {
      temp = that.container;
      while (temp != nullptr) {
        if (top == nullptr) top = container;
        else
          ++top;
        *top = *temp;
        if (temp == that.top) temp = nullptr;
        else
          ++temp;
      }
    }
  }  // copy

  MyStack(MyStack&& that) : container(that.container), top(that.top),
    max_size(that.max_size) {
  that.top = nullptr;
  that.container = nullptr;
  that.max_size = 0;
  }  // move

  ~MyStack() { delete[] container; }

  T get() const {
    try {
      if (top == nullptr) throw 0;
    } catch (int ex) { std::cerr << "can't get value from the empty stack\n";
      return 0;
      }
    return *top;
  }

  T pop() {
    try {
     if (top == nullptr) throw 0;
    } catch (int ex) { std::cerr << "can't pop from the empty stack\n";
    return 0;
    }
    T temp = *top;
    *top = 0;
    if (top == container) top = nullptr;
    else
      top--;
    return temp;
  }

  void push(T value, bool autoextension = false) {
    try {
      if (isFull() && autoextension) expand();
      else if (isFull()) throw 9;
    } catch (int ex) {
      std::cerr <<
      "Stack is full!Use expand before pushing or push with flag\n";
      return;
    }
  if (top == nullptr) top = container;
  else
    ++top;
  *top = value;
  if (autoextension) expand();
  }

  void expand() {
    if (isFull()) {
       MyStack<T> temp(std::move(*this));
    this->max_size = 2 * temp.max_size;
    try {
      this->container = new T[this->max_size]{0};
    } catch (...) {
      std::cerr << "Can't allocate greater stack\n";
    }
    temp.top = temp.container;
    while (temp.top != nullptr) {
      if (top == nullptr) top = container;
      else
        ++top;
      *(this->top) = *(temp.top);
      if (temp.isFull()) temp.top = nullptr;
      else
        temp.top++;
    }
    } else {
      return;
    }
  }

  bool isFull() const {return top == container + max_size - 1;}

  bool isEmpty() const {return top == nullptr;}

 private:
  int max_size = 0;
  T* top = nullptr;
  T* container = nullptr;
};
#endif  // INCLUDE_MYSTACK_H_
