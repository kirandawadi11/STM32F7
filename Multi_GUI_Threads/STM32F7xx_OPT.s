;/*****************************************************************************/
;/* STM32F7xx_OTP.s: STM32F7xx Flash Option Bytes                             */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */
;/*****************************************************************************/
;/*  This file is part of the uVision/ARM development tools                   */
;/*  Copyright (c) 2015 Keil - An ARM Company.                                */
;/*  All rights reserved.                                                     */
;/*****************************************************************************/

;// <e> Flash Option Bytes
FLASH_OPT       EQU     1

;// <h> Flash Read Protection
;//     <i> Read protection is used to protect the software code stored in Flash memory
;//   <o0.8..15> Read Protection Level
;//     <i> Level 0: No Protection
;//     <i> Level 1: Read Protection of Memories (debug features limited)
;//     <i> Level 2: Chip Protection (debug and boot in RAM features disabled)
;//          <0xAA=> Level 0 (No Protection)
;//          <0x00=> Level 1 (Read Protection of Memories)
;//          <0xCC=> Level 2 (Chip Protection)
;// </h>

;// <h> Flash Write Protection
;//   <h> nWRP Sectors 0 to 7
;//       <i> Not write protect Sectors 0 to 7
;//     <o0.16> Sector 0
;//     <o0.17> Sector 1
;//     <o0.18> Sector 2
;//     <o0.19> Sector 3
;//     <o0.20> Sector 4
;//     <o0.21> Sector 5
;//     <o0.22> Sector 6
;//     <o0.23> Sector 7
;//   </h>
;// </h>

;// <h> User Configuration
;//   <o0.2..3> BOR_LEV
;//          <0=> BOR Level 3 (VBOR3), brownout threshold level 3
;//          <1=> BOR Level 2 (VBOR2), brownout threshold level 2
;//          <2=> BOR Level 1 (VBOR1), brownout threshold level 1
;//          <3=> BOR off     (VBOR0), POR/PDR reset threshold level is applied
;//   <o0.4> WWDG_SW
;//          <0=> Hardware window watchdog
;//          <1=> Software window watchdog
;//   <o0.5> IWDG_SW
;//          <0=> Hardware independant watchdog
;//          <1=> Software independant watchdog
;//   <o0.6> nRST_STOP
;//     <i> Generate Reset when entering STOP Mode
;//          <0=> Enabled
;//          <1=> Disabled
;//   <o0.7> nRST_STDBY
;//     <i> Generate Reset when entering Standby Mode
;//          <0=> Enabled
;//          <1=> Disabled
;//   <o0.31> IWDG_STOP
;//     <i> Independent watchdog counter freeze in Stop mode
;//          <0=> Freeze IWDG counter in STOP mode
;//          <1=> IWDG counter active in STOP mode
;//   <o0.30> WDG_STDBY
;//     <i> Independent watchdog counter freeze in standby mode
;//          <0=> Freeze IWDG counter in standby mode
;//          <1=> IWDG counter active in standby mode
;// </h>

;// <h> Boot Address Configuration
;//     <i> The boot memory address can be programmed to any address in the range
;//     <i> 0x0000 0000 to 0x2004 FFFF with a granularity of 16KB
;//     <i> Example:
;//     <i> BOOT_ADDx = 0x0000: Boot from ITCM RAM (0x0000 0000)
;//     <i> BOOT_ADDx = 0x0040: Boot from System memory bootloader (0x0010 0000)
;//     <i> BOOT_ADDx = 0x0080: Boot from Flash on ITCM interface (0x0020 0000)
;//     <i> BOOT_ADDx = 0x2000: Boot from Flash on AXIM interface (0x0800 0000)
;//     <i> BOOT_ADDx = 0x8000: Boot from DTCM RAM (0x2000 0000)
;//     <i> BOOT_ADDx = 0x8004: Boot from SRAM1 (0x2001 0000)
;//     <i> BOOT_ADDx = 0x8013: Boot from SRAM2 (0x2004 C000)
;//   <o1.0..15>  Boot Address 0 <#/0x4000>
;//     <i> Boot base address when Boot pin = 1
;//   <o1.16..31> Boot Address 1 <#/0x4000>
;//     <i> Boot base address when Boot pin = 0
;// </h>

FLASH_OPTCR    EQU     0xC0FFAAFC       ; reset value 0xC0FFAAEC
FLASH_OPTCR1   EQU     0x00400080       ; reset value 0xFF7F0080
;// </e>


                IF      FLASH_OPT <> 0
                AREA    |.ARM.__AT_0x1FFF0000|, CODE, READONLY
                DCD     FLASH_OPTCR
                DCD     FLASH_OPTCR1
                ENDIF

                END
