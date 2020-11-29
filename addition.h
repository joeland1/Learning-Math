#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QRect>
#include <QStringList>

class Addition_window : public QWidget {

  Q_OBJECT

  public:
    Addition_window(QWidget *parent = nullptr);

  private slots:
    void create_pdf();
  private:
    QRectF draw_problem(int font_size, QPainter *painter, QPointF location, std::vector<std::string> numbers_inside_vector);
    QRectF calc_rect(int font_size, QPainter *painter, std::vector<std::string> numbers_inside_vector);
    std::vector<std::string> generate_qa_pair(std::vector<std::string> question_destionation);
    std::string calc_answer(std::string string_numbers[], int length);
    QRectF calc_equation_rec(std::string numbers[]);
};
