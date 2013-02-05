/*
 * sample_statusbar.c
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

#include "sample_statusbar.h"


SampleStatusbar::SampleStatusbar()
{
}

SampleStatusbar::~SampleStatusbar()
{
}

void 
SampleStatusbar::asyncTaskBegin(const Glib::ustring &cmd)
{
  type_map_cmds::iterator iter = m_mapCmds.find(&cmd);
  if(iter != m_mapCmds.end()) {
    std::cout << " Cmd already begin." << std::endl;
  } else {
    //unsigned int msg_id = 
  }
}

void 
SampleStatusbar::asyncTaskEnd(const Glib::ustring &cmd)
{
}


