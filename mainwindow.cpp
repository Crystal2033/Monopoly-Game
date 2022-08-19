#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mechanics.h"

#include <QPixmap>
#include <QLabel>
#include <QMessageBox>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(950 ,640);
    QPixmap pix(":/pictures/pictures/StartWindow.png");
    ui->label->setPixmap(pix);
    this->setGeometry(125,40, 950,640);

    set_colours(*ui);
}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::on_AboutBtn_clicked()
{
    QMessageBox::information(this, "Student info.", "The Monopoly game was done by Kulikov Paul, FIIT, MAI 2021");
}

void MainWindow::set_colours(Ui::MainWindow &window)
{
    window.AboutBtn->setStyleSheet("background-color: IndianRed");
    window.StartBtn->setStyleSheet("background-color: IndianRed");
    window.HelpBtn->setStyleSheet("background-color: IndianRed");
    window.ExitBtn->setStyleSheet("background-color: IndianRed");
    return;
}

void MainWindow::on_ExitBtn_clicked()
{
   QMessageBox::StandardButton reply = QMessageBox::question(this, "Monopoly exit.", "Do you really want to quit the Monopoly", QMessageBox::Yes | QMessageBox::No);
   if (reply == QMessageBox::Yes)
   {
        QApplication::quit();
   }
   else if(reply == QMessageBox::No)
   {
        return;
   }
}

void MainWindow::on_StartBtn_clicked()
{
    sec_window = new ChooseStartWindow(this);
    sec_window->setWindowModality(Qt::WindowModal);
    this->hide();
    sec_window->show();
}
