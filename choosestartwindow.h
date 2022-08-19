#ifndef CHOOSESTARTWINDOW_H
#define CHOOSESTARTWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class ChooseStartWindow;
}

class ChooseStartWindow : public QMainWindow
{
    Q_OBJECT
private:
    int value_of_players;
public:
    explicit ChooseStartWindow(QWidget *parent = nullptr);
    int get_value_of_players();
    ~ChooseStartWindow();

private slots:
    void on_ok_btn_pl_clicked();

    void on_back_btn_pl_clicked();

private:
    Ui::ChooseStartWindow *ui;
    void set_colours(Ui::ChooseStartWindow & window);
};

#endif // CHOOSESTARTWINDOW_H
