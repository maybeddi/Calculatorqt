#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qstring>
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
    void onOperationClicked(const Qstring &op); // слот для операций
    void onEqualsClicked(); // слот для равно
    void onDeleteClicked(); // слот для удаления
    void onDotClicked(); // слот для точки
private:
    Ui::MainWindow *ui;

    double currentValue = 0.0;
    Qstring currentOperation = "";
};
#endif // MAINWINDOW_H
