#include "choosestartwindow.h"
#include "ui_choosestartwindow.h"
#include <QPixmap>
#include <iostream>
#include "nameselecting.h"

ChooseStartWindow::ChooseStartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseStartWindow)
{
    ui->setupUi(this);
    value_of_players = 0;
    //QPixmap pix(":/pictures/pictures/StartWindow.png");
    //ui->
    //ui->sec_label->setPixmap(pix);
    this->setGeometry(125 + parent->width() / 4,40 + parent->height() / 4, parent->width() / 2, parent->height() / 2);
    this->setFixedSize(parent->width() / 2, parent->height() / 2);
    //connect(ui->ok_btn_pl, SIGNAL(clicked()), SLOT(on_ok_btn_pl_clicked()));

}

int ChooseStartWindow::get_value_of_players()
{
    return value_of_players;
}

ChooseStartWindow::~ChooseStartWindow()
{
    delete ui;
}

void ChooseStartWindow::on_ok_btn_pl_clicked()
{

    if(ui->radio_2_pl->isChecked())
    {
        //QMessageBox::information(this, "Value of players", "You have chosen 2 players.");
        value_of_players = 2;
        this->close();

    }
    else if (ui->radio_3_pl->isChecked())
    {
        //QMessageBox::information(this, "Value of players", "You have chosen 3 players.");
        value_of_players = 3;
        this->close();
    }
    else if (ui->radio_4_pl->isChecked())
    {
       // QMessageBox::information(this, "Value of players", "You have chosen 4 players.");
        value_of_players = 4;
        this->close();
    }
    else
    {
        QMessageBox::critical(this, "Danger", "You did not choose a value of players.");
        return;
    }

    if(value_of_players != 0)
    {
        NameSelecting *name_win = new NameSelecting(this);
        name_win->set_value_of_names(value_of_players);
        name_win->build_win_design();
        name_win->setWindowModality(Qt::WindowModal);
        name_win->show();

    }
    return;

}

void ChooseStartWindow::on_back_btn_pl_clicked()
{
    this->parentWidget()->show();
    this->close();
}
