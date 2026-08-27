#include "mainwindow.h"

#include <QApplication>
// движок калькулятора,запускает все приложение,выводит на экран и запускает бесконечный цикл ожидания кликов мыши
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
