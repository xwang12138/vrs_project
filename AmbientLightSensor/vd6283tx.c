#include "vd6283tx.h"

uint8_t addres = VD6283TX_SLAVE_ADDR;

uint8_t vd6283tx_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres, 0));
}

void vd6283tx_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres, 0);
}

void vd6283tx_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres, 0);
}

uint8_t vd6283tx_init(void)
{
	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t val = vd6283tx_read_byte(VD6283TX_DEVICE_ID);

	if(val == VD6283TX_DEVICE_ID_VALUE)
	{
		status = 1;
	}
	else
	{
		status = 0;
		//return status;
	}
	vd6283tx_ctrl_reg_reset();
	LL_mDelay(10);
	vd6283tx_ctrl_reg_init(0x07, 0x01);
	LL_mDelay(10);
	vd6283tx_set_als_gain();
	LL_mDelay(10);
	vd6283tx_set_als_exposure();
	LL_mDelay(10);
	vd6283tx_set_gpio1();
	LL_mDelay(10);
	vd6283tx_sda_config();
	LL_mDelay(10);
	vd6283tx_als_channel_enable();
	LL_mDelay(10);
	vd6283tx_als_channel6_enable();
	LL_mDelay(10);

	return status;
}

uint8_t vd6283tx_de_init(void)
{
	vd6283tx_ctrl_reg_init(0x00,0x00);

	return 1;
}

uint8_t vd6283tx_silicon_init(void)
{
	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t val = vd6283tx_read_byte(VD6283TX_REVISION_ID);

	if(val == VD6283TX_REVISION_ID_VALUE)
	{
		status = 1;
	}
	else
	{
		status = 0;
		//return status;
	}

	vd6283tx_ctrl_reg_init(0x07,0x01);
	vd6283tx_set_als_gain();
	vd6283tx_als_channel_enable();

	return status;
}

uint8_t vd6283tx_get_interrupt(void)
{
	volatile uint8_t interrupt_val = vd6283tx_read_byte(VD6283TX_INTERRUPT_CTRL);
	return interrupt_val;
}

void vd6283tx_clear_interrupt(void)
{
	volatile uint8_t flag = 0x01;
	vd6283tx_write_byte(VD6283TX_INTERRUPT_CTRL,flag);
	LL_mDelay(100);
	flag &= ~0x01;
	vd6283tx_write_byte(VD6283TX_INTERRUPT_CTRL,flag);
}

void vd6283tx_set_gpio1(void)
{
	volatile uint8_t config = vd6283tx_read_byte(VD6283TX_GPIO1_DRV_CFG);
	config &= ~0x02;
	config |= 0x01;
	vd6283tx_write_byte(VD6283TX_GPIO1_DRV_CFG,config);
}

void vd6283tx_sda_config(void)
{
	volatile uint8_t config = vd6283tx_read_byte(VD6283TX_SDA_DRV_CFG);
	config &= ~0x0F;
	config |= 0x09;
	vd6283tx_write_byte(VD6283TX_SDA_DRV_CFG,config);
}

void vd6283tx_ctrl_reg_init(uint8_t config, uint8_t period)
{
	volatile uint8_t als_ctrl = vd6283tx_read_byte(VD6283TX_ALS_CTRL);
	als_ctrl &= ~0x07;
	als_ctrl |= config;

	vd6283tx_write_byte(VD6283TX_ALS_CTRL,als_ctrl);

	LL_mDelay(100);

	volatile uint8_t als_period = vd6283tx_read_byte(VD6283TX_ALS_PERIOD);
	als_period &= ~0xFC;
	als_period |= period;

	vd6283tx_write_byte(VD6283TX_ALS_PERIOD,als_period);
}

void vd6283tx_ctrl_reg_reset(void)
{
	volatile uint8_t als_ctrl = vd6283tx_read_byte(VD6283TX_ALS_CTRL);
	als_ctrl &= ~0x07;
	als_ctrl |= 0x00;

	LL_mDelay(100);
	vd6283tx_write_byte(VD6283TX_ALS_CTRL,als_ctrl);
	LL_mDelay(100);
}

void vd6283tx_set_als_gain(void)
{
	volatile uint8_t als_ch1_gain = vd6283tx_read_byte(VD6283TX_ALS_GAIN_CH1);
	als_ch1_gain &= ~0x0F;
	als_ch1_gain |= 0x0D;
	vd6283tx_write_byte(VD6283TX_ALS_GAIN_CH1,als_ch1_gain);

	LL_mDelay(100);

	volatile uint8_t als_ch2_gain = vd6283tx_read_byte(VD6283TX_ALS_GAIN_CH2);
	als_ch2_gain &= ~0x0F;
	als_ch2_gain |= 0x0D;
	vd6283tx_write_byte(VD6283TX_ALS_GAIN_CH2,als_ch2_gain);

	LL_mDelay(100);

	volatile uint8_t als_ch3_gain = vd6283tx_read_byte(VD6283TX_ALS_GAIN_CH3);
	als_ch3_gain &= ~0x0F;
	als_ch3_gain |= 0x0D;
	vd6283tx_write_byte(VD6283TX_ALS_GAIN_CH3,als_ch3_gain);

	LL_mDelay(100);

	volatile uint8_t als_ch4_gain = vd6283tx_read_byte(VD6283TX_ALS_GAIN_CH4);
	als_ch4_gain &= ~0x0F;
	als_ch4_gain |= 0x0D;
	vd6283tx_write_byte(VD6283TX_ALS_GAIN_CH4,als_ch4_gain);

	LL_mDelay(100);

	volatile uint8_t als_ch5_gain = vd6283tx_read_byte(VD6283TX_ALS_GAIN_CH5);
	als_ch5_gain &= ~0x0F;
	als_ch5_gain |= 0x0D;
	vd6283tx_write_byte(VD6283TX_ALS_GAIN_CH5,als_ch5_gain);

	LL_mDelay(100);

	volatile uint8_t als_ch6_gain = vd6283tx_read_byte(VD6283TX_ALS_GAIN_CH6);
	als_ch6_gain &= ~0x0F;
	als_ch6_gain |= 0x0D;
	vd6283tx_write_byte(VD6283TX_ALS_GAIN_CH6,als_ch6_gain);

	LL_mDelay(100);

}

void vd6283tx_set_als_exposure(void)
{
	volatile uint8_t als_exposure_L = vd6283tx_read_byte(VD6283TX_ALS_EXPOSURE_L);
	als_exposure_L &= ~0x03;
	als_exposure_L |= 0x01;
	vd6283tx_write_byte(VD6283TX_ALS_EXPOSURE_L,als_exposure_L);

	LL_mDelay(100);

	volatile uint8_t als_exposure_M = vd6283tx_read_byte(VD6283TX_ALS_EXPOSURE_M);
	als_exposure_M &= ~0xFC;
	als_exposure_M |= 0xFC;
	vd6283tx_write_byte(VD6283TX_ALS_EXPOSURE_M,als_exposure_M);
}

void vd6283tx_als_channel_enable(void)
{
	volatile uint8_t als_enable = vd6283tx_read_byte(VD6283TX_ALS_CHANNEL_ENABLE);
	als_enable &= ~0x1F;
	als_enable |= 0x1F;
	vd6283tx_write_byte(VD6283TX_ALS_CHANNEL_ENABLE,als_enable);
}

void vd6283tx_als_channel6_enable(void)
{
	volatile uint8_t als_enable = vd6283tx_read_byte(VD6283TX_ALS_CHANNEL6_ENABLE);
	als_enable &= ~0x01;
	als_enable |= 0x01;
	LL_mDelay(100);
	vd6283tx_write_byte(VD6283TX_ALS_CHANNEL6_ENABLE,als_enable);
}

void vd6283tx_calculate_cct(int chRed, int chGreen, int chBlue, double *returnData)
{
	// inputs: channel 1; channel 4; channel 3
	//                        R         G       B
	static const float cX[] = {0.20557, 0.4167,-0.14382};
	static const float cY[] = {-0.02875, 0.506372, -0.12061};
	static const float cZ[] = {-0.55263, 0.335866, 0.494781};

	float data[3], tempX = 0, tempY = 0, tempZ = 0, x = 0, y = 0, denum = 1, n = 1;
	double cct = 0;
	float exposure_time = vd6283tx_get_als_exposure();
	if(exposure_time > 0)
		exposure_time = 0.1008/exposure_time;
	data[0] = (float)chRed/256.0;
	data[1] = (float)chGreen/256.0;
	data[2] = (float)chBlue/256.0;
	for(int i = 0; i < 3; i++)
	{
		tempX += data[i]*cX[i];
		tempY += data[i]*cY[i]; // LUX
		tempZ += data[i]*cZ[i];
	}
	denum = tempX + tempY + tempZ;
	if(denum != 0)
	{
		x = tempX/denum;
		y = tempY/denum;
	}
	n = (x-0.3320)/(0.1858-y);
	cct = (437*(n*n*n))+(3601*(n*n))+(6861*n)+5517;
	if(cct > 25000)
		cct = 25000;
	if(cct < 0)
		cct = 0;
	returnData[0] = tempY * exposure_time;
	returnData[1] = cct;
	returnData[2] = x;
    returnData[3] = y;
}

int vd6283tx_get_als_ch1()
{
	volatile uint8_t ALS_CH1_DATA_H = vd6283tx_read_byte(VD6283TX_ALS_CH1_DATA_H);
	volatile uint8_t ALS_CH1_DATA_M = vd6283tx_read_byte(VD6283TX_ALS_CH1_DATA_M);
	volatile uint8_t ALS_CH1_DATA_L = vd6283tx_read_byte(VD6283TX_ALS_CH1_DATA_L);
	volatile int32_t ALS_CH1_DATA = ALS_CH1_DATA_H << 16 | ALS_CH1_DATA_M << 8 | ALS_CH1_DATA_L;
	return (int) ALS_CH1_DATA;
}

int vd6283tx_get_als_ch2()
{
	volatile uint8_t ALS_CH2_DATA_H = vd6283tx_read_byte(VD6283TX_ALS_CH2_DATA_H);
	volatile uint8_t ALS_CH2_DATA_M = vd6283tx_read_byte(VD6283TX_ALS_CH2_DATA_M);
	volatile uint8_t ALS_CH2_DATA_L = vd6283tx_read_byte(VD6283TX_ALS_CH2_DATA_L);
	volatile int32_t ALS_CH2_DATA = ALS_CH2_DATA_H << 16 | ALS_CH2_DATA_M << 8 | ALS_CH2_DATA_L;
	return (int) ALS_CH2_DATA;
}

int vd6283tx_get_als_ch3()
{
	volatile uint8_t ALS_CH3_DATA_H = vd6283tx_read_byte(VD6283TX_ALS_CH3_DATA_H);
	volatile uint8_t ALS_CH3_DATA_M = vd6283tx_read_byte(VD6283TX_ALS_CH3_DATA_M);
	volatile uint8_t ALS_CH3_DATA_L = vd6283tx_read_byte(VD6283TX_ALS_CH3_DATA_L);
	volatile int32_t ALS_CH3_DATA = ALS_CH3_DATA_H << 16 | ALS_CH3_DATA_M << 8 | ALS_CH3_DATA_L;
	return (int) ALS_CH3_DATA;
}

int vd6283tx_get_als_ch4()
{
	volatile uint8_t ALS_CH4_DATA_H = vd6283tx_read_byte(VD6283TX_ALS_CH4_DATA_H);
	volatile uint8_t ALS_CH4_DATA_M = vd6283tx_read_byte(VD6283TX_ALS_CH4_DATA_M);
	volatile uint8_t ALS_CH4_DATA_L = vd6283tx_read_byte(VD6283TX_ALS_CH4_DATA_L);
	volatile int32_t ALS_CH4_DATA = ALS_CH4_DATA_H << 16 | ALS_CH4_DATA_M << 8 | ALS_CH4_DATA_L;
	return (int) ALS_CH4_DATA;
}

int vd6283tx_get_als_ch5()
{
	volatile uint8_t ALS_CH5_DATA_H = vd6283tx_read_byte(VD6283TX_ALS_CH5_DATA_H);
	volatile uint8_t ALS_CH5_DATA_M = vd6283tx_read_byte(VD6283TX_ALS_CH5_DATA_M);
	volatile uint8_t ALS_CH5_DATA_L = vd6283tx_read_byte(VD6283TX_ALS_CH5_DATA_L);
	volatile int32_t ALS_CH5_DATA = ALS_CH5_DATA_H << 16 | ALS_CH5_DATA_M << 8 | ALS_CH5_DATA_L;
	return (int) ALS_CH5_DATA;
}

int vd6283tx_get_als_ch6()
{
	volatile uint8_t ALS_CH6_DATA_H = vd6283tx_read_byte(VD6283TX_ALS_CH6_DATA_H);
	volatile uint8_t ALS_CH6_DATA_M = vd6283tx_read_byte(VD6283TX_ALS_CH6_DATA_M);
	volatile uint8_t ALS_CH6_DATA_L = vd6283tx_read_byte(VD6283TX_ALS_CH6_DATA_L);
	volatile int32_t ALS_CH6_DATA = ALS_CH6_DATA_H << 16 | ALS_CH6_DATA_M << 8 | ALS_CH6_DATA_L;
	return (int) ALS_CH6_DATA;
}

float vd6283tx_get_als_exposure(void)
{
	volatile uint8_t als_exposure_L = vd6283tx_read_byte(VD6283TX_ALS_EXPOSURE_L);
	volatile uint8_t als_exposure_M = vd6283tx_read_byte(VD6283TX_ALS_EXPOSURE_M);
	als_exposure_M &= ~0xFC;
	volatile uint16_t exposure_time = als_exposure_M << 2 | als_exposure_L;
	return (float) (exposure_time+1)*(16384.0/10240000.0);
}

void VD6283_INTRHandler(void)
{

}
