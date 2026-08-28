#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
//обьявление переменных, сигналов и функций кнопок. Тут нет логики
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onDigitClicked(int digit); //слот для цифр
    void onOperationClicked(const QString &op); // слот для операций
    void onEqualsClicked(); // слот для равно
    void onDeleteClicked(); // слот для удаления
    void onDotClicked(); // слот для точки
private:
    Ui::MainWindow *ui;
    //текущее состояние калькулятора
    void setupConnections(); //метод для подключения

    double currentValue = 0.0;
    QString currentOperation = "";
};
#endif // MAINWINDOW_H
