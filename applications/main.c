/*
 * Copyright (c) 2023, SenYang Development Team
 *
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-05     bright      first version
 *
 */

#include <rtthread.h>

#include "com_comm.h"
#include "com_fpga.h"

int main(void)
{
    /* component initialize */
    rt_kprintf("the component initialize :\n");
    comm_init();
    com_fpga_init();
    
    return 0; 
}
