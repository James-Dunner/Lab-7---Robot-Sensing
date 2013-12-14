/*
 * robot_motion.h
 *
 *  Created on: Dec 9, 2013
 *      Author: C14James.Dunn
 */

#define LEFT_THRESHOLD	0x2FF
#define RIGHT_THRESHOLD 0x3FE
#define FRONT_THRESHOLD	0x2FF
#define TRUE	1
#define FALSE	0

#ifndef SENSOR_H_
#define SENSOR_H_

unsigned int getLeftSensor(void);

unsigned int getFrontSensor(void);

unsigned int getRightSensor(void);

char wallFrontDetected(void);

char wallLeftDetected(void);

char wallRightDetected(void);

#endif /* SENSOR_H_ */
