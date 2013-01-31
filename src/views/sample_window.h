/*
 * sample_window.h
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
#ifndef SAMPLE_WINDOW_H
#define SAMPLE_WINDOW_H

#include <glibmm/refptr.h>
#include <gtkmm/window.h>
#include <gtkmm/actiongroup.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/box.h>


G_BEGIN_DECLS

class SampleWindow : public Gtk::Window 
{
 public:
  SampleWindow();
  virtual ~SampleWindow();

 protected:
  /* Always sensitive action callback */
  void onFileNew();
  void onFileOpen();
  void onFileQuit();
  void onHelpAbout();
  void onLeaveFullscreen();
  /* normal action callback */
  void onFileSave();
  void onFileSaveAs();
  void onEditUndo();
  void onEditRedo();
  void onEditCut();
  void onEditCopy();
  void onEditPaste();
  void onEditDelete();
  void onEditSelectAll();
  void onEditPreferences();
  /* Toggle action callback */
  void onViewToolbar();
  void onViewStatusbar();
  void onViewFullscreen();


  virtual bool on_delete_event(GdkEventAny* event); //override

 private:
  void initActions();
  void initUIManager();
  Glib::RefPtr<Gtk::ActionGroup> m_refSensitiveActionGroup;
  Glib::RefPtr<Gtk::ActionGroup> m_refNormalActionGroup;
  Glib::RefPtr<Gtk::ActionGroup> m_refToggleActionGroup;
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Gtk::VBox m_VBox;
};


G_END_DECLS

#endif /* ifndef SAMPLE_WINDOW_H */

