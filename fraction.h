#include <QWidget>

class Fraction_window : public QWidget {

  Q_OBJECT

  public:
    Fraction_window(QWidget *parent = nullptr);

  private slots:

  private:
    QList<QString> convert_common_denom(QList<QString> fractions);
    QString reduce_frac(QString fraction);

};
