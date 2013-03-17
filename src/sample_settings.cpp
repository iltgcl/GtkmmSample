#include <giomm.h>
#include <iostream>
//#include <glibmm/miscutils.h>

#include "sample_settings.h"

const Glib::ustring SampleSettings::KEY_WINDOW_STATE = "window-state";
const Glib::ustring SampleSettings::KEY_WINDOW_WIDTH = "window-width";
const Glib::ustring SampleSettings::KEY_WINDOW_HEIGHT = "window-height";
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
  m_refSettings = Gio::Settings::create("com.iltgcl.gtkmmsample");
  std::cout << Glib::ustring::compose("Initial value of '%1': '%2'\n", 
                                      KEY_TOOLBAR_VISIBLE, 
                                      m_refSettings->get_boolean(KEY_TOOLBAR_VISIBLE));
}

int 
SampleSettings::getWindowState()
{
  return m_refSettings->get_int(KEY_WINDOW_STATE);
}

void 
SampleSettings::setWindowState(int state)
{
  m_refSettings->set_int(KEY_WINDOW_STATE, state);
}

void 
SampleSettings::getWindowSize(int& width, int& height)
{
  width = m_refSettings->get_int(KEY_WINDOW_WIDTH);
  height = m_refSettings->get_int(KEY_WINDOW_HEIGHT);
  
}

void 
SampleSettings::setWindowSize(int width, int height)
{
  m_refSettings->set_int(KEY_WINDOW_WIDTH, width);
  m_refSettings->set_int(KEY_WINDOW_HEIGHT, height);
}

bool 
SampleSettings::getToolbarVisible()
{
  return m_refSettings->get_boolean(KEY_TOOLBAR_VISIBLE);
}

bool 
SampleSettings::getStatusbarVisible()
{
  return m_refSettings->get_boolean(KEY_STATUSBAR_VISIBLE);
}

void 
SampleSettings::setToolbarVisible(bool visible) 
{
  m_refSettings->set_boolean(KEY_TOOLBAR_VISIBLE, visible);
}

void 
SampleSettings::setStatusbarVisible(bool visible)
{
  m_refSettings->set_boolean(KEY_STATUSBAR_VISIBLE, visible);
}

