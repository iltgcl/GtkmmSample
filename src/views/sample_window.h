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
#include <gtkmm/menubar.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/actiongroup.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/box.h>
#include <gtkmm/action.h>
#include <gdkmm/window.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

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
  /* override signal */
  virtual bool on_window_state_event(GdkEventWindowState* event);
  virtual bool on_configure_event(GdkEventConfigure* event);

  /* callbacks */
  void onToolbarVisibleChanged();
  void onStatusbarVisibleChanged();
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
  void onMenuItemSelect(const Glib::RefPtr<Gtk::Action>& action);
  void onMenuItemDeselect();
  void onConnectProxy(const Glib::RefPtr<Gtk::Action>& action, Gtk::Widget* widget);
  /* fullscreen window callback  */
  bool onEnterNotifyEvent(GdkEventCrossing* event);
  bool onLeaveNotifyEvent(GdkEventCrossing* event);
  bool onDeleteEvent(GdkEventAny* event); //override

 private:
  void initToolbarVisible();
  void initStatusbarVisible();
  void initActions();
  void initUI();
  void saveWindowState();
  void requestFullscreen();
  void requestUnfullscreen();
  void displayFullscreenToolbar(bool is_show);
  bool onAnimationTimeout();
  void beginAnimation(bool is_enter);
  void getGeometry(Gdk::Rectangle &rect);

  guint m_ctxId;
  GdkWindowState m_winState;

  Glib::RefPtr<Gtk::ActionGroup> m_refSensitiveActionGroup;
  Glib::RefPtr<Gtk::ActionGroup> m_refNormalActionGroup;
  Glib::RefPtr<Gtk::ActionGroup> m_refToggleActionGroup;
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Gtk::VBox m_VBox;
  Gtk::MenuBar *m_pMenuBar;
  Gtk::Toolbar *m_pToolbar;
  SampleStatusbar m_Statusbar;
  sigc::connection m_tbVisibleConnection;
  sigc::connection m_sbVisibleConnection;
  /* fullscreen toolbar */
  bool m_isEnter;
  Gtk::Window m_winFullscreen;
};


#endif /* ifndef SAMPLE_WINDOW_H */

