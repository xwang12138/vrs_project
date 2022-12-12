#include "main.h"
#include "i2c.h"


#define VD6283TX_DEVICE_ID 				0x00
#define VD6283TX_DEVICE_ID_VALUE 		0x70
#define VD6283TX_SLAVE_ADDR 			0x40
#define VD6283TX_REVISION_ID 			0x01
#define VD6283TX_REVISION_ID_VALUE 		0xBD
#define VD6283TX_INTERRUPT_CTRL 		0x02
#define VD6283TX_ALS_CTRL		 		0x03
#define VD6283TX_ALS_PERIOD		 		0x04
#define VD6283TX_ALS_CH1_DATA_H		 	0x06
#define VD6283TX_ALS_CH1_DATA_M		 	0x07
#define VD6283TX_ALS_CH1_DATA_L		 	0x08
#define VD6283TX_ALS_CH2_DATA_H		 	0x0A
#define VD6283TX_ALS_CH2_DATA_M		 	0x0B
#define VD6283TX_ALS_CH2_DATA_L		 	0x0C
#define VD6283TX_ALS_CH3_DATA_H		 	0x0E
#define VD6283TX_ALS_CH3_DATA_M		 	0x0F
#define VD6283TX_ALS_CH3_DATA_L		 	0x10
#define VD6283TX_ALS_CH4_DATA_H		 	0x12
#define VD6283TX_ALS_CH4_DATA_M		 	0x13
#define VD6283TX_ALS_CH4_DATA_L		 	0x14
#define VD6283TX_ALS_CH5_DATA_H		 	0x16
#define VD6283TX_ALS_CH5_DATA_M		 	0x17
#define VD6283TX_ALS_CH5_DATA_L		 	0x18
#define VD6283TX_ALS_CH6_DATA_H		 	0x1A
#define VD6283TX_ALS_CH6_DATA_M		 	0x1B
#define VD6283TX_ALS_CH6_DATA_L		 	0x1C
#define VD6283TX_ALS_EXPOSURE_M		 	0x1D
#define VD6283TX_ALS_EXPOSURE_L		 	0x1E
#define VD6283TX_ALS_GAIN_CH1		 	0x25
#define VD6283TX_ALS_GAIN_CH2		 	0x26
#define VD6283TX_ALS_GAIN_CH3		 	0x27
#define VD6283TX_ALS_GAIN_CH4		 	0x28
#define VD6283TX_ALS_GAIN_CH5		 	0x29
#define VD6283TX_ALS_GAIN_CH6		 	0x2A
#define VD6283TX_ALS_CHANNEL6_ENABLE	0x2D
#define VD6283TX_ALS_CHANNEL_ENABLE		0x2E
#define VD6283TX_AC_MODE_CTRL			0x31
#define VD6283TX_PEDESTAL_VALUE			0x32
#define VD6283TX_SDA_DRV_CFG			0x3C
#define VD6283TX_GPIO1_DRV_CFG			0x41

uint8_t vd6283tx_init(void);
uint8_t vd6283tx_de_init(void);
uint8_t vd6283tx_silicon_init(void);
uint8_t vd6283tx_read_byte(uint8_t reg_addr);
uint8_t vd6283tx_get_interrupt(void);
void vd6283tx_write_byte(uint8_t reg_addr, uint8_t value);
void vd6283tx_readArray(uint8_t * data, uint8_t reg, uint8_t length);
void VD6283_INTRHandler(void);
void vd6283tx_ctrl_reg_init(uint8_t config, uint8_t period);
void vd6283tx_ctrl_reg_reset(void);
void vd6283tx_set_als_gain(void);
void vd6283tx_set_als_exposure(void);
void vd6283tx_set_gpio1(void);
void vd6283tx_als_channel_enable(void);
void vd6283tx_als_channel6_enable(void);
void vd6283tx_clear_interrupt(void);
void vd6283tx_sda_config(void);
void vd6283tx_calculate_cct(int chRed, int chGreen, int chBlue, double *returnData);
int vd6283tx_get_als_ch1();
int vd6283tx_get_als_ch2();
int vd6283tx_get_als_ch3();
int vd6283tx_get_als_ch4();
int vd6283tx_get_als_ch5();
int vd6283tx_get_als_ch6();
float vd6283tx_get_als_exposure(void);
