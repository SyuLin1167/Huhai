#pragma once
//�{�^����T�C�Y
constexpr int SelectTypeSize = 3;

//�{�^����
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