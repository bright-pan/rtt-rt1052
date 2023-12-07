/*
 * Copyright (c) 2023, SenYang Development Team
 *
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-05     bright      first version
 *
 */

#ifndef __COM_COMM__
#define __COM_COMM__

#include <rtthread.h>

typedef struct {
    rt_int8_t type;
} comm_msg_t;

rt_err_t comm_init(void);
rt_err_t comm_msg_send(comm_msg_t *msg);

#endif
