#include "mainwindow.h"
#include "ui_mainwindow.h"
// логика калькулятора,он приводит в действие все то, что описано в файле .h(пример: свзязывание кнопок,обработка нажатий )
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //init
}

MainWindow::~MainWindow()
{
    delete ui;
}
