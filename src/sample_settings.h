/*
 * sample_settings.h
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
#ifndef SAMPLE_SETTINGS_H
#define SAMPLE_SETTINGS_H

#include <glibmm/object.h>
#include <giomm.h>

class SampleSettings : public Glib::Object 
{
 public:
  const static Glib::ustring KEY_WINDOW_STATE;
  const static Glib::ustring KEY_WINDOW_WIDTH;
  const static Glib::ustring KEY_WINDOW_HEIGHT;
  const static Glib::ustring KEY_TOOLBAR_VISIBLE;
  const static Glib::ustring KEY_STATUSBAR_VISIBLE;

  static SampleSettings* getDefault();
  int getWindowState();
  void setWindowState(int state);
  void getWindowSize(int& width, int& height);
  void setWindowSize(int width, int height);
  bool getToolbarVisible();
  bool getStatusbarVisible();
  void setToolbarVisible(bool visible);
  void setStatusbarVisible(bool visible);

 private:
  SampleSettings();

  Glib::RefPtr<Gio::Settings> m_refPrefUI;
  Glib::RefPtr<Gio::Settings> m_refWinState;
  static SampleSettings* m_Instance;
};






#endif /* ifndef SAMPLE_SETTINGS_H */

