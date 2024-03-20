/**
 * @file bldc.h
 * @brief BLDC Motor Driver
 * @author Michael Burmeister
 * @date October 30, 2023
 * @version 1.0
 * 
*/

#ifndef __BLDC_H
#define __BLDC_H


/**
 * @brief Initialize BLDC Motor Driver.
 * @param left_pins starting pin for driver
 * @param right_pins starting pin for driver
 * @returns int value
 */
int BLDC_Init(int left_pins, int right_pins) __fromfile("libbldc/bldc.c");

/**
 * @brief Hall Sense values
 * @param left left hall value
 * @param right right hall value
 */
void BLDC_Hall(int left, int right);

/**
 * @brief Step
 * @param forward step direction 1/-1
 */
void BLDC_Step(int forward);

/**
 * @brief Stop
 * 
 */
void BLDC_Stop(void);

/**
 * @brief Get Step
 * @return step
 */
int BLDC_StepValue(void);

/**
 * @brief Enable
 * @return step value
 */
int BLDC_Enable(void);

/**
 * @brief Move
 * @param left enable move 0/1
 * @param right enable move 0/1
 */
void BLDC_Move(int left, int right);

/**
 * @brief Set total ticks
 * @param left count
 * @param right count
 */
void BLDC_Ticks(int left, int right);

/**
 * @brief Get tick count
 * @param left tick count
 * @param right tick count
 */
void BLDC_GetTicks(int left, int right);

/**
 * @brief Set motor direction
 * @param left motor 0 - forward 1 - backwards
 * @param right motor 0 - forward 1 - backwards
 */
void BLDC_SetDirection(int left, int right);

/**
 * @brief Set motor speed
 * @param left speed value 10 - 40
 * @param right speed value 10 - 40
 */
void BLDC_SetSpeed(int left, int right);

/**
 * @brief Status of move
 * @return status  0 - move done 1 - still moving
 */
int BLDC_Status(void);


#endif
