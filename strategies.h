/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef STRATEGIES
#define	STRATEGIES

#include <xc.h> 
#include "smctl.h"
#define DELAY_TIME 5000 
typedef enum possible_states{LISTENING, WAITING, SEARCHING, RUNNING, ATTACKING} State;

State state = LISTENING;

void delayTMR1(int tms);
void waitingRoutine(unsigned char delay_type);
void searchRoutine(unsigned char * fmove, unsigned char * fatk, unsigned char * stdstg, State state);
void attackRoutine(State state);
void saveYourselfRoutine(State state);
void getFirstMove(unsigned char * fmove);
void getFirstAttack(unsigned char * fatk);
void getStrategy(unsigned char * stdstg);
void rotate(int side);
void arch(int side, int direction, int speed);
State getState(int line, int target, State state);

#endif	

