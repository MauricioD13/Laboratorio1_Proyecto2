
#include <PIC16F1827.h>
#define LED_A PORTAbits.RA2
#define LED_B PORTAbits.RA3
#define LED_C PORTBbits.RB4
#define LED_D PORTAbits.RA6
#define LED_E PORTAbits.RA7
#define LED_F PORTAbits.RA1
#define LED_G PORTAbits.RA0
void zero(){
    LED_A = 1;
    LED_B = 1;
    LED_C = 1;
    LED_D = 1;
    LED_E = 1;
    LED_F = 1;
    LED_G = 0;
}
void one(){
    LED_A = 0;
    LED_B = 1;
    LED_C = 1;
    LED_D = 0;
    LED_E = 0;
    LED_F = 0;
    LED_G = 0;
}
void two(){
    LED_A = 1;
    LED_B = 1;
    LED_C = 0;
    LED_D = 1;
    LED_E = 1;
    LED_F = 0;
    LED_G = 1;
    
    
}
void three() {
    LED_A = 1;
    LED_B = 1;
    LED_C = 1;
    LED_D = 1;
    LED_E = 0;
    LED_F = 0;
    LED_G = 1;
}
void four(){
    LED_A = 0;
    LED_B = 1;
    LED_C = 1;
    LED_D = 0;
    LED_E = 0;
    LED_F = 1;
    LED_G = 1;
}
void five(){
    LED_A = 1;
    LED_B = 0;
    LED_C = 1;
    LED_D = 1;
    LED_E = 0;
    LED_F = 1;
    LED_G = 1;
}

void six(){
    LED_A = 1;
    LED_B = 0;
    LED_C = 1;
    LED_D = 1;
    LED_E = 1;
    LED_F = 1;
    LED_G = 1;
}

void seven(){
    LED_A = 1;
    LED_B = 1;
    LED_C = 1;
    LED_D = 0;
    LED_E = 0;
    LED_F = 0;
    LED_G = 0;
}

void eight(){
    LED_A = 1;
    LED_B = 1;
    LED_C = 1;
    LED_D = 1;
    LED_E = 1;
    LED_F = 1;
    LED_G = 1;
}
void nine(){
    LED_A = 1;
    LED_B = 1;
    LED_C = 1;
    LED_D = 1;
    LED_E = 0;
    LED_F = 1;
    LED_G = 1;
}



void show_number(int result){
    //for(int i=0;i<3;i++){
    
    int i=0;
        if(result==1){
          one(); 
        }
        else if(result==2){
          two(); 
        }
        else if(result==3){
          three(); 
        }
        else if(result==4){
          four(); 
        }
        else if(result==5){
          five(); 
        }
        else if(result==6){
          six(); 
        }
        else if(result==7){
          seven(); 
        }
        else if(result==8){
          eight(); 
        }
        else if(result==9){
          nine(); 
        }
        else if(result==0){
          zero(); 
        }
    //}    
}