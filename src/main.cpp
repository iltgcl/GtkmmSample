#include <gtkmm.h>
#include "views/sample_window.h"

int
main(int argc, char *argv[]) {
  Gtk::Main kit(argc, argv);

  SampleWindow main_window;
  Gtk::Main::run(main_window);
  return 0;
}

