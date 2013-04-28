/*
 * request.cpp
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

#include "request.h"

Request::Request(unsigned int id, const IView* from, int arg_0, int arg_1, const Glib::ustring& str)
  : m_Id(id), m_From(from), m_Int0(arg_0), m_Int1(arg_1), m_Str(str)
{
}

Request::~Request()
{
}

unsigned int 
Request::getId() 
{ 
  return m_Id;
}
int 
Request::getInt0() 
{ 
  return m_Int0;
}

int 
Request::getInt1() 
{ 
  return m_Int1;
}

const Glib::ustring& 
Request::getStr() 
{ 
  return m_Str;
}



