#include <QWidget>
#include <QPainter>
#include <QString>

class Addition_window : public QWidget {

  Q_OBJECT

  public:
    Addition_window(QWidget *parent = nullptr);

  private slots:
    void create_pdf();
  private:
    void create_problem(int font_size, QPainter *painter);
    QString calc_answer(std::string string_numbers[], int length);
};
