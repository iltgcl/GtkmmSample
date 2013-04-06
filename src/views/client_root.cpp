
#include <iostream>

#include "client_root.h"

ClientRoot::ClientRoot()
  : Glib::ObjectBase (typeid (ClientRoot)),
    prop_can_save(*this, "can-save"),
    prop_can_save_as(*this, "can-save-as"),
    prop_can_undo(*this, "can-undo"),
    prop_can_redo(*this, "can-redo"),
    prop_can_cut(*this, "can-cut"),
    prop_can_copy(*this, "can-copy"),
    prop_can_paste(*this, "can-paste"),
    prop_can_delete(*this, "can-delete"),
    prop_can_select_all(*this, "can-select-all"),
    m_SidePane("SidePane"),
    m_MainPane("MainPane")
{
  pack1(m_SidePane, true, false);
  pack2(m_MainPane, true, false);
  m_MainPane.signal_clicked().connect(sigc::mem_fun(*this, &ClientRoot::onTestProperties));
}

void ClientRoot::onTestProperties()
{
  static bool sState = false;
  sState = ! sState;

  prop_can_save = sState;
  prop_can_save_as = sState;
  prop_can_undo = sState;
  prop_can_redo = sState;
  prop_can_cut = sState;
  prop_can_copy = sState;
  prop_can_paste = sState;
  prop_can_delete = sState;
  prop_can_select_all = sState;
}

ClientRoot::~ClientRoot()
{
}

Glib::PropertyProxy<bool> 
ClientRoot::property_can_save()
{
  return prop_can_save.get_proxy();
}

Glib::PropertyProxy<bool> 
ClientRoot::property_can_save_as()
{
  return prop_can_save_as.get_proxy();
}

Glib::PropertyProxy<bool> 
ClientRoot::property_can_undo()
{
  return prop_can_undo.get_proxy();
}

Glib::PropertyProxy<bool> 
ClientRoot::property_can_redo()
{
  return prop_can_redo.get_proxy();
}

Glib::PropertyProxy<bool> 
ClientRoot::property_can_cut()
{
  return prop_can_cut.get_proxy();
}

Glib::PropertyProxy<bool> 
ClientRoot::property_can_copy()
{
  return prop_can_copy.get_proxy();
}

Glib::PropertyProxy<bool> 
ClientRoot::property_can_paste()
{
  return prop_can_paste.get_proxy();
}

Glib::PropertyProxy<bool> 
ClientRoot::property_can_delete()
{
  return prop_can_delete.get_proxy();
}

Glib::PropertyProxy<bool> 
ClientRoot::property_can_select_all()
{
  return prop_can_select_all.get_proxy();
}

