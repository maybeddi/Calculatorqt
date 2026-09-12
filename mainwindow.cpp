#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    // подключение сигнала clicked для операций
    connect(ui->pushButtonPlus,&QPushButton::clicked,
            this,[this](){onOperationClicked("+"); });
    connect(ui->pushButtonMinus,&QPushButton::clicked,
            this,[this](){onOperationClicked("-"); });
    connect(ui->pushButtonMultiply,&QPushButton::clicked,
            this,[this](){onOperationClicked("*"); });
    connect(ui->pushButtonDivide,&QPushButton::clicked,
            this,[this](){onOperationClicked(":"); });
    connect(ui->pushButtonPercent,&QPushButton::clicked,
            this,[this](){onOperationClicked("%"); });

    //особые кнопки
    connect(ui->pushButtonDot,&QPushButton::clicked,
            this,&MainWindow::onDotClicked);
    connect(ui->pushButtonDelete,&QPushButton::clicked,
            this,&MainWindow::onDeleteClicked);
    connect(ui->pushButtonEquals,&QPushButton::clicked,
            this,&MainWindow::onEqualsClicked);

}
// реализация слотов
void MainWindow::onDigitClicked(int digit){
    double currentText = ui->lcdNumber->value(); // текущее состояние дисплея
    if(currentText == "0"){
        ui->lcdNumber->display(digit);
    }else{
        ui->lcdNumber->display(currentText + QString::number(digit));
    }
    qDebug()<<"[DEBUG] Нажата цифра: " << digit;
}

void MainWindow::onOperationClicked(const QString &op){
    currentValue = ui->lcdNumber->value(); // текущее число на экране
    currentOperation = op; //операция которую нажали
    ui->lcdNumber->display(0);//очищаем экран для ввода второго числа

    qDebug() << "[DEBUG] Операция:" << op << "первое число:" << currentValue;
}

void MainWindow::onEqualsClicked(){
    double secondValue = ui->lcdNumber->value;
    double rezult = 0.0;

    if(currentOperation == "+"){
        rezult = currentValue + secondValue;
    }else if(currentOperation == "-"){
        rezult = currentValue - secondValue;
    }else if(currentOperation == "*"){
        rezult = currentValue * secondValue;
    }else if(currentOperation == "/"){
        if (secondValue == 0.0){
            ui->lcdNumber->display(0);
            qDebug() << "[Error] Деление на ноль!";
            return;
        }
        rezult = currentValue / secondValue;
    }else if (currentOperation == "%") {
        result = currentValue * secondValue / 100.0;
    }else{
        qDebug() << "[WARNING] операция не нажата.";
    }

    ui->lcdNumber->display(rezult); // вывод результата операции на экран
    currentValue = rezult; // сохраняем результат для цепочки вычислений
}

void MainWindow::onDeleteClicked(){
    ui->lcdNumber->display(0);

    currentValue = 0.0;
    currentOperation = "";

    qDebug() << "[DEBUG] Очистили экран";
}

void MainWindow::onDotClicked(){
    double currentNumber = ui->lcdNumber->value();

    // Преобразуем в строку для проверки
    QString currentText = QString::number(currentNumber, 'f', 10);

    // Убираем лишние нули
    while (currentText.endsWith('0') && currentText.contains('.')) {
        currentText.chop(1);
    }
    if (currentText.endsWith('.')) {
        currentText.chop(1);
    }

    // Проверяем, есть ли уже точка
    if (currentText.contains('.')) {
        qDebug() << "[DEBUG] Точка уже добавлена";
        return;
    }

    // Добавляем точку
    if (currentNumber == 0.0) {
        ui->lcdNumber->display("0.");
    } else {
        ui->lcdNumber->display(currentText + ".");
    }

    qDebug() << "[DEBUG] Добавлена точка";
}

