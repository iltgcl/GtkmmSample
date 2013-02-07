
#include "fullscreen_toolbar.h"


FullscreenToolbar::FullscreenToolbar(Gtk::Window &transient, Gtk::Toolbar &toolbar)
  : m_transient(transient)
{
  set_transient_for(transient);
  add(toolbar);
  toolbar.set_toolbar_style(Gtk::TOOLBAR_BOTH_HORIZ);
}

FullscreenToolbar::~FullscreenToolbar()
{
}

void
FullscreenToolbar::on_show()
{
  Gdk::Rectangle rect;
  int w, h;
  int monitor_num;
  Glib::RefPtr<const Gdk::Screen> screen = m_transient.get_screen();
  monitor_num = screen->get_monitor_at_window(m_transient.get_window());
  screen->get_monitor_geometry(monitor_num, rect);
  get_size(w, h);
  resize(rect.get_width(), h);
  move(rect.get_x(), rect.get_y() - h + 1);
  show_all();
}

