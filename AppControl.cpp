#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>

MdLcd mlcd;
MdWBGTMonitor mwbgt;
MdMusicPlayer mmplay;
MdMeasureDistance mmdist;
MdDateTime mdtime;

const char* g_str_orange[] = {
    COMMON_ORANGE0_IMG_PATH,
    COMMON_ORANGE1_IMG_PATH,
    COMMON_ORANGE2_IMG_PATH,
    COMMON_ORANGE3_IMG_PATH,
    COMMON_ORANGE4_IMG_PATH,
    COMMON_ORANGE5_IMG_PATH,
    COMMON_ORANGE6_IMG_PATH,
    COMMON_ORANGE7_IMG_PATH,
    COMMON_ORANGE8_IMG_PATH,
    COMMON_ORANGE9_IMG_PATH,
};

const char* g_str_blue[] = {
    COMMON_BLUE0_IMG_PATH,
    COMMON_BLUE1_IMG_PATH,
    COMMON_BLUE2_IMG_PATH,
    COMMON_BLUE3_IMG_PATH,
    COMMON_BLUE4_IMG_PATH,
    COMMON_BLUE5_IMG_PATH,
    COMMON_BLUE6_IMG_PATH,
    COMMON_BLUE7_IMG_PATH,
    COMMON_BLUE8_IMG_PATH,
    COMMON_BLUE9_IMG_PATH,
};

void AppControl::setBtnAFlg(bool flg)
{
    m_flag_btnA_is_pressed = flg;
}

void AppControl::setBtnBFlg(bool flg)
{
    m_flag_btnB_is_pressed = flg;
}

void AppControl::setBtnCFlg(bool flg)
{
    m_flag_btnC_is_pressed = flg;
}

void AppControl::setBtnAllFlgFalse()
{
    m_flag_btnA_is_pressed = false;
    m_flag_btnB_is_pressed = false;
    m_flag_btnC_is_pressed = false;
}

State AppControl::getState()
{
    return m_state;
}

void AppControl::setState(State state)
{
    m_state = state;
}

Action AppControl::getAction()
{
    return m_action;
}

void AppControl::setAction(Action action)
{
    m_action = action;
}

void AppControl::setStateAction(State state, Action action)
{
    setState(state);
    setAction(action);
}

FocusState AppControl::getFocusState()
{
    return m_focus_state;
}

void AppControl::setFocusState(FocusState fs)
{
    m_focus_state = fs;
}

/***********************************************************************
                            タイトル画面を描画する
***********************************************************************/
void AppControl::displayTitleInit()
{
    mlcd.displayJpgImage(TITLE_IMG_PATH);
}


/***********************************************************************
                            メニュー画面を初期化して描画する
***********************************************************************/
void AppControl::displayMenuInit()
{
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH, MENU_UP_X_CRD, MENU_UP_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH, MENU_DECIDE_X_CRD, MENU_DECIDE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH, MENU_DOWN_X_CRD, MENU_DOWN_Y_CRD);
}

/***********************************************************************
                            メニュー画面においてフォーカスを移動させる
***********************************************************************/
void AppControl::focusChangeImg(FocusState current_state, FocusState next_state)
{
    //非フォーカス画像に切り替え
    if(current_state == MENU_WBGT){
        mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
    }else if(current_state == MENU_MUSIC){
        mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
    }else if(current_state == MENU_MEASURE){
        mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
    }else if(current_state == MENU_DATE){
        mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
    }

    //フォーカス画像に切り替え
    if(next_state == MENU_WBGT){
        mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH, MENU_WBGT_X_CRD, MENU_WBGT_Y_CRD);
    }else if(next_state == MENU_MUSIC){
        mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH, MENU_MUSIC_X_CRD, MENU_MUSIC_Y_CRD);
    }else if(next_state == MENU_MEASURE){
        mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH, MENU_MEASURE_X_CRD, MENU_MEASURE_Y_CRD);
    }else if(next_state == MENU_DATE){
        mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH, MENU_DATE_X_CRD, MENU_DATE_Y_CRD);
    }
}

/***********************************************************************
                    熱中症モニタの初期画面を描画する
***********************************************************************/
void AppControl::displayWBGTInit()
{
    mwbgt.init();
    mlcd.fillBackgroundWhite();
    displayTempHumiIndex();
    //戻るボタンの表示
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,WBGT_BACK_X_CRD,WBGT_BACK_Y_CRD);
    //「温度」表示
    mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH,WBGT_TEMPERATURE_X_CRD,WBGT_TEMPERATURE_Y_CRD);
    //「湿度」表示
    mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH,WBGT_HUMIDITY_X_CRD,WBGT_HUMIDITY_Y_CRD);
    //温度の「.」の表示
    mlcd.displayJpgImageCoordinate(COMMON_ORANGEDOT_IMG_PATH,WBGT_TDOT_X_CRD,WBGT_TDOT_Y_CRD);
    //温度の「℃」の表示
    mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH,WBGT_DEGREE_X_CRD,WBGT_DEGREE_Y_CRD);
    //湿度の「.」の表示
    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH,WBGT_HDOT_X_CRD,WBGT_HDOT_Y_CRD);
    //湿度の「%」の表示
    mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH,WBGT_PERCENT_X_CRD,WBGT_PERCENT_Y_CRD);
}

/***********************************************************************
                熱中症モニタの画面に温度・湿度・アラートを描画する
***********************************************************************/
void AppControl::displayTempHumiIndex()
{
    double temperature;
    double humidity;
    WbgtIndex index;
    mwbgt.getWBGT(&temperature, &humidity, &index);
    /***********************************************************************************************
    　　　　　　　　　　　　                    温度表示部分（Temprature）
    ***********************************************************************************************/
    int t2_digit = (int)(temperature / 10) % 10;
    int t1_digit = (int)temperature % 10;
    int t1_deci = (int)(temperature * 10) % 10;

    //温度表示（十の位）
    switch(t2_digit){
        case 0:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE0_IMG_PATH,WBGT_T2DIGIT_X_CRD,WBGT_T2DIGIT_Y_CRD);
            break;
        case 1:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE1_IMG_PATH,WBGT_T2DIGIT_X_CRD,WBGT_T2DIGIT_Y_CRD);
            break;
        case 2:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE2_IMG_PATH,WBGT_T2DIGIT_X_CRD,WBGT_T2DIGIT_Y_CRD);
            break;
        case 3:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE3_IMG_PATH,WBGT_T2DIGIT_X_CRD,WBGT_T2DIGIT_Y_CRD);
            break;
        case 4:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE4_IMG_PATH,WBGT_T2DIGIT_X_CRD,WBGT_T2DIGIT_Y_CRD);
            break;
        case 5:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE5_IMG_PATH,WBGT_T2DIGIT_X_CRD,WBGT_T2DIGIT_Y_CRD);
            break;
        case 6:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE6_IMG_PATH,WBGT_T2DIGIT_X_CRD,WBGT_T2DIGIT_Y_CRD);
            break;
        case 7:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE7_IMG_PATH,WBGT_T2DIGIT_X_CRD,WBGT_T2DIGIT_Y_CRD);
            break;
        case 8:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE8_IMG_PATH,WBGT_T2DIGIT_X_CRD,WBGT_T2DIGIT_Y_CRD);
            break;
        case 9:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE9_IMG_PATH,WBGT_T2DIGIT_X_CRD,WBGT_T2DIGIT_Y_CRD);
            break;
        }

    //温度表示（一の位）
    switch(t1_digit){
        case 0:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE0_IMG_PATH,WBGT_T1DIGIT_X_CRD,WBGT_T1DIGIT_Y_CRD);
            break;
        case 1:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE1_IMG_PATH,WBGT_T1DIGIT_X_CRD,WBGT_T1DIGIT_Y_CRD);
            break;
        case 2:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE2_IMG_PATH,WBGT_T1DIGIT_X_CRD,WBGT_T1DIGIT_Y_CRD);
            break;
        case 3:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE3_IMG_PATH,WBGT_T1DIGIT_X_CRD,WBGT_T1DIGIT_Y_CRD);
            break;
        case 4:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE4_IMG_PATH,WBGT_T1DIGIT_X_CRD,WBGT_T1DIGIT_Y_CRD);
            break;
        case 5:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE5_IMG_PATH,WBGT_T1DIGIT_X_CRD,WBGT_T1DIGIT_Y_CRD);
            break;
        case 6:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE6_IMG_PATH,WBGT_T1DIGIT_X_CRD,WBGT_T1DIGIT_Y_CRD);
            break;
        case 7:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE7_IMG_PATH,WBGT_T1DIGIT_X_CRD,WBGT_T1DIGIT_Y_CRD);
            break;
        case 8:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE8_IMG_PATH,WBGT_T1DIGIT_X_CRD,WBGT_T1DIGIT_Y_CRD);
            break;
        case 9:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE9_IMG_PATH,WBGT_T1DIGIT_X_CRD,WBGT_T1DIGIT_Y_CRD);
            break;
        }
    //温度表示（少数点第一位）
    switch(t1_deci){
        case 0:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE0_IMG_PATH,WBGT_T1DECIMAL_X_CRD,WBGT_T1DECIMAL_Y_CRD);
            break;
        case 1:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE1_IMG_PATH,WBGT_T1DECIMAL_X_CRD,WBGT_T1DECIMAL_Y_CRD);
            break;
        case 2:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE2_IMG_PATH,WBGT_T1DECIMAL_X_CRD,WBGT_T1DECIMAL_Y_CRD);
            break;
        case 3:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE3_IMG_PATH,WBGT_T1DECIMAL_X_CRD,WBGT_T1DECIMAL_Y_CRD);
            break;
        case 4:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE4_IMG_PATH,WBGT_T1DECIMAL_X_CRD,WBGT_T1DECIMAL_Y_CRD);
            break;
        case 5:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE5_IMG_PATH,WBGT_T1DECIMAL_X_CRD,WBGT_T1DECIMAL_Y_CRD);
            break;
        case 6:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE6_IMG_PATH,WBGT_T1DECIMAL_X_CRD,WBGT_T1DECIMAL_Y_CRD);
            break;
        case 7:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE7_IMG_PATH,WBGT_T1DECIMAL_X_CRD,WBGT_T1DECIMAL_Y_CRD);
            break;
        case 8:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE8_IMG_PATH,WBGT_T1DECIMAL_X_CRD,WBGT_T1DECIMAL_Y_CRD);
            break;
        case 9:
            mlcd.displayJpgImageCoordinate(COMMON_ORANGE9_IMG_PATH,WBGT_T1DECIMAL_X_CRD,WBGT_T1DECIMAL_Y_CRD);
            break;
        }

    /***********************************************************************************************
    　　　　　　　　　　　　                    湿度表示部分（Humidity）
    ***********************************************************************************************/
    int h2_digit = (int)(humidity / 10) % 10;
    int h1_digit = (int)(humidity) % 10;
    int h1_deci = (int)(humidity * 10) % 10;

    //湿度表示（十の位）
    switch(h2_digit){
        case 0:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH,WBGT_H2DIGIT_X_CRD,WBGT_H2DIGIT_Y_CRD);
            break;
        case 1:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH,WBGT_H2DIGIT_X_CRD,WBGT_H2DIGIT_Y_CRD);
            break;
        case 2:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH,WBGT_H2DIGIT_X_CRD,WBGT_H2DIGIT_Y_CRD);
            break;
        case 3:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH,WBGT_H2DIGIT_X_CRD,WBGT_H2DIGIT_Y_CRD);
            break;
        case 4:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH,WBGT_H2DIGIT_X_CRD,WBGT_H2DIGIT_Y_CRD);
            break;
        case 5:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH,WBGT_H2DIGIT_X_CRD,WBGT_H2DIGIT_Y_CRD);
            break;
        case 6:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH,WBGT_H2DIGIT_X_CRD,WBGT_H2DIGIT_Y_CRD);
            break;
        case 7:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH,WBGT_H2DIGIT_X_CRD,WBGT_H2DIGIT_Y_CRD);
            break;
        case 8:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH,WBGT_H2DIGIT_X_CRD,WBGT_H2DIGIT_Y_CRD);
            break;
        case 9:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH,WBGT_H2DIGIT_X_CRD,WBGT_H2DIGIT_Y_CRD);
            break;
        }

    //湿度表示（一の位）
    switch(h1_digit){
        case 0:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH,WBGT_H1DIGIT_X_CRD,WBGT_H1DIGIT_Y_CRD);
            break;
        case 1:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH,WBGT_H1DIGIT_X_CRD,WBGT_H1DIGIT_Y_CRD);
            break;
        case 2:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH,WBGT_H1DIGIT_X_CRD,WBGT_H1DIGIT_Y_CRD);
            break;
        case 3:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH,WBGT_H1DIGIT_X_CRD,WBGT_H1DIGIT_Y_CRD);
            break;
        case 4:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH,WBGT_H1DIGIT_X_CRD,WBGT_H1DIGIT_Y_CRD);
            break;
        case 5:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH,WBGT_H1DIGIT_X_CRD,WBGT_H1DIGIT_Y_CRD);
            break;
        case 6:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH,WBGT_H1DIGIT_X_CRD,WBGT_H1DIGIT_Y_CRD);
            break;
        case 7:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH,WBGT_H1DIGIT_X_CRD,WBGT_H1DIGIT_Y_CRD);
            break;
        case 8:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH,WBGT_H1DIGIT_X_CRD,WBGT_H1DIGIT_Y_CRD);
            break;
        case 9:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH,WBGT_H1DIGIT_X_CRD,WBGT_H1DIGIT_Y_CRD);
            break;
        }

    //湿度表示（少数点第一位）
    switch(h1_deci){
        case 0:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH,WBGT_H1DECIMAL_X_CRD,WBGT_H1DECIMAL_Y_CRD);
            break;
        case 1:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH,WBGT_H1DECIMAL_X_CRD,WBGT_H1DECIMAL_Y_CRD);
            break;
        case 2:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH,WBGT_H1DECIMAL_X_CRD,WBGT_H1DECIMAL_Y_CRD);
            break;
        case 3:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH,WBGT_H1DECIMAL_X_CRD,WBGT_H1DECIMAL_Y_CRD);
            break;
        case 4:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH,WBGT_H1DECIMAL_X_CRD,WBGT_H1DECIMAL_Y_CRD);
            break;
        case 5:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH,WBGT_H1DECIMAL_X_CRD,WBGT_H1DECIMAL_Y_CRD);
            break;
        case 6:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH,WBGT_H1DECIMAL_X_CRD,WBGT_H1DECIMAL_Y_CRD);
            break;
        case 7:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH,WBGT_H1DECIMAL_X_CRD,WBGT_H1DECIMAL_Y_CRD);
            break;
        case 8:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH,WBGT_H1DECIMAL_X_CRD,WBGT_H1DECIMAL_Y_CRD);
            break;
        case 9:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH,WBGT_H1DECIMAL_X_CRD,WBGT_H1DECIMAL_Y_CRD);
            break;
        }

    /***********************************************************************************************
    　　　　　　　　　　　　                    アラート表示部分
    ***********************************************************************************************/
    switch(index){
        case SAFE:
            mlcd.displayJpgImageCoordinate(WBGT_SAFE_IMG_PATH,WBGT_NOTICE_X_CRD,WBGT_NOTICE_Y_CRD);
            break;
        case ATTENTION:
            mlcd.displayJpgImageCoordinate(WBGT_ATTENTION_IMG_PATH,WBGT_NOTICE_X_CRD,WBGT_NOTICE_Y_CRD);
            break;
        case ALERT:
            mlcd.displayJpgImageCoordinate(WBGT_ALERT_IMG_PATH,WBGT_NOTICE_X_CRD,WBGT_NOTICE_Y_CRD);
            break;
        case HIGH_ALERT:
            mlcd.displayJpgImageCoordinate(WBGT_HIGH_ALERT_IMG_PATH,WBGT_NOTICE_X_CRD,WBGT_NOTICE_Y_CRD);
            break;
        case DANGER:
            mlcd.displayJpgImageCoordinate(WBGT_DANGER_IMG_PATH,WBGT_NOTICE_X_CRD,WBGT_NOTICE_Y_CRD);
            break;
        }
}

/***********************************************************************
                音楽プレイヤーの画面を初期化して描画する
***********************************************************************/
void AppControl::displayMusicInit()
{
    mmplay.init();
    displayMusicTitle();
}

/***********************************************************************
                音楽停止画面を描画する
***********************************************************************/
void AppControl::displayMusicStop()
{
    mlcd.fillBackgroundWhite();
    displayMusicTitle();
    mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH,MUSIC_NOTICE_X_CRD,MUSIC_NOTICE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,MUSIC_BACK_X_CRD,MUSIC_BACK_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH,MUSIC_PLAY_X_CRD,MUSIC_PLAY_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH,MUSIC_NEXT_X_CRD,MUSIC_NEXT_Y_CRD);
}

/***********************************************************************
                音楽ファイルのファイル名を描画する
***********************************************************************/
void AppControl::displayMusicTitle()
{
    mlcd.displayText("                     ",MUSIC_TITLE_X_CRD,MUSIC_TITLE_Y_CRD); //表示切り替え時の残像消し用
    mlcd.displayText(mmplay.getTitle(),MUSIC_TITLE_X_CRD,MUSIC_TITLE_Y_CRD);
}

/***********************************************************************
                次の音楽ファイル開き、そのファイル名を描画する
***********************************************************************/
void AppControl::displayNextMusic()
{
    mmplay.selectNextMusic();
    displayMusicTitle();
}

/***********************************************************************
                音楽再生画面を描画する
***********************************************************************/
void AppControl::displayMusicPlay()
{
    mmplay.prepareMP3();
    mlcd.fillBackgroundWhite();
    displayMusicTitle();
    mlcd.displayJpgImageCoordinate(MUSIC_NOWPLAYING_IMG_PATH,MUSIC_NOTICE_X_CRD,MUSIC_NOTICE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_STOP_IMG_PATH,MUSIC_STOP_X_CRD,MUSIC_STOP_Y_CRD);
}

/***********************************************************************
                距離測定画面の初期画面を描画する
***********************************************************************/
void AppControl::displayMeasureInit()
{
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(MEASURE_NOTICE_IMG_PATH,MEASURE_NOTICE_X_CRD,MEASURE_NOTICE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,MEASURE_BACK_X_CRD,MEASURE_BACK_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH,MEASURE_DOT_X_CRD,MEASURE_DOT_Y_CRD);
    mlcd.displayJpgImageCoordinate(MEASURE_CM_IMG_PATH,MEASURE_CM_X_CRD,MEASURE_CM_Y_CRD);
    displayMeasureDistance();
}

/***********************************************************************
                測定した距離を描画する
***********************************************************************/
void AppControl::displayMeasureDistance()
{
    //距離(cm)を取得
    double distance = mmdist.getDistance();
    //コンマ表示
    mlcd.displayJpgImageCoordinate(COMMON_BLUEDOT_IMG_PATH,MEASURE_DOT_X_CRD,MEASURE_DOT_Y_CRD);

    //「cm」表示
    mlcd.displayJpgImageCoordinate(MEASURE_CM_IMG_PATH,MEASURE_CM_X_CRD,MEASURE_CM_Y_CRD);

    int d3_digit = (int)(distance / 100) % 10;
    int d2_digit = (int)(distance / 10) % 10;
    int d1_digit = (int)distance % 10;
    int d1_deci = (int)(distance * 10) % 10;

    //距離表示（百の位）
    switch(d3_digit){
        case 0:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH,MEASURE_DIGIT3_X_CRD,MEASURE_DIGIT3_Y_CRD);
            break;
        case 1:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH,MEASURE_DIGIT3_X_CRD,MEASURE_DIGIT3_Y_CRD);
            break;
        case 2:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH,MEASURE_DIGIT3_X_CRD,MEASURE_DIGIT3_Y_CRD);
            break;
        case 3:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH,MEASURE_DIGIT3_X_CRD,MEASURE_DIGIT3_Y_CRD);
            break;
        case 4:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH,MEASURE_DIGIT3_X_CRD,MEASURE_DIGIT3_Y_CRD);
            break;
        case 5:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH,MEASURE_DIGIT3_X_CRD,MEASURE_DIGIT3_Y_CRD);
            break;
        case 6:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH,MEASURE_DIGIT3_X_CRD,MEASURE_DIGIT3_Y_CRD);
            break;
        case 7:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH,MEASURE_DIGIT3_X_CRD,MEASURE_DIGIT3_Y_CRD);
            break;
        case 8:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH,MEASURE_DIGIT3_X_CRD,MEASURE_DIGIT3_Y_CRD);
            break;
        case 9:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH,MEASURE_DIGIT3_X_CRD,MEASURE_DIGIT3_Y_CRD);
            break;
    }

    //距離表示（10の位の数字）
    switch(d2_digit){
        case 0:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH,MEASURE_DIGIT2_X_CRD,MEASURE_DIGIT2_Y_CRD);
            break;
        case 1:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH,MEASURE_DIGIT2_X_CRD,MEASURE_DIGIT2_Y_CRD);
            break;
        case 2:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH,MEASURE_DIGIT2_X_CRD,MEASURE_DIGIT2_Y_CRD);
            break;
        case 3:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH,MEASURE_DIGIT2_X_CRD,MEASURE_DIGIT2_Y_CRD);
            break;
        case 4:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH,MEASURE_DIGIT2_X_CRD,MEASURE_DIGIT2_Y_CRD);
            break;
        case 5:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH,MEASURE_DIGIT2_X_CRD,MEASURE_DIGIT2_Y_CRD);
            break;
        case 6:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH,MEASURE_DIGIT2_X_CRD,MEASURE_DIGIT2_Y_CRD);
            break;
        case 7:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH,MEASURE_DIGIT2_X_CRD,MEASURE_DIGIT2_Y_CRD);
            break;
        case 8:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH,MEASURE_DIGIT2_X_CRD,MEASURE_DIGIT2_Y_CRD);
            break;
        case 9:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH,MEASURE_DIGIT2_X_CRD,MEASURE_DIGIT2_Y_CRD);
            break;
        }

    //距離表示（一の位）
    switch(d1_digit){
        case 0:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH,MEASURE_DIGIT1_X_CRD,MEASURE_DIGIT1_Y_CRD);
            break;
        case 1:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH,MEASURE_DIGIT1_X_CRD,MEASURE_DIGIT1_Y_CRD);
            break;
        case 2:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH,MEASURE_DIGIT1_X_CRD,MEASURE_DIGIT1_Y_CRD);
            break;
        case 3:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH,MEASURE_DIGIT1_X_CRD,MEASURE_DIGIT1_Y_CRD);
            break;
        case 4:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH,MEASURE_DIGIT1_X_CRD,MEASURE_DIGIT1_Y_CRD);
            break;
        case 5:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH,MEASURE_DIGIT1_X_CRD,MEASURE_DIGIT1_Y_CRD);
            break;
        case 6:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH,MEASURE_DIGIT1_X_CRD,MEASURE_DIGIT1_Y_CRD);
            break;
        case 7:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH,MEASURE_DIGIT1_X_CRD,MEASURE_DIGIT1_Y_CRD);
            break;
        case 8:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH,MEASURE_DIGIT1_X_CRD,MEASURE_DIGIT1_Y_CRD);
            break;
        case 9:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH,MEASURE_DIGIT1_X_CRD,MEASURE_DIGIT1_Y_CRD);
            break;
    }
    //距離表示（少数点第一位）
    switch(d1_deci){
        case 0:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE0_IMG_PATH,MEASURE_DECIMAL_X_CRD,MEASURE_DECIMAL_Y_CRD);
            break;
        case 1:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE1_IMG_PATH,MEASURE_DECIMAL_X_CRD,MEASURE_DECIMAL_Y_CRD);
            break;
        case 2:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE2_IMG_PATH,MEASURE_DECIMAL_X_CRD,MEASURE_DECIMAL_Y_CRD);
            break;
        case 3:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE3_IMG_PATH,MEASURE_DECIMAL_X_CRD,MEASURE_DECIMAL_Y_CRD);
            break;
        case 4:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE4_IMG_PATH,MEASURE_DECIMAL_X_CRD,MEASURE_DECIMAL_Y_CRD);
            break;
        case 5:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE5_IMG_PATH,MEASURE_DECIMAL_X_CRD,MEASURE_DECIMAL_Y_CRD);
            break;
        case 6:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE6_IMG_PATH,MEASURE_DECIMAL_X_CRD,MEASURE_DECIMAL_Y_CRD);
            break;
        case 7:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE7_IMG_PATH,MEASURE_DECIMAL_X_CRD,MEASURE_DECIMAL_Y_CRD);
            break;
        case 8:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE8_IMG_PATH,MEASURE_DECIMAL_X_CRD,MEASURE_DECIMAL_Y_CRD);
            break;
        case 9:
            mlcd.displayJpgImageCoordinate(COMMON_BLUE9_IMG_PATH,MEASURE_DECIMAL_X_CRD,MEASURE_DECIMAL_Y_CRD);
            break;
    }
}

/***********************************************************************
                時刻表示画面の初期画面を描画する
***********************************************************************/
void AppControl::displayDateInit()
{
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH,DATE_NOTICE_X_CRD,DATE_NOTICE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,DATE_BACK_X_CRD,DATE_BACK_Y_CRD);
    displayDateUpdate();

}

/***********************************************************************
                現在の日時を描画する
***********************************************************************/
void AppControl::displayDateUpdate()
{
    mlcd.displayDateText(mdtime.readDate(),DATE_YYYYMMDD_X_CRD,DATE_YYYYMMDD_Y_CRD);
    mlcd.displayDateText(mdtime.readTime(),DATE_HHmmSS_X_CRD,DATE_HHmmSS_Y_CRD);
}

/***********************************************************************
                メニュー画面で機能を選択し、その機能と画面を呼び出す。
***********************************************************************/
void AppControl::controlApplication()
{
    while (1) {

        switch (getState()) {
        case TITLE:
            switch (getAction()) {
            case ENTRY:
                
                /*
                ** まずはここにタイトル画面の表示処理を呼び出してみよう。
                ** タイトル画面表示の関数はdisplayTitleInit()である。
                ** この関数の中身はまだ何もないので、この関数にタイトル画面表示処理を書いてみよう。
                */
                displayTitleInit();
                setStateAction(TITLE,DO);
                break;

            case DO:
                if(m_flag_btnA_is_pressed || m_flag_btnB_is_pressed || m_flag_btnC_is_pressed) {
                setBtnAllFlgFalse(); //ボタンフラグの初期化
                setStateAction(TITLE,EXIT);
                }
                
                break;

            case EXIT:
                mlcd.clearDisplay();//画面初期化
                setStateAction(MENU,ENTRY);
                break;

            default:
                break;
            }
            break;

        case MENU:

            switch (getAction()) {
            case ENTRY:
                displayMenuInit();
                setFocusState(MENU_WBGT);
                setStateAction(MENU,DO);
                break;

            case DO:
                /*MENU画面で「↑」ボタン押下時の挙動*/
                if(m_flag_btnA_is_pressed){
                    setBtnAllFlgFalse();
                    switch(getFocusState()){
                        case MENU_MUSIC:
                            setFocusState(MENU_WBGT);
                            focusChangeImg(MENU_MUSIC,MENU_WBGT);
                            break;
                        case MENU_MEASURE:
                            setFocusState(MENU_MUSIC);
                            focusChangeImg(MENU_MEASURE,MENU_MUSIC);
                            break;
                        case MENU_DATE:
                            setFocusState(MENU_MEASURE);
                            focusChangeImg(MENU_DATE,MENU_MEASURE);
                            break;
                        case MENU_WBGT:
                            setFocusState(MENU_DATE);
                            focusChangeImg(MENU_WBGT,MENU_DATE);
                            break;
                    }
                }
                /*MENU画面で「↓」ボタン押下時の挙動*/
                if(m_flag_btnC_is_pressed){
                    setBtnAllFlgFalse();
                    switch(getFocusState()){
                        case MENU_WBGT:
                            setFocusState(MENU_MUSIC);
                            focusChangeImg(MENU_WBGT,MENU_MUSIC);
                            break;
                        case MENU_MUSIC:
                            setFocusState(MENU_MEASURE);
                            focusChangeImg(MENU_MUSIC,MENU_MEASURE);
                            break;
                        case MENU_MEASURE:
                            setFocusState(MENU_DATE);
                            focusChangeImg(MENU_MEASURE,MENU_DATE);
                            break;
                        case MENU_DATE:
                            setFocusState(MENU_WBGT);
                            focusChangeImg(MENU_DATE,MENU_WBGT);
                            break;
                    }
                }
                /*MENU画面で「決定」ボタン押下時の挙動*/
                if(m_flag_btnB_is_pressed){
                    setBtnAllFlgFalse();
                    setStateAction(MENU,EXIT);
                }
                break;

            case EXIT:
                mlcd.clearDisplay();
                switch(getFocusState()){
                    case MENU_WBGT:
                        displayWBGTInit();
                        setStateAction(WBGT,ENTRY);
                        break;
                    case MENU_MUSIC:
                        displayMusicInit();
                        setStateAction(MUSIC_STOP,ENTRY);
                        break;
                    case MENU_MEASURE:
                        displayMeasureInit();
                        setStateAction(MEASURE,ENTRY);
                        break;
                    case MENU_DATE:
                        displayDateInit();
                        setStateAction(DATE,ENTRY);
                        break;
                }

            default:
                break;
            }
            break;

        case WBGT:
            switch (getAction()) {
            case ENTRY:
                setStateAction(WBGT,DO);
                break;
            case DO:
                displayTempHumiIndex();
                delay(100); //シーケンス図（スライド6）より
                if(m_flag_btnB_is_pressed){
                    setBtnAllFlgFalse();
                    setStateAction(WBGT,EXIT);
                }
                break;
            case EXIT:
                mlcd.clearDisplay();
                setStateAction(MENU,ENTRY);
                break;
            default:
                break;
            }
            break;

        case MUSIC_STOP:
            switch (getAction()) {
            case ENTRY:
                displayMusicStop();
                setStateAction(MUSIC_STOP,DO);
                break;
            case DO:
                if(m_flag_btnA_is_pressed){
                    setStateAction(MUSIC_STOP,EXIT);
                }
                if(m_flag_btnB_is_pressed){
                    setStateAction(MUSIC_STOP,EXIT);
                }
                if(m_flag_btnC_is_pressed){
                    setBtnAllFlgFalse();
                    displayNextMusic();
                }
                break;
            case EXIT:
                if(m_flag_btnA_is_pressed){
                    setBtnAllFlgFalse();
                    setStateAction(MUSIC_PLAY,ENTRY);
                }
                if(m_flag_btnB_is_pressed){
                    mlcd.clearDisplay();
                    setBtnAllFlgFalse();
                    setStateAction(MENU,ENTRY);
                }
                break;
            default:
                break;
            }
            break;

        case MUSIC_PLAY:
            switch (getAction()) {
            case ENTRY:
                displayMusicPlay();
                setStateAction(MUSIC_PLAY,DO);
                break;
            case DO:
                mmplay.playMP3();
                if(m_flag_btnA_is_pressed){
                    setBtnAllFlgFalse();
                    if(mmplay.isRunningMP3()){
                        mmplay.stopMP3();
                    }
                    setStateAction(MUSIC_PLAY,EXIT);
                }
                break;
            case EXIT:
                setStateAction(MUSIC_STOP,ENTRY);
                break;
            default:
                break;
            }

            break;
        case MEASURE:

            switch (getAction()) {
            case ENTRY:
                setStateAction(MEASURE,DO);
                break;

            case DO:
                displayMeasureDistance();
                delay(250); //シーケンス図（スライド9）より
                if(m_flag_btnB_is_pressed){
                    setBtnAllFlgFalse();
                    setStateAction(MEASURE,EXIT);
                }
                break;

            case EXIT:
                mlcd.clearDisplay();
                setStateAction(MENU,ENTRY);
                break;

            default:
                break;
            }

            break;

        case DATE:

            switch (getAction()) {
            case ENTRY:
                setStateAction(DATE,DO);
                break;

            case DO:
                displayDateUpdate();
                delay(100); //シーケンス図（スライド10）より
                if(m_flag_btnB_is_pressed){
                    setBtnAllFlgFalse();
                    setStateAction(DATE,EXIT);
                }
                break;

            case EXIT:
                mlcd.clearDisplay();
                setStateAction(MENU,ENTRY);
                break;

            default:
                break;
            }

        default:
            break;
        }
    }
}
