#pragma once
constexpr int TypeSize = 3;

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