#include "home.h"
#include "addition.h"

#include <QStackedWidget>
#include <QWidget>
HomeWindow::HomeWindow(QWidget *parent): QMainWindow(parent)
{
  Addition_window *addition = new Addition_window();
  stacked_home = new QStackedWidget();
    stacked_home->addWidget(addition);
  this->setCentralWidget(stacked_home);
}
