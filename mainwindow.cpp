#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyEvent"
#include "QDebug" // для отладки (вывод в консоль)
// логика калькулятора,он приводит в действие все то, что описано в файле .h(пример: свзязывание кнопок,обработка нажатий )
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupConnections(); //сюда подключаем сигналы к слотам
    // настройка QLCDNumber
    ui->lcdNumber->display(0); // 0 при старте
    ui->lcdNumber->setDigitCount(15); // максимальное кол-во цифр на экране
    ui->lcdNumber->setSegmentStyle(QLCDNumber:: Filled); // стиль заполненный

}
MainWindow::~MainWindow() // деструктор
{
    delete ui;
}
void MainWindow::setupConnections()
{
    // список указателей на кнопки
    QList<QPushButton*> digitButtons = { ui->pushButton0, ui->pushButton1, ui->pushButton2,
        ui->pushButton3, ui->pushButton4, ui->pushButton5,
        ui->pushButton6, ui->pushButton7, ui->pushButton8, ui->pushButton9
    };
// перебираем список указателей на кнопки ОТ 0-9 и через лямбду подключаем сигнал clicked
    for(int i = 0; i < digitButtons.size();++i){
        int digit = i;

        connect(digitButtons[i],&QPushButton::clicked,
                this, [this, digit](){
                    onDigitClicked(digit);
        });

    }
}
