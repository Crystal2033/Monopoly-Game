#include "figures.h"
//#include "ui_gamewindow.h"


Figure::Figure()
{
    init_mini_figures_coords();
    blackPen->setWidth(2);
    return;
}

int Figure::set_new_figure_pos(int position)
{
    Q_UNUSED(position);
    return 0;
}

void Figure::set_figure_on_start(QGraphicsScene *scn)
{
    Q_UNUSED(scn);
    return;
}

void Figure::set_figure_on_bar(QGraphicsScene *scn, QPointF pos)
{
    Q_UNUSED(scn);
    Q_UNUSED(pos);
    return;
}

void Figure::set_mini_figure_on_card(QGraphicsScene *scn, int card_index)
{
    Q_UNUSED(scn);
    Q_UNUSED(card_index);
    return;
}

void Figure::init_mini_figures_coords()
{
    coords_mini_fugures_on_cards[1] = QPointF(807, 565);
    coords_mini_fugures_on_cards[3] = QPointF(652, 565);
    coords_mini_fugures_on_cards[5] = QPointF(497, 565);
    coords_mini_fugures_on_cards[6] = QPointF(420, 565);
    coords_mini_fugures_on_cards[8] = QPointF(265, 565);
    coords_mini_fugures_on_cards[9] = QPointF(190, 565);
    coords_mini_fugures_on_cards[11] = QPointF(105, 542);
    coords_mini_fugures_on_cards[12] = QPointF(105, 487);
    coords_mini_fugures_on_cards[13] = QPointF(105, 437);
    coords_mini_fugures_on_cards[14] = QPointF(105, 385);
    coords_mini_fugures_on_cards[15] = QPointF(105, 332);
    coords_mini_fugures_on_cards[16] = QPointF(105, 282);
    coords_mini_fugures_on_cards[18] = QPointF(105, 177);
    coords_mini_fugures_on_cards[19] = QPointF(105, 125);
    coords_mini_fugures_on_cards[21] = QPointF(185, 70);
    coords_mini_fugures_on_cards[23] = QPointF(340, 70);
    coords_mini_fugures_on_cards[24] = QPointF(420, 70);
    coords_mini_fugures_on_cards[25] = QPointF(500, 70);
    coords_mini_fugures_on_cards[26] = QPointF(575, 70);
    coords_mini_fugures_on_cards[27] = QPointF(650, 70);
    coords_mini_fugures_on_cards[28] = QPointF(725, 70);
    coords_mini_fugures_on_cards[29] = QPointF(800, 70);
    coords_mini_fugures_on_cards[31] = QPointF(830, 125);
    coords_mini_fugures_on_cards[32] = QPointF(830, 175);
    coords_mini_fugures_on_cards[34] = QPointF(830, 285);
    coords_mini_fugures_on_cards[35] = QPointF(830, 330);
    coords_mini_fugures_on_cards[37] = QPointF(830, 440);
    coords_mini_fugures_on_cards[39] = QPointF(830, 545);
    return;
}

Ellipsoid::Ellipsoid()
{
    width = 40;
    height = 20;
    brush = new QBrush(Qt::darkCyan);
    current_ell_index = 0;
    temp_pos = 0;
    return;
}

void Ellipsoid::set_figure_on_start(QGraphicsScene *scn)
{

    init_ellipse_move_points();
    ellipse_item = scn->addEllipse(ellipse_points[0].x(), ellipse_points[0].y(), width, height, blackPen->color(), brush->color());
    current_point_pos = ellipse_item->pos();
    return;
}

int Ellipsoid::set_new_figure_pos(int position)
{

    //ellipse_item->setPos(ellipse_points[position] - ellipse_points[current_ell_position]);
//    qDebug() << current_point_pos;
//    qDebug() << "CURRENT" << current_point_pos + ellipse_points[position] - ellipse_points[current_ell_index];
    if (ellipse_item->pos() == (current_point_pos + ellipse_points[position] - ellipse_points[current_ell_index]))
    {
        temp_pos = 0;
        current_point_pos = ellipse_item->pos();
        current_ell_index = position;
        return 1;
    }

    if (ellipse_item->x() > current_point_pos_for_next.x() + ellipse_points[(current_ell_index + temp_pos + 1) % 40].x() - ellipse_points[(current_ell_index + temp_pos) % 40].x()
        && ellipse_item->y() == current_point_pos_for_next.y() + ellipse_points[(current_ell_index + temp_pos + 1) % 40].y() - ellipse_points[(current_ell_index + temp_pos) % 40].y())
    {
        ellipse_item->moveBy(-speed, 0);

        if (ellipse_item->pos() == current_point_pos_for_next + ellipse_points[(current_ell_index + temp_pos + 1) % 40] - ellipse_points[(current_ell_index + temp_pos) % 40])
        {
             current_point_pos_for_next = ellipse_item->pos();
             //qDebug() << "Ellipse->pos = " << ellipse_item->pos() << "  positions delta = " << ellipse_points[(current_ell_index + temp + 1) % 40] - ellipse_points[(current_ell_index + temp) % 40];
             temp_pos++;
        }
    }

    else if (ellipse_item->x() == current_point_pos_for_next.x() + ellipse_points[(current_ell_index + temp_pos + 1) % 40].x() - ellipse_points[(current_ell_index + temp_pos) % 40].x()
             && ellipse_item->y() > current_point_pos_for_next.y() + ellipse_points[(current_ell_index + temp_pos + 1) % 40].y() - ellipse_points[(current_ell_index + temp_pos) % 40].y())
    {
        ellipse_item->moveBy(0, -speed);

        if (ellipse_item->pos() == current_point_pos_for_next + ellipse_points[(current_ell_index + temp_pos + 1) % 40] - ellipse_points[(current_ell_index + temp_pos) % 40])
        {
             current_point_pos_for_next = ellipse_item->pos();
             //qDebug()  << "SECOND 10: "<< "Ellipse->pos = " << ellipse_item->pos() << "  positions delta = " << ellipse_points[(current_ell_index + temp + 1) % 40] - ellipse_points[(current_ell_index + temp) % 40];
             temp_pos++;
        }
    }

    else if (ellipse_item->x() < current_point_pos_for_next.x() + ellipse_points[(current_ell_index + temp_pos + 1) % 40].x() - ellipse_points[(current_ell_index + temp_pos) % 40].x()
             && ellipse_item->y() == current_point_pos_for_next.y() + ellipse_points[(current_ell_index + temp_pos + 1) % 40].y() - ellipse_points[(current_ell_index + temp_pos) % 40].y())
    {
        ellipse_item->moveBy(speed, 0);

        if (ellipse_item->pos() == current_point_pos_for_next + ellipse_points[(current_ell_index + temp_pos + 1) % 40] - ellipse_points[(current_ell_index + temp_pos) % 40])
        {
             current_point_pos_for_next = ellipse_item->pos();
             //qDebug()  << "THIRD 10: "<< "Ellipse->pos = " << ellipse_item->pos() << "  positions delta = " << ellipse_points[(current_ell_index + temp + 1) % 40] - ellipse_points[(current_ell_index + temp) % 40];
             temp_pos++;
        }
    }

    else if (ellipse_item->x() == current_point_pos_for_next.x() + ellipse_points[(current_ell_index + temp_pos + 1) % 40].x() - ellipse_points[(current_ell_index + temp_pos) % 40].x()
             && ellipse_item->y() < current_point_pos_for_next.y() + ellipse_points[(current_ell_index + temp_pos + 1) % 40].y() - ellipse_points[(current_ell_index + temp_pos) % 40].y())
    {
        ellipse_item->moveBy(0, speed);

        if (ellipse_item->pos() == current_point_pos_for_next + ellipse_points[(current_ell_index + temp_pos + 1) % 40] - ellipse_points[(current_ell_index + temp_pos) % 40])
        {
             current_point_pos_for_next = ellipse_item->pos();
             //qDebug()  << "FOURTH 10: "<< "Ellipse->pos = " << ellipse_item->pos() << "  positions delta = " << ellipse_points[(current_ell_index + temp + 1) % 40] - ellipse_points[(current_ell_index + temp) % 40];
             temp_pos++;
        }
    }

    return 0;
}

void Ellipsoid::init_ellipse_move_points()
{
    ellipse_points[0].setX(890);
    ellipse_points[0].setY(600);

    ellipse_points[1].setX(750);
    ellipse_points[1].setY(600);

    ellipse_points[2].setX(670);
    ellipse_points[2].setY(600);

    ellipse_points[3].setX(600);
    ellipse_points[3].setY(600);

    ellipse_points[4].setX(520);
    ellipse_points[4].setY(600);

    ellipse_points[5].setX(440);
    ellipse_points[5].setY(600);

    ellipse_points[6].setX(360);
    ellipse_points[6].setY(600);

    ellipse_points[7].setX(280);
    ellipse_points[7].setY(600);

    ellipse_points[8].setX(210);
    ellipse_points[8].setY(600);

    ellipse_points[9].setX(130);
    ellipse_points[9].setY(600);

    ellipse_points[10].setX(20);
    ellipse_points[10].setY(600);

   /////////////////////////////

    ellipse_points[11].setX(20);
    ellipse_points[11].setY(510);

    ellipse_points[12].setX(20);
    ellipse_points[12].setY(460);


    ellipse_points[13].setX(20);
    ellipse_points[13].setY(400);

    ellipse_points[14].setX(20);
    ellipse_points[14].setY(350);

    ellipse_points[15].setX(20);
    ellipse_points[15].setY(300);

    ellipse_points[16].setX(20);
    ellipse_points[16].setY(250);

    ellipse_points[17].setX(20);
    ellipse_points[17].setY(190);

    ellipse_points[18].setX(20);
    ellipse_points[18].setY(140);

    ellipse_points[19].setX(20);
    ellipse_points[19].setY(90);

    ellipse_points[20].setX(20);
    ellipse_points[20].setY(20);
    /////////////////////////// SECOND 20

    ellipse_points[21].setX(160);
    ellipse_points[21].setY(20);

    ellipse_points[22].setX(240);
    ellipse_points[22].setY(20);

    ellipse_points[23].setX(320);
    ellipse_points[23].setY(20);

    ellipse_points[24].setX(400);
    ellipse_points[24].setY(20);

    ellipse_points[25].setX(480);
    ellipse_points[25].setY(20);

    ellipse_points[26].setX(550);
    ellipse_points[26].setY(20);

    ellipse_points[27].setX(630);
    ellipse_points[27].setY(20);

    ellipse_points[28].setX(710);
    ellipse_points[28].setY(20);

    ellipse_points[29].setX(780);
    ellipse_points[29].setY(20);

    ellipse_points[30].setX(890);
    ellipse_points[30].setY(20);

    //////////////////////////// THIRD 10

    ellipse_points[31].setX(890);
    ellipse_points[31].setY(110);

    ellipse_points[32].setX(890);
    ellipse_points[32].setY(170);

    ellipse_points[33].setX(890);
    ellipse_points[33].setY(220);

    ellipse_points[34].setX(890);
    ellipse_points[34].setY(270);

    ellipse_points[35].setX(890);
    ellipse_points[35].setY(320);

    ellipse_points[36].setX(890);
    ellipse_points[36].setY(380);

    ellipse_points[37].setX(890);
    ellipse_points[37].setY(430);

    ellipse_points[38].setX(890);
    ellipse_points[38].setY(480);

    ellipse_points[39].setX(890);
    ellipse_points[39].setY(530);
}

void Ellipsoid::set_figure_on_bar(QGraphicsScene *scn, QPointF pos)
{
    ellipse_item = scn->addEllipse(pos.x(), pos.y(), (width * 2) / 3, (height * 2) / 3, blackPen->color(), brush->color());
    return;
}

void Ellipsoid::set_mini_figure_on_card(QGraphicsScene *scn, int card_index)
{
    ellipse_item = scn->addEllipse(coords_mini_fugures_on_cards[card_index].x(), coords_mini_fugures_on_cards[card_index].y(), width / 2, height / 2 , blackPen->color(), brush->color());
    return;
}



Square::Square()
{
    width = 25;
    height = 25;
    brush = new QBrush(Qt::green);
    current_sqr_position = 0;
    temp_pos = 0;
    return;
}

void Square::set_figure_on_start(QGraphicsScene *scn)
{
    //square_item = scn->addRect(square_points[0].x(), square_points[0].y(), 20, 20, greenBrush->color(), blackPen->color());
    init_square_move_points();
    square_item = scn->addRect(square_points[0].x(), square_points[0].y(), width, height, blackPen->color(), brush->color());
    current_point_pos = square_item->pos();
    qDebug() << square_item->pos();
    return;

}

int Square::set_new_figure_pos(int position)
{
    if (square_item->pos() == (current_point_pos + square_points[position] - square_points[current_sqr_position]))
    {
        temp_pos = 0;
        current_point_pos = square_item->pos();
        current_sqr_position = position;
        return 1;
    }

    if (square_item->x() > current_point_pos_for_next.x() + square_points[(current_sqr_position + temp_pos + 1) % 40].x() - square_points[(current_sqr_position + temp_pos) % 40].x()
        && square_item->y() == current_point_pos_for_next.y() + square_points[(current_sqr_position + temp_pos + 1) % 40].y() - square_points[(current_sqr_position + temp_pos) % 40].y())
    {
        square_item->moveBy(-speed, 0);

        if (square_item->pos() == current_point_pos_for_next + square_points[(current_sqr_position + temp_pos + 1) % 40] - square_points[(current_sqr_position + temp_pos) % 40])
        {
             current_point_pos_for_next = square_item->pos();
             //qDebug() << "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }

    else if (square_item->x() == current_point_pos_for_next.x() + square_points[(current_sqr_position + temp_pos + 1) % 40].x() - square_points[(current_sqr_position + temp_pos) % 40].x()
             && square_item->y() > current_point_pos_for_next.y() + square_points[(current_sqr_position + temp_pos + 1) % 40].y() - square_points[(current_sqr_position + temp_pos) % 40].y())
    {
        square_item->moveBy(0, -speed);

        if (square_item->pos() == current_point_pos_for_next + square_points[(current_sqr_position + temp_pos + 1) % 40] - square_points[(current_sqr_position + temp_pos) % 40])
        {
             current_point_pos_for_next = square_item->pos();
             //qDebug()  << "SECOND 10: "<< "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }

    else if (square_item->x() < current_point_pos_for_next.x() + square_points[(current_sqr_position + temp_pos + 1) % 40].x() - square_points[(current_sqr_position + temp_pos) % 40].x()
             && square_item->y() == current_point_pos_for_next.y() + square_points[(current_sqr_position + temp_pos + 1) % 40].y() - square_points[(current_sqr_position + temp_pos) % 40].y())
    {
        square_item->moveBy(speed, 0);

        if (square_item->pos() == current_point_pos_for_next + square_points[(current_sqr_position + temp_pos + 1) % 40] - square_points[(current_sqr_position + temp_pos) % 40])
        {
             current_point_pos_for_next = square_item->pos();
             //qDebug()  << "THIRD 10: "<< "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }

    else if (square_item->x() == current_point_pos_for_next.x() + square_points[(current_sqr_position + temp_pos + 1) % 40].x() - square_points[(current_sqr_position + temp_pos) % 40].x()
             && square_item->y() < current_point_pos_for_next.y() + square_points[(current_sqr_position + temp_pos + 1) % 40].y() - square_points[(current_sqr_position + temp_pos) % 40].y())
    {
        square_item->moveBy(0, speed);

        if (square_item->pos() == current_point_pos_for_next + square_points[(current_sqr_position + temp_pos + 1) % 40] - square_points[(current_sqr_position + temp_pos) % 40])
        {
             current_point_pos_for_next = square_item->pos();
             //qDebug()  << "FOURTH 10: "<< "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }
    return 0;
}

void Square::init_square_move_points()
{
    square_points[0].setX(890);
    square_points[0].setY(600);

    square_points[1].setX(770);
    square_points[1].setY(600);

    square_points[2].setX(710);
    square_points[2].setY(600);

    square_points[3].setX(630);
    square_points[3].setY(600);

    square_points[4].setX(550);
    square_points[4].setY(600);

    square_points[5].setX(480);
    square_points[5].setY(600);

    square_points[6].setX(390);
    square_points[6].setY(600);

    square_points[7].setX(310);
    square_points[7].setY(600);

    square_points[8].setX(230);
    square_points[8].setY(600);

    square_points[9].setX(160);
    square_points[9].setY(600);

    square_points[10].setX(20);
    square_points[10].setY(600);

    square_points[11].setX(20);
    square_points[11].setY(530);

    square_points[12].setX(20);
    square_points[12].setY(480);

    /////////////////////////////
    square_points[13].setX(20);
    square_points[13].setY(430);

    square_points[14].setX(20);
    square_points[14].setY(360);

    square_points[15].setX(20);
    square_points[15].setY(320);

    square_points[16].setX(20);
    square_points[16].setY(270);

    square_points[17].setX(20);
    square_points[17].setY(220);

    square_points[18].setX(20);
    square_points[18].setY(160);

    square_points[19].setX(20);
    square_points[19].setY(110);

    square_points[20].setX(20);
    square_points[20].setY(20);
    /////////////////////////// SECOND 20

    square_points[21].setX(130);
    square_points[21].setY(20);

    square_points[22].setX(210);
    square_points[22].setY(20);

    square_points[23].setX(290);
    square_points[23].setY(20);

    square_points[24].setX(360);
    square_points[24].setY(20);

    square_points[25].setX(450);
    square_points[25].setY(20);

    square_points[26].setX(520);
    square_points[26].setY(20);

    square_points[27].setX(600);
    square_points[27].setY(20);

    square_points[28].setX(680);
    square_points[28].setY(20);

    square_points[29].setX(760);
    square_points[29].setY(20);

    square_points[30].setX(890);
    square_points[30].setY(20);

    //////////////////////////// THIRD 10

    square_points[31].setX(890);
    square_points[31].setY(100);

    square_points[32].setX(890);
    square_points[32].setY(150);

    square_points[33].setX(890);
    square_points[33].setY(210);

    square_points[34].setX(890);
    square_points[34].setY(260);

    square_points[35].setX(890);
    square_points[35].setY(310);

    square_points[36].setX(890);
    square_points[36].setY(360);

    square_points[37].setX(890);
    square_points[37].setY(410);

    square_points[38].setX(890);
    square_points[38].setY(470);

    square_points[39].setX(890);
    square_points[39].setY(520);
}

void Square::set_figure_on_bar(QGraphicsScene *scn, QPointF pos)
{
    square_item = scn->addRect(pos.x(), pos.y(), (width * 2) / 3, (height * 2) / 3, blackPen->color(), brush->color());
    return;
}

void Square::set_mini_figure_on_card(QGraphicsScene *scn, int card_index)
{
    square_item = scn->addRect(coords_mini_fugures_on_cards[card_index].x(), coords_mini_fugures_on_cards[card_index].y(), width / 2, height / 2 , blackPen->color(), brush->color());
    return;
}

Rectangloid::Rectangloid()
{
    width = 40;
    height = 15;
    brush = new QBrush(Qt::magenta);
    current_rect_position = 0;
    temp_pos = 0;
    return;
}

void Rectangloid::set_figure_on_start(QGraphicsScene *scn)
{
    init_rect_move_points();
    rectangle_item = scn->addRect(rectangle_points[0].x(), rectangle_points[0].y(), width, height, blackPen->color(), brush->color());
    current_point_pos = rectangle_item->pos();
    qDebug() << rectangle_item->pos();
    return;
}

int Rectangloid::set_new_figure_pos(int position)
{

    if (rectangle_item->pos() == (current_point_pos + rectangle_points[position] - rectangle_points[current_rect_position]))
    {
        temp_pos = 0;
        current_point_pos = rectangle_item->pos();
        current_rect_position = position;
        return 1;
    }

    if (rectangle_item->x() > current_point_pos_for_next.x() + rectangle_points[(current_rect_position + temp_pos + 1) % 40].x() - rectangle_points[(current_rect_position + temp_pos) % 40].x()
        && rectangle_item->y() == current_point_pos_for_next.y() + rectangle_points[(current_rect_position + temp_pos + 1) % 40].y() - rectangle_points[(current_rect_position + temp_pos) % 40].y())
    {
        rectangle_item->moveBy(-speed, 0);

        if (rectangle_item->pos() == current_point_pos_for_next + rectangle_points[(current_rect_position + temp_pos + 1) % 40] - rectangle_points[(current_rect_position + temp_pos) % 40])
        {
             current_point_pos_for_next = rectangle_item->pos();
             //qDebug() << "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }

    else if (rectangle_item->x() == current_point_pos_for_next.x() + rectangle_points[(current_rect_position + temp_pos + 1) % 40].x() - rectangle_points[(current_rect_position + temp_pos) % 40].x()
             && rectangle_item->y() > current_point_pos_for_next.y() + rectangle_points[(current_rect_position + temp_pos + 1) % 40].y() - rectangle_points[(current_rect_position + temp_pos) % 40].y())
    {
        rectangle_item->moveBy(0, -speed);

        if (rectangle_item->pos() == current_point_pos_for_next + rectangle_points[(current_rect_position + temp_pos + 1) % 40] - rectangle_points[(current_rect_position + temp_pos) % 40])
        {
             current_point_pos_for_next = rectangle_item->pos();
             //qDebug()  << "SECOND 10: "<< "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }

    else if (rectangle_item->x() < current_point_pos_for_next.x() + rectangle_points[(current_rect_position + temp_pos + 1) % 40].x() - rectangle_points[(current_rect_position + temp_pos) % 40].x()
             && rectangle_item->y() == current_point_pos_for_next.y() + rectangle_points[(current_rect_position + temp_pos + 1) % 40].y() - rectangle_points[(current_rect_position + temp_pos) % 40].y())
    {
        rectangle_item->moveBy(speed, 0);

        if (rectangle_item->pos() == current_point_pos_for_next + rectangle_points[(current_rect_position + temp_pos + 1) % 40] - rectangle_points[(current_rect_position + temp_pos) % 40])
        {
             current_point_pos_for_next = rectangle_item->pos();
             //qDebug()  << "THIRD 10: "<< "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }

    else if (rectangle_item->x() == current_point_pos_for_next.x() + rectangle_points[(current_rect_position + temp_pos + 1) % 40].x() - rectangle_points[(current_rect_position + temp_pos) % 40].x()
             && rectangle_item->y() < current_point_pos_for_next.y() + rectangle_points[(current_rect_position + temp_pos + 1) % 40].y() - rectangle_points[(current_rect_position + temp_pos) % 40].y())
    {
        rectangle_item->moveBy(0, speed);

        if (rectangle_item->pos() == current_point_pos_for_next + rectangle_points[(current_rect_position + temp_pos + 1) % 40] - rectangle_points[(current_rect_position + temp_pos) % 40])
        {
             current_point_pos_for_next = rectangle_item->pos();
             //qDebug()  << "FOURTH 10: "<< "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }
    return 0;
}

void Rectangloid::init_rect_move_points()
{

    rectangle_points[0].setX(890);
    rectangle_points[0].setY(600);

    rectangle_points[1].setX(760);
    rectangle_points[1].setY(600);

    rectangle_points[2].setX(700);
    rectangle_points[2].setY(600);

    rectangle_points[3].setX(620);
    rectangle_points[3].setY(600);

    rectangle_points[4].setX(540);
    rectangle_points[4].setY(600);

    rectangle_points[5].setX(470);
    rectangle_points[5].setY(600);

    rectangle_points[6].setX(380);
    rectangle_points[6].setY(600);

    rectangle_points[7].setX(300);
    rectangle_points[7].setY(600);

    rectangle_points[8].setX(220);
    rectangle_points[8].setY(600);

    rectangle_points[9].setX(150);
    rectangle_points[9].setY(600);

    rectangle_points[10].setX(20);
    rectangle_points[10].setY(600);

    rectangle_points[11].setX(20);
    rectangle_points[11].setY(520);

    rectangle_points[12].setX(20);
    rectangle_points[12].setY(470);

    /////////////////////////////
    rectangle_points[13].setX(20);
    rectangle_points[13].setY(420);

    rectangle_points[14].setX(20);
    rectangle_points[14].setY(370);

    rectangle_points[15].setX(20);
    rectangle_points[15].setY(320);

    rectangle_points[16].setX(20);
    rectangle_points[16].setY(260);

    rectangle_points[17].setX(20);
    rectangle_points[17].setY(210);

    rectangle_points[18].setX(20);
    rectangle_points[18].setY(150);

    rectangle_points[19].setX(20);
    rectangle_points[19].setY(100);

    rectangle_points[20].setX(20);
    rectangle_points[20].setY(20);
    /////////////////////////// SECOND 20

    rectangle_points[21].setX(140);
    rectangle_points[21].setY(20);

    rectangle_points[22].setX(220);
    rectangle_points[22].setY(20);

    rectangle_points[23].setX(300);
    rectangle_points[23].setY(20);

    rectangle_points[24].setX(370);
    rectangle_points[24].setY(20);

    rectangle_points[25].setX(460);
    rectangle_points[25].setY(20);

    rectangle_points[26].setX(530);
    rectangle_points[26].setY(20);

    rectangle_points[27].setX(610);
    rectangle_points[27].setY(20);

    rectangle_points[28].setX(690);
    rectangle_points[28].setY(20);

    rectangle_points[29].setX(760);
    rectangle_points[29].setY(20);

    rectangle_points[30].setX(890);
    rectangle_points[30].setY(20);

    //////////////////////////// THIRD 10

    rectangle_points[31].setX(890);
    rectangle_points[31].setY(100);

    rectangle_points[32].setX(890);
    rectangle_points[32].setY(150);

    rectangle_points[33].setX(890);
    rectangle_points[33].setY(210);

    rectangle_points[34].setX(890);
    rectangle_points[34].setY(260);

    rectangle_points[35].setX(890);
    rectangle_points[35].setY(310);

    rectangle_points[36].setX(890);
    rectangle_points[36].setY(360);

    rectangle_points[37].setX(890);
    rectangle_points[37].setY(410);

    rectangle_points[38].setX(890);
    rectangle_points[38].setY(470);

    rectangle_points[39].setX(890);
    rectangle_points[39].setY(520);
}

void Rectangloid::set_figure_on_bar(QGraphicsScene *scn, QPointF pos)
{
    rectangle_item = scn->addRect(pos.x(), pos.y(), (width * 2) / 3, (height * 2) / 3, blackPen->color(), brush->color());
    return;
}

void Rectangloid::set_mini_figure_on_card(QGraphicsScene *scn, int card_index)
{
    rectangle_item = scn->addRect(coords_mini_fugures_on_cards[card_index].x(), coords_mini_fugures_on_cards[card_index].y(), width / 2, height / 2 , blackPen->color(), brush->color());
    return;
}


Circle::Circle()
{
    width = 25;
    height = 25;
    brush = new QBrush(Qt::blue);
    current_cir_position = 0;
    temp_pos = 0;
    return;
}

void Circle::set_figure_on_start(QGraphicsScene *scn)
{
    init_circle_move_points();
    circle_item = scn->addEllipse(circle_points[0].x(), circle_points[0].y(), width, height, blackPen->color(), brush->color());
    current_point_pos = circle_item->pos();
    qDebug() << circle_item->pos();
    return;
}

int Circle::set_new_figure_pos(int position)
{
    if (circle_item->pos() == (current_point_pos + circle_points[position] - circle_points[current_cir_position]))
    {
        temp_pos = 0;
        current_point_pos = circle_item->pos();
        current_cir_position = position;
        return 1;
    }

    if (circle_item->x() > current_point_pos_for_next.x() + circle_points[(current_cir_position + temp_pos + 1) % 40].x() - circle_points[(current_cir_position + temp_pos) % 40].x()
        && circle_item->y() == current_point_pos_for_next.y() + circle_points[(current_cir_position + temp_pos + 1) % 40].y() - circle_points[(current_cir_position + temp_pos) % 40].y())
    {
        circle_item->moveBy(-speed, 0);

        if (circle_item->pos() == current_point_pos_for_next + circle_points[(current_cir_position + temp_pos + 1) % 40] - circle_points[(current_cir_position + temp_pos) % 40])
        {
             current_point_pos_for_next = circle_item->pos();
             //qDebug() << "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }

    else if (circle_item->x() == current_point_pos_for_next.x() + circle_points[(current_cir_position + temp_pos + 1) % 40].x() - circle_points[(current_cir_position + temp_pos) % 40].x()
             && circle_item->y() > current_point_pos_for_next.y() + circle_points[(current_cir_position + temp_pos + 1) % 40].y() - circle_points[(current_cir_position + temp_pos) % 40].y())
    {
        circle_item->moveBy(0, -speed);

        if (circle_item->pos() == current_point_pos_for_next + circle_points[(current_cir_position + temp_pos + 1) % 40] - circle_points[(current_cir_position + temp_pos) % 40])
        {
             current_point_pos_for_next = circle_item->pos();
             //qDebug()  << "SECOND 10: "<< "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }

    else if (circle_item->x() < current_point_pos_for_next.x() + circle_points[(current_cir_position + temp_pos + 1) % 40].x() - circle_points[(current_cir_position + temp_pos) % 40].x()
             && circle_item->y() == current_point_pos_for_next.y() + circle_points[(current_cir_position + temp_pos + 1) % 40].y() - circle_points[(current_cir_position + temp_pos) % 40].y())
    {
        circle_item->moveBy(speed, 0);

        if (circle_item->pos() == current_point_pos_for_next + circle_points[(current_cir_position + temp_pos + 1) % 40] - circle_points[(current_cir_position + temp_pos) % 40])
        {
             current_point_pos_for_next = circle_item->pos();
             //qDebug()  << "THIRD 10: "<< "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }

    else if (circle_item->x() == current_point_pos_for_next.x() + circle_points[(current_cir_position + temp_pos + 1) % 40].x() - circle_points[(current_cir_position + temp_pos) % 40].x()
             && circle_item->y() < current_point_pos_for_next.y() + circle_points[(current_cir_position + temp_pos + 1) % 40].y() - circle_points[(current_cir_position + temp_pos) % 40].y())
    {
        circle_item->moveBy(0, speed);

        if (circle_item->pos() == current_point_pos_for_next + circle_points[(current_cir_position + temp_pos + 1) % 40] - circle_points[(current_cir_position + temp_pos) % 40])
        {
             current_point_pos_for_next = circle_item->pos();
             //qDebug()  << "FOURTH 10: "<< "Square->pos = " << square_item->pos() << "  positions delta = " << square_points[(current_sqr_position + temp + 1) % 40] - square_points[(current_sqr_position + temp) % 40];
             temp_pos++;
        }
    }
    return 0;
}

void Circle::init_circle_move_points()
{
    circle_points[0].setX(890);
    circle_points[0].setY(600);

    circle_points[1].setX(760);
    circle_points[1].setY(600);

    circle_points[2].setX(700);
    circle_points[2].setY(600);

    circle_points[3].setX(620);
    circle_points[3].setY(600);

    circle_points[4].setX(540);
    circle_points[4].setY(600);

    circle_points[5].setX(470);
    circle_points[5].setY(600);

    circle_points[6].setX(380);
    circle_points[6].setY(600);

    circle_points[7].setX(300);
    circle_points[7].setY(600);

    circle_points[8].setX(220);
    circle_points[8].setY(600);

    circle_points[9].setX(150);
    circle_points[9].setY(600);

    circle_points[10].setX(20);
    circle_points[10].setY(600);

    circle_points[11].setX(20);
    circle_points[11].setY(520);

    circle_points[12].setX(20);
    circle_points[12].setY(470);

    /////////////////////////////
    circle_points[13].setX(20);
    circle_points[13].setY(420);

    circle_points[14].setX(20);
    circle_points[14].setY(370);

    circle_points[15].setX(20);
    circle_points[15].setY(320);

    circle_points[16].setX(20);
    circle_points[16].setY(260);

    circle_points[17].setX(20);
    circle_points[17].setY(210);

    circle_points[18].setX(20);
    circle_points[18].setY(150);

    circle_points[19].setX(20);
    circle_points[19].setY(100);

    circle_points[20].setX(20);
    circle_points[20].setY(20);
    /////////////////////////// SECOND 20

    circle_points[21].setX(140);
    circle_points[21].setY(20);

    circle_points[22].setX(220);
    circle_points[22].setY(20);

    circle_points[23].setX(300);
    circle_points[23].setY(20);

    circle_points[24].setX(370);
    circle_points[24].setY(20);

    circle_points[25].setX(460);
    circle_points[25].setY(20);

    circle_points[26].setX(530);
    circle_points[26].setY(20);

    circle_points[27].setX(610);
    circle_points[27].setY(20);

    circle_points[28].setX(690);
    circle_points[28].setY(20);

    circle_points[29].setX(760);
    circle_points[29].setY(20);

    circle_points[30].setX(890);
    circle_points[30].setY(20);

    //////////////////////////// THIRD 10

    circle_points[31].setX(890);
    circle_points[31].setY(100);

    circle_points[32].setX(890);
    circle_points[32].setY(150);

    circle_points[33].setX(890);
    circle_points[33].setY(210);

    circle_points[34].setX(890);
    circle_points[34].setY(260);

    circle_points[35].setX(890);
    circle_points[35].setY(310);

    circle_points[36].setX(890);
    circle_points[36].setY(360);

    circle_points[37].setX(890);
    circle_points[37].setY(410);

    circle_points[38].setX(890);
    circle_points[38].setY(470);

    circle_points[39].setX(890);
    circle_points[39].setY(520);
}

void Circle::set_figure_on_bar(QGraphicsScene *scn, QPointF pos)
{
    circle_item = scn->addEllipse(pos.x(), pos.y(), (width * 2) / 3, (height * 2) / 3, blackPen->color(), brush->color());
    return;
}

void Circle::set_mini_figure_on_card(QGraphicsScene *scn, int card_index)
{
    circle_item = scn->addEllipse(coords_mini_fugures_on_cards[card_index].x(), coords_mini_fugures_on_cards[card_index].y(), width / 2, height / 2 , blackPen->color(), brush->color());
    return;
}

