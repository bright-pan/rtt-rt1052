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
#include <rtdevice.h>
#include <cJSON.h>

#include "drv_gpio.h"
#include "com_comm.h"

#define COMM_THREAD_NAME "comm"
#define COMM_THREAD_STACK_SIZE 2048
#define COMM_THREAD_PRIORITY 10

/* defined the LED pin: GPIO2_IO14 */
#define LED0_PIN               GET_PIN(2,14)


static rt_thread_t comm_thread_tid;
/* 消息队列控制块 */
static struct rt_messagequeue comm_msg_mq;
/* 消息队列中用到的放置消息的内存池 */
static rt_uint8_t comm_msg_pool[2048];



void comm_thread_entry(void *param) {
    rt_err_t result = RT_EOK;
    rt_uint8_t led_status = PIN_LOW;
    comm_msg_t comm_msg;


    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    /* 初始化消息队列 */
    result = rt_mq_init(&comm_msg_mq,
                        "comm_msg_mq",
                        &comm_msg_pool[0],              /* 内存池指向msg_pool */
                        sizeof(comm_msg_t),							/* 每个消息的大小 */
                        sizeof(comm_msg_pool),          /* 内存池的大小是msg_pool的大小 */
                        RT_IPC_FLAG_FIFO);          		/* 如果有多个线程等待，按照先来先得到的方法分配消息 */
    RT_ASSERT(result == RT_EOK);

    while (1) {
        /* 从消息队列中接收消息 */
        if (rt_mq_recv(&comm_msg_mq, &comm_msg, sizeof(comm_msg_t), 500) == RT_EOK) {
            rt_kprintf("recv msg from msg queue\n", comm_msg);
        } else {
            if (led_status == PIN_HIGH) {
                rt_pin_write(LED0_PIN, PIN_LOW);
                led_status = PIN_LOW;
            } else {
                rt_pin_write(LED0_PIN, PIN_HIGH);
                led_status = PIN_HIGH;
            }
        }
    }
}

rt_err_t comm_init(void) {

    comm_thread_tid = rt_thread_create(COMM_THREAD_NAME, comm_thread_entry, RT_NULL,
                           COMM_THREAD_STACK_SIZE, COMM_THREAD_PRIORITY, 20);
    RT_ASSERT(comm_thread_tid != RT_NULL);
    rt_kprintf("%s is created!\n", COMM_THREAD_NAME);
    rt_thread_startup(comm_thread_tid);
    return RT_EOK;
}

rt_err_t comm_msg_send(comm_msg_t *msg) {
    return rt_mq_send(&comm_msg_mq, msg, sizeof(comm_msg_t));
}