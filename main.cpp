#include "typing.h"
using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);// 기초 설정
    ChangeFont("Comic Sans MS");
    vector<string> menuNames = { "Spot Practice", "Word Practice", "Short Writing Practice", "Long Writing Practice", "Exit" };
    int menuCnt = menuNames.size();
    int SelectNum = 0; // 메뉴 선택 번호
    int SelectNum2 = 0; // 긴글연습의 선택 번호
    int screen = 0; // 창모드, 전체화면 상태를 나타내는 정수
    int notepad = LoadGraph(resourcePaths.wallpaper.c_str());
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0){
        time_t random = time(NULL); //랜덤숫자 시작 위치 결정 (195738201738....로 이루어진 배열중 시작 위치 결정하는식)
        DrawGraph(-270, -100, notepad, TRUE);
        MoveSelection(SelectNum, menuCnt);
        DrawMenu(menuNames, SelectNum);
        SetFontSize(35);
        DrawString(110, 20, "English Typing Practice", GetColor(0, 0, 0));// 타이틀 달기
        SetFontSize(17);
        if (screen == 0 && Key[KEY_INPUT_ESCAPE] == 1) { // esc 입력시 프로그램 종료(창모드일때)
            gpUpdateKey();
            break;
        }
        if (Key[KEY_INPUT_F11] == 1) { // f11 입력으로 전체화면으로 변환
            gpUpdateKey();
            ChangeWindowMode(FALSE);
            SetDrawScreen(DX_SCREEN_BACK);
            notepad = LoadGraph(resourcePaths.wallpaper.c_str());
            screen = 1;
        }
        if (screen == 1 && Key[KEY_INPUT_ESCAPE] == 1) { // esc 입력으로 전체화면에서 창모드로 변환
            gpUpdateKey();
            ChangeWindowMode(TRUE);
            SetDrawScreen(DX_SCREEN_BACK);
            notepad = LoadGraph(resourcePaths.wallpaper.c_str());
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
                short_writing_practice(resourcePaths.shortWriting, random);
            }
            else if (SelectNum == 3){// 메뉴 안에 새로운 메뉴(긴글 선택)
                ClearDrawScreen();
                long_writing_menu(notepad, SelectNum2);
            }
            else if (SelectNum == 4){
                break;
            }
        }
    }
    DxLib_End();
    return 0;
}