#include "DxLib.h"
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

int Key[256]; // 키가 눌러진 프레임 수를 저장한다

int gpUpdateKey() {
    char tmpKey[256]; // 현재 키의 입력 상태 저장
    GetHitKeyStateAll(tmpKey); // 모든 키의 입력 상태를 얻는다.
    for (int i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) { // i번의 키코드에 대응하는 키를 누르고 있으면
            Key[i]++; // 더하기
        }
        else { // 누르지 않으면
            Key[i] = 0; // 0으로 설정
        }
    }
    return 0;
}// 가져온 코드

void long_writing_practice(string a) {
    char input[128];
    int textstream;
    int wrong_count = 0;
    float accuracy = 0;//정확도를 구하는데 필요한 변수
    char text[128];
    char a2[128];
    char type_per_min2[128];//2 붙은 것들은 출력을 위해 자료형을 변환시켜준 것들
    char real_accuracy2[128];
    float real_accuracy;
    double type_per_min;

    for (int i = 0; i < a.size(); i++) {
        a2[i] = a[i];
    }
    a2[a.size() + 1] = '\0';//a를 char[] 형식으로 변환
    textstream = FileRead_open(a2);
    time_t start, end;
    start = time(NULL);
    int Wy = 0;//문장들이 출력되는 위치를 조정하는 변수(y값)
    int roof = 0;//화면 밖으로 넘어가는걸 방지
    int next = 0;//한 화면이 끝난 뒤 계속할지를 정하는 변수
    while (FileRead_eof(textstream) == 0) {//한줄씩 읽어주기
        FileRead_gets(text, 256, textstream);
        if (roof == 23) {//문장이 화면 밖으로 나가지 않도록 제어해주는 조건문이자 화면의 끝에 도달했을때 결과창을 출력해주는 조건문
            ClearDrawScreen();
            Wy = 0;
            roof = 0;
            end = time(NULL);
            type_per_min = accuracy * (60 / (double)(end - start));
            real_accuracy = ((accuracy - wrong_count) / accuracy) * 100;
            sprintf_s(real_accuracy2, sizeof(real_accuracy2), "%0.2f", real_accuracy);
            DrawString(220, 195, "accuracy: ", GetColor(255, 255, 255));
            DrawString(320, 195, real_accuracy2, GetColor(255, 255, 255));
            DrawString(380, 195, "%", GetColor(255, 255, 255));
            DrawString(220, 230, "type per min: ", GetColor(255, 255, 255));
            char type_per_min2[128];
            sprintf_s(type_per_min2, sizeof(type_per_min2), "%0.2f", type_per_min);
            DrawString(350, 230, type_per_min2, GetColor(255, 255, 255));
            DrawString(170, 265, "Enter to continue, Esc to escape", GetColor(255, 255, 51));
            accuracy = 0;
            wrong_count = 0;
            ScreenFlip();
            WaitKey();
            start = time(NULL);
            ClearDrawScreen();
            gpUpdateKey();
            if (Key[KEY_INPUT_ESCAPE] == 1) {
                next = 1;
                break;
            }
        }//한 페이지 끝났을 때
        DrawString(0, Wy, text, GetColor(255, 255, 255));//써야되는 문장 출력
        KeyInputString(0, Wy + 20, 300, input, FALSE);//문장 쓰는거 입력
        int size = strlen(text);
        accuracy += size;
        for (int i = 0; i < size; i++) {//틀린계수 세기
            if (strlen(input) == 0) {
                wrong_count += strlen(text);
                DrawString(0, Wy, text, GetColor(255, 51, 51));
                break;
            }
            else if (input[i] != text[i]) {
                wrong_count++;
                DrawString(0, Wy, text, GetColor(255, 51, 51));
            }
        }
        Wy += 20;//한줄 출력 후 다음줄로 내리기
        roof++;
    }
    end = time(NULL);
    type_per_min = accuracy * (60 / (double)(end - start));
    //타이핑 끝난 시점이니 결과창 도출
    real_accuracy = ((accuracy - wrong_count) / accuracy) * 100;
    ClearDrawScreen();
    sprintf_s(real_accuracy2, sizeof(real_accuracy2), "%0.2f", real_accuracy);
    DrawString(220, 230, "accuracy: ", GetColor(255, 255, 255));
    DrawString(320, 230, real_accuracy2, GetColor(255, 255, 255));
    DrawString(380, 230, "%", GetColor(255, 255, 255));
    DrawString(220, 265, "type per min: ", GetColor(255, 255, 255));
    sprintf_s(type_per_min2, sizeof(type_per_min2), "%0.2f", type_per_min);
    DrawString(350, 265, type_per_min2, GetColor(255, 255, 255));
    FileRead_close(textstream);
    if (next == 0) {
        ScreenFlip();
        WaitKey();
    }//계속하기 원하면 그대로 진행하고 종료 원하면 메뉴화면으로 나가기
    gpUpdateKey();
}
void short_writing_practice(string a, int b) {
    char input[128];
    int textstream;
    char text[25][128];//25문장, 각 문장당 128글자까지 가능
    char a2[128];
    time_t start, end;
    for (int i = 0; i < a.size(); i++) {//a값 a2에 복사(string, char)
        a2[i] = a[i];
    }
    a2[a.size() + 1] = '\0';
    textstream = FileRead_open(a2);
    int Wy = 0;
    int s = 0;
    float accuracy = 0; // 정확도 아님 문장 전체 개수임(변수명에 맞지 않게 사용됨)
    float type_per_min;
    while (FileRead_eof(textstream) == 0) {
        FileRead_gets(text[s], 256, textstream);
        accuracy += 1;
        s++;
    }
    accuracy -= 1;
    SRand(b);
    for (int j = 0; j < 1; j) {//메인 실행 for문
        float wrong_count = 0;
        int ran = GetRand(accuracy);//랜덤으로 문장 고르기
        DrawString(0, Wy, text[ran], GetColor(255, 255, 255));//써야되는 문장 출력
        start = time(NULL);
        KeyInputString(0, Wy + 20, 300, input, FALSE);//문장 쓰는거 입력
        int wordsize = strlen(text[ran]);
        for (int i = 0; i < wordsize; i++) {
            if (input[i] != text[ran][i]) {
                wrong_count++;
            }
        }
        //타이핑 끝난 시점이니 결과창 도출
        end = time(NULL);
        float real_accuracy = ((wordsize - wrong_count) / wordsize) * 100;//진짜 정확도
        type_per_min = strlen(text[ran]) * (60 / (double)(end - start));
        if (strlen(input) == 0) real_accuracy = 0;
        char real_accuracy2[128];
        ClearDrawScreen();
        sprintf_s(real_accuracy2, sizeof(real_accuracy2), "%0.2f", real_accuracy);
        DrawString(220, 195, "accuracy: ", GetColor(255, 255, 255));
        DrawString(310, 195, real_accuracy2, GetColor(255, 255, 255));
        DrawString(370, 195, "%", GetColor(255, 255, 255));
        char type_per_min2[128];
        sprintf_s(type_per_min2, sizeof(type_per_min2), "%0.2f", type_per_min);
        DrawString(220, 230, "type per min: ", GetColor(255, 255, 255));
        DrawString(350, 230, type_per_min2, GetColor(255, 255, 255));
        DrawString(170, 265, "Enter to continue, Esc to escape", GetColor(255, 255, 51));
        ScreenFlip();
        FileRead_close(textstream);
        WaitKey();
        ClearDrawScreen();
        gpUpdateKey();
        if (Key[KEY_INPUT_ESCAPE] == 1) break;//esc눌러서 메뉴로 나가기
    }
}
void word_practice(int a) {
    char input[128];
    int textstream;
    int wrong_count = 0;
    float accuracy = 0;//전체 단어 개수임 정확도 아님(변수명 잘못 사용)
    int correct = 0;//현재 맞은 개수(실행중 표시해주기 위한)
    char** text = new char* [250];
    for (int i = 0; i < 250; i++) text[i] = new char[128];//동적 할당 해주기(250단어, 각각128글자씩 가능)
    textstream = FileRead_open("words.txt");
    int Wy = 0;
    int s = 0;
    while (FileRead_eof(textstream) == 0) {
        FileRead_gets(text[s], 256, textstream);
        accuracy += 1;
        s++;
    }
    accuracy -= 1;
    SRand(a);
    for (int j = 0; j < 10; j++) {
        int ran = GetRand(accuracy);
        char correct2[5];
        char per[5];
        SetFontSize(20);
        sprintf_s(correct2, sizeof(correct2), "%d", correct);
        sprintf_s(per, sizeof(per), "%d", j);
        SetFontSize(20);
        DrawString(540, 0, correct2, GetColor(255, 255, 51));
        DrawString(550, 0, "/", GetColor(255, 255, 51));
        DrawString(560, 0, per, GetColor(153, 203, 255));// 전체/맞은 단어 오른쪽 위에 출력하기
        SetFontSize(64);
        DrawString(200, 168, text[ran], GetColor(255, 255, 255));//써야되는 문장 출력
        KeyInputString(200, 232, 300, input, FALSE);//문장 쓰는거 입력
        ClearDrawScreen();
        int wordsize = strlen(text[ran]);
        int wrong = 0;
        for (int i = 0; i < wordsize; i++) {//틀린 개수 세기(한글자라도 틀리면 틀림)
            if (input[i] != text[ran][i]) {
                wrong++;
                break;//틀린거 찾으면 바로 break
            }
        }
        if (wrong != 0) wrong_count += 1;
        else correct++;
        Wy += 20;
    }//반복 횟수 조절로 정확도 체크까지 걸리는 반복수 조절
    //타이핑 끝난 시점이니 결과창 도출
    float real_accuracy = ((10.0 - wrong_count) / 10) * 100;//10 = 반복횟수(수정가능)
    char real_accuracy2[128];
    char wrong_count2[128];
    ClearDrawScreen();
    sprintf_s(real_accuracy2, sizeof(real_accuracy2), "%0.2f", real_accuracy);
    sprintf_s(wrong_count2, sizeof(wrong_count2), "%d", wrong_count);
    SetFontSize(17);
    DrawString(220, 240, "accuracy: ", GetColor(255, 255, 255));
    DrawString(310, 240, real_accuracy2, GetColor(255, 255, 255));
    DrawString(370, 240, "%", GetColor(255, 255, 255));
    DrawString(240, 270, "WrongCount: ", GetColor(255, 51, 51));
    DrawString(360, 270, wrong_count2, GetColor(255, 51, 51));
    ScreenFlip();
    FileRead_close(textstream);
    WaitKey();
    gpUpdateKey();
    for (int i = 0; i < 250; i++) delete[] text[i];
    delete[] text;//동적 할당 해제
}
void spot_practice(int a) {
    char spot[36] = { 'q','w','e','r','t','y','u','i','o','p'
        ,'a','s','d','f','g','h','j','k','l'
        ,'z','x','c','v','b','n','m'
        ,'1','2','3','4','5','6','7','8','9','0' };//알파벳, 숫자는 추가하거나 바꿀 필요 없으니 텍스트 파일로 저장하지 않고 그냥 배열에 저장
    float accuracy = 0;
    SRand(a);
    int WrongCount = 0;
    for (int i = 0; i < 10; i++) {
        char correct[5];
        char per[5];
        sprintf_s(correct, sizeof(correct), "%0.0f", accuracy);
        sprintf_s(per, sizeof(per), "%d", i);
        SetFontSize(20);
        DrawString(540, 0, correct, GetColor(255, 255, 51));
        DrawString(550, 0, "/", GetColor(255, 255, 51));
        DrawString(560, 0, per, GetColor(153, 203, 255));// 전체/맞은갯수 오른쪽 위에 출력하기
        char Rn[2];
        Rn[0] = spot[GetRand(35)];
        Rn[1] = '\0';
        SetFontSize(64);
        DrawString(280, 200, Rn, GetColor(255, 255, 255));
        while (ScreenFlip() == 0 && ProcessMessage() == 0 && gpUpdateKey() == 0) {//키의 저장상태를 받았으니 이를 이용하려 했는데 조금 더럽게 써진듯 하다...
            if (Rn[0] == 'q' && Key[KEY_INPUT_Q] == 1) accuracy += 1;
            else if (Rn[0] == 'w' && Key[KEY_INPUT_W] == 1) accuracy += 1;
            else if (Rn[0] == 'e' && Key[KEY_INPUT_E] == 1) accuracy += 1;
            else if (Rn[0] == 'r' && Key[KEY_INPUT_R] == 1) accuracy += 1;
            else if (Rn[0] == 't' && Key[KEY_INPUT_T] == 1) accuracy += 1;
            else if (Rn[0] == 'y' && Key[KEY_INPUT_Y] == 1) accuracy += 1;
            else if (Rn[0] == 'u' && Key[KEY_INPUT_U] == 1) accuracy += 1;
            else if (Rn[0] == 'i' && Key[KEY_INPUT_I] == 1) accuracy += 1;
            else if (Rn[0] == 'o' && Key[KEY_INPUT_O] == 1) accuracy += 1;
            else if (Rn[0] == 'p' && Key[KEY_INPUT_P] == 1) accuracy += 1;
            else if (Rn[0] == 'a' && Key[KEY_INPUT_A] == 1) accuracy += 1;
            else if (Rn[0] == 's' && Key[KEY_INPUT_S] == 1) accuracy += 1;
            else if (Rn[0] == 'd' && Key[KEY_INPUT_D] == 1) accuracy += 1;
            else if (Rn[0] == 'f' && Key[KEY_INPUT_F] == 1) accuracy += 1;
            else if (Rn[0] == 'g' && Key[KEY_INPUT_G] == 1) accuracy += 1;
            else if (Rn[0] == 'h' && Key[KEY_INPUT_H] == 1) accuracy += 1;
            else if (Rn[0] == 'j' && Key[KEY_INPUT_J] == 1) accuracy += 1;
            else if (Rn[0] == 'k' && Key[KEY_INPUT_K] == 1) accuracy += 1;
            else if (Rn[0] == 'l' && Key[KEY_INPUT_L] == 1) accuracy += 1;
            else if (Rn[0] == 'z' && Key[KEY_INPUT_Z] == 1) accuracy += 1;
            else if (Rn[0] == 'x' && Key[KEY_INPUT_X] == 1) accuracy += 1;
            else if (Rn[0] == 'c' && Key[KEY_INPUT_C] == 1) accuracy += 1;
            else if (Rn[0] == 'v' && Key[KEY_INPUT_V] == 1) accuracy += 1;
            else if (Rn[0] == 'b' && Key[KEY_INPUT_B] == 1) accuracy += 1;
            else if (Rn[0] == 'n' && Key[KEY_INPUT_N] == 1) accuracy += 1;
            else if (Rn[0] == 'm' && Key[KEY_INPUT_M] == 1) accuracy += 1;
            else if (Rn[0] == '1' && Key[KEY_INPUT_1] == 1) accuracy += 1;
            else if (Rn[0] == '2' && Key[KEY_INPUT_2] == 1) accuracy += 1;
            else if (Rn[0] == '3' && Key[KEY_INPUT_3] == 1) accuracy += 1;
            else if (Rn[0] == '4' && Key[KEY_INPUT_4] == 1) accuracy += 1;
            else if (Rn[0] == '5' && Key[KEY_INPUT_5] == 1) accuracy += 1;
            else if (Rn[0] == '6' && Key[KEY_INPUT_6] == 1) accuracy += 1;
            else if (Rn[0] == '7' && Key[KEY_INPUT_7] == 1) accuracy += 1;
            else if (Rn[0] == '8' && Key[KEY_INPUT_8] == 1) accuracy += 1;
            else if (Rn[0] == '9' && Key[KEY_INPUT_9] == 1) accuracy += 1;
            else if (Rn[0] == '0' && Key[KEY_INPUT_0] == 1) accuracy += 1;
            else if (Rn[0] == '1' && Key[KEY_INPUT_NUMPAD1] == 1) accuracy += 1;
            else if (Rn[0] == '2' && Key[KEY_INPUT_NUMPAD2] == 1) accuracy += 1;
            else if (Rn[0] == '3' && Key[KEY_INPUT_NUMPAD3] == 1) accuracy += 1;
            else if (Rn[0] == '4' && Key[KEY_INPUT_NUMPAD4] == 1) accuracy += 1;
            else if (Rn[0] == '5' && Key[KEY_INPUT_NUMPAD5] == 1) accuracy += 1;
            else if (Rn[0] == '6' && Key[KEY_INPUT_NUMPAD6] == 1) accuracy += 1;
            else if (Rn[0] == '7' && Key[KEY_INPUT_NUMPAD7] == 1) accuracy += 1;
            else if (Rn[0] == '8' && Key[KEY_INPUT_NUMPAD8] == 1) accuracy += 1;
            else if (Rn[0] == '9' && Key[KEY_INPUT_NUMPAD9] == 1) accuracy += 1;
            else if (Rn[0] == '0' && Key[KEY_INPUT_NUMPAD0] == 1) accuracy += 1;
            if (Key[KEY_INPUT_BACK] == 1 || Key[KEY_INPUT_TAB] == 1 || Key[KEY_INPUT_RETURN] == 1 ||
                Key[KEY_INPUT_LSHIFT] == 1 || Key[KEY_INPUT_RSHIFT] == 1 || Key[KEY_INPUT_LCONTROL] == 1 ||
                Key[KEY_INPUT_RCONTROL] == 1 || Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_SPACE] == 1 ||
                Key[KEY_INPUT_PGUP] == 1 || Key[KEY_INPUT_PGDN] == 1 || Key[KEY_INPUT_END] == 1 ||
                Key[KEY_INPUT_HOME] == 1 || Key[KEY_INPUT_LEFT] == 1 || Key[KEY_INPUT_UP] == 1 ||
                Key[KEY_INPUT_RIGHT] == 1 || Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_INSERT] == 1 ||
                Key[KEY_INPUT_DELETE] == 1 || Key[KEY_INPUT_MINUS] == 1 || Key[KEY_INPUT_PREVTRACK] == 1 ||
                Key[KEY_INPUT_PERIOD] == 1 || Key[KEY_INPUT_SLASH] == 1 || Key[KEY_INPUT_LALT] == 1 ||
                Key[KEY_INPUT_RALT] == 1 || Key[KEY_INPUT_SCROLL] == 1 || Key[KEY_INPUT_SEMICOLON] == 1 ||
                Key[KEY_INPUT_COLON] == 1 || Key[KEY_INPUT_LBRACKET] == 1 || Key[KEY_INPUT_RBRACKET] == 1 ||
                Key[KEY_INPUT_AT] == 1 || Key[KEY_INPUT_BACKSLASH] == 1 || Key[KEY_INPUT_COMMA] == 1 ||
                Key[KEY_INPUT_CAPSLOCK] == 1 || Key[KEY_INPUT_PAUSE] == 1 || Key[KEY_INPUT_NUMPAD0] == 1 ||
                Key[KEY_INPUT_NUMPAD1] == 1 || Key[KEY_INPUT_NUMPAD2] == 1 || Key[KEY_INPUT_NUMPAD3] == 1 ||
                Key[KEY_INPUT_NUMPAD4] == 1 || Key[KEY_INPUT_NUMPAD5] == 1 || Key[KEY_INPUT_NUMPAD6] == 1 ||
                Key[KEY_INPUT_NUMPAD7] == 1 || Key[KEY_INPUT_NUMPAD8] == 1 || Key[KEY_INPUT_NUMPAD9] == 1 ||
                Key[KEY_INPUT_MULTIPLY] == 1 || Key[KEY_INPUT_ADD] == 1 || Key[KEY_INPUT_SUBTRACT] == 1 ||
                Key[KEY_INPUT_DECIMAL] == 1 || Key[KEY_INPUT_DIVIDE] == 1 || Key[KEY_INPUT_NUMPADENTER] == 1 ||
                Key[KEY_INPUT_F1] == 1 || Key[KEY_INPUT_F2] == 1 || Key[KEY_INPUT_F3] == 1 ||
                Key[KEY_INPUT_F4] == 1 || Key[KEY_INPUT_F5] == 1 || Key[KEY_INPUT_F6] == 1 ||
                Key[KEY_INPUT_F7] == 1 || Key[KEY_INPUT_F8] == 1 || Key[KEY_INPUT_F9] == 1 ||
                Key[KEY_INPUT_F10] == 1 || Key[KEY_INPUT_F11] == 1 || Key[KEY_INPUT_F12] == 1 ||
                Key[KEY_INPUT_A] == 1 || Key[KEY_INPUT_B] == 1 || Key[KEY_INPUT_C] == 1 ||
                Key[KEY_INPUT_D] == 1 || Key[KEY_INPUT_E] == 1 || Key[KEY_INPUT_F] == 1 ||
                Key[KEY_INPUT_G] == 1 || Key[KEY_INPUT_H] == 1 || Key[KEY_INPUT_I] == 1 ||
                Key[KEY_INPUT_J] == 1 || Key[KEY_INPUT_K] == 1 || Key[KEY_INPUT_L] == 1 ||
                Key[KEY_INPUT_M] == 1 || Key[KEY_INPUT_N] == 1 || Key[KEY_INPUT_O] == 1 ||
                Key[KEY_INPUT_P] == 1 || Key[KEY_INPUT_Q] == 1 || Key[KEY_INPUT_R] == 1 ||
                Key[KEY_INPUT_S] == 1 || Key[KEY_INPUT_T] == 1 || Key[KEY_INPUT_U] == 1 ||
                Key[KEY_INPUT_V] == 1 || Key[KEY_INPUT_W] == 1 || Key[KEY_INPUT_X] == 1 ||
                Key[KEY_INPUT_Y] == 1 || Key[KEY_INPUT_Z] == 1 || Key[KEY_INPUT_0] == 1 ||
                Key[KEY_INPUT_1] == 1 || Key[KEY_INPUT_2] == 1 || Key[KEY_INPUT_3] == 1 ||
                Key[KEY_INPUT_4] == 1 || Key[KEY_INPUT_5] == 1 || Key[KEY_INPUT_6] == 1 ||
                Key[KEY_INPUT_7] == 1 || Key[KEY_INPUT_8] == 1 || Key[KEY_INPUT_9] == 1) {
                break;//키 입력받아서 while문 벗어나는거긴한데... 너무 지저분함
            }
        }
        ClearDrawScreen();
    }
    WrongCount = 10 - accuracy;//10은 반복횟수
    accuracy = accuracy * 100 / 10; //10은 반복횟수
    char WrongCount2[128];
    sprintf_s(WrongCount2, sizeof(WrongCount2), "%d", WrongCount);
    char accuracy2[128];
    sprintf_s(accuracy2, sizeof(accuracy2), "%0.2f", accuracy);
    SetFontSize(17);
    DrawString(220, 240, "accuracy: ", GetColor(255, 255, 255));
    DrawString(310, 240, accuracy2, GetColor(255, 255, 255));
    DrawString(370, 240, "%", GetColor(255, 255, 255));
    DrawString(240, 270, "WrongCount: ", GetColor(255, 51, 51));
    DrawString(360, 270, WrongCount2, GetColor(255, 51, 51));
    ScreenFlip();
    WaitKey();
    gpUpdateKey();
}
typedef struct {
    int x, y; // 좌표 저장용 변수
    char name[128]; // 항목 이름 저장 변수
} MenuElement_t;// 가져온 코드
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);// 기초 설정
    ChangeFont("Comic Sans MS");
    MenuElement_t MenuElement[5] = {
            { 80, 100, "Spot Practice"},
            { 100, 150, "Word Practice"},
            { 100, 200, "Short Writing Practice"},
            { 100, 250, "Long Writing Practice"},
            { 100, 300, "Exit"},
    };
    int SelectNum = 0; // 메뉴 선택 번호
    int SelectNum2 = 0; // 긴글연습의 선택 번호
    int screen = 0; // 창모드, 전체화면 상태를 나타내는 정수
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0){
        int notepad = LoadGraph("notepad.png");
        time_t random = time(NULL); //랜덤숫자 시작 위치 결정 (195738201738....로 이루어진 배열중 시작 위치 결정하는식)
        DrawGraph(-270, -100, notepad, TRUE);
        if (Key[KEY_INPUT_DOWN] == 1){ // 아래 키 눌렀을때 메뉴 제어
            SelectNum = (SelectNum + 1) % 5;
        }
        if (Key[KEY_INPUT_UP] == 1){ // 위 키 눌렀을때 메뉴 제어
            SelectNum = (SelectNum + 4) % 5;
        }
        if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1){
            for (int i = 0; i < 5; i++){
                if (i == SelectNum){
                    MenuElement[i].x = 80; // 선택된 메뉴의 x좌표를 80으로 설정(글 자체가 조금 뒤로 가서 마치 위로 떠있는 듯한 느낌을 줌)
                }
                else{
                    MenuElement[i].x = 100;
                }
            }
        }
        for (int i = 0; i < 5; i++){ // 메뉴 그리기

            DrawFormatString(MenuElement[i].x, MenuElement[i].y, GetColor(0, 0, 0), MenuElement[i].name);
        }
        SetFontSize(35);
        DrawFormatString(110, 20, GetColor(0, 0, 0), "English Typing Practice");// 타이틀 달기
        SetFontSize(17);
        if (screen == 0 && Key[KEY_INPUT_ESCAPE] == 1) { // esc 입력시 프로그램 종료(창모드일때)
            gpUpdateKey();
            break;
        }
        if (Key[KEY_INPUT_F11] == 1) { // f12 입력으로 전체화면으로 변환
            gpUpdateKey();
            ChangeWindowMode(FALSE);
            screen = 1;
        }
        if (screen == 1 && Key[KEY_INPUT_ESCAPE] == 1) { // esc 입력으로 전체화면에서 창모드로 변환
            gpUpdateKey();
            ChangeWindowMode(TRUE);
            screen = 0;
        }
        if (Key[KEY_INPUT_RETURN] == 1){
            if (SelectNum == 0) {
                ClearDrawScreen();
                spot_practice(random);
            }
            else if (SelectNum == 1){
                ClearDrawScreen();
                word_practice(random);
            }
            else if (SelectNum == 2){
                ClearDrawScreen();
                short_writing_practice("short.txt", random);
            }
            else if (SelectNum == 3){// 메뉴 안에 새로운 메뉴(긴글 선택)
                ClearDrawScreen();
                MenuElement_t MenuElement2[5] = {
            { 80, 100, "Daniel Powter - Bad day"},
            { 100, 150, "Hekuto Pascal - fish in the pool"},
            { 100, 200, "Christopher - Bad"},
            { 100, 250, "Lukas Graham - 7 years"},
            { 100, 300, "Back"},
                };
                while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0){
                    DrawGraph(-270, -100, notepad, TRUE);
                    if (Key[KEY_INPUT_DOWN] == 1){
                        SelectNum2 = (SelectNum2 + 1) % 5;
                    }
                    if (Key[KEY_INPUT_UP] == 1){
                        SelectNum2 = (SelectNum2 + 4) % 5;
                    }// 위 아래 키 눌렀을때 메뉴 제어
                    if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_UP] == 1){
                        for (int i = 0; i < 5; i++){
                            if (i == SelectNum2){
                                MenuElement2[i].x = 80; // 선택된 메뉴의 x좌표를 80으로 설정(글 자체가 조금 뒤로 가서 마치 위로 떠있는 듯한 느낌을 줌)
                            }
                            else{
                                MenuElement2[i].x = 100;
                            }
                        }
                    }
                    for (int i = 0; i < 5; i++){ // 메뉴 그리기
                        DrawFormatString(MenuElement2[i].x, MenuElement2[i].y, GetColor(0, 0, 0), MenuElement2[i].name);
                    }
                    if (Key[KEY_INPUT_ESCAPE] == 1){
                        gpUpdateKey();
                        break;
                    }// esc 입력으로 메뉴 화면으로 돌아가기
                    if (Key[KEY_INPUT_RETURN] == 1){
                        if (SelectNum2 == 0) {
                            ClearDrawScreen();
                            long_writing_practice("Daniel Powter - Bad day.txt");
                        }
                        else if (SelectNum2 == 1){
                            ClearDrawScreen();
                            long_writing_practice("Hekuto Pascal - fish in the pool.txt");
                        }
                        else if (SelectNum2 == 2){
                            ClearDrawScreen();
                            long_writing_practice("Christopher - Bad.txt");
                        }
                        else if (SelectNum2 == 3){
                            ClearDrawScreen();
                            long_writing_practice("Lukas Graham - 7 years.txt");
                        }
                        else if (SelectNum2 == 4){
                            break;
                        }
                    }
                }
            }
            else if (SelectNum == 4){
                break;
            }
        }
    }
    DxLib_End();
    return 0;
}