#pragma once

#include <QLabel>
#include <QMainWindow>

#include "BoardView.hpp"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    BoardView board;
    QLabel startLabel;
};
