/*
 * request.h
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
#ifndef REQUEST_H
#define REQUEST_H

#include <glibmm/ustring.h>
#include <glibmm/objectbase.h>
#include "interface.h"

class Request : virtual public Glib::ObjectBase {
 public:
  Request(unsigned int id, const IView* from, int arg_0 = 0, int arg_1 = 0, const Glib::ustring& str = "");
  ~Request();
  unsigned int getId();
  int getInt0();
  int getInt1();
  const Glib::ustring& getStr();

 private:
  unsigned int m_Id;
  const IView* m_From;
  int m_Int0;
  int m_Int1;
  Glib::ustring m_Str;
};


#endif /* ifndef REQUEST_H */

