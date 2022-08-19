#include <string.h>
#include "mechanics.h"
#include <ctime>
#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    srand(time(NULL)); //Устанавливаем случайную зависимость.
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
