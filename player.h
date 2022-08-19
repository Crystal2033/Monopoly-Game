#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"

class Player
{
private:
std::string nickname; //имя чела.
int money_value; // количество денег.
Street* player_streets[22]; //карты игрока(улицы).
int value_of_streets; //количество улиц.
int value_of_stations; // количество станций.
int value_of_public_companies;  //количество предприятий.
int map_place;
bool has_electrostation;
bool has_waterstation;
//Card* map_ptr;
bool is_game_over; //Банкрот ли.
//TODO: переменная, чтобы определить, где находится игрок на поле.
//TODO: метод для бросания кубика.

public:
Player()
{
nickname = "Unknown";
money_value = 1500;
value_of_streets = 0;
value_of_stations = 0;
value_of_public_companies = 0;
map_place = 0;
is_game_over = false;
has_electrostation = false;
has_waterstation = false;
}


int* drop_cubes() const;
int* drop_cubes(std::string);
void add_money(int money);
void add_new_map_place(int* dropped_nums);
void add_new_map_place(int pos);
std::string get_nickname() const;
void set_nickname(std::string);
int get_map_pos() const;
int remained_money() const;
bool is_bankrot() const;
void set_game_over();
bool is_possible_to_buy(int buy_price) const;
void add_electrostation();
void add_waterstation();
void add_value_of_streets();
int get_value_of_streets();
int get_value_of_stations();
bool is_playing();
void add_value_of_stations();
void add_value_of_public_companies();
void add_cart_in_the_deck(Street* street);
//void clear_all_realties();

};

#endif // PLAYER_H
