#include <giomm.h>
#include <iostream>
//#include <glibmm/miscutils.h>

#include "sample_settings.h"

const Glib::ustring SampleSettings::KEY_WINDOW_STATE = "state";
const Glib::ustring SampleSettings::KEY_WINDOW_WIDTH = "width";
const Glib::ustring SampleSettings::KEY_WINDOW_HEIGHT = "height";
const Glib::ustring SampleSettings::KEY_TOOLBAR_VISIBLE = "toolbar-visible";
const Glib::ustring SampleSettings::KEY_STATUSBAR_VISIBLE = "statusbar-visible";

SampleSettings* SampleSettings::m_Instance = NULL;

SampleSettings* 
SampleSettings::getDefault()
{
  if(m_Instance == NULL) {
    m_Instance = new SampleSettings();
  }
  return m_Instance;
}

SampleSettings::SampleSettings() 
{
  /* I install my schema in res dir because this is a demo app.  
   * Generally you would install your schemas to the system schema 
   */
  Glib::setenv("GSETTINGS_SCHEMA_DIR", RES_DIR, true);
  //Glib::setenv("GSETTINGS_BACKEND", "memory", true);
  m_refPrefUI = Gio::Settings::create("com.iltgcl.gtkmmsample.preferences.ui");
  m_refWinState = Gio::Settings::create("com.iltgcl.gtkmmsample.state.window");
}

int 
SampleSettings::getWindowState()
{
  return m_refWinState->get_int(KEY_WINDOW_STATE);
}

void 
SampleSettings::setWindowState(int state)
{
  m_refWinState->set_int(KEY_WINDOW_STATE, state);
}

void 
SampleSettings::getWindowSize(int& width, int& height)
{
  width = m_refWinState->get_int(KEY_WINDOW_WIDTH);
  height = m_refWinState->get_int(KEY_WINDOW_HEIGHT);
  
}

void 
SampleSettings::setWindowSize(int width, int height)
{
  m_refWinState->set_int(KEY_WINDOW_WIDTH, width);
  m_refWinState->set_int(KEY_WINDOW_HEIGHT, height);
}

bool 
SampleSettings::getToolbarVisible()
{
  return m_refPrefUI->get_boolean(KEY_TOOLBAR_VISIBLE);
}

bool 
SampleSettings::getStatusbarVisible()
{
  return m_refPrefUI->get_boolean(KEY_STATUSBAR_VISIBLE);
}

void 
SampleSettings::setToolbarVisible(bool visible) 
{
  m_refPrefUI->set_boolean(KEY_TOOLBAR_VISIBLE, visible);
}

void 
SampleSettings::setStatusbarVisible(bool visible)
{
  m_refPrefUI->set_boolean(KEY_STATUSBAR_VISIBLE, visible);
}

