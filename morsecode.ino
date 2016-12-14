#include <avr/pgmspace.h>
#define led 13
#define Dur 100
String Target = "sos ";
void BlinkIntervalCacu(unsigned int Morsecode[], int length){
    int ChSpace = 3;                    //Character space
    int ElementSpace = 1;               //Element Space
    int WdSpace = 7;                    //Word Space
    for(int i = 0 ; i < length ; i++){
        if( Morsecode[i] != 7 ){
            int interval[5] = {
                Morsecode[i]/10000,
                ((Morsecode[i])%10000)/1000,
                ((Morsecode[i])%10000)%1000/100,
                ((Morsecode[i])%10000)%1000%100/10,
                ((Morsecode[i])%10000)%1000%100%10
                };
            for(int j = 0 ; j < 5 ; j++){
                if(interval[j] > 0){
                    Serial.println(interval[j]);
                    BlinkIntervalCacu(interval[j]);
                    delay(Dur*ElementSpace);                    // delay 1 dur time after transfer 1 dot or dash
                }
            }
            delay(Dur*(ChSpace-ElementSpace));                             // delay 2 dur time(total 2+1) after transfer 1 char
        }
        else if(Morsecode[i] == 7){
            delay(Dur*(WdSpace-ChSpace));                     // delay 4 dur time(total 4+3) after transfer 1 word
            }
    }
    //Serial.println("=====");
}

void BlinkIntervalCacu(int interval){
    digitalWrite(led,HIGH);
    delay(Dur*interval);
    Serial.print("LED ON    ");
    Serial.println(Dur*interval);
    digitalWrite(led,LOW);   
}
    
    
const int Array_V[] ={
    13,                 // A Index = 0
    3111,               // B Index = 1
    3131,               // C Index = 2
    311,                // D Index = 3
    1,                  // E Index = 4
    1131,               // F Index = 5
    331,                // G Index = 6
    1111,               // H Index = 7
    11,                 // I Index = 8
    1333,               // J Index = 9
    313,                // K Index = 10
    1311,               // L Index = 11
    33,                 // M Index = 12
    31,                 // N Index = 13
    333,                // O Index = 14
    1331,               // P Index = 15
    3313,               // Q Index = 16
    131,                // R Index = 17
    111,                // S Index = 18
    3,                  // T Index = 19
    113,                // U Index = 20
    1113,               // V Index = 21
    133,                // W Index = 22
    3113,               // X Index = 23
    3133,               // Y Index = 24
    3311                // Z Index = 25
};
const unsigned int Array_N[] ={
    13333,    // 0 Index = 0
    11333,    // 1 Index = 1
    11133,    // 2 Index = 2
    11113,    // 3 Index = 3
    11111,    // 4 Index = 4
    31111,    // 5 Index = 5
    33111,    // 6 Index = 6
    33311,    // 7 Index = 7
    33331,    // 8 Index = 8
    33333     // 9 Index = 9
};

void setup(){
    Serial.begin(9600);
    pinMode(led, OUTPUT);
}
void loop(){
    Target.toUpperCase();
    char TargetSplit[Target.length()+1];        //+1 for end of array
    for(int i = 0 ; i <= sizeof(TargetSplit) ; i++) TargetSplit[i] = 0;
    unsigned int Morsecode[sizeof(TargetSplit)];        //+1 for end of array
    for(int i = 0 ; i <= sizeof(Morsecode) ; i++){
        Morsecode[i] = 0;
        //Serial.print("Morse initialized");
    }
    Target.toCharArray(TargetSplit,sizeof(TargetSplit));
    for(int i = 0 ; i < sizeof(TargetSplit) ; i++){
        if((90 >= (int)TargetSplit[i]) && ((int)TargetSplit[i] >= 65 )){    // loop 1
            Morsecode[i] = Array_V[(int)TargetSplit[i] - 65];
            // Serial.print("i in loop 1 = ");
            // Serial.println(i);
            // Serial.println("---");
        }
        else if((57 >= (int)TargetSplit[i]) && ((int)TargetSplit[i] >= 48 )){   //loop2
            Morsecode[i] = Array_N[(int)TargetSplit[i] - 48];
            //Serial.println(Morsecode[i]);
        }
        else if((int)TargetSplit[i] == 32)  Morsecode[i] = 7;           //word gap = 7*Dur
    }
    BlinkIntervalCacu(Morsecode,Target.length());
}


