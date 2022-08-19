#ifndef FIGURE_H
#define FIGURE_H
#include "gamewindow.h"


class Figure //: protected GameWindow
{
public:
    Figure();
    int width = 0;
    int height = 0;
    QPen *blackPen = new QPen(Qt::black);
    QBrush *brush;
    virtual int set_new_figure_pos(int position);
    virtual void set_figure_on_start(QGraphicsScene* scn);
    virtual void set_figure_on_bar(QGraphicsScene* scn, QPointF pos);
    virtual void set_mini_figure_on_card(QGraphicsScene* scn, int card_index);
    void init_mini_figures_coords();
    QPointF current_point_pos;
    QPointF current_point_pos_for_next;
    int temp_pos;
    int speed = 2;
    int current_index = 0;
    QPointF coords_mini_fugures_on_cards[40]; // 40, потому что мы не сможем в противном случае найти нужную координату.
   virtual ~Figure()
    {
        delete brush;
        delete blackPen;
    }

};

class Ellipsoid : public Figure
{
private:
    QGraphicsEllipseItem *ellipse_item;
    QPointF ellipse_points[40];
    //QBrush *yellowBrush = new QBrush(Qt::yellow);
    int current_ell_index;

//    QPointF current_point_pos;
//    QPointF current_point_pos_for_next;

public:
   Ellipsoid();
   void set_figure_on_start(QGraphicsScene* scn);
   int set_new_figure_pos(int position);
   void init_ellipse_move_points();

   void set_figure_on_bar(QGraphicsScene* scn, QPointF pos);
   void set_mini_figure_on_card(QGraphicsScene* scn, int card_index);
   //void draw_ell(QGraphicsScene* scn, int position);


   ~Ellipsoid()
   {
       delete ellipse_item;
   }

public slots:
   void update_ellipse();

};



class Square : public Figure
{
private:
    QGraphicsRectItem *square_item;
    QPointF square_points[40];
    int current_sqr_position;

public:
    Square();
    void set_figure_on_start(QGraphicsScene* scn);
    int set_new_figure_pos(int position);
    void init_square_move_points();

    void set_figure_on_bar(QGraphicsScene* scn, QPointF pos);
    void set_mini_figure_on_card(QGraphicsScene* scn, int card_index);

    ~Square()
    {
        delete square_item;
    }
};



class Rectangloid : public Figure
{
private:
    QGraphicsRectItem *rectangle_item;
    QPointF rectangle_points[40];
    //QBrush *magentaBrush = new QBrush(Qt::magenta);
    int current_rect_position;
//    int speed = 5;
public:
    Rectangloid();
    void set_figure_on_start(QGraphicsScene* scn);
    int set_new_figure_pos(int position);
    void init_rect_move_points();

    void set_figure_on_bar(QGraphicsScene* scn, QPointF pos);
    void set_mini_figure_on_card(QGraphicsScene* scn, int card_index);

    ~Rectangloid()
    {
        delete rectangle_item;
    }
};



class Circle : public Figure
{
private:
    QGraphicsEllipseItem *circle_item;
    QPointF circle_points[40];
    int current_cir_position;

public:
    Circle();
    void set_figure_on_start(QGraphicsScene* scn);
    int set_new_figure_pos(int position);
    void init_circle_move_points();

    void set_figure_on_bar(QGraphicsScene* scn, QPointF pos);
    void set_mini_figure_on_card(QGraphicsScene* scn, int card_index);

    ~Circle()
    {
        delete circle_item;
    }
};



#endif // FIGURE_H
