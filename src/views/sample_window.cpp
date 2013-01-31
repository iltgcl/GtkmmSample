#include <iostream>
#include <gtkmm/stock.h>
#include <gtkmm/main.h>
#include <gtkmm/toggleaction.h>

#include "sample_window.h"

#define  SAMPLE_UI_FILE     RES_DIR "/sample_ui.xml" 

SampleWindow::SampleWindow()
{
  add(m_VBox);

  m_refSensitiveActionGroup = Gtk::ActionGroup::create("SensitiveActions");
  m_refNormalActionGroup = Gtk::ActionGroup::create("NormalActions");
  m_refToggleActionGroup = Gtk::ActionGroup::create("ToggleActions");
  m_refUIManager = Gtk::UIManager::create();
  add_accel_group(m_refUIManager->get_accel_group());

  initActions();
  initUIManager();

  show_all();

  signal_delete_event().connect(sigc::mem_fun(*this, &SampleWindow::on_delete_event)); 
}

SampleWindow::~SampleWindow()
{
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
      sigc::mem_fun(*this, &SampleWindow::onFileNew));

  m_refSensitiveActionGroup->add(
      Gtk::Action::create("FileOpen", Gtk::Stock::OPEN, "_Open...", "Open a file"),
      sigc::mem_fun(*this, &SampleWindow::onFileOpen));

  m_refSensitiveActionGroup->add(
      Gtk::Action::create("FileQuit", Gtk::Stock::QUIT, "_Quit", "Quit the program"),
      sigc::mem_fun(*this, &SampleWindow::onFileQuit));

  m_refSensitiveActionGroup->add(
      Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT ),
      sigc::mem_fun(*this, &SampleWindow::onHelpAbout));

  m_refSensitiveActionGroup->add(
      Gtk::Action::create("LeaveFullscreen", Gtk::Stock::LEAVE_FULLSCREEN),
      sigc::mem_fun(*this, &SampleWindow::onLeaveFullscreen));

  /* normal action */
  m_refNormalActionGroup->add(
      Gtk::Action::create("FileSave", Gtk::Stock::SAVE),
      sigc::mem_fun(*this, &SampleWindow::onFileSave));

  m_refNormalActionGroup->add(
      Gtk::Action::create("FileSaveAs", Gtk::Stock::SAVE_AS),
      sigc::mem_fun(*this, &SampleWindow::onFileSaveAs));

  m_refNormalActionGroup->add(
      Gtk::Action::create("EditUndo", Gtk::Stock::UNDO),
      sigc::mem_fun(*this, &SampleWindow::onEditUndo));

  m_refNormalActionGroup->add(
      Gtk::Action::create("EditRedo", Gtk::Stock::REDO),
      sigc::mem_fun(*this, &SampleWindow::onEditRedo));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditCut", Gtk::Stock::CUT),
      sigc::mem_fun(*this, &SampleWindow::onEditCut));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditCopy", Gtk::Stock::COPY),
      sigc::mem_fun(*this, &SampleWindow::onEditCopy));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditPaste", Gtk::Stock::PASTE),
      sigc::mem_fun(*this, &SampleWindow::onEditPaste));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditDelete", Gtk::Stock::DELETE),
      sigc::mem_fun(*this, &SampleWindow::onEditDelete));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditSelectAll", Gtk::Stock::SELECT_ALL),
      sigc::mem_fun(*this, &SampleWindow::onEditSelectAll));
  m_refNormalActionGroup->add(
      Gtk::Action::create("EditPreferences", Gtk::Stock::PREFERENCES),
      sigc::mem_fun(*this, &SampleWindow::onEditPreferences));
  /* Toggle action */
  m_refToggleActionGroup->add(
      Gtk::ToggleAction::create("ViewToolbar",  "Toolbar"),
      sigc::mem_fun(*this, &SampleWindow::onViewToolbar));
  m_refToggleActionGroup->add(
      Gtk::ToggleAction::create("ViewStatusbar",  "Statusbar"),
      sigc::mem_fun(*this, &SampleWindow::onViewStatusbar));
  m_refToggleActionGroup->add(
      Gtk::ToggleAction::create("ViewFullscreen",  "Fullscreen"),
      sigc::mem_fun(*this, &SampleWindow::onViewFullscreen));

}

void
SampleWindow::initUIManager()
{
  m_refUIManager->insert_action_group(m_refSensitiveActionGroup);
  m_refUIManager->insert_action_group(m_refNormalActionGroup);
  m_refUIManager->insert_action_group(m_refToggleActionGroup);

  m_refUIManager->add_ui_from_file(SAMPLE_UI_FILE);

  Gtk::Widget* pWidget = m_refUIManager->get_widget("/MenuBar");
  m_VBox.pack_start(*pWidget, Gtk::PACK_SHRINK);

  pWidget = m_refUIManager->get_widget("/ToolBar");
  m_VBox.pack_start(*pWidget, Gtk::PACK_SHRINK);
}



