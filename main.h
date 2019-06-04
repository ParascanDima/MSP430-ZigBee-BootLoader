/*
 * main.h
 *
 *  Created on: May 15, 2019
 *      Author: dumitru
 */

#ifndef MAIN_H_
#define MAIN_H_

#define TASK(TASK_NAME)   void TASK_NAME(void)

void GlobalInterruptsDisnable(void);
void GlobalInterruptsEnable(void);
extern void MainPlatformInit(void);
extern TASK(Main_10ms);

#endif /* MAIN_H_ */
