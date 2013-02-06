#include <iostream>
#include <gtkmm/stock.h>
#include <gtkmm/main.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/item.h>
#include <gtkmm/toggleaction.h>
#include <gtkmm/accelkey.h>

#include "sample_window.h"

#define  SAMPLE_UI_FILE     RES_DIR "/sample_ui.xml" 

SampleWindow::SampleWindow()
{
  set_default_size(800, 8 * 62);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  add(m_VBox);

  m_refSensitiveActionGroup = Gtk::ActionGroup::create("SensitiveActions");
  m_refNormalActionGroup = Gtk::ActionGroup::create("NormalActions");
  m_refToggleActionGroup = Gtk::ActionGroup::create("ToggleActions");
  m_refUIManager = Gtk::UIManager::create();
  add_accel_group(m_refUIManager->get_accel_group());

  initActions();
  initUI();

  show_all();


  signal_delete_event().connect(sigc::mem_fun(*this, &SampleWindow::on_delete_event)); 
}

SampleWindow::~SampleWindow()
{
}

bool
SampleWindow::isFullscreen()
{
  return m_winState & GDK_WINDOW_STATE_FULLSCREEN;
}

bool 
SampleWindow::on_window_state_event(GdkEventWindowState* event)
{
  m_winState = event->new_window_state;
  return false;
}

void
SampleWindow::onFileNew()
{
  std::cout << " onFileNew " << std::endl;
}

void
SampleWindow::onFileOpen()
{
  std::cout << " onFileOpen " << std::endl;
}

void 
SampleWindow::onFileSave()
{
  std::cout << " onFileSave " << std::endl;
}

void 
SampleWindow::onFileSaveAs()
{
  std::cout << " onFileSaveAs " << std::endl;
}

void
SampleWindow::onFileQuit()
{
  std::cout << " onFileQuit " << std::endl;
  Gtk::Main::quit();
}

/* Edit menu */
void 
SampleWindow::onEditUndo()
{
  std::cout << " onEditUndo " << std::endl;
}

void 
SampleWindow::onEditRedo()
{
  std::cout << " onEditRedo " << std::endl;
}

void 
SampleWindow::onEditCut()
{
  std::cout << " onEditCut " << std::endl;
}

void 
SampleWindow::onEditCopy()
{
  std::cout << " onEditCopy " << std::endl;
}

void 
SampleWindow::onEditPaste()
{
  std::cout << " onEditPaste " << std::endl;
}

void 
SampleWindow::onEditDelete()
{
  std::cout << " onEditDelete " << std::endl;
}

void 
SampleWindow::onEditSelectAll()
{
  std::cout << " onEditSelectAll " << std::endl;
}

void 
SampleWindow::onEditPreferences()
{
  std::cout << " onEditPreferences " << std::endl;
}

void 
SampleWindow::onViewToolbar()
{
  std::cout << " onViewToolbar " << std::endl;
}

void 
SampleWindow::onViewStatusbar()
{
  std::cout << " onViewStatusbar " << std::endl;
}

void 
SampleWindow::onViewFullscreen()
{
  std::cout << " onViewFullscreen " << std::endl;
  if(isFullscreen()) {
    requestUnfullscreen();
  } else {
    requestFullscreen();
  }
}

/* Help menu */
void
SampleWindow::onHelpAbout()
{
  std::cout << " onHelpAbout " << std::endl;
}

bool 
SampleWindow::on_delete_event(GdkEventAny* event)
{
  onFileQuit();
  return TRUE;
}

void 
SampleWindow::onLeaveFullscreen()
{
  Glib::RefPtr<Gtk::Action> action = m_refToggleActionGroup->get_action("ViewToolbar");
  g_assert(action != 0);
  action->block_activate();
  (Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic(action))->set_active(false);
  requestUnfullscreen();
  action->unblock_activate();
}

void
SampleWindow::initActions()
{
  /* Top menu */
  m_refSensitiveActionGroup->add(Gtk::Action::create("File", "_File"));
  m_refSensitiveActionGroup->add(Gtk::Action::create("Edit", "_Edit"));
  m_refSensitiveActionGroup->add(Gtk::Action::create("View", "_View"));
  m_refSensitiveActionGroup->add(Gtk::Action::create("Help", "_Help"));

  /* sensitive action */
  m_refSensitiveActionGroup->add(
      Gtk::Action::create("FileNew", Gtk::Stock::NEW, "_New", "Create a new document"),
      Gtk::AccelKey("<control>N"),
      sigc::mem_fun(*this, &SampleWindow::onFileNew));

  m_refSensitiveActionGroup->add(
      Gtk::Action::create("FileOpen", Gtk::Stock::OPEN, "_Open...", "Open a file"),
      Gtk::AccelKey("<control>O"),
      sigc::mem_fun(*this, &SampleWindow::onFileOpen));

  m_refSensitiveActionGroup->add(
      Gtk::Action::create("FileQuit", Gtk::Stock::QUIT, "_Quit", "Quit the program"),
      Gtk::AccelKey("<control>Q"),
      sigc::mem_fun(*this, &SampleWindow::onFileQuit));

  m_refSensitiveActionGroup->add(
      Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT, 
                          "_About", "About this application" ),
      sigc::mem_fun(*this, &SampleWindow::onHelpAbout));

  m_refSensitiveActionGroup->add(
      Gtk::Action::create("LeaveFullscreen", Gtk::Stock::LEAVE_FULLSCREEN),
      sigc::mem_fun(*this, &SampleWindow::onLeaveFullscreen));
  m_refUIManager->insert_action_group(m_refSensitiveActionGroup);

  /* normal action */
  m_refNormalActionGroup->add(
      Gtk::Action::create("FileSave", Gtk::Stock::SAVE, Glib::ustring(), "Save the current file"),
      Gtk::AccelKey("<control>S"),
      sigc::mem_fun(*this, &SampleWindow::onFileSave));

  m_refNormalActionGroup->add(
      Gtk::Action::create("FileSaveAs", Gtk::Stock::SAVE_AS, 
                          Glib::ustring(), "Save the current file with different name"),
      Gtk::AccelKey("<shift><control>S"),
      sigc::mem_fun(*this, &SampleWindow::onFileSaveAs));

  m_refNormalActionGroup->add(
      Gtk::Action::create("EditUndo", Gtk::Stock::UNDO, Glib::ustring(), "Undo the last action"),
      Gtk::AccelKey("<control>Z"),
      sigc::mem_fun(*this, &SampleWindow::onEditUndo));

  m_refNormalActionGroup->add(
      Gtk::Action::create("EditRedo", Gtk::Stock::REDO, 
                          Glib::ustring(), "Redo the last undone action"),
      Gtk::AccelKey("<shift><control>Z"),
      sigc::mem_fun(*this, &SampleWindow::onEditRedo));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditCut", Gtk::Stock::CUT, Glib::ustring(), "Cut the selection"),
      Gtk::AccelKey("<control>X"),
      sigc::mem_fun(*this, &SampleWindow::onEditCut));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditCopy", Gtk::Stock::COPY, Glib::ustring(), "Copy the selection"),
      Gtk::AccelKey("<control>C"),
      sigc::mem_fun(*this, &SampleWindow::onEditCopy));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditPaste", Gtk::Stock::PASTE, Glib::ustring(), "Paste the clipboard"),
      Gtk::AccelKey("<control>V"),
      sigc::mem_fun(*this, &SampleWindow::onEditPaste));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditDelete", Gtk::Stock::DELETE, 
                          Glib::ustring(), "Delete the selected text"),
      sigc::mem_fun(*this, &SampleWindow::onEditDelete));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditSelectAll", Gtk::Stock::SELECT_ALL, 
                          Glib::ustring(), "Select the entire document"),
      Gtk::AccelKey("<control>A"),
      sigc::mem_fun(*this, &SampleWindow::onEditSelectAll));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditPreferences", Gtk::Stock::PREFERENCES, 
                          "Pr_eferences", "Configure the application"),
      sigc::mem_fun(*this, &SampleWindow::onEditPreferences));
  m_refUIManager->insert_action_group(m_refNormalActionGroup);
  /* Toggle action */
  m_refToggleActionGroup->add(
      Gtk::ToggleAction::create("ViewToolbar",  "_Toolbar", 
                                "Show or hide the toolbar in the current window"),
      sigc::mem_fun(*this, &SampleWindow::onViewToolbar));
  m_refToggleActionGroup->add(
      Gtk::ToggleAction::create("ViewStatusbar",  "_Statusbar",
                                "Show or hide the statusbar in the current window"),
      sigc::mem_fun(*this, &SampleWindow::onViewStatusbar));
  m_refToggleActionGroup->add(
      Gtk::ToggleAction::create("ViewFullscreen",  "Fullscreen", "Fullscreen"),
      Gtk::AccelKey("F11"),
      sigc::mem_fun(*this, &SampleWindow::onViewFullscreen));
  m_refUIManager->insert_action_group(m_refToggleActionGroup);

}

void
SampleWindow::on_menu_item_select(const Glib::RefPtr<Gtk::Action>& action)
{
  Glib::ustring tooltip = action->get_tooltip();
  if(!tooltip.empty()) {
    m_Statusbar.push(tooltip, m_ctxId);
  }
}

void
SampleWindow::on_menu_item_deselect()
{
  m_Statusbar.pop(m_ctxId);
}

void 
SampleWindow::on_connect_proxy(const Glib::RefPtr<Gtk::Action>& action, Gtk::Widget *widget)
{
  Gtk::MenuItem* menu_item = dynamic_cast<Gtk::MenuItem*>(widget);
  if(menu_item) {
    Gtk::Item *item = dynamic_cast<Gtk::Item*>(menu_item);
    item->signal_select().connect(
        sigc::bind(sigc::mem_fun(*this, &SampleWindow::on_menu_item_select), action));
    item->signal_deselect().connect(
        sigc::mem_fun(*this, &SampleWindow::on_menu_item_deselect));
  }

}

void
SampleWindow::on_toolbar_visible_changed()
{
}

void
SampleWindow::on_statusbar_visible_changed()
{
}

void
SampleWindow::requestFullscreen()
{
  if(isFullscreen()) return;
  fullscreen();
  Gtk::Widget* pWidget = m_refUIManager->get_widget("/MenuBar");
  pWidget->hide();
  m_tbVisibleConnection.block();
  pWidget = m_refUIManager->get_widget("/ToolBar");
  pWidget->hide();
  m_sbVisibleConnection.block();
  m_Statusbar.hide();
  
}

void
SampleWindow::requestUnfullscreen()
{
  if(!isFullscreen()) return;
  unfullscreen();
  Gtk::Widget* pWidget = m_refUIManager->get_widget("/MenuBar");
  pWidget->show();
  m_tbVisibleConnection.unblock();
  pWidget = m_refUIManager->get_widget("/ToolBar");
  Glib::RefPtr<Gtk::Action> action = m_refToggleActionGroup->get_action("ViewToolbar");
  g_assert(action != 0);
  if((Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic(action))->get_active()) {
    pWidget->show();
  }
  m_sbVisibleConnection.unblock();
}

void
SampleWindow::initUI()
{
  m_refUIManager->add_ui_from_file(SAMPLE_UI_FILE);
  m_refUIManager->signal_connect_proxy().connect(sigc::mem_fun(*this, &SampleWindow::on_connect_proxy));

  Gtk::Widget* pWidget = m_refUIManager->get_widget("/MenuBar");
  m_VBox.pack_start(*pWidget, Gtk::PACK_SHRINK);

  pWidget = m_refUIManager->get_widget("/ToolBar");
  m_VBox.pack_start(*pWidget, Gtk::PACK_SHRINK);
  m_tbVisibleConnection = pWidget->property_visible().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::on_toolbar_visible_changed));

  m_Statusbar.show();
  m_VBox.pack_end(m_Statusbar, Gtk::PACK_SHRINK);
  m_ctxId = m_Statusbar.get_context_id("tip_message");
  m_tbVisibleConnection = m_Statusbar.property_visible().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::on_statusbar_visible_changed));
}



