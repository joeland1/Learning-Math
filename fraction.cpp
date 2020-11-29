#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <time.h>
#include <stdlib.h>

#include "fraction.h"

Fraction_window::Fraction_window(QWidget *parent):QWidget(parent)
{
  QHBoxLayout *overall_layout= new QHBoxLayout();
  QVBoxLayout *difficulty = new QVBoxLayout();

  QCheckBox *fundamenals_button = new QCheckBox("Fundamentals");
  QCheckBox *easy_button = new QCheckBox("Easy");
  QCheckBox *medium_button = new QCheckBox("Medium");
  QCheckBox *hard_button = new QCheckBox("Hard");

  difficulty->addWidget(new QLabel("Difficulty Presets"));
  difficulty->addWidget(fundamenals_button);
  difficulty->addWidget(easy_button);
  difficulty->addWidget(medium_button);
  difficulty->addWidget(hard_button);

  QVBoxLayout *decision = new QVBoxLayout();

  /*QCheckBox *worksheet = new QCheckBox("Create Worksheet");
  QCheckBox *worksheet_even_answers = new QCheckBox("Has even answers");
  QCheckBox *worksheet_odd_answers = new QCheckBox("Has odd answers");
  QCheckBox *answer_key = new QCheckBox("Create Answer Key");*/
  QPushButton *create = new QPushButton("Generate");

  decision->addWidget(new QLabel("Fraction"));
  /*decision->addWidget(worksheet);
  decision->addWidget(worksheet_even_answers);
  decision->addWidget(worksheet_odd_answers);
  decision->addWidget(answer_key);*/
  decision->addWidget(create);

  overall_layout->addLayout(difficulty);
  overall_layout->addLayout(decision);
  setLayout(overall_layout);
}

QList<QString> Fraction_window::convert_common_denom(QList<QString> fractions)
{
  // form in "123/2"
  QList<QString> denominators;
  for(int i=0;i<fractions.size();i++)
    denominators.append(fractions.split("/")[1]);
}

QString Fraction_window::reduce_frac(QString fraction)
{
  //form in "122/2"
  QString split_frac_pre = fraction.split("/");
  int split_frac[2]={split_frac_pre[0].toInt(), split_frac_pre[1].toInt()};
  //numerator is 0, denom is 1
  std::vector<int> numerator_factors;
  for(int i=2;i<split_frac[0];i++)
    if(split_frac%i==0)
      numerator_factors.push_back(i);

  std::vector<int> denominator_factors;
  for(int i=2;i<split_frac[1];i++)
    if(split_frac%i==0)
      denominator_factors.push_back(i);

  if(numerator_factors.size()==0||denominator_factors.size()==0)
    return fraction;

  int gcf;
  for(int i=numerator_factors.size();i>=0;i--)
  {
    for(int j=denominator_factors.size();j>=0;j--)
      if(numerator_factors.at(i)==denominator_factors.at(j))
        gcf=numerator_factors.at(i);
  }
  return QString::fromStdString((split_frac[0]/gcf)+"/"+(split_frac[1]/gcf));

}
