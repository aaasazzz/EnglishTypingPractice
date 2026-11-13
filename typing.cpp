#include "typing.h"
using namespace std;

struct SpotKey {
    char c;
    int key;
    int numpadKey; //numpadKey처리를 위한 변수 (숫자 아니면 -1)
};

const SpotKey spotKeyList[] = {
    { 'q', KEY_INPUT_Q, -1 }, { 'w', KEY_INPUT_W, -1 }, { 'e', KEY_INPUT_E, -1 }, { 'r', KEY_INPUT_R, -1 },
    { 't', KEY_INPUT_T, -1 }, { 'y', KEY_INPUT_Y, -1 }, { 'u', KEY_INPUT_U, -1 }, { 'i', KEY_INPUT_I, -1 },
    { 'o', KEY_INPUT_O, -1 }, { 'p', KEY_INPUT_P, -1 }, { 'a', KEY_INPUT_A, -1 }, { 's', KEY_INPUT_S, -1 }, 
    { 'd', KEY_INPUT_D, -1 }, { 'f', KEY_INPUT_F, -1 }, { 'g', KEY_INPUT_G, -1 }, { 'h', KEY_INPUT_H, -1 }, 
    { 'j', KEY_INPUT_J, -1 }, { 'k', KEY_INPUT_K, -1 }, { 'l', KEY_INPUT_L, -1 }, { 'z', KEY_INPUT_Z, -1 },
    { 'x', KEY_INPUT_X, -1 }, { 'c', KEY_INPUT_C, -1 }, { 'v', KEY_INPUT_V, -1 }, { 'b', KEY_INPUT_B, -1 }, 
    { 'n', KEY_INPUT_N, -1 }, { 'm', KEY_INPUT_M, -1 },
    { '1', KEY_INPUT_1, KEY_INPUT_NUMPAD1 }, { '2', KEY_INPUT_2, KEY_INPUT_NUMPAD2 },
    { '3', KEY_INPUT_3, KEY_INPUT_NUMPAD3 }, { '4', KEY_INPUT_4, KEY_INPUT_NUMPAD4 },
    { '5', KEY_INPUT_5, KEY_INPUT_NUMPAD5 }, { '6', KEY_INPUT_6, KEY_INPUT_NUMPAD6 },
    { '7', KEY_INPUT_7, KEY_INPUT_NUMPAD7 }, { '8', KEY_INPUT_8, KEY_INPUT_NUMPAD8 },
    { '9', KEY_INPUT_9, KEY_INPUT_NUMPAD9 }, { '0', KEY_INPUT_0, KEY_INPUT_NUMPAD0 },
};

int Key[256]; // 키가 눌러진 프레임 수를 저장한다
const ResourcePaths resourcePaths;

void ClearPendingInput() {
    while (CheckHitKey(KEY_INPUT_RETURN) != 0) {
        if (ProcessMessage() != 0) return;
    }
    ProcessMessage();
    ClearInputCharBuf();
}

vector<string> LoadLines(string path) {
    vector<string> lines;
    int handle = FileRead_open(path.c_str());
    char buffer[256];
    while (FileRead_eof(handle) == 0) {
        FileRead_gets(buffer, sizeof(buffer) - 1, handle);
        lines.push_back(buffer);
    }
    FileRead_close(handle);
    return lines;
}

void MoveSelection(int& select, int count) {
    if (Key[KEY_INPUT_DOWN] == 1) select = (select + 1) % count;
    if (Key[KEY_INPUT_UP] == 1) select = (select + count - 1) % count;
}

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
    int wrong_count = 0;
    float accuracy = 0;//정확도를 구하는데 필요한 변수
    char type_per_min2[128];//2 붙은 것들은 출력을 위해 자료형을 변환시켜준 것들
    char real_accuracy2[128];
    float real_accuracy;
    double type_per_min;

    vector<string> lines = LoadLines(a);
    time_t start, end;
    start = time(NULL);
    int Wy = 0;//문장들이 출력되는 위치를 조정하는 변수(y값)
    int roof = 0;//화면 밖으로 넘어가는걸 방지
    int next = 0;//한 화면이 끝난 뒤 계속할지를 정하는 변수
    for(string line : lines) {
        if(roof == 23){
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
            if(Key[KEY_INPUT_ESCAPE] == 1){
                next = 1;
                break;
            }
        }
        DrawString(0, Wy, line.c_str(), GetColor(255, 255, 255));//써야되는 문장 출력
        ClearPendingInput();
        KeyInputString(0, Wy + 20, sizeof(input)-1, input, FALSE);//문장 쓰는거 입력
        int size = (int)line.size();
        accuracy += size;
        for (int i = 0; i < size; i++) {//틀린계수 세기
            if (strlen(input) == 0) {
                wrong_count += size;
                DrawString(0, Wy, line.c_str(), GetColor(255, 51, 51));
                break;
            }
            else if (input[i] != line[i]) {
                wrong_count++;
                DrawString(0, Wy, line.c_str(), GetColor(255, 51, 51));
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
    if (next == 0) {
        ScreenFlip();
        WaitKey();
    }//계속하기 원하면 그대로 진행하고 종료 원하면 메뉴화면으로 나가기
    gpUpdateKey();
}

void short_writing_practice(string a, int b) {
    char input[128];
    time_t start, end;
    int Wy = 0;
    float type_per_min;
    vector<string> lines = LoadLines(a);
    SRand(b);
    for (int j = 0; j < 1; j) {//메인 실행 for문
        float wrong_count = 0;
        int ran = GetRand(lines.size() - 1);//랜덤으로 문장 고르기
        string target = lines[ran];
        DrawString(0, Wy, target.c_str(), GetColor(255, 255, 255));//써야되는 문장 출력
        start = time(NULL);
        ClearPendingInput();
        KeyInputString(0, Wy + 20, sizeof(input)-1, input, FALSE);//문장 쓰는거 입력
        int wordsize = target.size();
        for (int i = 0; i < wordsize; i++) {
            if (input[i] != target[i]) wrong_count++;
        }
        //타이핑 끝난 시점이니 결과창 도출
        end = time(NULL);
        float real_accuracy = ((wordsize - wrong_count) / wordsize) * 100;//진짜 정확도
        type_per_min = target.size() * (60 / (double)(end - start));
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
        WaitKey();
        ClearDrawScreen();
        gpUpdateKey();
        if (Key[KEY_INPUT_ESCAPE] == 1) break;//esc눌러서 메뉴로 나가기
    }
}

void word_practice(int a) {
    char input[128];
    int wrong_count = 0;
    int correct = 0;//현재 맞은 개수(실행중 표시해주기 위한)
    int Wy = 0;
    vector<string> lines = LoadLines(resourcePaths.words);
    SRand(a);
    for (int j = 0; j < 10; j++) {
        int ran = GetRand(lines.size() - 1);
        string target = lines[ran];
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
        DrawString(200, 168, target.c_str(), GetColor(255, 255, 255));//써야되는 문장 출력
        ClearPendingInput();
        KeyInputString(200, 232, sizeof(input)-1, input, FALSE);//문장 쓰는거 입력
        ClearDrawScreen();
        int wordsize = target.size();
        int wrong = 0;
        for (int i = 0; i < wordsize; i++) {//틀린 개수 세기(한글자라도 틀리면 틀림)
            if (input[i] != target[i]) {
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
    WaitKey();
    gpUpdateKey();
}

void spot_practice(int a) {
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
        int count = sizeof(spotKeyList) / sizeof(spotKeyList[0]);
        SpotKey spotKey = spotKeyList[GetRand(count - 1)];
        SetFontSize(64);
        DrawString(280, 200, string(1, spotKey.c).c_str(), GetColor(255, 255, 255));
        while (ScreenFlip() == 0 && ProcessMessage() == 0 && gpUpdateKey() == 0) {
            if (Key[spotKey.key] == 1 || (spotKey.numpadKey != -1 && Key[spotKey.numpadKey] == 1)) accuracy += 1;
            bool escape_flag = false;
            for (int k = 0; k < 256; k++) {
                if (Key[k] == 1){
                    escape_flag = true; 
                    break;
                }
            }
            if (escape_flag) break;
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

void DrawMenu(vector<string> items, int select){
    for (int i = 0;i<items.size();i++){
        int x;
        if(i == select) x = 80;
        else x = 100;
        int y = 100 + i * 50;
        DrawFormatString(x, y, GetColor(0, 0, 0), items[i].c_str());
    }
}

void long_writing_menu(int notepad, int& select){
    vector<string> longWritingMenuNames;
    for(int i = 0; i<resourcePaths.longWriting.size();i++){
        longWritingMenuNames.push_back(resourcePaths.longWriting[i].title);
    }
    longWritingMenuNames.push_back("Back");
    int itemCnt = longWritingMenuNames.size();
    while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0){
        DrawGraph(-270, -100, notepad, TRUE);
        MoveSelection(select, itemCnt);
        DrawMenu(longWritingMenuNames, select);
        if (Key[KEY_INPUT_ESCAPE] == 1){
            gpUpdateKey();
            break;
        }// esc 입력으로 메뉴 화면으로 돌아가기
        if (Key[KEY_INPUT_RETURN] == 1) {
            if (select < itemCnt - 1) {
                ClearDrawScreen();
                long_writing_practice(resourcePaths.longWriting[select].filePath);
            }
            else if (select == itemCnt - 1) {
                break;
            }
        }
    }
}