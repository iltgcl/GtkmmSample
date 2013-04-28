/*
 * notifier.h
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
#ifndef MVC_NOTIFIER_H
#define MVC_NOTIFIER_H

#include <glibmm/main.h>
#include <glibmm/refptr.h>

#include "response.h"
#include "request.h"

#include "utils/async_queue.h"


class Notifier : public Glib::Source {
  public:
   static Glib::RefPtr<Notifier> create();
  protected:
    Notifier();
    ~Notifier();

    virtual bool prepare(int& timeout);
    virtual bool check();
    virtual bool dispatch(sigc::slot_base* slot);
  private:
    AsyncQueue<Glib::RefPtr<Response> > m_AsyncQueue;

};

#endif /* ifndef MVC_NOTIFIER_H */

