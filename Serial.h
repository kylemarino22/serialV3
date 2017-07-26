#ifndef Serial_h_
#define Serial_h_
extern int commandRecieved;
extern int dataRecieved;
extern short rawData[18];
void beginSerial();
void recieveSerial();
#endif
