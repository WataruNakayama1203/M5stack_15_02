#include "MdHighAndLow.h"

void Mdhighandlow::init(){
    srand((unsigned)time(NULL));
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.fillScreen(BLACK);
}

char Mdhighandlow::leftAns(){
    char leftAns = rand() % 10; 
    while (leftAns == 0)
	{
		leftAns = rand() % 10; //0なら再生成
	}
    return leftAns;
}

char Mdhighandlow::rightAns(){
    char rightAns = rand() % 10; 
    while (rightAns == 0)
	{
		rightAns = rand() % 10; //0なら再生成
	}
    return rightAns;
}

BattleResult Mdhighandlow::getBattleResult(UserAns userAns, char leftAns, char rightAns){
    switch(userAns){
        case ANS_HIGH:
            if(leftAns < rightAns){
                return WIN;
            }
            else{
                return LOSE;
            }
            break;
        case ANS_LOW:
            if(leftAns > rightAns){
                return WIN;
            }
            else{
                return LOSE;
            }
            break;
    }
}