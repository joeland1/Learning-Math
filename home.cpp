#include "home.h"
#include "addition.h"
#include "fraction.h"

#include <QStackedWidget>
#include <QWidget>
#include <QAction>
#include <QToolBar>


HomeWindow::HomeWindow(QWidget *parent): QMainWindow(parent)
{
  Addition_window *addition = new Addition_window;
  Fraction_window *fraction = new Fraction_window;
  stacked_home = new QStackedWidget();
    stacked_home->addWidget(addition);
    stacked_home->addWidget(fraction);

  QToolBar *toolbar = addToolBar("main toolbar");
     addToolBar(Qt::LeftToolBarArea, toolbar);

  QAction *goto_addition = new QAction("&Addition");
    toolbar->addAction(goto_addition);
    connect(goto_addition, &QAction::triggered, this,[=]{stacked_home->setCurrentWidget(addition);});

  QAction *goto_fraction = new QAction("&Fraction");
    toolbar->addAction(goto_fraction);
    connect(goto_fraction, &QAction::triggered, this,[=]{stacked_home->setCurrentWidget(fraction);});

  this->setCentralWidget(stacked_home);
}
