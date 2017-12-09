#ifndef __MEMORY_H_
#define __MEMORY_H_

#include "STM32f10x.h"
#include "bsp.h"
#include "menu.h"

#define I2C_Speed              200000
#define I2C_SLAVE_ADDRESS7     0xA0
#define I2C_FLASH_PAGESIZE     16
#define EEPROM_HW_ADDRESS      0xA0   /* E0 = E1 = E2 = 0 */


void I2C_EE_BufferWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
void I2C_EE_BufferRead(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);
void I2C_EE_ByteWrite(uint8_t* pBuffer, uint16_t WriteAddr);
void I2C_EE_PageWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite);
void I2C_EE_WaitEepromStandbyState(void);

void I2C_save_options(menuComboType* mcombo);
void I2C_load_options(menuComboType* mcombo);

void I2C_save_all_lists(menuListType** mlist);
void I2C_load_all_lists(menuListType** mlist);

#define MEM_OPTIONS_CNT     4

// !!!!!!!!!!!!!!
// AT24C16 = 2Kbytes capacity: [0x0000: 0x0800]
// AT24C16 has 16 bytes write page size

#define MEM_OPTIONS_START_ADR       0x0080
#define MEM_LISTS_START_ADR         0x0100


#endif // __MEMORY_H_
