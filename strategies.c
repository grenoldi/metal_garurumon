#include <xc.h>
#include "strategies.h"

 void delayTMR1(int tms){
    T1CON = 0b10000000;
    for (int i = 0; i < tms; i++){
        TMR1 = 60537;
        T1CONbits.TMR1ON = 1;
        while(PIR1bits.TMR1IF == 0);
        T1CONbits.TMR1ON = 0;
        PIR1bits.TMR1IF  = 0;
        readTarget();
        if(target != 0 && line == 0){
            state = ATTACKING;
            INTCONbits.TMR0IE = 1;
            break;
        }
    }
}

void waitingRoutine(unsigned char delay_type){
    if(delay_type =='a'){
        __delay_ms(DELAY_TIME);
        state = SEARCHING;
    }
    else if(delay_type =='b'){
        delayTMR1(DELAY_TIME);
        state = SEARCHING;
    }
}

void searchRoutine(unsigned char * fmove, unsigned char * fatk, unsigned char * stdstg, State state){
    getFirstMove(fmove);
    getFirstAttack(fatk);
    getStrategy(stdstg);
}

/*
 //sensor positioning (target):
  ______front______
 |3       2       1|
 |                 |
 |4               0|
 |                 |
 |                 |
 |        5        |
 
 */

void attackRoutine(State state){
    readTarget();
    switch(target){
        case  1:
            moveMotor(right, backward, 100);
            moveMotor(left, forward, 100);
            __delay_ms(100);
            stopMotors();
            break;
        case  2:
            moveMotor(right, backward, 100);
            moveMotor(left, forward, 100);
            break;
        case  3:
            moveMotor(right, backward, 100);
            moveMotor(left, forward, 100);
            break;
        case  4:
            moveMotor(right, forward, 100);
            moveMotor(left, forward, 100);
            break;
        case  6:
            moveMotor(right, forward, 100);
            moveMotor(left, forward, 100);
            break;
        case  8: 
            moveMotor(right, forward, 100);
            moveMotor(left, backward, 100);
            break;
        case 10: 
            moveMotor(right, forward, 100);
            moveMotor(left, forward, 100);
            break;
        case 12: 
            moveMotor(right, forward, 100);
            moveMotor(left, forward, 100);
            break;
        case 14: 
            moveMotor(right, forward, 100);
            moveMotor(left, forward, 100);
            break;
        case 16: 
            moveMotor(right, forward, 100);
            moveMotor(left, backward, 100);
            __delay_ms(100);
            stopMotors();
            break;
        case 24: 
            moveMotor(right, forward, 100);
            moveMotor(left, backward, 100);
            break;
        default: 
            moveMotor(right, forward, 80);
            moveMotor(left,  forward, 80);
            break;
    }
}
/*
 //sensor positioning(line):
  ______front______
 |1               0|
 |                 |
 |                 |
 |                 |
 |                 |
 |2               3|
 
 */
void saveYourselfRoutine(State state){
    readLine();
    switch(line){
        case 0:
            readTarget();
            if(target) state = ATTACKING;
            else       state = SEARCHING;
            break;
        case  1:
            stopMotors();
            arch(left, backward, 50);
            rotate(left);
            delay_ms(100);
            break;
        case  2:
            arch(right, backward, 50);
            break;
        case  3:
            moveMotor(left,  backward, 50);
            moveMotor(right, backward, 50);
            break;
        case  4: 
            arch(right, forward, 50);
            break;
        case  5:
            arch(left, forward, 50);
            break;
        case  6:
            arch(right, forward, 50);
            break;
        //case  7: break; //pouco provavel
        case  8:
            arch(left, forward, 50);
            break;
        case  9:
            arch(left, forward, 50);
            break;
        case 10:
            arch(right, forward, 50);
            break;
        //case 11: break; //pouco provavel
        case 12:
            moveMotor(left,  forward, 50);
            moveMotor(right, forward, 50);
            break;
        //case 13: break; //pouco provavel
        //case 14: break; //pouco provavel
        //case 15: break; //quase impossivel!
    }
}

void getFirstMove(unsigned char * fmove){
    
    if((*fmove) == 'a');
    
    else if      ((*fmove) == 'b') {
        rotate(right);
        delayTMR1(100);
        stopMotors();
    }
    
    else if ((*fmove) == 'c') {
        rotate(left);
        delayTMR1(100);
        stopMotors();
    }
    
    else if ((*fmove) == 'd') {
        arch(right, backward, 100);
    }
    
    else if ((*fmove) == 'e') {
        arch(left, backward, 100);
    }
    
    else if ((*fmove) == 'f') {
        moveMotor(right, backward, 50);
        moveMotor(left,  backward, 50);
    }
    
    (*fmove) = 'a';
}

void getFirstAttack(unsigned char * fatk){
    if ((*fatk) == 'a');
    
    else if((*fatk) == 'b'){
        arch(right, forward, 100);
    }
    
    else if((*fatk) == 'c'){
        arch(left, forward, 100);
    }
    
    (*fatk) = 'a';
}

void getStrategy(unsigned char * stdstg){
    if ((*stdstg) == 'a'){
        moveMotor(right, forward, 80);
        moveMotor(left,  forward, 80);
    }
    
    else if ((*stdstg) == 'b'){
        rotate(right);
    }
    
    else if ((*stdstg) == 'c'){
        rotate(left);
    }
    
    else if((*stdstg) == 'd'){
        moveMotor(right, forward, 30);
        moveMotor(left,  forward, 30);
    }
    
    else if((*stdstg) == 'e'){
        //TODO: pica pau
    }
}

void rotate(int side){
    if(side){
        moveMotor(right, backward, 100);
        moveMotor(left,   forward, 100);
    }
    
    else{
        moveMotor(right, forward, 100);
        moveMotor(left, backward, 100);
    }
}

void arch(int side, int direction, int speed){
    if(side){
        if(direction){
            moveMotor(right,  forward, speed - 10);
            moveMotor(left,   forward, speed + 10);
        }
        
        else{
            moveMotor(right,  backward, speed - 10);
            moveMotor(left,   backward, speed + 10);
        }
    }
    
    else {
        if(direction){
            moveMotor(right,  forward, speed + 10);
            moveMotor(left,   forward, speed - 10);
        }
        
        else{
            moveMotor(right,  backward, speed + 10);
            moveMotor(left,   backward, speed - 10);
        }
    }
}

State getState(int line, int target, State state){
    if(state == LISTENING) return LISTENING;
    if(line != 0)          return RUNNING;
    else if(target != 0)   return ATTACKING;
    else                   return SEARCHING;
}
