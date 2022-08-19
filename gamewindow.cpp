#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QMouseEvent>
#include <QtGui>
#include "figures.h"

class House : public QGraphicsPixmapItem
{
private:
    QPointF coords_for_houses[40];
public:
    House( QGraphicsScene* scene, int value_of_houses );

    void init_house_coords();
    void set_house_on_card(int position);
};

class Hotel : public QGraphicsPixmapItem
{
private:
    QPointF coords_for_hotels[40];
public:
    Hotel( QGraphicsScene* scene );
    void init_hotels_coords();
    void set_hotel_on_card(int position);

};


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    setWindowIcon(QIcon(":/pictures/pictures/Mnply_Icon.jpg"));
    total_value_of_players = 0;
    current_player_move_turn = -1;
    init_map(game_map);

    ui->setupUi(this);
    this->setFixedSize(950, 640); // 950 640

    QPixmap pix(":/pictures/pictures/MnplyMapReworked.png"); //:/pictures/pictures/MnplyMap.png
    ui->map->hide();

    this->setGeometry(125, 20, width(), height());
    this->setWindowModality(Qt::WindowModal);

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(move_ellipse_timer()));
    connect(timer, SIGNAL(timeout()), this, SLOT(move_square_timer()));
    connect(timer, SIGNAL(timeout()), this, SLOT(move_circle_timer()));
    connect(timer, SIGNAL(timeout()), this, SLOT(move_rect_timer()));



    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    pix = pix.scaled(width() - 2, height() - 2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->graphicsView->scene()->addPixmap(pix);


    ui->graphicsView->setFixedSize(width(), height());
    ui->graphicsView->setGeometry(0, 0, width(), height());


    ui->drop_cubes->setGeometry(width()/2 - 60, height() / 4 - 50 , 130, 60);
    ui->drop_cubes->setStyleSheet("background-color: PaleGreen");

    ui->buy_the_card_btn->setStyleSheet("background-color: OliveDrab");
    ui->set_the_house_btn->setStyleSheet("background-color: RoyalBlue");
    ui->set_the_hotel_btn->setStyleSheet("background-color: DarkOrchid");

    ui->set_the_hotel_btn->hide();
    ui->set_the_house_btn->hide();
    ui->buy_the_card_btn->hide();

    value_of_dropped_cubes = 0;

    setMouseTracking(true);


}

void GameWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
}

void GameWindow::set_value_players(int value)
{
    total_value_of_players = value;
    players = new Player[total_value_of_players];
    players_remaining = total_value_of_players;
    return;
}

void GameWindow::input_nicknames(char** names_arr)
{

    for (int i = 0; i < total_value_of_players; i++)
    {
        players[i].set_nickname(names_arr[i]);
        std::cout << players[i].get_nickname() << std::endl;
    }
    return;
}

int GameWindow::remained_players()
{
    return players_remaining;
}

void GameWindow::add_index_player_move()
{
    current_player_move_turn = (current_player_move_turn + 1) % total_value_of_players;
    while(players_remaining != 1 && !players[current_player_move_turn].is_playing())
    {
        current_player_move_turn = (current_player_move_turn + 1) % total_value_of_players;
    }

    return;
}

void GameWindow::init_figures()
{
    Ellipsoid *ellipse = new Ellipsoid;
    //Ellipsoid *ellipse_bar = new Ellipsoid;


    Square *square = new Square;
    //Square *square_bar = new Square;


    Circle *circle = new Circle;
    //Circle *circle_bar = new Circle;

    Rectangloid *rectangle = new Rectangloid;
    //Rectangloid *rectangle_bar = new Rectangloid;



    figures[0] = ellipse;
    figures[1] = square;
    figures[2] = circle;
    figures[3] = rectangle;
}

void GameWindow::on_drop_cubes_clicked()
{
    Ellipsoid *ellipse_bar;
    Square *square_bar;
    Rectangloid *rectangle_bar;
    Circle *circle_bar;


    for (int i = 0; i < total_value_of_players; i++)
    {
        if (players[i].is_bankrot() && players[i].is_playing())
        {
            players_remaining--;
            players[i].set_game_over();
        }
    }


    if (players_remaining == 1)
    {
        QString winner_name;
        for (int i = 0; i <  total_value_of_players; i++)
        {
            if (players[i].is_playing())
            {
                winner_name = QString::fromStdString(players[i].get_nickname());
                break;
            }
        }

        QMessageBox::information(this, "WE HAVE A WINNER!", "CONGRATULATIONS, " + winner_name + ", IS WINNER!!! " );
        this->close();
    }

    if (value_of_dropped_cubes == 0)
    {
        ellipse_bar = new Ellipsoid;
        square_bar = new Square;
        rectangle_bar = new Rectangloid;
        circle_bar = new Circle;
        figure_bars[0] = ellipse_bar;
        figure_bars[1] = square_bar;
        figure_bars[2] = rectangle_bar;
        figure_bars[3] = circle_bar;


        init_figures();
        for (int i = 0; i < total_value_of_players; i++)
        {
            figures[i]->set_figure_on_start(scene);
        }

        ellipse_bar->set_figure_on_bar(scene, QPointF(275, 250));
        ui->first_player_figure->setText("1. " + QString::fromStdString(players[0].get_nickname()));

        square_bar->set_figure_on_bar(scene, QPointF(275, 290));
        ui->second_player_figure->setText("2. " + QString::fromStdString(players[1].get_nickname()));

        if (total_value_of_players >= 3)
        {
             circle_bar->set_figure_on_bar(scene, QPointF(275, 330));
             ui->third_player_figure->setText("3. " + QString::fromStdString(players[2].get_nickname()));
        }

        if (total_value_of_players == 4)
        {
             rectangle_bar->set_figure_on_bar(scene, QPointF(275, 370));
             ui->fourth_player_figure->setText("4. " + QString::fromStdString(players[3].get_nickname()));
        }

    }
    value_of_dropped_cubes++;
    ui->laps->setText(QString::fromStdString(std::to_string(cubes_laps - (value_of_dropped_cubes / total_value_of_players))));

    if(value_of_dropped_cubes > cubes_laps * total_value_of_players)
    {
        QString winner_name = QString::fromStdString(players[0].get_nickname());
        int winner_money_value = players[0].remained_money();

        for(int i = 1; i < total_value_of_players; i++)
        {
            if (players[i].remained_money() > winner_money_value)
            {
                winner_name = QString::fromStdString(players[i].get_nickname());
                winner_money_value = players[i].remained_money();
            }
        }

        for(int i = 0; i < total_value_of_players; i++)
        {
            std::cout << players[i].get_nickname() << " has " << players[i].remained_money() << " money." << std::endl;
        }
        QMessageBox::information(this, "WE HAVE A WINNER!", "CONGRATULATIONS, " + winner_name + ", IS WINNER!!! " );
        this->close();

    }

    add_index_player_move();
    ui->nickname_btn->setText(QString::fromStdString( players[current_player_move_turn].get_nickname()));
    ui->money_btn->setStyleSheet("color: Black");
    ui->money_bar_btn->setStyleSheet("color: Black");
    ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
    int *dropped_nums = nullptr;
    QPixmap *one = new QPixmap(":/pictures/pictures/cube_1.png");
    QPixmap *two = new QPixmap(":/pictures/pictures/cube_2.png");
    QPixmap *three = new QPixmap(":/pictures/pictures/cube_3.png");
    QPixmap *four = new QPixmap(":/pictures/pictures/cube_4.png");
    QPixmap *five = new QPixmap(":/pictures/pictures/cube_5.png");
    QPixmap *six = new QPixmap(":/pictures/pictures/cube_6.png");

    dropped_nums = players[current_player_move_turn].drop_cubes();

    switch (dropped_nums[0])
    {
        case 1:
        {
            ui->first_cube->setPixmap(*one);
            break;
        }
        case 2:
        {
            ui->first_cube->setPixmap(*two);
            break;
        }
        case 3:
        {
            ui->first_cube->setPixmap(*three);
            break;
        }
        case 4:
        {
            ui->first_cube->setPixmap(*four);
            break;
        }
        case 5:
        {
            ui->first_cube->setPixmap(*five);
            break;
        }
        case 6:
        {
            ui->first_cube->setPixmap(*six);
            break;
        }
    }

    switch (dropped_nums[1])
    {
        case 1:
        {
            ui->second_cube->setPixmap(*one);
            break;
        }
        case 2:
        {
            ui->second_cube->setPixmap(*two);
            break;
        }
        case 3:
        {
            ui->second_cube->setPixmap(*three);
            break;
        }
        case 4:
        {
            ui->second_cube->setPixmap(*four);
            break;
        }
        case 5:
        {
            ui->second_cube->setPixmap(*five);
            break;
        }
        case 6:
        {
            ui->second_cube->setPixmap(*six);
            break;
        }
    }

    int last_pos = players[current_player_move_turn].get_map_pos();
    players[current_player_move_turn].add_new_map_place(dropped_nums);
    int new_pos = players[current_player_move_turn].get_map_pos();

    if (new_pos < last_pos)
    {
        players[current_player_move_turn].add_money(200);
        ui->money_btn->setStyleSheet("color: Green");
        ui->money_bar_btn->setStyleSheet("color: Green");
        ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
    }


    ui->drop_cubes->hide();
    ui->set_the_hotel_btn->hide();
    ui->set_the_house_btn->hide();
    ui->buy_the_card_btn->hide();

    switch (current_player_move_turn)
    {
        case 0:
        {
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_square_timer()));
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_circle_timer()));
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_rect_timer()));
            break;
        }
        case 1:
        {
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_ellipse_timer()));
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_circle_timer()));
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_rect_timer()));
            break;
        }
        case 2:
        {
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_ellipse_timer()));
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_square_timer()));
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_rect_timer()));
            break;
        }
        case 3:
        {
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_ellipse_timer()));
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_square_timer()));
            disconnect(timer, SIGNAL(timeout()), this, SLOT(move_circle_timer()));
            break;
        }
    }

    timer->start(5);

    std::cout << players[current_player_move_turn].get_nickname() << " now on the " << players[current_player_move_turn].get_map_pos() << " position." << std::endl;
    std::cout << players[current_player_move_turn].get_nickname() << " staying on the " << game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() << std::endl;
    delete one;
    delete two;
    delete three;
    delete four;
    delete five;
    delete six;
}

void GameWindow::drop_cubes_for_public_clicked()
{
    ui->drop_cubes->hide();
    int *dropped_nums = nullptr;

    dropped_nums = players[current_player_move_turn].drop_cubes();
    QPixmap *one = new QPixmap(":/pictures/pictures/cube_1.png");
    QPixmap *two = new QPixmap(":/pictures/pictures/cube_2.png");
    QPixmap *three = new QPixmap(":/pictures/pictures/cube_3.png");
    QPixmap *four = new QPixmap(":/pictures/pictures/cube_4.png");
    QPixmap *five = new QPixmap(":/pictures/pictures/cube_5.png");
    QPixmap *six = new QPixmap(":/pictures/pictures/cube_6.png");
    switch (dropped_nums[0])
    {
        case 1:
        {
            ui->first_cube->setPixmap(*one);
            break;
        }
        case 2:
        {
            ui->first_cube->setPixmap(*two);
            break;
        }
        case 3:
        {
            ui->first_cube->setPixmap(*three);
            break;
        }
        case 4:
        {
            ui->first_cube->setPixmap(*four);
            break;
        }
        case 5:
        {
            ui->first_cube->setPixmap(*five);
            break;
        }
        case 6:
        {
            ui->first_cube->setPixmap(*six);
            break;
        }
    }

    switch (dropped_nums[1])
    {
        case 1:
        {
            ui->second_cube->setPixmap(*one);
            break;
        }
        case 2:
        {
            ui->second_cube->setPixmap(*two);
            break;
        }
        case 3:
        {
            ui->second_cube->setPixmap(*three);
            break;
        }
        case 4:
        {
            ui->second_cube->setPixmap(*four);
            break;
        }
        case 5:
        {
            ui->second_cube->setPixmap(*five);
            break;
        }
        case 6:
        {
            ui->second_cube->setPixmap(*six);
            break;
        }
    }

    int dropped_summ = dropped_nums[0] + dropped_nums[1];
    delete dropped_nums;
    int coeff = 0;
    if (game_map[12]->has_card_owner() && game_map[28]->has_card_owner())
    {
        if (game_map[12]->get_owner_name() == game_map[28]->get_owner_name())
        {
            coeff = 10;
        }
        else coeff = 4;
    }
    else coeff = 4;

    dropped_summ *= coeff;


    std::string owner_nickname = game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name();



    for (int i  = 0; i < total_value_of_players; i++)
    {
        if (players[i].get_nickname() == owner_nickname && players[i].is_playing())
        {
            players[current_player_move_turn].add_money(-dropped_summ);

//            if (players[current_player_move_turn].is_bankrot())
//            {
//                players_remaining--;
//                players[current_player_move_turn].set_game_over();
//            }

            players[i].add_money(dropped_summ);

        }
        else if (players[i].get_nickname() == owner_nickname && (!players[i].is_playing()))
        {
            break;
        }
    }

    //ui->nicknam_btn->setText(QString::fromStdString( players[current_player_move_turn].get_nickname()));
    ui->money_btn->setStyleSheet("color: Red");
    ui->money_bar_btn->setStyleSheet("color: Red");
    ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");

    connect(ui->drop_cubes, SIGNAL(clicked()), this, SLOT(on_drop_cubes_clicked()));
    disconnect(ui->drop_cubes, SIGNAL(clicked()), this, SLOT(drop_cubes_for_public_clicked()));

    ui->drop_cubes->setStyleSheet("background-color: PaleGreen");
    ui->drop_cubes->show();
    delete one;
    delete two;
    delete three;
    delete four;
    delete five;
    delete six;
    return;
}

GameWindow::~GameWindow()
{
    for (int i = 0; i < 40; i++)
    {
        delete game_map[i];
    }
    for (int i = 0; i < 4; i++)
    {
        delete figures[i];
        delete figure_bars[i];
    }
    for (int i = 0; i < value_bought_cards; i++)
    {
        delete mini_figures_on_bought_cards[i];
    }
    for(int i = 0; i < value_of_houses_on_map; i++)
    {
        delete houses[i];
    }

    for(int i = 0; i < value_of_hotels_on_map; i++)
    {
        delete hotels[i];
    }

    delete timer;
    delete players;

    delete ui;
}

void GameWindow::on_buy_the_card_btn_clicked()
{
//    delete figures[current_player_move_turn];
//    players[current_player_move_turn].add_money(-10000);
//    return;
    ui->buy_the_card_btn->hide();
    bool want_to_buy = true;
    bool set_house = false;
    bool set_hotel = false;
    int last_money_value = players[current_player_move_turn].remained_money();
    int new_money_value;
    int status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);
    new_money_value = players[current_player_move_turn].remained_money();
    //status_code = -4;
    if (status_code == 0)
    {
        if (last_money_value > new_money_value)
        {
            ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
            ui->money_btn->setStyleSheet("color: Red");
            ui->money_bar_btn->setStyleSheet("color: Red");
        }

        //Ставим маленькие иконочки на купленные карты.
        if (current_player_move_turn == 0)
        {
            Ellipsoid *mini_ellipse = new Ellipsoid;
            mini_figures_on_bought_cards[value_bought_cards++] = mini_ellipse;
            mini_ellipse->set_mini_figure_on_card(scene, players[current_player_move_turn].get_map_pos());
        }
        else if (current_player_move_turn == 1)
        {

            Square *mini_square = new Square;
            mini_figures_on_bought_cards[value_bought_cards++] = mini_square;
            mini_square->set_mini_figure_on_card(scene, players[current_player_move_turn].get_map_pos());

        }
        else if (current_player_move_turn == 2)
        {
            Circle *mini_circle = new Circle;
            mini_figures_on_bought_cards[value_bought_cards++] = mini_circle;
            mini_circle->set_mini_figure_on_card(scene, players[current_player_move_turn].get_map_pos());

        }
        else if (current_player_move_turn == 3)
        {
            Rectangloid *mini_rectangle = new Rectangloid;
            mini_figures_on_bought_cards[value_bought_cards++] = mini_rectangle;
            mini_rectangle->set_mini_figure_on_card(scene, players[current_player_move_turn].get_map_pos());
        }
        return;
    }
    else if (status_code == -1) //Ошибка покупки.
    {
        QMessageBox::warning(this, "Money value error.", "You don't have enough money to do this!");
        return;
    }
    return;
}

void GameWindow::move_ellipse_timer()
{

    int timer_stop_checker = figures[0]->set_new_figure_pos(players[current_player_move_turn].get_map_pos());

    bool want_to_buy, set_house, set_hotel;
    int status_code = 0;
    if (timer_stop_checker)
    {
        timer->stop();
        if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Public")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->drop_cubes->show();
                ui->buy_the_card_btn->show();
            }
            else
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

                if (status_code == -4 || status_code == -10) //случай, когда человек попал на предприятие и должен бросить кубики для четырехкратной оплаты владельцу
                {
                    QMessageBox::StandardButton reply = QMessageBox::warning(this, "Public.", "You have to drop cubes and pay" \
                    " dropped summ * " + QString::fromStdString(std::to_string(status_code * -1)) + " to " \
                    + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()));

                    qDebug() << reply;

                    if (reply == QMessageBox::Ok || reply == QMessageBox::Close)
                    {
                        disconnect(ui->drop_cubes, SIGNAL(clicked()), this, SLOT(on_drop_cubes_clicked()));
                        connect(ui->drop_cubes, SIGNAL(clicked()), this, SLOT(drop_cubes_for_public_clicked()));
                        ui->drop_cubes->setStyleSheet("background-color: Crimson");
                    }
                }
            }
        }
        else if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Jail" || game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "GoToJail")
        {
            want_to_buy = false;
            set_house = false;
            set_hotel = false;
            status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

            QMessageBox::warning(this, "JAIL", "You are in Jail, you have to pay 100M.");
            ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
            ui->money_btn->setStyleSheet("color: Red");
            ui->money_bar_btn->setStyleSheet("color: Red");
        }
        else if(game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Railway")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->buy_the_card_btn->show();
            }
            else
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);
                if (status_code == 2)
                {
                    QMessageBox::warning(this, "Railway.", "You have to pay to " + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()) \
                         + " " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
                    ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
                    ui->money_btn->setStyleSheet("color: Red");
                    ui->money_bar_btn->setStyleSheet("color: Red");
                }
            }
        }
        else if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Payment")
        {
            want_to_buy = false;
            set_house = false;
            set_hotel = false;
            game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

            QMessageBox::warning(this, "Payment.", "You have to pay to bank " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
            ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
            ui->money_btn->setStyleSheet("color: Red");
            ui->money_bar_btn->setStyleSheet("color: Red");

        }
        else if(game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Street")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->buy_the_card_btn->show();
            }

            else if (game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name() == players[current_player_move_turn].get_nickname())
            {
                if(game_map[players[current_player_move_turn].get_map_pos()]->is_full_cards_complect())
                {
                    ui->set_the_house_btn->show();
                }
                if (game_map[players[current_player_move_turn].get_map_pos()]->is_full_houses_complect())
                {
                    ui->set_the_house_btn->hide();
                    ui->set_the_hotel_btn->show();
                }

            }
            else if (game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

                if (status_code == 2)
                {
                    QMessageBox::warning(this, "Street rent.", "You have to pay to " + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()) \
                         + " " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
                    ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
                    ui->money_btn->setStyleSheet("color: Red");
                    ui->money_bar_btn->setStyleSheet("color: Red");
                }
            }
        }

        ui->drop_cubes->show();


//        ui->set_the_hotel_btn->show();
//        ui->set_the_house_btn->show();
//        ui->buy_the_card_btn->show();
        connect(timer, SIGNAL(timeout()), this, SLOT(move_square_timer()));
        connect(timer, SIGNAL(timeout()), this, SLOT(move_circle_timer()));
        connect(timer, SIGNAL(timeout()), this, SLOT(move_rect_timer()));
        return;
    }
}

void GameWindow::move_square_timer()
{
    int timer_stop_checker = figures[1]->set_new_figure_pos(players[current_player_move_turn].get_map_pos());


    bool want_to_buy, set_house, set_hotel;
    int status_code = 0;
    if (timer_stop_checker)
    {
        timer->stop();
        if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Public")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->drop_cubes->show();
                ui->buy_the_card_btn->show();
            }
            else
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

                if (status_code == -4 || status_code == -10) //случай, когда человек попал на предприятие и должен бросить кубики для четырехкратной оплаты владельцу
                {
                    QMessageBox::StandardButton reply = QMessageBox::warning(this, "Public.", "You have to drop cubes and pay" \
                    " dropped summ * " + QString::fromStdString(std::to_string(status_code * -1)) + " to " \
                    + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()));

                    qDebug() << reply;

                    if (reply == QMessageBox::Ok || reply == QMessageBox::Close)
                    {
                        disconnect(ui->drop_cubes, SIGNAL(clicked()), this, SLOT(on_drop_cubes_clicked()));
                        connect(ui->drop_cubes, SIGNAL(clicked()), this, SLOT(drop_cubes_for_public_clicked()));
                        ui->drop_cubes->setStyleSheet("background-color: Crimson");
                    }
                }
            }
        }
        else if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Jail" || game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "GoToJail")
        {
            want_to_buy = false;
            set_house = false;
            set_hotel = false;
            status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

            QMessageBox::warning(this, "JAIL", "You are in Jail, you have to pay 100M.");
            ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
            ui->money_btn->setStyleSheet("color: Red");
            ui->money_bar_btn->setStyleSheet("color: Red");
        }
        else if(game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Railway")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->buy_the_card_btn->show();
            }
            else
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);
                if (status_code == 2)
                {
                    QMessageBox::warning(this, "Railway.", "You have to pay to " + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()) \
                         + " " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
                    ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
                    ui->money_btn->setStyleSheet("color: Red");
                    ui->money_bar_btn->setStyleSheet("color: Red");
                }
            }
        }
        else if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Payment")
        {
            want_to_buy = false;
            set_house = false;
            set_hotel = false;
            game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

            QMessageBox::warning(this, "Payment.", "You have to pay to bank " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
            ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
            ui->money_btn->setStyleSheet("color: Red");
            ui->money_bar_btn->setStyleSheet("color: Red");

        }
        else if(game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Street")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->buy_the_card_btn->show();
            }

            else if (game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name() == players[current_player_move_turn].get_nickname())
            {
                if(game_map[players[current_player_move_turn].get_map_pos()]->is_full_cards_complect())
                {
                    ui->set_the_house_btn->show();
                }
                if (game_map[players[current_player_move_turn].get_map_pos()]->is_full_houses_complect())
                {
                    ui->set_the_house_btn->hide();
                    ui->set_the_hotel_btn->show();
                }

            }
            else if (game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

                if (status_code == 2)
                {
                    QMessageBox::warning(this, "Street rent.", "You have to pay to " + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()) \
                         + " " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
                    ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
                    ui->money_btn->setStyleSheet("color: Red");
                    ui->money_bar_btn->setStyleSheet("color: Red");
                }
            }
        }

        ui->drop_cubes->show();

//        ui->set_the_hotel_btn->show();
//        ui->set_the_house_btn->show();
//        ui->buy_the_card_btn->show();
        connect(timer, SIGNAL(timeout()), this, SLOT(move_ellipse_timer()));
        connect(timer, SIGNAL(timeout()), this, SLOT(move_circle_timer()));
        connect(timer, SIGNAL(timeout()), this, SLOT(move_rect_timer()));
        return;
    }
}

void GameWindow::move_circle_timer()
{
    int timer_stop_checker = figures[2]->set_new_figure_pos(players[current_player_move_turn].get_map_pos());

    bool want_to_buy, set_house, set_hotel;
    int status_code = 0;

    if (timer_stop_checker)
    {
        timer->stop();
        if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Public")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->drop_cubes->show();
                ui->buy_the_card_btn->show();
            }
            else
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

                if (status_code == -4 || status_code == -10) //случай, когда человек попал на предприятие и должен бросить кубики для четырехкратной оплаты владельцу
                {
                    QMessageBox::StandardButton reply = QMessageBox::warning(this, "Public.", "You have to drop cubes and pay" \
                    " dropped summ * " + QString::fromStdString(std::to_string(status_code * -1)) + " to " \
                    + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()));

                    qDebug() << reply;

                    if (reply == QMessageBox::Ok || reply == QMessageBox::Close)
                    {
                        disconnect(ui->drop_cubes, SIGNAL(clicked()), this, SLOT(on_drop_cubes_clicked()));
                        connect(ui->drop_cubes, SIGNAL(clicked()), this, SLOT(drop_cubes_for_public_clicked()));
                        ui->drop_cubes->setStyleSheet("background-color: Crimson");
                    }
                }
            }
        }
        else if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Jail" || game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "GoToJail")
        {
            want_to_buy = false;
            set_house = false;
            set_hotel = false;
            status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

            QMessageBox::warning(this, "JAIL", "You are in Jail, you have to pay 100M.");
            ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
            ui->money_btn->setStyleSheet("color: Red");
            ui->money_bar_btn->setStyleSheet("color: Red");
        }
        else if(game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Railway")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->buy_the_card_btn->show();
            }
            else
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);
                if (status_code == 2)
                {
                    QMessageBox::warning(this, "Railway.", "You have to pay to " + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()) \
                         + " " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
                    ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
                    ui->money_btn->setStyleSheet("color: Red");
                    ui->money_bar_btn->setStyleSheet("color: Red");
                }
            }
        }
        else if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Payment")
        {
            want_to_buy = false;
            set_house = false;
            set_hotel = false;
            game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

            QMessageBox::warning(this, "Payment.", "You have to pay to bank " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
            ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
            ui->money_btn->setStyleSheet("color: Red");
            ui->money_bar_btn->setStyleSheet("color: Red");

        }
        else if(game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Street")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->buy_the_card_btn->show();
            }

            else if (game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name() == players[current_player_move_turn].get_nickname())
            {
                if(game_map[players[current_player_move_turn].get_map_pos()]->is_full_cards_complect())
                {
                    ui->set_the_house_btn->show();
                }
                if (game_map[players[current_player_move_turn].get_map_pos()]->is_full_houses_complect())
                {
                    ui->set_the_house_btn->hide();
                    ui->set_the_hotel_btn->show();
                }

            }
            else if (game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

                if (status_code == 2)
                {
                    QMessageBox::warning(this, "Street rent.", "You have to pay to " + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()) \
                         + " " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
                    ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
                    ui->money_btn->setStyleSheet("color: Red");
                    ui->money_bar_btn->setStyleSheet("color: Red");
                }
            }
        }
        ui->drop_cubes->show();

//        ui->set_the_hotel_btn->show();
//        ui->set_the_house_btn->show();
//        ui->buy_the_card_btn->show();
        connect(timer, SIGNAL(timeout()), this, SLOT(move_ellipse_timer()));
        connect(timer, SIGNAL(timeout()), this, SLOT(move_square_timer()));
        connect(timer, SIGNAL(timeout()), this, SLOT(move_rect_timer()));
        return;
    }
}

void GameWindow::move_rect_timer()
{
    int timer_stop_checker = figures[3]->set_new_figure_pos(players[current_player_move_turn].get_map_pos());

    bool want_to_buy, set_house, set_hotel;
    int status_code = 0;
    if (timer_stop_checker)
    {
        timer->stop();
        if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Public")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->drop_cubes->show();
                ui->buy_the_card_btn->show();
            }
            else
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

                if (status_code == -4 || status_code == -10) //случай, когда человек попал на предприятие и должен бросить кубики для четырехкратной оплаты владельцу
                {
                    QMessageBox::StandardButton reply = QMessageBox::warning(this, "Public.", "You have to drop cubes and pay" \
                    " dropped summ * " + QString::fromStdString(std::to_string(status_code * -1)) + " to " \
                    + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()));

                    qDebug() << reply;

                    if (reply == QMessageBox::Ok || reply == QMessageBox::Close)
                    {
                        disconnect(ui->drop_cubes, SIGNAL(clicked()), this, SLOT(on_drop_cubes_clicked()));
                        connect(ui->drop_cubes, SIGNAL(clicked()), this, SLOT(drop_cubes_for_public_clicked()));
                        ui->drop_cubes->setStyleSheet("background-color: Crimson");
                    }
                }
            }
        }
        else if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Jail" || game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "GoToJail")
        {
            want_to_buy = false;
            set_house = false;
            set_hotel = false;
            status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

            QMessageBox::warning(this, "JAIL", "You are in Jail, you have to pay 100M.");
            ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
            ui->money_btn->setStyleSheet("color: Red");
            ui->money_bar_btn->setStyleSheet("color: Red");
        }
        else if(game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Railway")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->buy_the_card_btn->show();
            }
            else
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);
                if (status_code == 2)
                {
                    QMessageBox::warning(this, "Railway.", "You have to pay to " + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()) \
                         + " " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
                    ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
                    ui->money_btn->setStyleSheet("color: Red");
                    ui->money_bar_btn->setStyleSheet("color: Red");
                }
            }
        }
        else if (game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Payment")
        {
            want_to_buy = false;
            set_house = false;
            set_hotel = false;
            game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

            QMessageBox::warning(this, "Payment.", "You have to pay to bank " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
            ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
            ui->money_btn->setStyleSheet("color: Red");
            ui->money_bar_btn->setStyleSheet("color: Red");

        }
        else if(game_map[players[current_player_move_turn].get_map_pos()]->get_type_name() == "Street")
        {
            if (!game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                ui->buy_the_card_btn->show();
            }

            else if (game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name() == players[current_player_move_turn].get_nickname())
            {
                if(game_map[players[current_player_move_turn].get_map_pos()]->is_full_cards_complect())
                {
                    ui->set_the_house_btn->show();
                }
                if (game_map[players[current_player_move_turn].get_map_pos()]->is_full_houses_complect())
                {
                    ui->set_the_house_btn->hide();
                    ui->set_the_hotel_btn->show();
                }

            }
            else if (game_map[players[current_player_move_turn].get_map_pos()]->has_card_owner())
            {
                want_to_buy = false;
                set_house = false;
                set_hotel = false;
                status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);

                if (status_code == 2)
                {
                    QMessageBox::warning(this, "Street rent.", "You have to pay to " + QString::fromStdString(game_map[players[current_player_move_turn].get_map_pos()]->get_owner_name()) \
                         + " " + QString::fromStdString(std::to_string(game_map[players[current_player_move_turn].get_map_pos()]->get_rent_price(players))) + " M");
                    ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
                    ui->money_btn->setStyleSheet("color: Red");
                    ui->money_bar_btn->setStyleSheet("color: Red");
                }
            }
        }
        ui->drop_cubes->show();

        connect(timer, SIGNAL(timeout()), this, SLOT(move_ellipse_timer()));
        connect(timer, SIGNAL(timeout()), this, SLOT(move_square_timer()));
        connect(timer, SIGNAL(timeout()), this, SLOT(move_circle_timer()));
        return;
    }
}




void GameWindow::on_set_the_house_btn_clicked()
{
    ui->set_the_house_btn->hide();
    bool want_to_buy, set_house, set_hotel;
    int status_code = 0;
    want_to_buy = false;
    set_house = true;
    set_hotel = false;

    int last_money_value = players[current_player_move_turn].remained_money();
    int new_money_value;
    status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);
    new_money_value = players[current_player_move_turn].remained_money();

    if (status_code == 0)
    {
        if (last_money_value > new_money_value)
        {
            ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
            ui->money_btn->setStyleSheet("color: Red");
            ui->money_bar_btn->setStyleSheet("color: Red");
            int value_of_houses = game_map[players[current_player_move_turn].get_map_pos()]->get_value_of_houses();

            House *house;
            if(value_of_houses == 1)
            {
               house = new House(scene, 1);
               house->set_house_on_card(players[current_player_move_turn].get_map_pos());
               houses[value_of_houses_on_map++] = house;
            }
            else if(value_of_houses == 2)
            {
                house = new House(scene, 2);
                house->set_house_on_card(players[current_player_move_turn].get_map_pos());
                houses[value_of_houses_on_map++] = house;
            }
            else if(value_of_houses == 3)
            {
                house = new House(scene, 3);
                house->set_house_on_card(players[current_player_move_turn].get_map_pos());
                houses[value_of_houses_on_map++] = house;
            }
            else if(value_of_houses == 4)
            {
                house = new House(scene, 4);
                house->set_house_on_card(players[current_player_move_turn].get_map_pos());
                houses[value_of_houses_on_map++] = house;
            }
        }

        //Ставим маленькие иконочки на купленные карты.
        return;
    }
    else if (status_code == -1) //Ошибка покупки.
    {
        QMessageBox::warning(this, "Money value error.", "You don't have enough money to do this!");
        return;
    }
    return;


}

void GameWindow::on_set_the_hotel_btn_clicked()
{
    ui->set_the_hotel_btn->hide();
    bool want_to_buy, set_house, set_hotel;
    int status_code = 0;
    want_to_buy = false;
    set_house = false;
    set_hotel = true;

    int last_money_value = players[current_player_move_turn].remained_money();
    int new_money_value;
    status_code = game_map[players[current_player_move_turn].get_map_pos()]->action(players[current_player_move_turn], want_to_buy, set_house, set_hotel, players);
    new_money_value = players[current_player_move_turn].remained_money();

    if (status_code == 0)
    {
        if (last_money_value > new_money_value)
        {
            ui->money_btn->setText(QString::fromStdString(std::to_string(players[current_player_move_turn].remained_money())) + " M");
            ui->money_btn->setStyleSheet("color: Red");
            ui->money_bar_btn->setStyleSheet("color: Red");
        }

        Hotel *hotel = new Hotel(scene);
        hotel->set_hotel_on_card(players[current_player_move_turn].get_map_pos());
        hotels[value_of_hotels_on_map++] = hotel;

        //Ставим маленькие иконочки на купленные карты.
        return;
    }

    else if (status_code == -1) //Ошибка покупки.
    {
        QMessageBox::warning(this, "Money value error.", "You don't have enough money to do this!");
        return;
    }
    return;
}






House::House(QGraphicsScene *scene, int value_of_houses)
{
    init_house_coords();
    QPixmap house;
    switch (value_of_houses)
    {
        case 1:
        {
            house = QPixmap(":/pictures/pictures/House_1.png");
            break;
        }
        case 2:
        {
            house = QPixmap(":/pictures/pictures/House_2.png");
            break;
        }
        case 3:
        {
            house = QPixmap(":/pictures/pictures/House_3.png");
            break;
        }
        case 4:
        {
            house = QPixmap(":/pictures/pictures/House_4.png");
            break;
        }
    }

    //QPixmap house(":/pictures/pictures/House.png");
    //house = QPixmap(40, 40);
    house = house.scaled(30, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(house);
    scene->addItem( this );
    //this->setPos(0, 0);
}

void House::init_house_coords()
{
    coords_for_houses[1] = QPointF(777,556);
    coords_for_houses[3] = QPointF(627,557);
    coords_for_houses[6] = QPointF(394,557);
    coords_for_houses[8] = QPointF(238,557);
    coords_for_houses[9] = QPointF(161,557);
    coords_for_houses[11] = QPointF(97,507);
    coords_for_houses[13] = QPointF(97,402);
    coords_for_houses[14] = QPointF(97,352);
    coords_for_houses[16] = QPointF(97,247);
    coords_for_houses[18] = QPointF(97,142);
    coords_for_houses[19] = QPointF(97,90);
    coords_for_houses[21] = QPointF(156,65);
    coords_for_houses[23] = QPointF(311,65);
    coords_for_houses[24] = QPointF(391,65);
    coords_for_houses[26] = QPointF(546,65);
    coords_for_houses[27] = QPointF(626,65);
    coords_for_houses[29] = QPointF(776,65);
    coords_for_houses[31] = QPointF(824,96);
    coords_for_houses[32] = QPointF(824,146);
    coords_for_houses[34] = QPointF(824,246);
    coords_for_houses[37] = QPointF(824,406);
    coords_for_houses[39] = QPointF(824,511);
}

void House::set_house_on_card(int position)
{
    this->setPos(coords_for_houses[position]);
    return;
}

Hotel::Hotel(QGraphicsScene *scene)
{
    init_hotels_coords();

    QPixmap hotel(":/pictures/pictures/Hotel.png");
    hotel = hotel.scaled(40, 33, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(hotel);
    scene->addItem( this );
    //this->setPos(400, 400);

}

void Hotel::init_hotels_coords()
{
    coords_for_hotels[1] = QPointF(773,554);
    coords_for_hotels[3] = QPointF(623,554);
    coords_for_hotels[6] = QPointF(391,554);
    coords_for_hotels[8] = QPointF(234,554);
    coords_for_hotels[9] = QPointF(157,554);
    coords_for_hotels[11] = QPointF(92,503);
    coords_for_hotels[13] = QPointF(92,399);
    coords_for_hotels[14] = QPointF(92,340);
    coords_for_hotels[16] = QPointF(92,243);
    coords_for_hotels[18] = QPointF(92,138);
    coords_for_hotels[19] = QPointF(92,88);
    coords_for_hotels[21] = QPointF(152,61);
    coords_for_hotels[23] = QPointF(306,61);
    coords_for_hotels[24] = QPointF(386,61);
    coords_for_hotels[26] = QPointF(541,61);
    coords_for_hotels[27] = QPointF(621,61);
    coords_for_hotels[29] = QPointF(771,61);
    coords_for_hotels[31] = QPointF(820,93);
    coords_for_hotels[32] = QPointF(820,143);
    coords_for_hotels[34] = QPointF(820,243);
    coords_for_hotels[37] = QPointF(820,403);
    coords_for_hotels[39] = QPointF(820,507);
}

void Hotel::set_hotel_on_card(int position)
{
    this->setPos(coords_for_hotels[position]);
    return;
}
