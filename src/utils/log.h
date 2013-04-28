/*
 * log.h
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
#ifndef UTILS_LOG_H
#define UTILS_LOG_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <glibmm/timer.h>
#include <glibmm/ustring.h>

#ifndef HERE
#define HERE __ASSERT_FUNCTION << ":" <<__FILE__<< ":" << __LINE__ << ": "
#endif

#ifndef PRETY_FUNCTION_NAME_
#define PRETTY_FUNCTION_NAME_ __ASSERT_FUNCTION                                                         
#endif

#ifndef LOG_STREAM
#define LOG_STREAM  std::cout
#define LOG_ENDLINE std::endl
#endif

#ifdef DEBUG
#define LOG(msg)  LOG_STREAM <<"  |I|" << HERE << msg << LOG_ENDLINE
#define LOGD(msg) LOG_STREAM <<"  |D|" << HERE << msg << LOG_ENDLINE
#define LOGE(msg) LOG_STREAM <<"  |E|" << HERE << msg << LOG_ENDLINE
class ScopeLogger {
 public:
  ScopeLogger(const char*scope_name)
  : name(scope_name) {
    LOG_STREAM <<"|{|" << name << ":" << LOG_ENDLINE;
    timer.start();
  }
  virtual ~ScopeLogger(){
    timer.stop();
    LOG_STREAM <<"|}|" << name << " elapsed:"<< timer.elapsed ()*1000 << "(ms)" << LOG_ENDLINE;
  }
 private:
  Glib::Timer timer;
  Glib::ustring name;
};

#define LOG_FUNCTION_SCOPE ScopeLogger scope_logger(PRETTY_FUNCTION_NAME_)
#else
#define LOG(msg)
#define LOGD(msg)
#define LOGE(msg)
#define LOG_FUNCTION_SCOPE
#endif /* #ifdef DEBUG */


#endif /* #ifndef UTILS_LOG_H */

