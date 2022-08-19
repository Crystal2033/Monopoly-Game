#ifndef NAMESELECTING_H
#define NAMESELECTING_H

#include <QMainWindow>
#include <QLabel>
class ChooseStartWindow;
namespace Ui {
class NameSelecting;
}

class NameSelecting : public QMainWindow
{
    Q_OBJECT

public:
    explicit NameSelecting(QWidget *parent = nullptr);
    void set_value_of_names(int value);
    void build_win_design();
    void start_game();
    ~NameSelecting();

private slots:
    void on_ok_btn_clicked();

    void on_pushButton_clicked();

private:
    Ui::NameSelecting *ui;
    int value_of_names;
};

#endif // NAMESELECTING_H
