#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "choosestartwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_AboutBtn_clicked();

    void on_ExitBtn_clicked();

    void on_StartBtn_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap *game_map;
    ChooseStartWindow *sec_window;
    void set_colours(Ui::MainWindow & window);
    //QLabel *label;
};
#endif // MAINWINDOW_H
