#include "mechanics.h"
#include <cstring>
#include <string>


void Mechanics::GameMech(Card** game_map, Player* players, const int total_players_value)
{
    /*Card* game_map[40];
    init_map(game_map);

    int players_value = 0;
    std::cout << "Input value of players: " << std::endl;
    std::cin >> players_value;
    players_remaining = players_value;

    Player *players = new Player[players_value];
    std::string input_name;
    for (int i = 0; i < players_value; i++)
    {
        std::cout << "Input your nickname without spaces." << std::endl;
        std::cin >> input_name;
        players[i].set_nickname(input_name);
    }*/

    int* dropped_nums;
    int last_pos, new_pos; //penalty_counter = 0;
    int rent_price; //0 - without rent, > 0 need to pay rent (returned rent)
    std::string card_owner;
    for (int i = 0; i < total_players_value; i++)
    {
        if (players[i].is_bankrot())
        {
            continue;
        }
        dropped_nums = players[i].drop_cubes();

//        if (dropped_nums[0] == 0)
//        {
//            while (dropped_nums[0] == 0)
//            {
//                penalty_counter++;
//                std::cout << players[i].get_nickname() << " has got double, reroll please!" << std::endl;

//                if (penalty_counter == 3) //Если у чела три раза выпал дубль на костях, то чел идет в тьюрьму.s
//                {
//                    players[i].add_new_map_place(10);
//                    new_pos = players[i].get_map_pos();
//                    std::cout << players[i].get_nickname() << " stand on " << game_map[new_pos]->get_type_name() << std::endl;
//                    game_map[new_pos]->action(players[i]);

//                   /* if (players[i].is_bankrot())
//                    {
//                        players_remaining--;
//                        players[i].set_game_over();
//                        if (players_remaining == 1)
//                        {
//                            return;
//                        }
//                    }*/

//                    break;
//                }

//                dropped_nums = players[i].drop_cubes(); //Перебрасывает кубики.
//                if (dropped_nums[0] != 0)
//                {
//                    penalty_counter = 0;
//                    break;
//                }
//                continue;
//            }
//        }  // это все на случай выпадения дубля.
//        if (penalty_counter == 3)
//        {
//            penalty_counter = 0;
//            continue;
//        } // // это все на случай выпадения дубля.


        last_pos = players[i].get_map_pos();
        players[i].add_new_map_place(dropped_nums);
        //ACTION.
        new_pos = players[i].get_map_pos();
        if (new_pos < last_pos)
        {
            players[i].add_money(200); //За проход начала полагается +200;
        }

        rent_price = game_map[new_pos]->action(players[i], true, false, false, players);
        if (rent_price != 0) //кто-то должен заплатить ренту.
        {
            if (!players[i].is_possible_to_buy(rent_price)) //если игрок способен заплатить, то платит, иначе у него забирают оставшиеся деньги и отдают тому, кому надо было заплатить.
            {
                rent_price = players[i].remained_money();
            }
            players[i].add_money(-rent_price);
            /*if (players[i].is_bankrot())
            {
                players[i].set_game_over();
                players_remaining--;
                if (players_remaining == 1)
                {
                    return;
                }
            }*/

            card_owner = game_map[new_pos]->get_owner_name();
            for (int j = 0; j < total_players_value; j++)
            {
                if (players[j].is_bankrot())
                {
                    continue;
                }
                if (players[j].get_nickname() == card_owner)
                {
                    players[j].add_money(rent_price);
                    break;
                }
            }
        }

        std::cout << std::endl;
        //std::cout << players[i].get_nickname() << " stand on " << game_map[new_pos]->get_type_name() << std::endl;
        //penalty_counter = 0;
    }

    for (int i = 0; i < total_players_value; i++)
    {
        if (players[i].is_bankrot() && (players[i].is_playing()))
        {
            players[i].set_game_over();
            players_remaining--;
        }
    }

    /*for (int i = 0; i < 40; i++)
    {
        delete game_map[i];
    }
    delete[] players;*/
}

void Mechanics::set_value_players(int value)
{
    players_remaining = value;
    return;
}

int Mechanics::remained_players()
{
    return players_remaining;
}

int Mechanics::get_whose_turn()
{
    return whose_turn;
}

//void Mechanics::next_turn()
//{

//}
