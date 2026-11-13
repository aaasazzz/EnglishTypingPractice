#pragma once
#include "DxLib.h"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

struct LongText {
    std::string title;
    std::string filePath;
};

struct ResourcePaths{
    std::string wallpaper = "resources/notepad.png";
    std::string words = "resources/words.txt";
    std::string shortWriting = "resources/short.txt";
    std::vector<LongText> longWriting = {
        { "Alice's Adventures in Wonderland", "resources/long_writing/Alice's Adventures in Wonderland.txt" },
        { "Peter Pan", "resources/long_writing/Peter Pan.txt" },
        { "The Wonderful Wizard of Oz", "resources/long_writing/The Wonderful Wizard of Oz.txt" },
    };
};

extern const ResourcePaths resourcePaths;

extern int Key[256]; // 키가 눌러진 프레임 수를 저장한다

void ClearPendingInput();
std::vector<std::string> LoadLines(std::string path);
void MoveSelection(int& select, int count);
int gpUpdateKey();
void long_writing_practice(std::string a);
void short_writing_practice(std::string a, int b);
void spot_practice(int a);
void word_practice(int a);
void DrawMenu(std::vector<std::string> items, int select);
void long_writing_menu(int notepad, int& select);
