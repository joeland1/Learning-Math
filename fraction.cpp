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
  new QLabel(reduce_frac(QString("88/8")), this);

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
  // form in "123/2, 2/3"

  QList<QString> simplified_terms;
  for(int i=0;i<fractions.size();i++)
    simplified_terms.append(reduce_frac(simplified_terms.at(i)));

  std::vector<std::vector<int>> factored_results;
  for(int i=0;i<simplified_terms.size();i++)
  {
    int denominator = simplified_terms.at(i).split("/")[1].toInt();
    while(denominator>1)
    {
      int lowest_factor=2;
      if(denominator%lowest_factor==0)
        factored_results.at(i).push_back(lowest_factor);
      else
        lowest_factor++;
    }
  }

  /*
  { {2,2,3}, {5}, {3,5,7,11} }
  */

  std::vector<int> final_lcm_factors;
  for(int i=0;i<factored_results.at(0).size();i++)
  {
    int current_factor_testing=factored_results.at(0).at(i);
    bool is_all_same = true;
    for(int j=1;j<factored_results.size();j++)
      for(int k=0;k<factored_results.at(j).size();k++)
      {
        if(current_factor_testing==factored_results.at(j).at(k))
          break;
        else if(j==factored_results.at(j).size())
          is_all_same=false;
        else
          continue;
      }


    if(is_all_same==true)
    {
      int common_factor = factored_results.at(0).at(i);

      factored_results.at(0).erase(factored_results.at(0).begin()+i);
      for(int j=1;j<factored_results.size();j++)
      {
        bool deleted_factor=false;
        for(int k=0;deleted_factor==false;k++)
        {
          if(common_factor==factored_results.at(j).at(k))
          {
            deleted_factor=true;
            factored_results.at(i).erase(factored_results.at(i).begin()+k);
          }
        }
      }
    }
  }

  for(int i=0;i<factored_results.size();i++)
    for(int j=0;j<factored_results.at(i).size();j++)
      final_lcm_factors.push_back(factored_results.at(i).at(j));

  int lcm=1;
  for(int i=0;i<final_lcm_factors.size();i++)
    lcm*=final_lcm_factors.at(i);

  for(int i=0;i<simplified_terms.size();i++)
  {
    int multiplying_factor = lcm/simplified_terms.at(i).split("/")[1].toInt();
    int new_numerator = multiplying_factor * simplified_terms.at(i).split("/")[0].toInt();
    int new_demoninator = lcm;
    fractions.replace(i,QString(new_numerator)+QString("/")+QString(lcm));
  }
  return fractions;
}

QString Fraction_window::reduce_frac(QString fraction)
{
  //form in "122/2"
  QStringList split_frac_pre = fraction.split("/");
  int split_frac[2]={split_frac_pre.value(0).toInt(), split_frac_pre.value(1).toInt()};
  //numerator is 0, denom is 1
  std::vector<int> numerator_factors;
  for(int i=1;i<=split_frac[0];i++)
    if(split_frac[0]%i==0)
      numerator_factors.push_back(i);

  std::vector<int> denominator_factors;
  for(int i=1;i<=split_frac[1];i++)
    if(split_frac[1]%i==0)
      denominator_factors.push_back(i);

  if((numerator_factors.size()==2||denominator_factors.size()==2)&&(split_frac[0]%split_frac[1]!=0))
    return fraction;
  else
  {
    int gcf=1;
    for(int i=0;i<numerator_factors.size();i++)
    {
      for(int j=0;j<denominator_factors.size();j++)
        if(numerator_factors.at(i)==denominator_factors.at(j))
          gcf=numerator_factors.at(i);
    }
    if(split_frac[1]/gcf==1)
      return QString::number(split_frac[0]/gcf);
    return QString::number(split_frac[0]/gcf)+QString("/")+QString::number(split_frac[1]/gcf);
  }
}
