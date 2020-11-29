#include <QApplication>
#include "home.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  HomeWindow main_window;

  main_window.resize(250, 150);
  main_window.setWindowTitle("Joe Bot");
  main_window.show();

  return app.exec();
}
