/*
 * controller.cpp
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

#include "controller.h"

Controller::Controller()
  : Glib::ThreadPool(3), m_ModelVector(NUM_OF_MODELS)
{
  m_refNotifier = Notifier::create();
}

Controller::~Controller()
{
  shutdown();
}

void
Controller::addModel(int index, IModel* model)
{
  m_ModelVector[index] = model;
}

IModel*
Controller::getModel(int index)
{
  return m_ModelVector[index];
}

void
Controller::request(const Request *req)
{
}


