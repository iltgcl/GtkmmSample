/*
 * cmd_id.h
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
#ifndef MVC_CMD_ID_H
#define MVC_CMD_ID_H

/* Change this value according to your need */
#define NUM_OF_MODELS     (2)

/* The max number per model equal 2 ^ 5 = 32, change below to meet your needs.
 * The trick is that: shift CmdId right by POWER_OF_CMD_NUM, get the model id.
 */
#define POWER_OF_CMD_NUM  (5)
#define CMD_ID_TO_MODEL_ID(id)   (id >> POWER_OF_CMD_NUM)

typedef enum CmdId_ {
  /* model 0 */
  /* TODO: add  cmd id bellow */
  MODEL0_BEGIN = (0 << POWER_OF_CMD_NUM),

  /* model 1 */
  /* TODO: add  cmd id bellow */
  MODEL1_BEGIN = (1 << POWER_OF_CMD_NUM),

  /* model 2 */
  MODEL2_BEGIN = (2 << POWER_OF_CMD_NUM),

}CmdId;


#endif /* ifndef MVC_CMD_ID_H */

