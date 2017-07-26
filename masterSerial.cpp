#include "Serial.h"
#include <stdio.h>

void sendData(uint8_t command, uint8_t data){
        int i;
        int j;
        uint8_t controlByte;
        uint8_t byteToSend;
        gpioWrite(27,1); //start
        delayMicroseconds(75);
        for(j = 0; j < 2; j++) {

                delayMicroseconds(50);
                gpioWrite(27,1);
                // printf("on\n");
                delayMicroseconds(100);
                gpioWrite(27,0);
                delayMicroseconds(75);

                if(j == 0) {
                        // Command
                        controlByte = 1;
                        byteToSend = command;
                }
                if(j == 1) {
                        // Data
                        controlByte = 0;
                        byteToSend = data;
                }

                for(i = 3; i >=0; i--) {

                        gpioWrite(27,(byteToSend & ( 1 << ((i*2) + 1))) >> ((i*2)+1));//data
                        delayMicroseconds(75);
                        gpioWrite(27,(byteToSend & ( 1 << (i*2))) >> (i*2)); // data
                        delayMicroseconds(75);

                }

                gpioWrite(27,0);


        }

}
