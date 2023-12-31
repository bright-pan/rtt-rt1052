/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "evkbimxrt1050_flexspi_nor_config.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.xip_board"
#endif


//Pre-defined LUT index
#define NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD                         0
#define NOR_CMD_LUT_SEQ_IDX_READ_STATUSREG                         1
#define NOR_CMD_LUT_SEQ_IDX_WRITE_ENABLE                           3 
#define NOR_CMD_LUT_SEQ_IDX_ERASE_SECTOR                           5
#define NOR_CMD_LUT_SEQ_IDX_ERASE_BLOCK                            8
#define NOR_CMD_LUT_SEQ_IDX_PAGE_PROGRAM_SINGLE                    9
#define NOR_CMD_LUT_SEQ_IDX_CHIP_ERASE                             11
#define NOR_CMD_LUT_SEQ_IDX_DUMMY                                  15

//Reserved
#define NOR_CMD_LUT_SEQ_IDX_WRITE_STATUSREG                        2
#define NOR_CMD_LUT_SEQ_IDX_READ_ID                                4

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(XIP_BOOT_HEADER_ENABLE) && (XIP_BOOT_HEADER_ENABLE == 1)
#if defined(__CC_ARM) || defined(__ARMCC_VERSION) || defined(__GNUC__)
__attribute__((section(".boot_hdr.conf"), used))
#elif defined(__ICCARM__)
#pragma location = ".boot_hdr.conf"
#endif

const flexspi_nor_config_t
    hyperflash_config =
        {
            .memConfig =
                {
                    .tag                = FLEXSPI_CFG_BLK_TAG,
                    .version            = FLEXSPI_CFG_BLK_VERSION,
                    .readSampleClkSrc   = kFlexSPIReadSampleClk_LoopbackInternally,
                    .csHoldTime         = 3u,
                    .csSetupTime        = 3u,
                    .columnAddressWidth = 0u,
                    // Enable DDR mode, Wordaddassable, Safe configuration, Differential clock
                    .deviceType         = kFlexSpiDeviceType_SerialNOR,
                    .sflashPadType      = kSerialFlash_8Pads,
                    .serialClkFreq      = kFlexSpiSerialClk_133MHz,
                    .sflashA1Size       = 8u * 1024u * 1024u,
                    .dataValidTime      = {15u, 0u},
                    .lookupTable =
                        {
                    // QSPI Read
                    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD] = 
                        FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x6B, RADDR_SDR, FLEXSPI_1PAD, 0x18),
                    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD + 1] = 
                        FLEXSPI_LUT_SEQ(DUMMY_SDR, FLEXSPI_4PAD, 0x08, READ_SDR, FLEXSPI_4PAD, 0x4),

                    // Read Status
                    [4 * NOR_CMD_LUT_SEQ_IDX_READ_STATUSREG] = 
                        FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xA5, READ_SDR, FLEXSPI_1PAD, 0x04),

                    // Write enable
                    [4 * NOR_CMD_LUT_SEQ_IDX_WRITE_ENABLE] = 
                        FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x06, STOP, FLEXSPI_1PAD, 0x00),

                    // Erase Sector
                    [4 * NOR_CMD_LUT_SEQ_IDX_ERASE_SECTOR] = 
                        FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xD7, RADDR_SDR, FLEXSPI_1PAD, 0x18),

                    // Erase Block 64KB
                    [4 * NOR_CMD_LUT_SEQ_IDX_ERASE_BLOCK] = 
                        FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x52, RADDR_SDR, FLEXSPI_1PAD, 0x18),

                    // Page Program
                    [4 * NOR_CMD_LUT_SEQ_IDX_PAGE_PROGRAM_SINGLE] = 
                        FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x02, RADDR_SDR, FLEXSPI_1PAD, 0x18),
                    [4 * NOR_CMD_LUT_SEQ_IDX_PAGE_PROGRAM_SINGLE + 1] = 
                        FLEXSPI_LUT_SEQ(WRITE_SDR, FLEXSPI_1PAD, 0x04, STOP, FLEXSPI_1PAD, 0x00),

                    // Chip Erase
                    [4 * NOR_CMD_LUT_SEQ_IDX_CHIP_ERASE] = 
                        FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xC7, STOP, FLEXSPI_1PAD, 0x00),

                    // Dummy
                    [4 * NOR_CMD_LUT_SEQ_IDX_DUMMY] = 0,

                    // write status reg
                    [4 * NOR_CMD_LUT_SEQ_IDX_WRITE_STATUSREG] = 
                        FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x01, WRITE_SDR, FLEXSPI_1PAD, 0x04),

                    // read id
                    [4 * NOR_CMD_LUT_SEQ_IDX_READ_ID] = 
                        FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xAB, DUMMY_SDR, FLEXSPI_1PAD, 0x18),
                    [4 * NOR_CMD_LUT_SEQ_IDX_READ_ID + 1] = 
                        FLEXSPI_LUT_SEQ(READ_SDR, FLEXSPI_1PAD, 0x04, STOP, FLEXSPI_1PAD, 0x00),
                },
                    // LUT customized sequence
                    .lutCustomSeq = {{
                                         .seqNum   = 0,
                                         .seqId    = 0,
                                         .reserved = 0,
                                     },
                                     {
                                         .seqNum   = 2,
                                         .seqId    = 1,
                                         .reserved = 0,
                                     },
                                     {
                                         .seqNum   = 2,
                                         .seqId    = 3,
                                         .reserved = 0,
                                     },
                                     {
                                         .seqNum   = 4,
                                         .seqId    = 5,
                                         .reserved = 0,
                                     },
                                     {
                                         .seqNum   = 2,
                                         .seqId    = 9,
                                         .reserved = 0,
                                     },
                                     {
                                         .seqNum   = 4,
                                         .seqId    = 11,
                                         .reserved = 0,
                                     }},
                },
            .pageSize           = 512u,
            .sectorSize         = 256u * 1024u,
            .ipcmdSerialClkFreq = 1u,
            .serialNorType      = 1u,
            .blockSize          = 256u * 1024u,
            .isUniformBlockSize = true,
};
#endif /* XIP_BOOT_HEADER_ENABLE */
