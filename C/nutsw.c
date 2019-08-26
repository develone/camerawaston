#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

//T9	BCM24
#  define PIN_SW 5 //BCM24 	PIN 18, GPIO.5, IOB_79	T9
// For reference, here are four valuable definitions found within wiringPi.h
//
// #define	LOW	0
// #define	HIGH	1
// #define	INPUT	0
// #define	OUTPUT	1
#  define PIN_SW 5 //BCM24 	PIN 18, GPIO.5, IOB_79	T9
void main() {
	char	ir_sw = 0;
	int flag = 1;
	
	wiringPiSetup();
	pinMode(PIN_SW, INPUT);
	while (flag == 1) {
		if (digitalRead(PIN_SW)) {
			ir_sw |= 0x1;
			printf("ir_sw= 0x%x no nut\n",ir_sw);
			printf("\n");
		}	
		else {
			ir_sw = 0x0;
			printf("ir_sw= 0x%x nut coming\n",ir_sw);
		}
	} //end endless loop
		
}
