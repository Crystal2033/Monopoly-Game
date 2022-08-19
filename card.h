#pragma once
#include <iostream>

class Player;

class Card
{
protected:
std::string type_card; //jail, street, station, public_company, chance, public_treasure, other

public:
Card()
{
    type_card = "Unknown";
}

Card(std::string type_name)
{
    type_card = type_name;
}
virtual ~Card()
{
    return;
}

//void set_type_name(std::string type);

virtual std::string get_owner_name();
virtual std::string  get_type_name(void);
virtual int action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players);
virtual bool has_card_owner();
virtual int get_rent_price(Player *all_players);

virtual bool is_full_cards_complect(); //Для улицы
virtual bool is_full_houses_complect(); //Для улицы
virtual int get_value_of_houses();
};


class Street : public Card
{
protected:
    std::string street_name; //имя улицы.
    std::string owner_name;// имя владельца.
    bool has_owner; //На случай, если чел захочет назваться "Unknown".
    int purchase_price; //стоимость покупки улицы.
    int rent_price; //стоимость ренты.
    int value_of_houses; // количество домов на этой улице.
    int house_price; // цена дома.
    int rent_with_one_house;
    int rent_with_two_houses;
    int rent_with_three_houses;
    int rent_with_four_houses;
    int hotel_price; // цена отеля.
    int rent_with_hotel;
    int value_of_streets_this_color; // количество карт данного цвета.
    Street* color_friends[2]; // указатели на карты этого цвета(братские карты)
    bool is_hotel_exist; // существует ли отель

public:

Street()
{
    type_card = "Street";
    street_name = "Unknown";
    owner_name = "Unknown";
    has_owner = false;
    purchase_price = 0;
    rent_price = 0;
    house_price = 0;
    rent_with_one_house = 0;
    rent_with_two_houses = 0;
    rent_with_three_houses = 0;
    rent_with_four_houses = 0;
    rent_with_hotel = 0;
    hotel_price = 0;
    value_of_streets_this_color = 0;

    value_of_houses = 0;
    is_hotel_exist = false;
    //TODO: сделать конструктор.
}

~Street()
{
    return;
}

int action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players); //действие для улицы, дописать.

void set_town_name(std::string street);
void set_owner_name(std::string owner);
void delete_owner();
void set_purchase_price(int price);
void set_rent_price(int rent);
void set_house_price(int price);
void set_hotel_price(int price);
void set_value_of_streets_this_color(int value);
void set_card_friends(Street** arr_friends);
void set_rent_with_one_house(int price);
void set_rent_with_two_houses(int price);
void set_rent_with_three_houses(int price);
void set_rent_with_four_houses(int price);
void set_rent_with_hotel(int price);

std::string get_owner_name();
int get_buy_price();
std::string  get_type_name();
bool has_card_owner();
int get_rent_price(Player *all_players);
bool is_full_cards_complect(); //Для улицы
bool is_full_houses_complect(); //Для улицы
int get_value_of_houses();
//void change_hotel_availability(void){is_hotel_exist = true;};
//# TODO: доделать еще выкупную стоимость и возможность заложить карту и получить деньги за нее.

};

class Jail : public Card
{
public:
    int action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players); //действие для тюрьмы, дописать.
    bool has_card_owner();
    std::string  get_type_name(void);
    int get_rent_price(Player *all_players);
    bool is_full_cards_complect(); //Для улицы
    bool is_full_houses_complect(); //Для улицы
    int get_value_of_houses();

Jail()
{
    type_card = "Jail";
}

~Jail()
{
    return;
}
};


class Start : public Card
{
public:
    int action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players); //действие для начальной карты, дописать.

    std::string  get_type_name(void);
    bool has_card_owner();
    int get_rent_price(Player *all_players);
    bool is_full_cards_complect(); //Для улицы
    bool is_full_houses_complect(); //Для улицы
    int get_value_of_houses();

Start()
{
    type_card = "Start";
}

~Start()
{
    return;
}
};

class GoToJail: public Card
{
public:
    int action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players); //действие для карты иди в тюрьму, дописать.

    std::string  get_type_name(void);
    bool has_card_owner();
    int get_rent_price(Player *all_players);
    bool is_full_cards_complect(); //Для улицы
    bool is_full_houses_complect(); //Для улицы
    int get_value_of_houses();

GoToJail()
{
    type_card = "GoToJail";
}

~GoToJail()
{
    return;
}
};

class Railway: public Card
{
protected:
    std::string owner_name;
    bool has_owner;
    std::string name_station;
    int purchase_price;
    int rent_with_one_railway;
    int rent_with_two_railways;
    int rent_with_three_railways;
    int rent_with_four_railways;
    Railway* station_friends[3];

public:
    int action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players); //действие для ЖД, дописать.
    void set_owner_name(std::string owner);
    void set_name_station(std::string name);
    void set_rent_with_one_railway(int price);
    void set_rent_with_two_railways(int price);
    void set_rent_with_three_railways(int price);
    void set_rent_with_four_railways(int price);
    void set_card_friends(Railway** arr_friends);
    int get_buy_price();

    bool has_card_owner();
    std::string  get_type_name(void);
    std::string get_owner_name();
    int get_rent_price(Player *all_players);
    bool is_full_cards_complect(); //Для улицы
    bool is_full_houses_complect(); //Для улицы
    int get_value_of_houses();

Railway()
{

    type_card = "Railway";
    owner_name = "Unknown";
    has_owner = false;
    name_station = "Unknown";
    purchase_price = 200;
    rent_with_one_railway = 0;
    rent_with_two_railways = 0;
    rent_with_three_railways = 0;
    rent_with_four_railways = 0;
}

~Railway()
{
    return;
}
};

class Payment: public Card
{
protected:
int taxs_price;
public:
    int action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players); //действие для заплати налог, дописать.
    void set_taxs_price(int price);

    bool has_card_owner();
    std::string  get_type_name(void);
    int get_rent_price(Player *all_players);
    bool is_full_cards_complect(); //Для улицы
    bool is_full_houses_complect(); //Для улицы
    int get_value_of_houses();

Payment()
{
    taxs_price = 0;
    type_card = "Payment";
}

~Payment()
{
    return;
}
};

class PublicComp : public Card
{
protected:
    std::string owner_name;
    std::string type_public;
    bool has_owner;
    int buy_price;
    PublicComp* friend_public;
public:
    int action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players); //действие для электростанции, дописать.
    void set_owner_name(std::string owner);
    int get_buy_price();
    std::string  get_type_name(void); 
    void set_friend_card(PublicComp** card);
    void set_type_public(std::string type);

    bool has_card_owner();
    std::string get_type_public(); //electro or water
    std::string get_owner_name();
    int get_rent_price(Player *all_players);
    bool is_full_cards_complect(); //Для улицы
    bool is_full_houses_complect(); //Для улицы
    int get_value_of_houses();

    PublicComp()
    {
        type_card = "Public";
        type_public = "Unknown";
        owner_name = "Unknown";
        has_owner = false;
        buy_price = 150;
    }
    ~PublicComp()
    {
        return;
    }
};

class Skip : public Card
{
public:
    int action(Player & player, bool want_to_buy, bool set_house, bool set_hotel, Player * all_players);
    bool has_card_owner();
    std::string  get_type_name(void);
    int get_rent_price(Player *all_players);
    bool is_full_cards_complect(); //Для улицы
    bool is_full_houses_complect(); //Для улицы
    int get_value_of_houses();

Skip()
{
    type_card = "Skip";
}
~Skip()
{
    return;
}
};


