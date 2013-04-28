/*
 * response.cpp
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

#include "response.h"

Response::Response(unsigned int id, ResponseState resp_state, const Glib::ustring& msg)
  : m_Id(id), m_State(resp_state), m_Msg(msg)
{
}

Response::~Response()
{
}

unsigned int 
Response::getId()
{
  return m_Id;
}

ResponseState 
Response::getState()
{
  return m_State;
}

void
Response::setState(ResponseState resp_state)
{
  m_State = resp_state;
}

const Glib::ustring& 
Response::getMsg()
{
  return m_Msg;
}

void
Response::setMsg(const Glib::ustring& msg)
{
  m_Msg = msg;
}

ModelChangedResponse::ModelChangedResponse(unsigned int id, const IModel *model)
  : Response(id, RESPONSE_MODEL_CHANGED), m_Model(model)
{
}

ModelChangedResponse::~ModelChangedResponse()
{
}

const IModel* 
ModelChangedResponse::getModel()
{
  return m_Model;
}

