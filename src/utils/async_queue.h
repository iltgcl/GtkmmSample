/*
 * async_queue.h
 *
 * Copyright (C) 2012 - Lei.Cao
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * $Id$
 */
#ifndef UTILS_ASYNC_QUEUE_H
#define UTILS_ASYNC_QUEUE_H

#include <list>
#include <glibmm/thread.h>
#include <glibmm/refptr.h>

#include "utils/log.h"

template <class T>
class AsyncQueue
{
 public:
  AsyncQueue() {}
  ~AsyncQueue(){}
  void push(const T& item);
  void pop(T& item);

  /* Returns the length of the queue, negative values mean waiting threads,
   * positive values mean available entries in the queue 
   */
  int length();
 private:
  Glib::Mutex m_Mutex;
  Glib::Cond m_Cond;
  std::list<T> m_Lists;
  int m_WaitingThreads;
};

template <class T>
void AsyncQueue<T>::push(const T& item)
{
  Glib::Mutex::Lock lock (m_Mutex);
  m_Lists.push_front(item);
  if(m_WaitingThreads > 0) {
    m_Cond.signal();
  }
} 
  
template <class T>
void AsyncQueue<T>::pop(T& item)
{ 
  Glib::Mutex::Lock lock (m_Mutex);
  if(m_Lists.empty()) {
    m_WaitingThreads++;
    while(m_Lists.empty()) {
      m_Cond.wait(m_Mutex);
    }
    m_WaitingThreads--;
  } 
  item = m_Lists.back();
  m_Lists.pop_back();
}   
  
  
template <class T>
int AsyncQueue<T>::length()
{ 
  Glib::Mutex::Lock lock (m_Mutex);
  return m_Lists.size() - m_WaitingThreads;
}


#endif /* ifndef UTILS_ASYNC_QUEUE_H */

