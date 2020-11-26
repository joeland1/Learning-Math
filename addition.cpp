#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QFileDialog>

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
  QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save File"),
    "test.pdf",
    tr("Images (*.pdf)"));

  QFile file(fileName);
  file.open(QIODevice::WriteOnly);
  file.write("Foo");
  file.close();

}
