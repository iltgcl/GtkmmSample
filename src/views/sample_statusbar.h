/*
 * sample_statusbar.h
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
#ifndef SAMPLE_STATUSBAR_H
#define SAMPLE_STATUSBAR_H

#include <gtkmm/statusbar.h>
#include <gtkmm/spinner.h>
#include <gtkmm/label.h>
#include <map>
#include <iostream>

class SampleStatusbar : public Gtk::Statusbar
{
 public: 
  SampleStatusbar();
  virtual ~SampleStatusbar();
  void asyncTaskBegin(const Glib::ustring &cmd);
  void asyncTaskEnd(const Glib::ustring &cmd);
 private:
  typedef std::map<const Glib::ustring*, unsigned int> type_map_cmds;
  type_map_cmds m_mapCmds;

};


#endif /* ifndef SAMPLE_STATUSBAR_H */

