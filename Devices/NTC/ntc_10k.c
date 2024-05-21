#define F_CPU 16000000

#include <math.h>

#include "AD.h"
#include "ntc_10k.h"

#define _NTC_R_SERIES         10000.0f
#define _NTC_R_NOMINAL        10000.0f
#define _NTC_TEMP_NOMINAL     25.0f
#define _NTC_ADC_MAX          1024 //  
#define _NTC_BETA             3950


uint16_t get_temperature(uint8_t channel)
{
	uint16_t	ADCVal  = adc_read(channel);
	return ntc_convertToC_10times(ADCVal);
}

float ntc_convertToC(uint16_t adcValue)
{
	float rntc = (((double)_NTC_R_SERIES * 5  / (3.3 * adcValue)) * (double)_NTC_ADC_MAX) - 10000;
	
	float temp;
	temp = rntc / (float)_NTC_R_NOMINAL;
	temp = logf(temp);
	temp /= (float)_NTC_BETA;
	temp += 1.0f / ((float)_NTC_TEMP_NOMINAL + 273.15f);
	temp = 1.0f / temp;
	temp -= 273.15f;
	return temp;
}

uint16_t	ntc_convertToC_10times(uint16_t adcValue)
{
	return	10*ntc_convertToC(adcValue);
}