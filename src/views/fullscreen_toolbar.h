/*
 * FullscreenToolbar.h
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
#ifndef FULLSCREENTOOLBAR_H
#define FULLSCREENTOOLBAR_H

#include <gtkmm/window.h>
#include <gtkmm/toolbar.h>

class FullscreenToolbar : public Gtk::Window
{
 public:
  FullscreenToolbar(Gtk::Window &transient, Gtk::Toolbar &toolbar);
  ~FullscreenToolbar();
 protected: 
  virtual void on_show();
 private:
  Gtk::Window &m_transient;

};




#endif /* ifndef FULLSCREENTOOLBAR_H */

