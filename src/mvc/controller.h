/*
 * controller.h
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
#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

#include <vector>
#include <glibmm/threadpool.h>
#include <glibmm/refptr.h>

#include "interface.h"
#include "cmd_id.h"
#include "notifier.h"

class Controller : public Glib::ThreadPool, implements IController {
 public:
  Controller();
  virtual ~Controller();
  virtual void addModel(int index, IModel* model);
  virtual IModel* getModel(int index);
  virtual void request(const Request *req);


 private:
  std::vector<IModel*> m_ModelVector;
  Glib::RefPtr<Notifier> m_refNotifier;
};

#endif /* #ifndef MVC_CONTROLLER_H */
