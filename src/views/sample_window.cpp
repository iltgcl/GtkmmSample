#include <iostream>
#include <gtkmm/stock.h>
#include <gtkmm/main.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/toggleaction.h>
#include <gtkmm/accelkey.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/clipboard.h>

#include "sample_window.h"
#include "../sample_settings.h"
#include "../utils/log.h"

#define  SAMPLE_UI_FILE     RES_DIR "/sample_ui.xml" 
#define  LOGO_FILE     RES_DIR "/logo.png" 
#define ANIMATION_SPEED 4

SampleWindow::SampleWindow()
  :m_winFullscreen(Gtk::WINDOW_POPUP)
{
  int w, h, state;

  set_default_icon_from_file(LOGO_FILE);

  state = SampleSettings::getDefault()->getWindowState();
  SampleSettings::getDefault()->getWindowSize(w, h);
  set_default_size(w, h);
  set_position(Gtk::WIN_POS_CENTER_ALWAYS);
  if((state & GDK_WINDOW_STATE_MAXIMIZED) != 0) {
    maximize();
  } else {
    unmaximize();
  }

  add(m_VBox);

  m_refUIManager = Gtk::UIManager::create();
  add_accel_group(m_refUIManager->get_accel_group());

  initActions();

  /* create ui */
  m_refUIManager->add_ui_from_file(SAMPLE_UI_FILE);

  Gtk::Widget* pWidget = m_refUIManager->get_widget("/MenuBar");
  m_pMenuBar = static_cast<Gtk::MenuBar*>(pWidget);
  m_VBox.pack_start(*m_pMenuBar, Gtk::PACK_SHRINK);
  m_pMenuBar->show();

  pWidget = m_refUIManager->get_widget("/ToolBar");
  m_pToolbar = static_cast<Gtk::Toolbar*>(pWidget);
  m_VBox.pack_start(*m_pToolbar, Gtk::PACK_SHRINK);
  m_tbVisibleConnection = pWidget->property_visible().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::onToolbarVisibleChanged));

  m_VBox.pack_start(m_ClientRoot, true, true);
  m_ClientRoot.show_all();

  m_VBox.pack_end(m_Statusbar, Gtk::PACK_SHRINK);
  m_ctxId = m_Statusbar.get_context_id("tip_message");
  m_sbVisibleConnection = m_Statusbar.property_visible().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::onStatusbarVisibleChanged));

  show_all();

  initUI();
  initFullscreen();

  /* signal connect */
  signal_delete_event().connect(sigc::mem_fun(*this, &SampleWindow::onDeleteEvent)); 
  m_ClientRoot.property_can_save().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::onCanSaveChanged));
  m_ClientRoot.property_can_save_as().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::onCanSaveAsChanged));
  m_ClientRoot.property_can_undo().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::onCanUndoChanged));
  m_ClientRoot.property_can_redo().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::onCanRedoChanged));
  m_ClientRoot.property_can_cut().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::onCanCutChanged));
  m_ClientRoot.property_can_copy().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::onCanCopyChanged));
  m_ClientRoot.property_can_paste().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::onCanPasteChanged));
  m_ClientRoot.property_can_delete().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::onCanDeleteChanged));
  m_ClientRoot.property_can_select_all().signal_changed().connect(
      sigc::mem_fun(*this, &SampleWindow::onCanSelectAllChanged));
}

void 
SampleWindow::onCanSaveChanged()
{
  Glib::RefPtr<Gtk::Action> action = m_refNormalActionGroup->get_action("FileSave");
  g_assert(action != 0);
  action->set_sensitive(m_ClientRoot.property_can_save().get_value());
}

void 
SampleWindow::onCanSaveAsChanged()
{
  Glib::RefPtr<Gtk::Action> action = m_refNormalActionGroup->get_action("FileSaveAs");
  g_assert(action != 0);
  action->set_sensitive(m_ClientRoot.property_can_save_as().get_value());
}

void 
SampleWindow::onCanUndoChanged()
{
  Glib::RefPtr<Gtk::Action> action = m_refNormalActionGroup->get_action("EditUndo");
  g_assert(action != 0);
  action->set_sensitive(m_ClientRoot.property_can_undo().get_value());
}

void 
SampleWindow::onCanRedoChanged()
{
  Glib::RefPtr<Gtk::Action> action = m_refNormalActionGroup->get_action("EditRedo");
  g_assert(action != 0);
  action->set_sensitive(m_ClientRoot.property_can_redo().get_value());
}

void 
SampleWindow::onCanCutChanged()
{
  Glib::RefPtr<Gtk::Action> action = m_refNormalActionGroup->get_action("EditCut");
  g_assert(action != 0);
  action->set_sensitive(m_ClientRoot.property_can_cut().get_value());
}

void 
SampleWindow::onCanCopyChanged()
{
  Glib::RefPtr<Gtk::Action> action = m_refNormalActionGroup->get_action("EditCopy");
  g_assert(action != 0);
  action->set_sensitive(m_ClientRoot.property_can_copy().get_value());
}

void 
SampleWindow::onCanPasteChanged()
{
  Glib::RefPtr<Gtk::Action> action = m_refNormalActionGroup->get_action("EditPaste");
  g_assert(action != 0);
  action->set_sensitive(m_ClientRoot.property_can_paste().get_value());
}

void 
SampleWindow::onCanDeleteChanged()
{
  Glib::RefPtr<Gtk::Action> action = m_refNormalActionGroup->get_action("EditDelete");
  g_assert(action != 0);
  action->set_sensitive(m_ClientRoot.property_can_delete().get_value());
}

void 
SampleWindow::onCanSelectAllChanged()
{
  Glib::RefPtr<Gtk::Action> action = m_refNormalActionGroup->get_action("EditSelectAll");
  g_assert(action != 0);
  action->set_sensitive(m_ClientRoot.property_can_select_all().get_value());
}

void SampleWindow::initFullscreen() 
{
  /* init fullscreen */
  Gtk::Widget *pWidget = m_refUIManager->get_widget("/FullscreenToolBar");
  m_winFullscreen.add(*pWidget);
  m_winFullscreen.set_transient_for(*this);
  m_winFullscreen.signal_enter_notify_event().connect(
      sigc::mem_fun(*this, &SampleWindow::onEnterNotifyEvent));
  m_winFullscreen.signal_leave_notify_event().connect(
      sigc::mem_fun(*this, &SampleWindow::onLeaveNotifyEvent));
}

void
SampleWindow::saveWindowState()
{
  if((m_winState & (GDK_WINDOW_STATE_MAXIMIZED | GDK_WINDOW_STATE_FULLSCREEN)) == 0 ) {
    int w = get_allocation().get_width();
    int h = get_allocation().get_height();
    SampleSettings::getDefault()->setWindowSize(w, h); 
  }
}

SampleWindow::~SampleWindow()
{
  saveWindowState();
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
  SampleSettings::getDefault()->setWindowState(m_winState);

  return false;
}

void
SampleWindow::onClipboardReceived(const Gtk::SelectionData& selection_data)
{
  bool sens = selection_data.targets_include_text() && m_ClientRoot.property_can_paste().get_value();
  Glib::RefPtr<Gtk::Action> action = m_refNormalActionGroup->get_action("EditPaste");
  g_assert(action != 0);
  LOGD("sensitive  = " << sens);
  action->set_sensitive(sens);
}

void
SampleWindow::setPasteSensitivity()
{
  Gtk::Clipboard::get(GDK_SELECTION_CLIPBOARD)->request_contents(
      "TARGETS", sigc::mem_fun(*this, &SampleWindow::onClipboardReceived));
}

void
SampleWindow::onOwnerChange(GdkEventOwnerChange* event)
{
  setPasteSensitivity();
}

void
SampleWindow::on_realize()
{
  LOGD("can_undo property  = " << m_ClientRoot.property_can_undo().get_value());
  Gtk::Clipboard::get(GDK_SELECTION_CLIPBOARD)->signal_owner_change().connect(
      sigc::mem_fun(*this, &SampleWindow::onOwnerChange));

  Window::on_realize();
}

bool 
SampleWindow::on_configure_event(GdkEventConfigure* event)
{
  if(get_realized() && 
     ((m_winState & (GDK_WINDOW_STATE_MAXIMIZED | GDK_WINDOW_STATE_FULLSCREEN))==0)) {
    saveWindowState();
  }
  return Window::on_configure_event(event);
}

void
SampleWindow::onFileNew()
{
  //print message using red color.
  //std::cout<<"\033[0;31m"<< " onFileNew" <<"\033[0m"<<std::endl;
  LOGD("onFileNew. ");
}

void
SampleWindow::onFileOpen()
{
  LOGD("onFileOpen. ");
}

void 
SampleWindow::onFileSave()
{
  LOGD("onFileSave. ");
}

void 
SampleWindow::onFileSaveAs()
{
  LOGD("onFileSaveAs. ");
}

void
SampleWindow::onFileQuit()
{
  LOGD("onFileQuit. ");
  Gtk::Main::quit();
}

/* Edit menu */
void 
SampleWindow::onEditUndo()
{
  LOGD("onEditUndoonEditUndo. ");
}

void 
SampleWindow::onEditRedo()
{
  LOGD("onEditRedo. ");
}

void 
SampleWindow::onEditCut()
{
  LOGD("onEditCut. ");
}

void 
SampleWindow::onEditCopy()
{
  LOGD("onEditCopy. ");
}

void 
SampleWindow::onEditPaste()
{
  LOGD("onEditPaste. ");
}

void 
SampleWindow::onEditDelete()
{
  LOGD("onEditDelete. ");
}

void 
SampleWindow::onEditSelectAll()
{
  LOGD("onEditSelectAll. ");
}

void 
SampleWindow::onEditPreferences()
{
  LOGD("onEditPreferences. ");
}

void 
SampleWindow::onViewToolbar()
{
  Glib::RefPtr<Gtk::ToggleAction> action =
     Glib::RefPtr<Gtk::ToggleAction>::cast_static(
         m_refToggleActionGroup->get_action("ViewToolbar"));
  if(action->get_active()) {
    m_pToolbar->show();
  } else {
    m_pToolbar->hide();
  }
  LOGD("onViewToolbar. ");
}

void 
SampleWindow::onViewStatusbar()
{
  Glib::RefPtr<Gtk::ToggleAction> action =
     Glib::RefPtr<Gtk::ToggleAction>::cast_static(
         m_refToggleActionGroup->get_action("ViewStatusbar"));
  if(action->get_active()) {
    m_Statusbar.show();
  } else {
    m_Statusbar.hide();
  }
  LOGD("onViewStatusbar. ");
}

void 
SampleWindow::onViewFullscreen()
{
  LOGD(" onViewFullscreen. ");
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
  static Gtk::AboutDialog *pAbout = NULL;
  LOGD(" onHelpAbout.");
  if(pAbout == NULL) {
    std::vector<Glib::ustring> authors;
    std::vector<Glib::ustring> documenters;
    authors.push_back("iltgcl <iltgcl@163.com>");
    pAbout = new Gtk::AboutDialog();
    pAbout->set_name("GtkmmSample");
    pAbout->set_authors(authors);
    pAbout->set_version("0.1");
    pAbout->set_copyright("Copyright \xc2\xa9 2004-2011 iltgcl");
    pAbout->set_comments("A Gtkmm example.");
    pAbout->set_translator_credits("");
    pAbout->set_documenters(documenters);
  }
  pAbout->run();
  pAbout->hide();
}

bool 
SampleWindow::onDeleteEvent(GdkEventAny* event)
{
  onFileQuit();
  return TRUE;
}

void 
SampleWindow::onLeaveFullscreen()
{
  Glib::RefPtr<Gtk::Action> action = m_refToggleActionGroup->get_action("ViewFullscreen");
  g_assert(action != 0);
  action->block_activate();
  (Glib::RefPtr<Gtk::ToggleAction>::cast_static(action))->set_active(false);
  requestUnfullscreen();
  action->unblock_activate();
}

void
SampleWindow::initActions()
{
  m_refSensitiveActionGroup = Gtk::ActionGroup::create("SensitiveActions");
  m_refNormalActionGroup = Gtk::ActionGroup::create("NormalActions");
  m_refToggleActionGroup = Gtk::ActionGroup::create("ToggleActions");
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

  Glib::RefPtr<Gtk::Action> action = Gtk::Action::create(
      "LeaveFullscreen", Gtk::Stock::LEAVE_FULLSCREEN);
  action->set_is_important(true);
  m_refSensitiveActionGroup->add(
      action,
      sigc::mem_fun(*this, &SampleWindow::onLeaveFullscreen));
  m_refUIManager->insert_action_group(m_refSensitiveActionGroup);

  /* normal action */
  action = Gtk::Action::create("FileSave", Gtk::Stock::SAVE, 
                               Glib::ustring(), "Save the current file");
  m_refNormalActionGroup->add(action, Gtk::AccelKey("<control>S"),
      sigc::mem_fun(*this, &SampleWindow::onFileSave));
  action->set_sensitive(false);

  action = Gtk::Action::create("FileSaveAs", Gtk::Stock::SAVE_AS, 
                               Glib::ustring(), "Save the current file with different name");
  m_refNormalActionGroup->add(action, Gtk::AccelKey("<shift><control>S"),
      sigc::mem_fun(*this, &SampleWindow::onFileSaveAs));
  action->set_sensitive(false);

  action = Gtk::Action::create("EditUndo", Gtk::Stock::UNDO, 
                               Glib::ustring(), "Undo the last action");
  m_refNormalActionGroup->add(action, Gtk::AccelKey("<control>Z"),
      sigc::mem_fun(*this, &SampleWindow::onEditUndo));
  action->set_sensitive(false);

  action = Gtk::Action::create("EditRedo", Gtk::Stock::REDO, 
                               Glib::ustring(), "Redo the last undone action");
  m_refNormalActionGroup->add(action, Gtk::AccelKey("<shift><control>Z"),
      sigc::mem_fun(*this, &SampleWindow::onEditRedo));
  action->set_sensitive(false);

  action = Gtk::Action::create("EditCut", Gtk::Stock::CUT, 
                               Glib::ustring(), "Cut the selection");
  m_refNormalActionGroup->add(action, Gtk::AccelKey("<control>X"),
      sigc::mem_fun(*this, &SampleWindow::onEditCut));
  action->set_sensitive(false);

  action = Gtk::Action::create("EditCopy", Gtk::Stock::COPY, 
                               Glib::ustring(), "Copy the selection");
  m_refNormalActionGroup->add(action, Gtk::AccelKey("<control>C"),
      sigc::mem_fun(*this, &SampleWindow::onEditCopy));
  action->set_sensitive(false);

  action = Gtk::Action::create("EditPaste", Gtk::Stock::PASTE, 
                               Glib::ustring(), "Paste the clipboard");
  m_refNormalActionGroup->add(action, Gtk::AccelKey("<control>V"),
      sigc::mem_fun(*this, &SampleWindow::onEditPaste));
  action->set_sensitive(false);

  action = Gtk::Action::create("EditDelete", Gtk::Stock::DELETE, 
                               Glib::ustring(), "Delete the selected text");
  m_refNormalActionGroup->add(action, sigc::mem_fun(*this, &SampleWindow::onEditDelete));
  action->set_sensitive(false);

  action = Gtk::Action::create("EditSelectAll", Gtk::Stock::SELECT_ALL, 
                               Glib::ustring(), "Select the entire document");
  m_refNormalActionGroup->add(action, Gtk::AccelKey("<control>A"),
      sigc::mem_fun(*this, &SampleWindow::onEditSelectAll));
  action->set_sensitive(false);

  m_refNormalActionGroup->add(
      Gtk::Action::create("EditPreferences", Gtk::Stock::PREFERENCES, 
                          "Pr_eferences", "Configure the application"),
      sigc::mem_fun(*this, &SampleWindow::onEditPreferences));
  m_refUIManager->insert_action_group(m_refNormalActionGroup);
  /* Toggle action */
  m_refToggleActionGroup->add(
      Gtk::ToggleAction::create(
          "ViewToolbar",  "_Toolbar", "Show or hide the toolbar in the current window"), 
      sigc::mem_fun(*this, &SampleWindow::onViewToolbar));

  m_refToggleActionGroup->add(
      Gtk::ToggleAction::create(
          "ViewStatusbar",  "_Statusbar", "Show or hide the statusbar in the current window"), 
      sigc::mem_fun(*this, &SampleWindow::onViewStatusbar));

  m_refToggleActionGroup->add(
      Gtk::ToggleAction::create("ViewFullscreen",  "Fullscreen", "Fullscreen"),
      Gtk::AccelKey("F11"),
      sigc::mem_fun(*this, &SampleWindow::onViewFullscreen));
  m_refUIManager->insert_action_group(m_refToggleActionGroup);
}

void
SampleWindow::onToolbarVisibleChanged()
{
  bool visible = m_pToolbar->get_visible();
  LOGD(" toolbar visible =  " << visible);
  SampleSettings::getDefault()->setToolbarVisible(visible);
  Glib::RefPtr<Gtk::ToggleAction> action =
     Glib::RefPtr<Gtk::ToggleAction>::cast_static(
         m_refToggleActionGroup->get_action("ViewToolbar"));
  g_assert(action != 0);
  LOGD(" action active =  " << action->get_active());
  if(action->get_active() != visible) {
    action->set_active(visible);
  }
}

void
SampleWindow::onStatusbarVisibleChanged()
{
  bool visible = m_Statusbar.get_visible();
  SampleSettings::getDefault()->setStatusbarVisible(visible);
  Glib::RefPtr<Gtk::ToggleAction> action =
     Glib::RefPtr<Gtk::ToggleAction>::cast_static(
         m_refToggleActionGroup->get_action("ViewStatusbar"));
  g_assert(action != 0);
  if(action->get_active() != visible) {
    action->set_active(visible);
  }
}

void
SampleWindow::requestFullscreen()
{
  if(isFullscreen()) return;
  fullscreen();
  m_tbVisibleConnection.block();
  m_sbVisibleConnection.block();
  m_pMenuBar->hide();
  m_pToolbar->hide();
  m_Statusbar.hide();
  displayFullscreenToolbar(true);
}

void
SampleWindow::requestUnfullscreen()
{
  if(!isFullscreen()) return;
  unfullscreen();
  m_pMenuBar->show();

  Glib::RefPtr<Gtk::ToggleAction> action =
     Glib::RefPtr<Gtk::ToggleAction>::cast_static(
         m_refToggleActionGroup->get_action("ViewToolbar"));
  g_assert(action != 0);
  if(action->get_active()) {
    m_pToolbar->show();
  }
  m_tbVisibleConnection.unblock();

  action = Glib::RefPtr<Gtk::ToggleAction>::cast_static(
         m_refToggleActionGroup->get_action("ViewStatusbar"));
  g_assert(action != 0);
  if(action->get_active()) {
    m_Statusbar.show();
  }
  m_sbVisibleConnection.unblock();
  displayFullscreenToolbar(false);
}

void
SampleWindow::initToolbarVisible()
{
  SampleSettings* settings = SampleSettings::getDefault();
  bool visible = settings->getToolbarVisible();
  Glib::RefPtr<Gtk::ToggleAction> action = 
      Glib::RefPtr<Gtk::ToggleAction>::cast_static(
          m_refToggleActionGroup->get_action("ViewToolbar"));
  action->set_active(visible);
  m_pToolbar->set_visible(visible);
}

void
SampleWindow::initStatusbarVisible()
{
  SampleSettings* settings = SampleSettings::getDefault();
  bool visible = settings->getStatusbarVisible();
  Glib::RefPtr<Gtk::ToggleAction> action = 
      Glib::RefPtr<Gtk::ToggleAction>::cast_static(
          m_refToggleActionGroup->get_action("ViewStatusbar"));
  action->set_active(visible);
  m_Statusbar.set_visible(visible);
}

void
SampleWindow::initUI()
{
  initToolbarVisible();
  initStatusbarVisible();
}

void 
SampleWindow::getGeometry(Gdk::Rectangle &rect)
{
  int monitor_num;
  Glib::RefPtr<const Gdk::Screen> screen = get_screen();
  monitor_num = screen->get_monitor_at_window(get_window());
  screen->get_monitor_geometry(monitor_num, rect);
}

bool 
SampleWindow::onAnimationTimeout()
{
  Gdk::Rectangle rect;
  bool ret = true;
  int x, y;

  getGeometry(rect);

  m_winFullscreen.get_position(x, y);

  if(m_isEnter) {
    if(y == rect.get_y()) {
      ret = false;
    } else {
      m_winFullscreen.move(x, y + 1);
    }
  } else {
    int w, h;
    m_winFullscreen.get_size(w, h);
    if(y == rect.get_y() - h + 1) {
      ret = false;
    } else {
      m_winFullscreen.move(x, y - 1);
    }
  }
  return ret;
}

void 
SampleWindow::beginAnimation(bool is_enter)
{
  static sigc::connection sConn;
  m_isEnter = is_enter;
  if(!sConn) {
    sConn = Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &SampleWindow::onAnimationTimeout),
        ANIMATION_SPEED);
  }
}

bool 
SampleWindow::onEnterNotifyEvent(GdkEventCrossing* event)
{
  beginAnimation(true);
  return false;
}

bool 
SampleWindow::onLeaveNotifyEvent(GdkEventCrossing* event)
{
  beginAnimation(false);
  return false;
}

void 
SampleWindow::displayFullscreenToolbar(bool is_show)
{
  if(is_show) {
    Gdk::Rectangle rect;
    int w, h;
    getGeometry(rect);
    m_winFullscreen.get_size(w, h);
    m_winFullscreen.resize(rect.get_width(), h);
    m_winFullscreen.move(rect.get_x(), rect.get_y() - h + 1);
    m_winFullscreen.show_all();
  } else {
    m_winFullscreen.hide();
  }
}

