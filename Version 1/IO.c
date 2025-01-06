#include <LPC21xx.h> // Include LPC2129 header file

 main(){
    IODIR0 = 0x01;    

    while (1) {
        IOSET0 = 0x01; 
        for (int i = 0; i < 100000; i++); 

        IOCLR0 = 0x01; 
        for (int i = 0; i < 100000; i++);
    }
}
