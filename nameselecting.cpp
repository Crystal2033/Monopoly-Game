#include "nameselecting.h"
#include "ui_nameselecting.h"
#include <QtWidgets>
#include <iostream>
#include <QMessageBox>
#include <QDebug>
#include "gamewindow.h"

NameSelecting::NameSelecting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NameSelecting)
{
    ui->setupUi(this);
    this->setWindowTitle("Player`s names");
    this->setGeometry(parent->x(), parent->y(), parent->width(), parent->height());
    this->setFixedSize(parent->width(), parent->height());

}

void NameSelecting::set_value_of_names(int value)
{
    value_of_names = value;
    return;
}

void NameSelecting::build_win_design()
{
    if (value_of_names == 2)
    {
        ui->third_name->setVisible(false);
        ui->third_player->setVisible(false);
        ui->fourth_name->setVisible(false);
        ui->fourth_player->setVisible(false);
    }
    else if (value_of_names == 3)
    {
        ui->fourth_name->setVisible(false);
        ui->fourth_player->setVisible(false);
    }
    else if(value_of_names == 4)
    {

    }

}

void NameSelecting::start_game()
{
    GameWindow * game_win = new GameWindow();
    char* names[4];
    names[0] = (char*)ui->first_name->text().toStdString().c_str();
    names[1] = (char*)ui->second_name->text().toStdString().c_str();
    names[2] = (char*)ui->third_name->text().toStdString().c_str();
    names[3] = (char*)ui->fourth_name->text().toStdString().c_str();


    game_win->set_value_players(value_of_names);
    game_win->input_nicknames(names);
    game_win->show();

}

NameSelecting::~NameSelecting()
{
    delete ui;
}

void NameSelecting::on_ok_btn_clicked()
{
    bool is_okay = true;

    if (ui->first_name->text().isEmpty())
    {
        QMessageBox::critical(this, "Name error.", "First player has not name.");
        is_okay = false;
    }
    else if (ui->second_name->text().isEmpty())
    {
        QMessageBox::critical(this, "Name error.", "Second player has not name.");
        is_okay = false;
    }

    if (ui->first_name->text().length() > 15)
    {
        QMessageBox::critical(this, "Name error.", "First player name is too long. (MAX 15 symbols)");
        is_okay = false;
    }
    else if (ui->second_name->text().length() > 15)
    {
        QMessageBox::critical(this, "Name error.", "Second player name is too long. (MAX 15 symbols)");
        is_okay = false;
    }
    else if (ui->third_name->text().length() > 15)
    {
        QMessageBox::critical(this, "Name error.", "Third player name is too long. (MAX 15 symbols)");
        is_okay = false;
    }
    else if (ui->fourth_name->text().length() > 15)
    {
        QMessageBox::critical(this, "Name error.", "Fourth player name is too long. (MAX 15 symbols)");
        is_okay = false;
    }


    if (ui->first_name->text() == ui->second_name->text() && is_okay)
    {
        QMessageBox::critical(this, "Name error.", "First and second player names are the same.");
        is_okay =false;
    }

    if (value_of_names == 4)
    {
        if (ui->third_name->text().isEmpty())
        {
            QMessageBox::critical(this, "Name error.", "Third player has not name.");
            is_okay = false;
        }
        else if (ui->fourth_name->text().isEmpty())
        {
            QMessageBox::critical(this, "Name error.", "Fourth player has not name.");
            is_okay = false;
        }


        if (ui->first_name->text() == ui->third_name->text() && is_okay)
        {
            QMessageBox::critical(this, "Name error.", "First and third player names are the same.");
            is_okay =false;
        }
        else if (ui->first_name->text() == ui->fourth_name->text() && is_okay)
        {
            QMessageBox::critical(this, "Name error.", "First and fourth player names are the same.");
            is_okay =false;
        }
        else if (ui->second_name->text() == ui->third_name->text() && is_okay)
        {
            QMessageBox::critical(this, "Name error.", "Second and third player names are the same.");
            is_okay =false;
        }
        else if (ui->second_name->text() == ui->fourth_name->text() && is_okay)
        {
            QMessageBox::critical(this, "Name error.", "Second and fourth player names are the same.");
            is_okay =false;
        }
        else if (ui->third_name->text() == ui->fourth_name->text() && is_okay)
        {
            QMessageBox::critical(this, "Name error.", "Third and fourth player names are the same.");
            is_okay =false;
        }

    }
    else if (value_of_names == 3)
    {
        if (ui->third_name->text().isEmpty())
        {
            QMessageBox::critical(this, "Name error.", "Third player has not name.");
            is_okay = false;
        }

        if (ui->first_name->text() == ui->third_name->text() && is_okay)
        {
            QMessageBox::critical(this, "Name error.", "First and third player names are the same.");
            is_okay =false;
        }
        else if (ui->second_name->text() == ui->third_name->text() && is_okay)
        {
            QMessageBox::critical(this, "Name error.", "Second and third player names are the same.");
            is_okay =false;
        }
    }
    if (is_okay)

    {
        //QMessageBox::information(this, "ALL IS OK.", "All names are correct.");
        this->close();
        start_game();
    }

}

void NameSelecting::on_pushButton_clicked()
{
    this->close();
    this->parentWidget()->show();
}
