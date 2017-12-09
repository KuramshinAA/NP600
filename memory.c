
#include "bsp.h"
#include "memory.h"
#include "font.h"
#include "lcd_UC1701.h"
#include "delay.h"


//***************************************************************************//
//  Load temperature program from EEPROM
//***************************************************************************//
//  Memory MAP
//  0x0000: MEMORY START
//  ...
//  0x0400: END for AT24C08
//***************************************************************************//

//***************************************************************************//
//  Save lists values
//***************************************************************************//
void I2C_save_all_lists(menuListType** mlist)
{
    uint8_t i2c_buff[4];
    uint16_t adr = 0;

    for (uint8_t i=0; i<MENU_LIST_CNT; i++)
    {
        for (uint8_t c=0; c<mlist[i]->items_cnt; c++)
        {
            uint32_t v = mlist[i]->item[c].val;
            i2c_buff[0] = (uint8_t)(v>>24);
            i2c_buff[1] = (uint8_t)(v>>16);
            i2c_buff[2] = (uint8_t)(v>>8);
            i2c_buff[3] = (uint8_t)(v);
            I2C_EE_BufferWrite(i2c_buff, MEM_LISTS_START_ADR + adr, 4);
            adr += 4;
        }
    }
}

//***************************************************************************//
//  Load lists values
//***************************************************************************//
void I2C_load_all_lists(menuListType** mlist)
{
    uint8_t i2c_buff[4];
    uint16_t adr = 0;

    for (uint8_t i=0; i<MENU_LIST_CNT; i++)
    {
        for (uint8_t c=0; c<mlist[i]->items_cnt; c++)
        {
            I2C_EE_BufferRead(i2c_buff, MEM_LISTS_START_ADR + adr, 4);
            uint32_t v = ((uint32_t)i2c_buff[0]<<24) + ((uint32_t)i2c_buff[1]<<16) +
                ((uint32_t)i2c_buff[2]<<8) + i2c_buff[3];

            if (v == 0xFFFFFFFF) v = 0;

            mlist[i]->item[c].val = v;
            adr += 4;
        }
    }
}

//***************************************************************************//
//  Load options
//***************************************************************************//
void I2C_load_options(menuComboType* mcombo)
{
    uint8_t i2c_buff[MEM_OPTIONS_CNT];

    I2C_EE_BufferRead(i2c_buff, MEM_OPTIONS_START_ADR, MEM_OPTIONS_CNT);

    for (uint8_t i=0; i<MEM_OPTIONS_CNT; i++)
    {
        if (i2c_buff[i] == 0xFF)
        {
            i2c_buff[i] = 0;
        }

        mcombo->item[i].selected = i2c_buff[i];
    }
}

//***************************************************************************//
//  Save options
//***************************************************************************//
void I2C_save_options(menuComboType* mcombo)
{
    uint8_t i2c_buff[MEM_OPTIONS_CNT];

    // Диаметр шланга
    i2c_buff[0] = mcombo->item[0].selected;
    // толщ.стенки
    i2c_buff[1] = mcombo->item[1].selected;
    // головка
    i2c_buff[2] = mcombo->item[2].selected;
    // коэфф.передачи
    i2c_buff[3] = mcombo->item[3].selected;

    I2C_EE_BufferWrite(i2c_buff, MEM_OPTIONS_START_ADR, MEM_OPTIONS_CNT);
}

/***************************************************************************//**
 * @brief      Writes buffer of data to the I2C EEPROM.
 * @param[in]  pBuffer : pointer to the buffer  containing the data to be
 *                       written to the EEPROM.
 * @param[in]  WriteAddr : EEPROM's internal address to write to.
 * @param[in]  NumByteToWrite : number of bytes to write to the EEPROM.
 * @return     None
 ******************************************************************************/
void I2C_EE_BufferWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, count = 0;
  uint16_t Addr = 0;

  WriteAddr = WriteAddr & 0x7FF;
  Addr = WriteAddr % I2C_FLASH_PAGESIZE;
  count = I2C_FLASH_PAGESIZE - Addr;
  NumOfPage =  NumByteToWrite / I2C_FLASH_PAGESIZE;
  NumOfSingle = NumByteToWrite % I2C_FLASH_PAGESIZE;

  /* If WriteAddr is I2C_FLASH_PAGESIZE aligned  */
  if (Addr == 0)
  {
    /* If NumByteToWrite < I2C_FLASH_PAGESIZE */
    if (NumOfPage == 0)
    {
      I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      I2C_EE_WaitEepromStandbyState();
    }
    /* If NumByteToWrite > I2C_FLASH_PAGESIZE */
    else
    {
      while(NumOfPage--)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_FLASH_PAGESIZE);
        I2C_EE_WaitEepromStandbyState();
        WriteAddr +=  I2C_FLASH_PAGESIZE;
        pBuffer += I2C_FLASH_PAGESIZE;
      }

      if(NumOfSingle != 0)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        I2C_EE_WaitEepromStandbyState();
      }
    }
  }
  /* If WriteAddr is not I2C_FLASH_PAGESIZE aligned  */
  else
  {
    /* If NumByteToWrite < I2C_FLASH_PAGESIZE */
    if(NumOfPage== 0)
    {
      /* If the number of data to be written is more than the remaining space
        in the current page: */
      if (NumByteToWrite > count)
      {
        /* Write the data conained in same page */
        I2C_EE_PageWrite(pBuffer, WriteAddr, count);
        I2C_EE_WaitEepromStandbyState();

        /* Write the remaining data in the following page */
        I2C_EE_PageWrite((uint8_t*)(pBuffer + count), (WriteAddr + count), (NumByteToWrite - count));
        I2C_EE_WaitEepromStandbyState();
      }

      else
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        I2C_EE_WaitEepromStandbyState();
      }
    }

    /* If NumByteToWrite > I2C_FLASH_PAGESIZE */
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / I2C_FLASH_PAGESIZE;
      NumOfSingle = NumByteToWrite % I2C_FLASH_PAGESIZE;

      if(count != 0)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, count);
        I2C_EE_WaitEepromStandbyState();
        WriteAddr += count;
        pBuffer += count;
      }

      while(NumOfPage--)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_FLASH_PAGESIZE);
        I2C_EE_WaitEepromStandbyState();
        WriteAddr +=  I2C_FLASH_PAGESIZE;
        pBuffer += I2C_FLASH_PAGESIZE;
      }

      if(NumOfSingle != 0)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        I2C_EE_WaitEepromStandbyState();
      }
    }
  }
}


/***************************************************************************//**
 * @brief      Reads a block of data from the EEPROM.
 * @param[in]  pBuffer : pointer to the buffer that receives the data read
 *                       from the EEPROM.
 * @param[in]  ReadAddr : EEPROM's internal address to read from.
 * @param[in]  NumByteToRead : number of bytes to read from the EEPROM.
 * @return     None
 ******************************************************************************/
void I2C_EE_BufferRead(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead)
{
  ReadAddr = ReadAddr & 0x7FF;

  /* While the bus is busy */
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

  /* Send START condition */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send EEPROM address for write */
  uint8_t tmp = ((ReadAddr>>8)<<1) | EEPROM_HW_ADDRESS;
  I2C_Send7bitAddress(I2C1, tmp, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Send the EEPROM's internal address to read from: LSB of the address */
  I2C_SendData(I2C1, (uint8_t)(ReadAddr & 0x00FF));

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send STRAT condition a second time */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send EEPROM address for read */
  I2C_Send7bitAddress(I2C1, EEPROM_HW_ADDRESS, I2C_Direction_Receiver);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  /* While there is data to be read */
  while(NumByteToRead)
  {
    if(NumByteToRead == 1)
    {
        /* Disable Acknowledgement */
        I2C_AcknowledgeConfig(I2C1, DISABLE);

        /* Send STOP Condition */
        I2C_GenerateSTOP(I2C1, ENABLE);
    }

  /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
        /* Read a byte from the EEPROM */
        *pBuffer = I2C_ReceiveData(I2C1);

        /* Point to the next location where the byte read will be saved */
        pBuffer++;

        /* Decrement the read bytes counter */
        NumByteToRead--;
    }
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2C1, ENABLE);
}

/***************************************************************************//**
 * @brief      Writes one byte to the I2C EEPROM.
 * @param[in]  pBuffer   : pointer to the buffer  containing the data to be
 *                         written to the EEPROM.
 * @param[in]  WriteAddr : EEPROM's internal address to write to.
 * @return     None
 ******************************************************************************/
void I2C_EE_ByteWrite(uint8_t* pBuffer, uint16_t WriteAddr)
{
  /* Send STRAT condition */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send EEPROM address for write */
  uint8_t tmp = ((WriteAddr>>8)<<1) | EEPROM_HW_ADDRESS;
  I2C_Send7bitAddress(I2C1, tmp, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Send the EEPROM's internal address to write to : LSB of the address */
  I2C_SendData(I2C1, (uint8_t)(WriteAddr & 0x00FF));

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send the byte to be written */
  I2C_SendData(I2C1, *pBuffer);

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send STOP condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
}

/***************************************************************************//**
 * @brief      Writes more than one byte to the EEPROM with a single WRITE cycle.
 *             Note: The number of byte can't exceed the EEPROM page size.
 * @param[in]  pBuffer : pointer to the buffer containing the data to be
 *                       written to the EEPROM.
 * @param[in]  WriteAddr : EEPROM's internal address to write to.
 * @param[in]  NumByteToWrite : number of bytes to write to the EEPROM.
 * @return     None
 ******************************************************************************/
void I2C_EE_PageWrite(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t NumByteToWrite)
{
  /* While the bus is busy */
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

  /* Send START condition */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send EEPROM address for write */
  uint8_t tmp = ((WriteAddr>>8)<<1) | EEPROM_HW_ADDRESS;
  I2C_Send7bitAddress(I2C1, tmp, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Send the EEPROM's internal address to write to : LSB of the address */
  I2C_SendData(I2C1, (uint8_t)(WriteAddr & 0x00FF));

  /* Test on EV8 and clear it */
  while(! I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* While there is data to be written */
  while(NumByteToWrite--)
  {
    /* Send the current byte */
    I2C_SendData(I2C1, *pBuffer);

    /* Point to the next byte to be written */
    pBuffer++;

    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  }

  /* Send STOP condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
}

/***************************************************************************//**
 * @brief  Wait for EEPROM Standby state
 ******************************************************************************/
void I2C_EE_WaitEepromStandbyState(void)
{
  __IO uint16_t SR1_Tmp = 0;

  do
  {
    /* Send START condition */
    I2C_GenerateSTART(I2C1, ENABLE);

    /* Read I2C1 SR1 register to clear pending flags */
    SR1_Tmp = I2C_ReadRegister(I2C1, I2C_Register_SR1);

    /* Send EEPROM address for write */
    I2C_Send7bitAddress(I2C1, EEPROM_HW_ADDRESS, I2C_Direction_Transmitter);
  }
  while(!(I2C_ReadRegister(I2C1, I2C_Register_SR1) & 0x0002));

  /* Clear AF flag */
  I2C_ClearFlag(I2C1, I2C_FLAG_AF);

  /* STOP condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
}

