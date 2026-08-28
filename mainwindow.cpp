#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox" //для сообщений об ошибках
#include "QDebug" // для отладки (вывод в консоль)
// логика калькулятора,он приводит в действие все то, что описано в файле .h(пример: свзязывание кнопок,обработка нажатий )
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupConnections(); //сюда подключаем сигналы к слотам
    // настройка QLSDNumber
    ui->lcdNumber->display(0); // 0 при старте
    ui->lcdNumber->setDigitCount(15); // максимальное кол-во цифр на экране
    ui->lcdNumber->setSegmentStyle(QLSDNumber:: Filled);

}
MainWindow::~MainWindow()
{
    delete ui;
}
