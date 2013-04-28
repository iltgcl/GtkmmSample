/*
 * notifier.cpp
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

#include "notifier.h"
#include "response.h"
#include "request.h"

//static 
Glib::RefPtr<Notifier> Notifier::create()
{
  return Glib::RefPtr<Notifier>(new Notifier());
}

Notifier::Notifier()
  : m_AsyncQueue()
{
  //set_priority(Glib::PRIORITY_DEFAULT);
}

Notifier::~Notifier()
{
}

bool 
Notifier::prepare(int& timeout)
{
  timeout = 50;
  return (m_AsyncQueue.length() > 0);
}

bool 
Notifier::check()
{
  return (m_AsyncQueue.length() > 0);
}

bool 
Notifier::dispatch(sigc::slot_base* slot)
{
  return false;
}


