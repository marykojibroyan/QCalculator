#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDigitClicked();
    void onOperatorClicked();
    void onEqualClicked();
    void onClearClicked();

private:
    QLineEdit *display;
    QPushButton *buttons[17];
    QString currentNumber;
    QString pendingNumber;
    QString pendingOperator;

    void createLayout();
    void setupConnections();
};

#endif // MAINWINDOW_H
