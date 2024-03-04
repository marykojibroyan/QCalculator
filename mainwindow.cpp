#include "mainwindow.h"
#include <QGridLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createLayout();
    setupConnections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createLayout()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    display = new QLineEdit(centralWidget);
    display->setAlignment(Qt::AlignRight);
    display->setReadOnly(true);

    QGridLayout *layout = new QGridLayout(centralWidget);
    layout->addWidget(display, 0, 0, 1, 4);

    const QString buttonLabels[17] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+",
        "C" // Clear button
    };

    for (int i = 0; i < 17; ++i) {
        buttons[i] = new QPushButton(buttonLabels[i], centralWidget);
        layout->addWidget(buttons[i], i / 4 + 1, i % 4);
    }
}

void MainWindow::setupConnections()
{
    for (int i = 0; i < 17; ++i) {
        if (i == 14) {
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::onEqualClicked);
        } else if (i == 13) {
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
        } else if (i == 15) {
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
        } else if (i == 16) {
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::onClearClicked);
        } else {
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::onDigitClicked);
        }
    }
}

void MainWindow::onDigitClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    currentNumber += button->text();
    display->setText(currentNumber);
}

void MainWindow::onOperatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    pendingNumber = currentNumber;
    currentNumber.clear();
    pendingOperator = button->text();
}

void MainWindow::onEqualClicked()
{
    double result = 0.0;
    double num1 = pendingNumber.toDouble();
    double num2 = currentNumber.toDouble();

    if (pendingOperator == "+") {
        result = num1 + num2;
    } else if (pendingOperator == "-") {
        result = num1 - num2;
    } else if (pendingOperator == "*") {
        result = num1 * num2;
    } else if (pendingOperator == "/") {
        if (num2 != 0.0) {
            result = num1 / num2;
        } else {
            QMessageBox::critical(this, "Error", "Division by zero!");
            return;
        }
    }

    display->setText(QString::number(result));
    currentNumber = QString::number(result);
}

void MainWindow::onClearClicked()
{
    currentNumber.clear();
    pendingNumber.clear();
    pendingOperator.clear();
    display->clear();
}
