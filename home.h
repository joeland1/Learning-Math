#include <QMainWindow>
#include <QApplication>
#include <QStackedWidget>

class HomeWindow : public QMainWindow {

  Q_OBJECT

  public:
    HomeWindow(QWidget *parent = nullptr);

  private slots:

  private:
    QStackedWidget *stacked_home;

};
