/* インクルードガード */
#pragma once

#include "M5All-In-One-Gadget.h"
#include <time.h>
#include <CSV_Parser.h>
#include <M5Stack.h>
 
class Mdhighandlow
{
    private:

    public:
    void init();
    char leftAns();
    char rightAns();
    BattleResult getBattleResult(UserAns userAns, char leftAns, char rightAns);

};