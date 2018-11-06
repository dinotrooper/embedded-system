/*
 * he_pid.c
 *
 *  Created on: Nov 3, 2018
 *      Author: chaise
 */

#include "he_pid.h"

/**
 * @brief PID Function for HE (Heating Element)
 * @param[in] i16_bTemp 	Bean Temperature
 * @param[in] i16_heTemp 	Heating Element Temperature
 * @param[in] i16_tTemp		Target Temperature
 * @param[in] reset			Resets all the internal PID loop values to zero (effectively restarting PID)
 * @retval		0			Cut the Heating element off
 * @retval		non-zero	Cut the Heating element On
 */
uint8_t HE_PID(int16_t i16_bTemp, int16_t i16_tTemp, uint8_t reset) {
	static float f_Error;
	static float f_lastError;
	static float f_Integral;
	static float f_Derivative;
	int16_t i16_PWM;

	/* Calculate Proportional component */
	f_Error = i16_tTemp - i16_bTemp;
	/* Calculate Integral component */
	f_Integral += f_Error;
	/* Calculate Derivative component */
	f_Derivative = f_Error - f_lastError;

	i16_PWM = (Kp * f_Error) + (Ki * f_Integral) + (Kd * f_Derivative);

	if (i16_PWM > 255) i16_PWM = 255;
	if (i16_PWM < 0) i16_PWM = 0;

	return (uint8_t) i16_PWM;
}
