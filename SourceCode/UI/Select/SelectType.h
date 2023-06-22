#pragma once
//ボタン種サイズ
constexpr int SelectTypeSize = 3;

//ボタン種
enum SelectType:unsigned int
{
    PLAY = 0,
    LOAD,
    EXIT,
};

constexpr SelectType selectTypeAll[] =
{
    SelectType::PLAY,
    SelectType::LOAD,
    SelectType::EXIT,
};