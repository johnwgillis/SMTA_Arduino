#include "SMTA_AMG88xx.h"

#include <Wire.h>

bool SMTA_AMG88xx::begin(uint8_t addr)
{
	_i2caddr = addr;
	
	_i2c_init();
	
	//enter normal mode
	_pctl.PCTL = AMG88xx_NORMAL_MODE;
	write8(AMG88xx_PCTL, _pctl.get());
	
	//software reset
	_rst.RST = AMG88xx_INITIAL_RESET;
	write8(AMG88xx_RST, _rst.get());
	
	//disable interrupts by default
	disableInterrupt();
	
	//set to 10 FPS
	_fpsc.FPS = AMG88xx_FPS_10;
	write8(AMG88xx_FPSC, _fpsc.get());

	return true;
}

void SMTA_AMG88xx::setMovingAverageMode(bool mode)
{
	_ave.MAMOD = mode;
	write8(AMG88xx_AVE, _ave.get());
}

void SMTA_AMG88xx::setInterruptLevels(float high, float low)
{
	setInterruptLevels(high, low, high * .95);
}

void SMTA_AMG88xx::setInterruptLevels(float high, float low, float hysteresis)
{
	int highConv = high / AMG88xx_PIXEL_TEMP_CONVERSION;
	highConv = constrain(highConv, -4095, 4095);
	_inthl.INT_LVL_H = highConv & 0xFF;
	_inthh.INT_LVL_H = (highConv & 0xF) >> 4;
	this->write8(AMG88xx_INTHL, _inthl.get());
	this->write8(AMG88xx_INTHH, _inthh.get());
	
	int lowConv = low / AMG88xx_PIXEL_TEMP_CONVERSION;
	lowConv = constrain(lowConv, -4095, 4095);
	_intll.INT_LVL_L = lowConv & 0xFF;
	_intlh.INT_LVL_L = (lowConv & 0xF) >> 4;
	this->write8(AMG88xx_INTLL, _intll.get());
	this->write8(AMG88xx_INTLH, _intlh.get());
	
	int hysConv = hysteresis / AMG88xx_PIXEL_TEMP_CONVERSION;
	hysConv = constrain(hysConv, -4095, 4095);
	_ihysl.INT_HYS = hysConv & 0xFF;
	_ihysh.INT_HYS = (hysConv & 0xF) >> 4;
	this->write8(AMG88xx_IHYSL, _ihysl.get());
	this->write8(AMG88xx_IHYSH, _ihysh.get());
}

void SMTA_AMG88xx::enableInterrupt()
{
	_intc.INTEN = 1;
	this->write8(AMG88xx_INTC, _intc.get());
}

void SMTA_AMG88xx::disableInterrupt()
{
	_intc.INTEN = 0;
	this->write8(AMG88xx_INTC, _intc.get());
}

void SMTA_AMG88xx::setInterruptMode(uint8_t mode)
{
	_intc.INTMOD = mode;
	this->write8(AMG88xx_INTC, _intc.get());
}

void SMTA_AMG88xx::getInterrupt(uint8_t *buf, uint8_t size)
{
	uint8_t bytesToRead = min(size, 8);
	
	this->read(AMG88xx_INT_OFFSET, buf, bytesToRead);
}

void SMTA_AMG88xx::clearInterrupt()
{
	_rst.RST = AMG88xx_FLAG_RESET;
	write8(AMG88xx_RST, _rst.get());
}

float SMTA_AMG88xx::readThermistor()
{
	uint8_t raw[2];
	this->read(AMG88xx_TTHL, raw, 2);
	uint16_t recast = ((uint16_t)raw[1] << 8) | ((uint16_t)raw[0]);

	return signedMag12ToFloat(recast) * AMG88xx_THERMISTOR_CONVERSION;
}

void SMTA_AMG88xx::readPixels(float *buf, uint8_t size)
{
	uint16_t recast;
	float converted;
	uint8_t bytesToRead = min(size << 1, AMG88xx_PIXEL_ARRAY_SIZE << 1);
	uint8_t rawArray[bytesToRead];
	this->read(AMG88xx_PIXEL_OFFSET, rawArray, bytesToRead);
	
	for(int i=0; i<size; i++){
		uint8_t pos = i << 1;
		recast = ((uint16_t)rawArray[pos + 1] << 8) | ((uint16_t)rawArray[pos]);
		
		converted = signedMag12ToFloat(recast) * AMG88xx_PIXEL_TEMP_CONVERSION;
		buf[i] = converted;
	}
}

void SMTA_AMG88xx::write8(byte reg, byte value)
{
	this->write(reg, &value, 1);
}

uint8_t SMTA_AMG88xx::read8(byte reg)
{
	uint8_t ret;
	this->read(reg, &ret, 1);
	
	return ret;
}













//#define I2C_EXAMPLE_MASTER_NUM             I2C_NUM_1        /*!< I2C port number for master dev */
//#define I2C_EXAMPLE_MASTER_TX_BUF_DISABLE  0                /*!< I2C master do not need buffer */
//#define I2C_EXAMPLE_MASTER_RX_BUF_DISABLE  0                /*!< I2C master do not need buffer */
//#define I2C_EXAMPLE_MASTER_FREQ_HZ         100000           /*!< I2C master clock frequency */
//
//#define ACK_CHECK_EN                       0x1              /*!< I2C master will check ack from slave*/
//#define ACK_VAL                            0x0              /*!< I2C ack value */
//#define NACK_VAL                           0x1              /*!< I2C nack value */
//
//
//
//void SMTA_AMG88xx::_i2c_init()
//{
//	int i2c_master_port = I2C_EXAMPLE_MASTER_NUM;
//  i2c_config_t conf;
//  conf.mode = I2C_MODE_MASTER;
//  conf.sda_io_num = ((gpio_num_t)GRIDEYE_SDA_PIN); /*!< gpio number for I2C master data  */
//  conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
//  conf.scl_io_num = (gpio_num_t) GRIDEYE_SCL_PIN; /*!< gpio number for I2C master clock */
//  conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
//  conf.master.clk_speed = I2C_EXAMPLE_MASTER_FREQ_HZ;
//  i2c_param_config(((i2c_port_t)i2c_master_port), &conf);
//  i2c_driver_install(((i2c_port_t)i2c_master_port), conf.mode,
//                     I2C_EXAMPLE_MASTER_RX_BUF_DISABLE,
//                     I2C_EXAMPLE_MASTER_TX_BUF_DISABLE, 0);
//}
//
//void SMTA_AMG88xx::read(uint8_t reg, uint8_t *buf, uint8_t num)
//{
//  uint8_t value;
//  uint8_t pos = 0;
//  
//  //on arduino we need to read in 32 byte chunks
//  while(pos < num){
//    
//    uint8_t read_now = min(32, num - pos);
//
//    uint8_t write_data = ((uint8_t)reg + pos);
//    write_raw(&write_data, sizeof(uint8_t));
//    
//    read_raw(buf,read_now);
//  }
//}
//
//void SMTA_AMG88xx::read_raw(uint8_t *buf, uint8_t num)
//{
//	if (num == 0) {
//      return;
//  }
//  i2c_port_t i2c_num = I2C_EXAMPLE_MASTER_NUM;
//  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//  i2c_master_start(cmd);
//  i2c_master_write_byte(cmd, ( (uint8_t)_i2caddr << 1 ) | I2C_MASTER_READ, ACK_CHECK_EN);
//  if (num > 1) {
//      i2c_master_read(cmd, buf, num - 1, ACK_VAL);
//  }
//  i2c_master_read_byte(cmd, buf + num - 1, NACK_VAL);
//  i2c_master_stop(cmd);
//  esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
//  i2c_cmd_link_delete(cmd);
//}
//
//void SMTA_AMG88xx::write(uint8_t reg, uint8_t *buf, uint8_t num)
//{
//  write_raw((uint8_t *)buf, num);
//}
//
//void SMTA_AMG88xx::write_raw(uint8_t *buf, uint8_t num)
//{
//  if (num == 0) {
//      return;
//  }
//  i2c_port_t i2c_num = I2C_EXAMPLE_MASTER_NUM;
//  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//  i2c_master_start(cmd);
//  i2c_master_write_byte(cmd, ( _i2caddr << 1 ) | I2C_MASTER_WRITE, ACK_CHECK_EN);
//  i2c_master_write(cmd, buf, num, ACK_CHECK_EN);
//  i2c_master_stop(cmd);
//  esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
//  i2c_cmd_link_delete(cmd);
//}









void SMTA_AMG88xx::_i2c_init()
{
  Wire.begin();
}

void SMTA_AMG88xx::read(uint8_t reg, uint8_t *buf, uint8_t num)
{
  uint8_t value;
  uint8_t pos = 0;
  
  //on arduino we need to read in 32 byte chunks
  while(pos < num){
    
    uint8_t read_now = min(32, num - pos);
    Wire.beginTransmission((uint8_t)_i2caddr);
    Wire.write((uint8_t)reg + pos);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)_i2caddr, read_now);
    
    for(int i=0; i<read_now; i++){
      buf[pos] = Wire.read();
      pos++;
    }
  }
}

void SMTA_AMG88xx::write(uint8_t reg, uint8_t *buf, uint8_t num)
{
  Wire.beginTransmission((uint8_t)_i2caddr);
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t *)buf, num);
  Wire.endTransmission();
}







float SMTA_AMG88xx::signedMag12ToFloat(uint16_t val)
{
	//take first 11 bits as absolute val
	uint16_t absVal = (val & 0x7FF);
	
	return (val & 0x8000) ? 0 - (float)absVal : (float)absVal ;
}
