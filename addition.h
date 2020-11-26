#include <QWidget>

class Addition_window : public QWidget {

  Q_OBJECT

  public:
    Addition_window(QWidget *parent = nullptr);

  private slots:
    void create_pdf();
  private:

};
