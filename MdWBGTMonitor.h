/* インクルードガード */
#pragma once

#include "M5All-In-One-Gadget.h"
#include "DrTHSensor.h"

class MdWBGTMonitor // classの定義
{
private: // privateはクラス内からしかアクセスできない
public: // publicはどこからでもアクセス可能
    void init();
    void getWBGT(double* temperature, double* humidity, WbgtIndex* index);
};
