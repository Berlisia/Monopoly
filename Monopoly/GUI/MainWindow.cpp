#include <QLabel>
#include <iostream>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    board.addfield(":/start.png", "START");

    const auto& fields = board.getFields();
    if (fields[0].pixmap->load(":/start.png"))
    {
        std::cout << "UDALO SIE" << std::endl;
    }
    startLabel.setPixmap(*(fields[0].pixmap));
    startLabel.setAlignment(Qt::AlignCenter);
    ui->fieldsLayout->addWidget(&startLabel, 10, 0);
    ui->fieldsLayout->activate();
}

MainWindow::~MainWindow()
{
    delete ui;
}
