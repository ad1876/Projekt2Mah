/*
 * Rotate.h
 *
 * Created: 2017-05-04 14:58:31
 *  Author: André Ahlbertz
 */


#ifndef ROTATE_H_
#define ROTATE_H_

void rotate(int d);
void initRotateMotor(void);
void updateDirection(int new_rotation);
void startupMeasure1(uint16_t x1,uint16_t x2);
void startupMeasure2(uint16_t x1,uint16_t x2);

#endif /* INCFILE1_H_ */