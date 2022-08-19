#include "player.h"
#include "card.h"
#include <ctime>

int* Player::drop_cubes(void) const
{
    int* dropped_numbers = new int[2];
    for (int i = 0; i < 2; i++) //2, потому что кубика в игре 2.
    {
        dropped_numbers[i] = rand() % 6 + 1;
    }
//    dropped_numbers[0] = 1;
//    dropped_numbers[1] = 0;

    return dropped_numbers;
}

int* Player::drop_cubes(std::string)
{
    int* dropped_numbers = new int[2];


    for (int i = 0; i < 2; i++) //2, потому что кубика в игре 2.
    {
        dropped_numbers[i] = rand() % 6 + 1;
    }
    return dropped_numbers;
}

void Player::set_nickname(std::string name)
{
    nickname = name;
    return;
}

std::string Player::get_nickname() const
{
    return nickname;
}

void Player::add_new_map_place(int* dropped_nums)
{
    std::cout << "Player: " << get_nickname() << " dropped: " << dropped_nums[0] << " and " << dropped_nums[1] << std::endl;
    map_place = (map_place + dropped_nums[0] + dropped_nums[1]) % 40;
    std::cout << get_nickname() << "`s new place is: " << map_place << std::endl;
    delete dropped_nums;
    return;
}



void Player::add_new_map_place(int pos)
{
    map_place = pos;
    return;
}

int Player::get_map_pos() const
{
    return map_place;
}


void Player::add_cart_in_the_deck(Street* street)
{
    player_streets[value_of_streets] = street;
    value_of_streets++;
    return;
}


void Player::add_money(int money)
{
    money_value+=money;
    std::cout << get_nickname() << " now has "<< money_value << " money."<< std::endl;
    return;
}

int Player::remained_money() const //отладочная функция.
{
    return money_value;
}

bool Player::is_bankrot() const
{
    if (money_value <= 0)
    {
        return true;
    }
    return false;
}

bool Player::is_possible_to_buy(int buy_price) const
{
    if (money_value - buy_price < 0)
    {
        return false;
    }
    else return true;
}

void Player::add_electrostation()
{
    has_electrostation = true;
    add_value_of_public_companies();
}

void Player::add_waterstation()
{
    has_waterstation = true;
    add_value_of_public_companies();
}

void Player::add_value_of_streets() { value_of_streets++; return; }
int Player::get_value_of_streets() { return value_of_streets; }

int Player::get_value_of_stations()
{
    return value_of_stations;
}
void Player::add_value_of_stations() { value_of_stations++; return; }
void Player::add_value_of_public_companies() { value_of_public_companies++; return; }


bool Player::is_playing()
{
    return !is_game_over;
}

void Player::set_game_over()
{
    is_game_over = true;
    return;
}
