#pragma once
#include "card.h"
#include "init_map.h"
#include "player.h"


#ifndef MECHANICS_H
#define MECHANICS_H


class Mechanics
{
private:
    int players_remaining;
    int whose_turn;
public:
    Mechanics()
    {
        players_remaining = 0;
    }

    void GameMech(Card** game_map, Player* players, const int total_players_value);
    void set_value_players(int value);
    int remained_players();
    int get_whose_turn();
    //void next_turn();
};

#endif // MECHANICS_H
