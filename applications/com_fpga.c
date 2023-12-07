/*
 * Copyright (c) 2023, SenYang Development Team
 *
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-12-05     bright      first version
 *
 */

#include <rtdevice.h>

#include "drv_gpio.h"
#include "com_fpga.h"

#define COM_FPGA_THREAD_NAME "fpga"
#define COM_FPGA_THREAD_STACK_SIZE 2048
#define COM_FPGA_THREAD_PRIORITY 10

/* defined the LED pin: GPIO2_IO15 */
#define LED1_PIN               GET_PIN(2,15)

static rt_thread_t com_fpga_thread_tid;


void com_fpga_thread_entry(void *param) {
    /* set LED0 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    while (1) {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

int com_fpga_init(void) {
    com_fpga_thread_tid = rt_thread_create(COM_FPGA_THREAD_NAME, com_fpga_thread_entry, RT_NULL,
                           COM_FPGA_THREAD_STACK_SIZE, COM_FPGA_THREAD_PRIORITY, 20);
    RT_ASSERT(com_fpga_thread_tid != RT_NULL);
    rt_kprintf("%s is created!\n", COM_FPGA_THREAD_NAME);
    rt_thread_startup(com_fpga_thread_tid);
    return 0;
}
