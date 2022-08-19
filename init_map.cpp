#include "init_map.h"
//проинициализировать мапу.
//class Player;
class Start;


void init_map(Card** game_map)
{
    Start* start = new Start;
    game_map[0] = start;

    Street* zhitnaya = new Street;
    zhitnaya->set_town_name("Zhitnaya");
    zhitnaya->set_value_of_streets_this_color(2);
    zhitnaya->set_purchase_price(60);
    zhitnaya->set_rent_price(2);
    zhitnaya->set_house_price(50);
    zhitnaya->set_rent_with_one_house(10);
    zhitnaya->set_rent_with_two_houses(30);
    zhitnaya->set_rent_with_three_houses(90);
    zhitnaya->set_rent_with_four_houses(160);
    zhitnaya->set_hotel_price(50);
    zhitnaya->set_rent_with_hotel(250);
    game_map[1] = zhitnaya;

    Skip *obshkazna1 = new Skip;
    game_map[2] = obshkazna1;

    Street *nagatinskaya = new Street;
    nagatinskaya->set_town_name("Nagatinskaya");
    nagatinskaya->set_value_of_streets_this_color(2);
    nagatinskaya->set_purchase_price(60);
    nagatinskaya->set_rent_price(4);
    nagatinskaya->set_house_price(50);
    nagatinskaya->set_rent_with_one_house(20);
    nagatinskaya->set_rent_with_two_houses(60);
    nagatinskaya->set_rent_with_three_houses(180);
    nagatinskaya->set_rent_with_four_houses(320);
    nagatinskaya->set_hotel_price(50);
    nagatinskaya->set_rent_with_hotel(450);
    game_map[3] = nagatinskaya;

    Payment *big_tax = new Payment;
    big_tax->set_taxs_price(200);
    game_map[4] = big_tax;

    Railway *rizhskaya = new Railway;
    rizhskaya->set_name_station("Rizhskaya");
    rizhskaya->set_rent_with_one_railway(25);
    rizhskaya->set_rent_with_two_railways(50);
    rizhskaya->set_rent_with_three_railways(100);
    rizhskaya->set_rent_with_four_railways(200);
    game_map[5] = rizhskaya;

    Street *varshavskoe = new Street;
    varshavskoe->set_town_name("Varshavskoe");
    varshavskoe->set_value_of_streets_this_color(3);
    varshavskoe->set_purchase_price(100);
    varshavskoe->set_rent_price(6);
    varshavskoe->set_house_price(50);
    varshavskoe->set_rent_with_one_house(30);
    varshavskoe->set_rent_with_two_houses(90);
    varshavskoe->set_rent_with_three_houses(270);
    varshavskoe->set_rent_with_four_houses(400);
    varshavskoe->set_hotel_price(50);
    varshavskoe->set_rent_with_hotel(550);
    game_map[6] = varshavskoe;

    Skip *chance1 = new Skip;
    game_map[7] = chance1;

    Street *ogarevo = new Street;
    ogarevo->set_town_name("Ogarevo");
    ogarevo->set_value_of_streets_this_color(3);
    ogarevo->set_purchase_price(100);
    ogarevo->set_rent_price(6);
    ogarevo->set_house_price(50);
    ogarevo->set_rent_with_one_house(30);
    ogarevo->set_rent_with_two_houses(90);
    ogarevo->set_rent_with_three_houses(270);
    ogarevo->set_rent_with_four_houses(400);
    ogarevo->set_hotel_price(50);
    ogarevo->set_rent_with_hotel(550);
    game_map[8] = ogarevo;

    Street *parkovaya = new Street;
    parkovaya->set_town_name("Parkovaya");
    parkovaya->set_value_of_streets_this_color(3);
    parkovaya->set_purchase_price(120);
    parkovaya->set_rent_price(8);
    parkovaya->set_house_price(50);
    parkovaya->set_rent_with_one_house(40);
    parkovaya->set_rent_with_two_houses(100);
    parkovaya->set_rent_with_three_houses(300);
    parkovaya->set_rent_with_four_houses(450);
    parkovaya->set_hotel_price(50);
    parkovaya->set_rent_with_hotel(600);
    game_map[9] = parkovaya;

    Jail *jail = new Jail;
    game_map[10] = jail;

    Street *polyanka = new Street;
    polyanka->set_town_name("Polyanka");
    polyanka->set_value_of_streets_this_color(3);
    polyanka->set_purchase_price(140);
    polyanka->set_rent_price(10);
    polyanka->set_house_price(100);
    polyanka->set_rent_with_one_house(50);
    polyanka->set_rent_with_two_houses(150);
    polyanka->set_rent_with_three_houses(450);
    polyanka->set_rent_with_four_houses(625);
    polyanka->set_hotel_price(100);
    polyanka->set_rent_with_hotel(750);
    game_map[11] = polyanka;

    PublicComp *electro = new PublicComp;
    electro->set_type_public("Electrostation");
    game_map[12] = electro;

    Street *sretenka = new Street;
    sretenka->set_town_name("Sretenka");
    sretenka->set_value_of_streets_this_color(3);
    sretenka->set_purchase_price(140);
    sretenka->set_rent_price(10);
    sretenka->set_house_price(100);
    sretenka->set_rent_with_one_house(50);
    sretenka->set_rent_with_two_houses(150);
    sretenka->set_rent_with_three_houses(450);
    sretenka->set_rent_with_four_houses(625);
    sretenka->set_hotel_price(100);
    sretenka->set_rent_with_hotel(750);
    game_map[13] = sretenka;

    Street *rostovskaya = new Street;
    rostovskaya->set_town_name("Rostovskaya");
    rostovskaya->set_value_of_streets_this_color(3);
    rostovskaya->set_purchase_price(160);
    rostovskaya->set_rent_price(12);
    rostovskaya->set_house_price(100);
    rostovskaya->set_rent_with_one_house(60);
    rostovskaya->set_rent_with_two_houses(180);
    rostovskaya->set_rent_with_three_houses(500);
    rostovskaya->set_rent_with_four_houses(700);
    rostovskaya->set_hotel_price(100);
    rostovskaya->set_rent_with_hotel(900);
    game_map[14] = rostovskaya;

    Railway *kurskaya = new Railway;
    kurskaya->set_name_station("Kurskaya");
    kurskaya->set_rent_with_one_railway(25);
    kurskaya->set_rent_with_two_railways(50);
    kurskaya->set_rent_with_three_railways(100);
    kurskaya->set_rent_with_four_railways(200);
    game_map[15] = kurskaya;

    Street *ryazanskiy = new Street;
    ryazanskiy->set_town_name("Ryazanskiy");
    ryazanskiy->set_value_of_streets_this_color(3);
    ryazanskiy->set_purchase_price(180);
    ryazanskiy->set_rent_price(14);
    ryazanskiy->set_house_price(100);
    ryazanskiy->set_rent_with_one_house(70);
    ryazanskiy->set_rent_with_two_houses(200);
    ryazanskiy->set_rent_with_three_houses(550);
    ryazanskiy->set_rent_with_four_houses(750);
    ryazanskiy->set_hotel_price(100);
    ryazanskiy->set_rent_with_hotel(950);
    game_map[16] = ryazanskiy;

    Skip *obshkazna2 = new Skip;
    game_map[17] = obshkazna2;

    Street* vavilova = new Street;
    vavilova->set_town_name("Vavilova");
    vavilova->set_value_of_streets_this_color(3);
    vavilova->set_purchase_price(180);
    vavilova->set_rent_price(14);
    vavilova->set_house_price(100);
    vavilova->set_rent_with_one_house(70);
    vavilova->set_rent_with_two_houses(200);
    vavilova->set_rent_with_three_houses(550);
    vavilova->set_rent_with_four_houses(750);
    vavilova->set_hotel_price(100);
    vavilova->set_rent_with_hotel(950);
    game_map[18] = vavilova;

    Street *rublevskoe = new Street;
    rublevskoe->set_town_name("Rublevskoe");
    rublevskoe->set_value_of_streets_this_color(3);
    rublevskoe->set_purchase_price(200);
    rublevskoe->set_rent_price(14);
    rublevskoe->set_house_price(100);
    rublevskoe->set_rent_with_one_house(70);
    rublevskoe->set_rent_with_two_houses(200);
    rublevskoe->set_rent_with_three_houses(550);
    rublevskoe->set_rent_with_four_houses(750);
    rublevskoe->set_hotel_price(100);
    rublevskoe->set_rent_with_hotel(950);
    game_map[19] = rublevskoe;

    Skip *free_stay = new Skip;
    game_map[20] = free_stay;

    Street *tverskaya = new Street;
    tverskaya->set_town_name("Tverskaya");
    tverskaya->set_value_of_streets_this_color(3);
    tverskaya->set_purchase_price(220);
    tverskaya->set_rent_price(18);
    tverskaya->set_house_price(150);
    tverskaya->set_rent_with_one_house(90);
    tverskaya->set_rent_with_two_houses(250);
    tverskaya->set_rent_with_three_houses(700);
    tverskaya->set_rent_with_four_houses(875);
    tverskaya->set_hotel_price(150);
    tverskaya->set_rent_with_hotel(1050);
    game_map[21] = tverskaya;

    Skip *chance2 = new Skip;
    game_map[22] = chance2;

    Street *pushkinskaya = new Street;
    pushkinskaya->set_town_name("Pushkinskaya");
    pushkinskaya->set_value_of_streets_this_color(3);
    pushkinskaya->set_purchase_price(220);
    pushkinskaya->set_rent_price(18);
    pushkinskaya->set_house_price(150);
    pushkinskaya->set_rent_with_one_house(90);
    pushkinskaya->set_rent_with_two_houses(250);
    pushkinskaya->set_rent_with_three_houses(700);
    pushkinskaya->set_rent_with_four_houses(875);
    pushkinskaya->set_hotel_price(150);
    pushkinskaya->set_rent_with_hotel(1050);
    game_map[23] = pushkinskaya;

    Street *mayakovskogo = new Street;
    mayakovskogo->set_town_name("Mayakovskogo");
    mayakovskogo->set_value_of_streets_this_color(3);
    mayakovskogo->set_purchase_price(240);
    mayakovskogo->set_rent_price(20);
    mayakovskogo->set_house_price(150);
    mayakovskogo->set_rent_with_one_house(100);
    mayakovskogo->set_rent_with_two_houses(300);
    mayakovskogo->set_rent_with_three_houses(750);
    mayakovskogo->set_rent_with_four_houses(925);
    mayakovskogo->set_hotel_price(150);
    mayakovskogo->set_rent_with_hotel(1100);
    game_map[24] = mayakovskogo;

    Railway *kazanskaya = new Railway;
    kazanskaya->set_name_station("Kazanskaya");
    kazanskaya->set_rent_with_one_railway(25);
    kazanskaya->set_rent_with_two_railways(50);
    kazanskaya->set_rent_with_three_railways(100);
    kazanskaya->set_rent_with_four_railways(200);
    game_map[25] = kazanskaya;

    Street *gruzinskiy = new Street;
    gruzinskiy->set_town_name("Gruzinskiy");
    gruzinskiy->set_value_of_streets_this_color(3);
    gruzinskiy->set_purchase_price(260);
    gruzinskiy->set_rent_price(22);
    gruzinskiy->set_house_price(150);
    gruzinskiy->set_rent_with_one_house(110);
    gruzinskiy->set_rent_with_two_houses(330);
    gruzinskiy->set_rent_with_three_houses(800);
    gruzinskiy->set_rent_with_four_houses(975);
    gruzinskiy->set_hotel_price(150);
    gruzinskiy->set_rent_with_hotel(1150);
    game_map[26] = gruzinskiy;

    Street *novinskiy = new Street;
    novinskiy->set_town_name("Novinskiy");
    novinskiy->set_value_of_streets_this_color(3);
    novinskiy->set_purchase_price(260);
    novinskiy->set_rent_price(22);
    novinskiy->set_house_price(150);
    novinskiy->set_rent_with_one_house(110);
    novinskiy->set_rent_with_two_houses(330);
    novinskiy->set_rent_with_three_houses(800);
    novinskiy->set_rent_with_four_houses(975);
    novinskiy->set_hotel_price(150);
    novinskiy->set_rent_with_hotel(1150);
    game_map[27] = novinskiy;

    PublicComp *water = new PublicComp;
    water->set_type_public("Waterstation");
    game_map[28] = water;

    Street *smolenskaya = new Street;
    smolenskaya->set_town_name("Smolenskaya");
    smolenskaya->set_value_of_streets_this_color(3);
    smolenskaya->set_purchase_price(280);
    smolenskaya->set_rent_price(24);
    smolenskaya->set_house_price(150);
    smolenskaya->set_rent_with_one_house(120);
    smolenskaya->set_rent_with_two_houses(360);
    smolenskaya->set_rent_with_three_houses(850);
    smolenskaya->set_rent_with_four_houses(1025);
    smolenskaya->set_hotel_price(150);
    smolenskaya->set_rent_with_hotel(1200);
    game_map[29] = smolenskaya;

    GoToJail *tojail = new GoToJail;
    game_map[30] = tojail;

    Street *shuseva = new Street;
    shuseva->set_town_name("Shuseva");
    shuseva->set_value_of_streets_this_color(3);
    shuseva->set_purchase_price(300);
    shuseva->set_rent_price(26);
    shuseva->set_house_price(200);
    shuseva->set_rent_with_one_house(130);
    shuseva->set_rent_with_two_houses(390);
    shuseva->set_rent_with_three_houses(900);
    shuseva->set_rent_with_four_houses(1100);
    shuseva->set_hotel_price(200);
    shuseva->set_rent_with_hotel(1275);
    game_map[31] = shuseva;

    Street *gogolevskiy = new Street;
    gogolevskiy->set_town_name("Gogolevskiy");
    gogolevskiy->set_value_of_streets_this_color(3);
    gogolevskiy->set_purchase_price(300);
    gogolevskiy->set_rent_price(26);
    gogolevskiy->set_house_price(200);
    gogolevskiy->set_rent_with_one_house(130);
    gogolevskiy->set_rent_with_two_houses(390);
    gogolevskiy->set_rent_with_three_houses(900);
    gogolevskiy->set_rent_with_four_houses(1100);
    gogolevskiy->set_hotel_price(200);
    gogolevskiy->set_rent_with_hotel(1275);
    game_map[32] = gogolevskiy;

    Skip *obshkazna3 = new Skip;
    game_map[33] = obshkazna3;

    Street *kutuzovskiy = new Street;
    kutuzovskiy->set_town_name("Kutuzovskiy");
    kutuzovskiy->set_value_of_streets_this_color(3);
    kutuzovskiy->set_purchase_price(320);
    kutuzovskiy->set_rent_price(28);
    kutuzovskiy->set_house_price(200);
    kutuzovskiy->set_rent_with_one_house(150);
    kutuzovskiy->set_rent_with_two_houses(450);
    kutuzovskiy->set_rent_with_three_houses(1000);
    kutuzovskiy->set_rent_with_four_houses(1200);
    kutuzovskiy->set_hotel_price(200);
    kutuzovskiy->set_rent_with_hotel(1400);
    game_map[34] = kutuzovskiy;

    Railway *leningradskaya = new Railway;
    leningradskaya->set_name_station("Leningradskaya");
    leningradskaya->set_rent_with_one_railway(25);
    leningradskaya->set_rent_with_two_railways(50);
    leningradskaya->set_rent_with_three_railways(100);
    leningradskaya->set_rent_with_four_railways(200);
    game_map[35] = leningradskaya;

    Skip *chance3 = new Skip;
    game_map[36] = chance3;

    Street *bronnaya = new Street;
    bronnaya->set_town_name("Bronnaya");
    bronnaya->set_value_of_streets_this_color(2);
    bronnaya->set_purchase_price(350);
    bronnaya->set_rent_price(35);
    bronnaya->set_house_price(200);
    bronnaya->set_rent_with_one_house(175);
    bronnaya->set_rent_with_two_houses(500);
    bronnaya->set_rent_with_three_houses(1100);
    bronnaya->set_rent_with_four_houses(1300);
    bronnaya->set_hotel_price(200);
    bronnaya->set_rent_with_hotel(1500);
    game_map[37] = bronnaya;

    Payment *small_tax = new Payment;
    small_tax->set_taxs_price(100);
    game_map[38] = small_tax;

    Street *arbat = new Street;
    arbat->set_town_name("Arbat");
    arbat->set_value_of_streets_this_color(2);
    arbat->set_purchase_price(400);
    arbat->set_rent_price(50);
    arbat->set_house_price(200);
    arbat->set_rent_with_one_house(200);
    arbat->set_rent_with_two_houses(600);
    arbat->set_rent_with_three_houses(1400);
    arbat->set_rent_with_four_houses(1700);
    arbat->set_hotel_price(200);
    arbat->set_rent_with_hotel(2000);
    game_map[39] = arbat;


    Street *street_friend[2];
    Railway* station_friend[3];
    PublicComp* friend_card;
    //BROWN
    street_friend[0] = nagatinskaya;
    zhitnaya->set_card_friends(street_friend);

    street_friend[0] = zhitnaya;
    nagatinskaya->set_card_friends(street_friend);

    //LIGHT BLUE
    street_friend[0] = ogarevo;
    street_friend[1] = parkovaya;
    varshavskoe->set_card_friends(street_friend);

    street_friend[0] = ogarevo;
    street_friend[1] = varshavskoe;
    parkovaya->set_card_friends(street_friend);

    street_friend[0] = parkovaya;
    street_friend[1] = varshavskoe;
    ogarevo->set_card_friends(street_friend);

    //PURPLE
    street_friend[0] = sretenka;
    street_friend[1] = rostovskaya;
    polyanka->set_card_friends(street_friend);

    street_friend[0] = polyanka;
    street_friend[1] = rostovskaya;
    sretenka->set_card_friends(street_friend);

    street_friend[0] = polyanka;
    street_friend[1] = sretenka;
    rostovskaya->set_card_friends(street_friend);

    //ORANGE
    street_friend[0] = ryazanskiy;
    street_friend[1] = vavilova;
    rublevskoe->set_card_friends(street_friend);

    street_friend[0] = rublevskoe;
    street_friend[1] = vavilova;
    ryazanskiy->set_card_friends(street_friend);

    street_friend[0] = ryazanskiy;
    street_friend[1] = rublevskoe;
    vavilova->set_card_friends(street_friend);

    //RED
    street_friend[0] = tverskaya;
    street_friend[1] = pushkinskaya;
    mayakovskogo->set_card_friends(street_friend);

    street_friend[0] = mayakovskogo;
    street_friend[1] = pushkinskaya;
    tverskaya->set_card_friends(street_friend);

    street_friend[0] = tverskaya;
    street_friend[1] = mayakovskogo;
    pushkinskaya->set_card_friends(street_friend);

    //YELLOW
    street_friend[0] = gruzinskiy;
    street_friend[1] = novinskiy;
    smolenskaya->set_card_friends(street_friend);

    street_friend[0] = smolenskaya;
    street_friend[1] = novinskiy;
    gruzinskiy->set_card_friends(street_friend);

    street_friend[0] = gruzinskiy;
    street_friend[1] = smolenskaya;
    novinskiy->set_card_friends(street_friend);

    //GREEN
    street_friend[0] = shuseva;
    street_friend[1] = gogolevskiy;
    kutuzovskiy->set_card_friends(street_friend);

    street_friend[0] = shuseva;
    street_friend[1] = kutuzovskiy;
    gogolevskiy->set_card_friends(street_friend);

    street_friend[0] = gogolevskiy;
    street_friend[1] = kutuzovskiy;
    shuseva->set_card_friends(street_friend);

    //DARK BLUE
    street_friend[0] = bronnaya;
    arbat->set_card_friends(street_friend);

    street_friend[0] = arbat;
    bronnaya->set_card_friends(street_friend);

    //STATIONS
    station_friend[0] = rizhskaya;
    station_friend[1] = kurskaya;
    station_friend[2] = kazanskaya;
    leningradskaya->set_card_friends(station_friend);

    station_friend[0] = leningradskaya;
    station_friend[1] = kurskaya;
    station_friend[2] = kazanskaya;
    rizhskaya->set_card_friends(station_friend);

    station_friend[0] = rizhskaya;
    station_friend[1] = leningradskaya;
    station_friend[2] = kazanskaya;
    kurskaya->set_card_friends(station_friend);

    station_friend[0] = rizhskaya;
    station_friend[1] = kurskaya;
    station_friend[2] = leningradskaya;
    kazanskaya->set_card_friends(station_friend); 

    //PUBLIC COMPANIES
    friend_card = water;
    electro->set_friend_card(&friend_card);

    friend_card = electro;
    water->set_friend_card(&friend_card);

}
