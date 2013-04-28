/*
 * response.h
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
#ifndef MVC_RESPONSE_H
#define MVC_RESPONSE_H

#include <glibmm/ustring.h>
#include <glibmm/objectbase.h>
#include "interface.h"

typedef enum {
  RESPONSE_CMD_PENDING = 0,
  RESPONSE_CMD_EXECUTING ,
  RESPONSE_CMD_DONE ,
  RESPONSE_CMD_ERROR ,
  RESPONSE_MODEL_CHANGED ,
}ResponseState;

class Response : virtual public Glib::ObjectBase {
 public:
  Response(unsigned int id, ResponseState resp_state, const Glib::ustring& msg = "");
  ~Response();
  unsigned int getId();
  ResponseState getState();
  void setState(ResponseState resp_state);
  const Glib::ustring& getMsg();
  void setMsg(const Glib::ustring& msg);
 private:
  unsigned int m_Id;
  ResponseState m_State;
  Glib::ustring m_Msg;
};

class ModelChangedResponse : public Response {
 public:
  ModelChangedResponse(unsigned int id, const IModel *model);
  ~ModelChangedResponse();
  const IModel* getModel();
 private:
  const IModel *m_Model;
};

#endif /* ifndef MVC_RESPONSE_H */

