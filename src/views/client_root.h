/*
 * client_root.h
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
#ifndef CLIENT_ROOT_H
#define CLIENT_ROOT_H

#include <gtkmm/paned.h>
#include <gtkmm/button.h>

class ClientRoot : public Gtk::HPaned 
{
 public:
  ClientRoot();
  virtual ~ClientRoot();
  Glib::PropertyProxy<bool> property_can_save();
  Glib::PropertyProxy<bool> property_can_save_as();
  Glib::PropertyProxy<bool> property_can_undo();
  Glib::PropertyProxy<bool> property_can_redo();
  Glib::PropertyProxy<bool> property_can_cut();
  Glib::PropertyProxy<bool> property_can_copy();
  Glib::PropertyProxy<bool> property_can_paste();
  Glib::PropertyProxy<bool> property_can_delete();
  Glib::PropertyProxy<bool> property_can_select_all();
 protected:
  void onTestProperties();
 private:
  Glib::Property<bool> prop_can_save;
  Glib::Property<bool> prop_can_save_as;
  Glib::Property<bool> prop_can_undo;
  Glib::Property<bool> prop_can_redo;
  Glib::Property<bool> prop_can_cut;
  Glib::Property<bool> prop_can_copy;
  Glib::Property<bool> prop_can_paste;
  Glib::Property<bool> prop_can_delete;
  Glib::Property<bool> prop_can_select_all;
  Gtk::Button m_SidePane;
  Gtk::Button m_MainPane;

};





#endif /* ifndef CLIENT_ROOT_H */

