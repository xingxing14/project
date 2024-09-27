#ifndef   _SERVO_H_
#define   _SERVO_H_

#include "tim.h"

void pwm_start(void);

void translate_angle_to_pulse(double angle_1,double angle_2,double angle_3,double angle_4,double angle_5,double angle_6);

void pwm_out(double angle_1, double angle_2, double angle_3, double angle_4, double angle_5,  double angle_6);

void servo_catch(double servo_target_angle_1,double servo_target_angle_2,double servo_target_angle_3,double servo_target_angle_4);

void servo_test(void);

void servo_reset_begin(void);

void servo_reset(void);

void servo_release(void);

void servo_control(double target_angle_1, double target_angle_2, double target_angle_3, double target_angle_4, double target_angle_5,  double target_angle_6);

void servo_angle_calculate(float target_x, float target_y, float target_z);


void servo_lift(void);

void servo_lift_return(void);

void servo_transfer(void);


