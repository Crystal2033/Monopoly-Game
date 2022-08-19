#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "mechanics.h"
#include <QtWidgets>
//#include "figures.h"
class Figure;
class Square;
class Rectangloid;
class Circle;
class Ellipsoid;
class Hotel;
class House;

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    void set_value_players(int value);
    void input_nicknames(char** names_arr);
    int remained_players();
    void add_index_player_move();
    void init_figures();

    //void set_figures_on_start(QGraphicsScene * scene);

    ~GameWindow();

private slots:
    void on_drop_cubes_clicked();
    void drop_cubes_for_public_clicked();

    void move_ellipse_timer();
    void move_square_timer();
    void move_circle_timer();
    void move_rect_timer();
    void on_buy_the_card_btn_clicked();

    void on_set_the_house_btn_clicked();

    void on_set_the_hotel_btn_clicked();

protected:
    int total_value_of_players;
    int players_remaining;
    int current_player_move_turn;
    int value_of_dropped_cubes;
    int cubes_laps = 5;
    QGraphicsScene *scene;
    QTimer *timer;
    Player *players;
    Figure *figures[4];
    Figure *figure_bars[4];
    int value_bought_cards = 0; //для очистки маленьких фигурок на картах.
    Figure *mini_figures_on_bought_cards[28]; //для очистки маленьких фигурок на картах.

    House *houses[88];
    int value_of_houses_on_map = 0;

    Hotel *hotels[22];
    int value_of_hotels_on_map = 0;



    Card *game_map[40];
    Ui::GameWindow *ui;
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // GAMEWINDOW_H
