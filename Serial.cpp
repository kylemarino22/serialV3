#include "Serial.h"
#include <Arduino.h>

int timer;
short input;
int command;
short rawData[18];
int dataRecieved;
int commandRecieved;
long elapsedTime = 1170;
int delayTime = 100;

void beginSerial(){

        DDRB |= B00000100;
}

void recieveSerial(){
        int i;
        bool sync = false;
        PORTB = B00000100;
        Serial.println("New Request");
        while((PINB & B00000010) == 0) ;
        PORTB = B00000000;

        //long timer = micros();

        //Serial.println("on");
        while((PINB & B00000010) == 2) ;
        delayMicroseconds(20);

        for(i = 0; i < 19; i++) {
                if(i == 9 && sync == false) {
                        delayMicroseconds(delayTime);
                        Serial.println((PINB & B00000010));
                        while((PINB & B00000010) == 2) ;
                        //elapsedTime = micros() - timer;
                        delayMicroseconds(15);
                        //Serial.print("\t");
                        sync = true;
                        i--;
                        continue;
                }
                if(i == 0) ;
                else if(PINB & B00000010) {
                        //Serial.print("1");
                        //delayMicroseconds(50);
                        rawData[i - 1] = 1;
                }
                else{
                        //Serial.print("0");
                        //delayMicroseconds(50);
                        rawData[i - 1] = 0;

                }
                delayMicroseconds(delayTime);
        }
        sync = false;
        // Serial.println();
        short tempShifter = 0;
        for(i = 0; i < 8; i++) {
                Serial.print(rawData[i]);
                tempShifter = tempShifter << 1;
                if(rawData[i] == 1) {
                        tempShifter +=1;
                }
        }
        // Serial.print("\t");
        commandRecieved = tempShifter;
        tempShifter = 0;
        for(i = 9; i < 17; i++) {
                Serial.print(rawData[i]);
                tempShifter = tempShifter << 1;
                if(rawData[i] == 1) {
                        tempShifter +=1;
                }
        }
        dataRecieved = tempShifter;
        // Serial.println();
        // Serial.println(dataRecieved);
        // Serial.println(elapsedTime);
        delayTime = (elapsedTime - 500) / 9;

}
