#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPageSize>
#include <QPainter>
#include <QMargins>
#include <QPageLayout>

#include "addition.h"

Addition_window::Addition_window(QWidget *parent):QWidget(parent)
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

  QCheckBox *worksheet = new QCheckBox("Create Worksheet");
  QCheckBox *worksheet_even_answers = new QCheckBox("Has even answers");
  QCheckBox *worksheet_odd_answers = new QCheckBox("Has odd answers");
  QCheckBox *answer_key = new QCheckBox("Create Answer Key");
  QPushButton *create = new QPushButton("Generate");

  connect(create, &QPushButton::pressed, this, &Addition_window::create_pdf);

  decision->addWidget(new QLabel("Options"));
  decision->addWidget(worksheet);
  decision->addWidget(worksheet_even_answers);
  decision->addWidget(worksheet_odd_answers);
  decision->addWidget(answer_key);
  decision->addWidget(create);

  overall_layout->addLayout(difficulty);
  overall_layout->addLayout(decision);
  setLayout(overall_layout);
}

void Addition_window::create_pdf()
{
  QString filename = QFileDialog::getSaveFileName(this,
    tr("Save File"),
    "test.pdf",
    tr("Images (*.pdf)"));

    QPdfWriter *writer = new QPdfWriter(filename);
    QPainter *painter = new QPainter(writer);

    painter->drawText(100,100, "string 1");

    create_problem(80, painter);
    painter->end();
}

void Addition_window::create_problem(int font_size, QPainter *painter)
{
  painter->drawText(1000,1000, "test string");
}

string Addition_window::calc_answer(string num1, string num2)
{
  //num1="123.123" num2="2"
  // first index is numbers above decimal, second index is numbers right of  decimal
  int num1_sides [2];
  int num2_sides [2];

  std::size_t found = num1.find('.');
  //found is the index
  if (found != std::string::npos)
  {
    num1_sides[0]=found;
    num1_sides[1]=num1.length()-found-1;
  }
  else
  {
    num1_sides[0]=num1.length()-1;
    num1_sides[1]=0;
  }

  found = num2.find('.');
  if (found != std::string::npos)
  {
    num2_sides[0]=found;
    num2_sides[1]=num2.length()-found-1;
  }
  else
  {
    num2_sides[0]=num2.length()-1;
    num2_sides[1]=0;
  }
  
  while()
}
