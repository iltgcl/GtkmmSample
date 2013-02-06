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
#include <gtkmm/action.h>
#include <gdkmm/window.h>

#include "sample_statusbar.h"

typedef enum {
  SAMPLE_WINDOW_STATE_NORMAL,
  SAMPLE_WINDOW_STATE_ASYNC_EXE,
  SAMPLE_WINDOW_STATE_ERROR,
}SampleWindowState;

class SampleWindow : public Gtk::Window 
{
 public:
  SampleWindow();
  virtual ~SampleWindow();
  bool isFullscreen();

 protected:
  sigc::connection m_tbVisibleConnection;
  sigc::connection m_sbVisibleConnection;
  void on_toolbar_visible_changed();
  void on_statusbar_visible_changed();
  /* override signal */
  virtual bool on_window_state_event(GdkEventWindowState* event);
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
  /* Menu item select and deselect. */
  void on_menu_item_select(const Glib::RefPtr<Gtk::Action>& action);
  void on_menu_item_deselect();
  void on_connect_proxy(const Glib::RefPtr<Gtk::Action>& action, Gtk::Widget* widget);

  virtual bool on_delete_event(GdkEventAny* event); //override

 private:
  void initActions();
  void initUI();
  void requestFullscreen();
  void requestUnfullscreen();
  Glib::RefPtr<Gtk::ActionGroup> m_refSensitiveActionGroup;
  Glib::RefPtr<Gtk::ActionGroup> m_refNormalActionGroup;
  Glib::RefPtr<Gtk::ActionGroup> m_refToggleActionGroup;
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Gtk::VBox m_VBox;
  SampleStatusbar m_Statusbar;
  guint m_ctxId;
  GdkWindowState m_winState;
};


#endif /* ifndef SAMPLE_WINDOW_H */

