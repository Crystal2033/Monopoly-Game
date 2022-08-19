#include "card.h"
#include "player.h"
#include "gamewindow.h"

//void Card::set_type_name(std::string type){type_card = type;};
int Card::action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players)
{
    Q_UNUSED(player);
    Q_UNUSED(want_to_buy);
    Q_UNUSED(set_house);
    Q_UNUSED(set_hotel);
    Q_UNUSED(all_players);
    std::cout << "I`m card" << std::endl;
    return 0;
}

bool Card::has_card_owner()
{
    return false;
}

int Card::get_rent_price(Player *all_players)
{
    Q_UNUSED(all_players);
    return 0;
}

bool Card::is_full_cards_complect()
{
    return false;
}

bool Card::is_full_houses_complect()
{
    return false;
}

int Card::get_value_of_houses()
{
    return 0;
}

std::string Card::get_owner_name() { return "NoOnwner"; }

int Street::action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players)
{

    if (!want_to_buy && !has_owner)
    {
        return 0;
    }

    else if (want_to_buy)
    {
        if (player.is_possible_to_buy(purchase_price))
        {
            player.add_money(-purchase_price);
            set_owner_name(player.get_nickname());
            player.add_cart_in_the_deck(this);
            return 0;
        }
        else return -1;
    }

    else if (set_house)
    {
        if (player.is_possible_to_buy(house_price))
        {
            player.add_money(-house_price);
            value_of_houses++;
            return 0;
        }
        else return -1;
    }

    else if (set_hotel)
    {
        if (player.is_possible_to_buy(hotel_price))
        {
            player.add_money(-hotel_price);
            is_hotel_exist = true;
            value_of_houses = 0;
            return 0;
        }
        else return -1;
    }


    if (has_owner)
    {
        if (is_hotel_exist)
        {
            for (int i = 0; i < 4; i++)
            {
                if (all_players[i].get_nickname() == owner_name && all_players[i].is_playing())
                {
                    player.add_money(-rent_with_hotel);
                    all_players[i].add_money(rent_with_hotel);
                    return 2;
                }
                else if (all_players[i].get_nickname() == owner_name && !all_players[i].is_playing())
                {
                    return 0;
                }
            }
        }

        else if (value_of_houses > 0) // если есть дома.
        {
            for (int i = 0; i < 4; i++)
            {
                if (all_players[i].get_nickname() == owner_name && all_players[i].is_playing())
                {

                    switch (value_of_houses)
                    {
                        case 1:
                        {
                            player.add_money(-rent_with_one_house);
                            all_players[i].add_money(rent_with_one_house);
                            return 2;
                        }
                        case 2:
                        {
                            player.add_money(-rent_with_two_houses);
                            all_players[i].add_money(rent_with_two_houses);
                            return 2;
                        }
                        case 3:
                        {
                            player.add_money(-rent_with_three_houses);
                            all_players[i].add_money(rent_with_three_houses);
                            return 2;
                        }
                        case 4:
                        {
                            player.add_money(-rent_with_four_houses);
                            all_players[i].add_money(rent_with_four_houses);
                            return 2;
                        }
                    }
                }
                else if (all_players[i].get_nickname() == owner_name && !all_players[i].is_playing())
                {
                    return 0;
                }
            }
        }

        else //если нет домов, возможно, имеет все улицы, а возможно и нет.
        {
            int owner_value_of_streets = 1;

            for (int i = 0; i < value_of_streets_this_color - 1; i++)
            {
                if (color_friends[i]->get_owner_name() == owner_name)
                {
                    owner_value_of_streets++;
                }
            }

            if (owner_value_of_streets == value_of_streets_this_color) // Рента X2
            {
                for (int i = 0; i < 4; i++)
                {
                    if (all_players[i].get_nickname() == owner_name && all_players[i].is_playing())
                    {
                        player.add_money(-rent_price*2);
                        all_players[i].add_money(rent_price*2);
                        return 2;

                    }
                    else if(all_players[i].get_nickname() == owner_name && !all_players[i].is_playing())
                    {
                        return 0;
                    }
                }
            }

            else //Рента X1
            {
                for (int i = 0; i < 4; i++)
                {
                    if (all_players[i].get_nickname() == owner_name)
                    {
                        player.add_money(-rent_price);
                        all_players[i].add_money(rent_price);
                        return 2;
                    }

                    else if(all_players[i].get_nickname() == owner_name && !all_players[i].is_playing())
                    {
                        return 0;
                    }
                }
            }
        }

    }



//    std::string ans;
//    std::string player_name;
//    player_name = player.get_nickname();
//    int full_complect = 1;

//    if (has_owner && (owner_name != player_name))
//    {
//        if (is_hotel_exist)
//        {
//            return rent_with_hotel;
//        }
//        else if(value_of_houses > 0) // если есть дома.
//        {
//            switch (value_of_houses)
//            {
//            case 1:
//                return rent_with_one_house;
//            case 2:
//                return rent_with_two_houses;
//            case 3:
//                return rent_with_three_houses;
//            case 4:
//                return rent_with_four_houses;
//            }
//        }
//        else //если нет домов, возможно, имеет все улицы, а возможно и нет.
//        {
//            for (int i = 0; i < value_of_streets_this_color - 1; i++)
//            {
//                if (color_friends[i]->get_owner_name() == owner_name)
//                {
//                    full_complect++;
//                }
//            }
//            if (full_complect == value_of_streets_this_color)
//            {
//                return rent_price * 2;
//            }
//            else
//            {
//                return rent_price;
//            }
//        }
//    }

//    if (!has_owner)
//    {
//        std::cout << "Do you want to buy " << street_name << " street? " << std::endl;
//        std::cin >> ans;
//        if (ans == "y")
//        {
//            if (player.is_possible_to_buy(purchase_price))
//            {
//                player.add_money(-purchase_price);
//                owner_name = player.get_nickname();
//                has_owner = true;
//                player.add_cart_in_the_deck(this);
//            }
//            else
//            {
//                std::cout << "Impossible to buy " << street_name << " street." << std::endl;
//                return 0;
//            }
//        }

//        if (ans == "n")
//        {
//            return 0;
//        }
//    }

//    for (int i = 0; i < value_of_streets_this_color - 1; i++)
//    {
//        if (color_friends[i]->get_owner_name() == player_name)
//        {
//            full_complect++;
//        }
//    }

//    if (full_complect == value_of_streets_this_color)
//    {
//        if (value_of_houses < 4 && !is_hotel_exist)
//        {
//            std::cout << "Do you want to place your " << value_of_houses << "`s house on " << street_name << " street y/n ?" << std::endl;
//            std::cin >> ans;
//            if (ans == "y")
//            {
//                if (player.is_possible_to_buy(house_price))
//                {
//                    player.add_money(-house_price);
//                    value_of_houses++;
//                }
//                else
//                {
//                    std::cout << "Impossible to place house on" << street_name << " street." << std::endl;
//                    return 0;
//                }
//            }
//            else
//                return 0;
//        }
//        if (value_of_houses == 4)
//        {
//            std::cout << "Do you want to place hotel on the " << street_name << " street y/n ?" << std::endl;
//            std::cin >> ans;
//            if (ans == "y")
//            {
//                if (player.is_possible_to_buy(hotel_price))
//                {
//                    player.add_money(-hotel_price);
//                    is_hotel_exist = true;
//                    value_of_houses = 0;
//                }
//                else
//                {
//                    std::cout << "Impossible to place hotel on" << street_name << " street." << std::endl;
//                    return 0;
//                }
//            }
//        }
//    }
   
    return 0;
}

void Street::set_town_name(std::string street) { street_name = street; return; }
void Street::set_owner_name(std::string owner) { owner_name = owner; has_owner = true; return; }
void Street::delete_owner(void) { owner_name = "Unknown"; has_owner = false; return; }
void Street::set_purchase_price(int price){purchase_price = price; return;}
void Street::set_rent_price(int rent){rent_price = rent; return;}
void Street::set_house_price(int price){house_price = price; return;}
void Street::set_rent_with_one_house(int price){rent_with_one_house = price; return;}
void Street::set_rent_with_two_houses(int price){rent_with_two_houses = price; return;}
void Street::set_rent_with_three_houses(int price){rent_with_three_houses = price; return;}
void Street::set_rent_with_four_houses(int price){rent_with_four_houses = price; return;}
void Street::set_hotel_price(int price){hotel_price = price; return;}
void Street::set_rent_with_hotel(int price){rent_with_hotel = price; return;}
void Street::set_value_of_streets_this_color(int value){value_of_streets_this_color = value; return;}

int Street::get_buy_price() { return purchase_price; }
std::string Street::get_owner_name() { return owner_name; }

void Street::set_card_friends(Street** arr_friends)
{
    for (int i = 0; i < value_of_streets_this_color - 1; i++)
    {
        color_friends[i] = arr_friends[i];
    }
    return;
}



int Jail::action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players)
{
    Q_UNUSED(want_to_buy);
    Q_UNUSED(set_house);
    Q_UNUSED(set_hotel);
    Q_UNUSED(all_players);

    player.add_money(-100);
    return 0;
}

bool Jail::has_card_owner()
{
    return false;
}

int Start::action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players) //Просто skip
{
    Q_UNUSED(player);
    Q_UNUSED(want_to_buy);
    Q_UNUSED(set_house);
    Q_UNUSED(set_hotel);
    Q_UNUSED(all_players);
    return 0;
}

int GoToJail::action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players)
{
    Q_UNUSED(want_to_buy);
    Q_UNUSED(set_house);
    Q_UNUSED(set_hotel);
    Q_UNUSED(all_players);
    player.add_money(-100);
    //player.add_new_map_place(10);
    return 0;
}

int Railway::action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players)
{
    Q_UNUSED(set_house);
    Q_UNUSED(set_hotel);

    if (!want_to_buy && !has_owner)
    {
        return 0;
    }

    else if (want_to_buy)
    {
        if (player.is_possible_to_buy(purchase_price))
        {
            set_owner_name(player.get_nickname());
            player.add_money(-purchase_price);
            player.add_value_of_stations();
            return 0;

        }
        else return -1;
    }
    else if (has_owner)
    {
        if (owner_name == player.get_nickname())
        {
            return 0;
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                if (all_players[i].get_nickname() == owner_name && !all_players[i].is_playing())
                {
                    return 0;
                }

                else if (all_players[i].get_nickname() == owner_name && all_players[i].is_playing())
                {
                    switch (all_players[i].get_value_of_stations())
                    {
                        case 1:
                        {
                            player.add_money(-rent_with_one_railway);
                            all_players[i].add_money(rent_with_one_railway);
                            return 2;
                        }

                        case 2:
                        {
                            player.add_money(-rent_with_two_railways);
                            all_players[i].add_money(rent_with_two_railways);
                            return 2;
                        }

                        case 3:
                        {
                            player.add_money(-rent_with_three_railways);
                            all_players[i].add_money(rent_with_three_railways);
                            return 2;
                        }

                        case 4:
                        {
                            player.add_money(-rent_with_four_railways);
                            all_players[i].add_money(rent_with_four_railways);
                            return 2;
                        }

                    }
                }
            }

        }
    }
//    std::string ans;
//    int station_value_of_the_curr_owner;
//    if (!has_owner)
//    {
//        std::cout << "Do you want to buy this railway: " << name_station << " y/n? " << std::endl;
//        std::cin >> ans;
//        if (ans == "y")
//        {
//            if (player.is_possible_to_buy(purchase_price))
//            {
//                owner_name = player.get_nickname();
//                has_owner = true;
//                player.add_money(-purchase_price);
//                player.add_value_of_stations();
//            }
//            else
//            {
//                std::cout << "Impossible to buy " << name_station << " railway." << std::endl;
//                return 0;
//            }
//        }
//    }
//    else if(has_owner)
//    {
//        station_value_of_the_curr_owner = 1;
//        if (owner_name == player.get_nickname())
//        {
//            return 0;
//        }
        
//        for (int i = 0; i < 3; i++)
//        {
//            if (station_friends[i]->get_owner_name() == owner_name)
//            {
//                station_value_of_the_curr_owner++;
//            }
//        }
//        switch (station_value_of_the_curr_owner)
//        {
//        case 1:
//            return rent_with_one_railway;
//        case 2:
//            return rent_with_two_railways;
//        case 3:
//            return rent_with_three_railways;
//        case 4:
//            return rent_with_four_railways;
//        }
        
//    }
    return 0;
}

void Railway::set_owner_name(std::string owner) { owner_name = owner; has_owner = true; return; }
void Railway::set_name_station(std::string name) { name_station = name; return; }
void Railway::set_rent_with_one_railway(int price) { rent_with_one_railway = price; return; }
void Railway::set_rent_with_two_railways(int price) { rent_with_two_railways = price; return; }
void Railway::set_rent_with_three_railways(int price) { rent_with_three_railways = price; return; }
void Railway::set_rent_with_four_railways(int price) { rent_with_four_railways = price; return; }

int Railway::get_buy_price() { return purchase_price; }

bool Railway::has_card_owner()
{
    return has_owner;
}

std::string Railway::get_owner_name() { return owner_name; }


int Railway::get_rent_price(Player *all_players)
{
    for (int i = 0; i < 4; i++)
    {
        if (all_players[i].get_nickname() == owner_name)
        {
            switch (all_players[i].get_value_of_stations())
            {
                case 1:
                {
                    return rent_with_one_railway;
                }
                case 2:
                {
                    return rent_with_two_railways;
                }
                case 3:
                {
                    return rent_with_three_railways;
                }
                case 4:
                {
                    return rent_with_four_railways;
                }
            }
        }
    }
    return 0;
}

bool Railway::is_full_cards_complect()
{
    if (has_owner)
    {
        int full_complect = 1;
        for (int i = 0; i < 3; i++)
        {
            if (station_friends[i]->get_owner_name() == owner_name)
            {
                full_complect++;
            }
        }
        if (full_complect == 4)
        {
            return true;
        }
    }
    return false;
}

bool Railway::is_full_houses_complect()
{
    return false;
}

int Railway::get_value_of_houses()
{
    return 0;
}

void Railway::set_card_friends(Railway** arr_friends)
{
    for (int i = 0; i < 3; i++) //станций всего 4, поэтому дружных будет 3.
    {
        station_friends[i] = arr_friends[i];
    }
    return;
}



int Payment::action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players)
{
    Q_UNUSED(want_to_buy);
    Q_UNUSED(set_house);
    Q_UNUSED(set_hotel);
    Q_UNUSED(all_players);
    player.add_money(-taxs_price);
    return 0;
}

void Payment::set_taxs_price(int price)
{
    taxs_price = price;
    return;
}

bool Payment::has_card_owner()
{
    return false;
}


void PublicComp::set_friend_card(PublicComp** card)
{
    friend_public = *card;
    return;
}

void PublicComp::set_owner_name(std::string owner) { owner_name = owner; has_owner = true; return; }


void PublicComp::set_type_public(std::string type) { type_public = type; return; }

bool PublicComp::has_card_owner()
{
    return has_owner;
}

std::string PublicComp::get_owner_name() { return owner_name; }

int PublicComp::get_rent_price(Player *all_players)
{
    Q_UNUSED(all_players);
    return 0;
}

bool PublicComp::is_full_cards_complect()
{
    if (has_owner)
    {
        if(friend_public->get_owner_name() == owner_name)
        {
            return true;
        }
    }
    return false;
}

bool PublicComp::is_full_houses_complect()
{
    return false;
}

int PublicComp::get_value_of_houses()
{
    return 0;
}

int PublicComp::action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players)
{
    Q_UNUSED(set_hotel);
    Q_UNUSED(set_house;)
    Q_UNUSED(all_players);

    if (!want_to_buy && !has_owner)
    {
        return 0;
    }

    else if (want_to_buy)
    {
        if (player.is_possible_to_buy(buy_price))
        {
            owner_name = player.get_nickname();
            player.add_money(-get_buy_price());
            if (type_public == "Electrostation")
            {
                player.add_electrostation();
                has_owner = true;
                player.add_value_of_public_companies();
            }
            else if (type_public == "Waterstation")
            {
                has_owner = true;
                player.add_waterstation();
                player.add_value_of_public_companies();
            }
            return 0;
        }
        else return -1; //Обработать qmessageBox "You don`t have enough money"
    }

    else if (has_owner)
    {
        for (int i = 0; i < 4; i++)
        {
            if (all_players[i].get_nickname() == owner_name && !all_players[i].is_playing())
            {
                return 0;
            }
            else if (all_players[i].get_nickname() == owner_name && all_players[i].is_playing())
            {
                break;
            }
        }

        if (owner_name == player.get_nickname())
        {
            return 0; //Ничего не происходит.
        }


        if (!friend_public->has_owner)
        {
            return -4; //Мы должны забрать четырехкратную сумму кубиков у того, кто стоит на этой карте и отдать владельцу карты.
        }
        else if(friend_public->has_owner)
        {
            if (owner_name != friend_public->get_owner_name())
            {
                return -4;  //Мы должны забрать четырехкратную сумму кубиков у того, кто стоит на этой карте и отдать владельцу карты.
            }
            else if (owner_name == friend_public->get_owner_name())
            {
                return -10; //Мы должны забрать десятикратную сумму кубиков у того, кто стоит на этой карте и отдать владельцу карты.
            }
        }
    }

    return 0;
}

int PublicComp::get_buy_price()
{
    return buy_price;
}



std::string PublicComp::get_type_public() { return type_public; }

int Skip::action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players)//ничего не делаем, просто пропуск.
{
    Q_UNUSED(player);
    Q_UNUSED(want_to_buy);
    Q_UNUSED(set_house);
    Q_UNUSED(set_hotel);
    Q_UNUSED(all_players);
    return 0;
}

bool Skip::has_card_owner()
{
    return false;
}

//отладка

std::string Card::get_type_name(void)
{
   return type_card;
}

std::string Street::get_type_name(void)
{
    return type_card;
}

bool Street::has_card_owner()
{
    return has_owner;
}

int Street::get_rent_price(Player *all_players)
{
    Q_UNUSED(all_players);

    if (is_hotel_exist)
    {
        return rent_with_hotel;
    }
    else if (is_full_cards_complect() && value_of_houses == 0)
    {
        return rent_price * 2;
    }
    else if (!is_full_cards_complect())
    {
        return rent_price;
    }
    else if(value_of_houses > 0)
    {
        switch (value_of_houses)
        {
            case 1:
            {
                return rent_with_one_house;
            }
            case 2:
            {
                return rent_with_two_houses;
            }
            case 3:
            {
                return rent_with_three_houses;
            }
            case 4:
            {
                return rent_with_four_houses;
            }
        }
    }
    return 0;
}

bool Street::is_full_cards_complect()
{
    if(is_hotel_exist)
    {
        return false;
    }

    if (has_owner)
    {
        int value_of_packed_streets = 1;
        for (int i = 0; i < value_of_streets_this_color - 1; i++)
        {
            if (owner_name == color_friends[i]->get_owner_name())
            {
                value_of_packed_streets++;
            }
        }
        if (value_of_packed_streets == value_of_streets_this_color)
        {
            return true;
        }
    }
    return false;
}

bool Street::is_full_houses_complect()
{
    if (value_of_houses == 4)
    {
        return true;
    }
    return false;
}

int Street::get_value_of_houses()
{
    return value_of_houses;
}

std::string Jail::get_type_name(void)
{
    return type_card;
}

int Jail::get_rent_price(Player *all_players)
{
    Q_UNUSED(all_players);
    return 0;
}

bool Jail::is_full_cards_complect()
{
    return false;
}

bool Jail::is_full_houses_complect()
{
    return false;
}

int Jail::get_value_of_houses()
{
    return 0;
}

std::string Start::get_type_name(void)
{
    return type_card;
}

bool Start::has_card_owner()
{
    return false;
}

int Start::get_rent_price(Player *all_players)
{
    Q_UNUSED(all_players);
    return 0;
}

bool Start::is_full_cards_complect()
{
    return false;
}

bool Start::is_full_houses_complect()
{
    return false;
}

int Start::get_value_of_houses()
{
    return 0;
}

std::string Skip::get_type_name(void)
{
    return type_card;
}

int Skip::get_rent_price(Player *all_players)
{
    Q_UNUSED(all_players);
    return 0;
}

bool Skip::is_full_cards_complect()
{
    return false;
}

bool Skip::is_full_houses_complect()
{
    return false;
}

int Skip::get_value_of_houses()
{
    return 0;
}

std::string PublicComp::get_type_name(void)
{
   return type_card;
}

std::string GoToJail::get_type_name(void)
{
    return type_card;
}

bool GoToJail::has_card_owner()
{
    return false;
}

int GoToJail::get_rent_price(Player *all_players)
{
    Q_UNUSED(all_players);
    return 0;
}

bool GoToJail::is_full_cards_complect()
{
    return false;
}

bool GoToJail::is_full_houses_complect()
{
    return false;
}

int GoToJail::get_value_of_houses()
{
    return 0;
}

std::string Payment::get_type_name(void)
{
    return type_card;
}

int Payment::get_rent_price(Player *all_players)
{
    Q_UNUSED(all_players);
    return taxs_price;
}

bool Payment::is_full_cards_complect()
{
    return false;
}

bool Payment::is_full_houses_complect()
{
    return false;
}

int Payment::get_value_of_houses()
{
    return 0;
}

std::string Railway::get_type_name(void)
{
    return type_card;
}
//отладка

