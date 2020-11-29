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
#include <stdlib.h>
#include <time.h>
#include <QPointF>
#include <QRectF>
#include <QStringList>

#include "addition.h"

Addition_window::Addition_window(QWidget *parent):QWidget(parent)
{
  srand(time(0));
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

    QPointF last_problem_pos;
    bool is_start=true;
    QPointF start_point(1000,500);
    for(int question_count=50;question_count>0;question_count--)
    {
      if(question_count==49)
      {
        std::vector<std::string> number_vector;
        number_vector = generate_qa_pair(number_vector);

        QRectF problem_location=draw_problem(80, painter, start_point, number_vector);
        last_problem_pos=QPointF(problem_location.right()+start_point.x(), start_point.y());
        is_start=false;
      }
      /*else
      {
        std::string * numbers = generate_qa_pair();
        QRectF last_problem_pending_area = calc_rect(80, painter, numbers);
        QPointF last_problem_pending_point=QPointF(last_problem_pending_area.right()+last_problem_pos.x(), last_problem_pos.y());
        if(last_problem_pending_area.right()+last_problem_pos.x()>=painter->viewport().right())
        {
          last_problem_pending_point = QPointF(start_point.x(),last_problem_pos.y()+200);
          QRectF answer_rect = draw_problem(80,painter,last_problem_pending_point, numbers);
          last_problem_pending_point = QPointF(last_problem_pending_point.x()+answer_rect.right(), last_problem_pending_point.y());
        }
        else
          draw_problem(80, painter, last_problem_pos, numbers);
        last_problem_pos=last_problem_pending_point;
      }*/

    }
    painter->end();
}

QRectF Addition_window::draw_problem(int font_size, QPainter *painter, QPointF location, std::vector<std::string> numbers_inside_vector)
{
  int  length = numbers_inside_vector.size();
  std::string numbers[length];
  for(int i=0;i<length;i++)
    numbers[i]=numbers_inside_vector.at(i);

  QString generated_problem="";

  for(int i=0;i<length;i++)
  {
    if(i==length-1)
      generated_problem.append(QString::fromStdString(numbers[i]));
    else if (i==length-2)
      generated_problem.append(QString::fromStdString(numbers[i]+"="));
    else
      generated_problem.append(QString::fromStdString(numbers[i]+"+"));
  }
  QRectF area = painter->boundingRect(painter->viewport(), generated_problem+QString::fromStdString("\t\t\t\t"));
  painter->drawText(location, generated_problem);
  return area;
  //painter->drawText(location, answer);
}

QRectF Addition_window::calc_rect(int font_size, QPainter *painter, std::string * numbers)
{
  QString generated_problem="";
  int  length = 0;
  while (!numbers[length].empty())
        ++length;

  for(int i=0;i<length;i++)
  {
    if(i==length-1)
      generated_problem.append(QString::fromStdString(numbers[i]));
    else if (i==length-2)
      generated_problem.append(QString::fromStdString(numbers[i]+"="));
    else
      generated_problem.append(QString::fromStdString(numbers[i]+"+"));
  }
  QRectF area = painter->boundingRect(painter->viewport(), generated_problem+QString::fromStdString("\t\t\t\t"));
  return area;
}

std::vector<std::string> Addition_window::generate_qa_pair(std::vector<std::string> question_destionation) //last index is the solution
{
  int ctr=rand() % 6+2;
  for(int i=0;i<=ctr;i++)
  {
    if(i==ctr)
    {
      std::string x[question_destionation.size()];
      for(int i=0;i<question_destionation.size();i++)
        x[i]=question_destionation.at(i);
      question_destionation.push_back(calc_answer(x, sizeof(x)/sizeof(*x)));
    }
    else
      question_destionation.push_back(std::to_string(rand() % 6+1));
  }

  return question_destionation;
}

std::string Addition_window::calc_answer(std::string string_numbers[], int length)
{
  int array_length = length;
  int num_sides[array_length][2];

  for (int i = 0; i < array_length; i++)
  {
    std::size_t found = string_numbers[i].find ('.');
    if (found != std::string::npos)
  	{
  	  num_sides[i][0] = found;
  	  num_sides[i][1] = string_numbers[i].length () - found - 1;
  	}
    else
  	{
  	  num_sides[i][0] = string_numbers[i].length ();
  	  num_sides[i][1] = 0;
  	}
  }

  int largest_left=-1;
  int largest_right=-1;

  for (int i = 0; i < array_length; i++)
  {
      if(num_sides[i][0]>largest_left)
        largest_left=num_sides[i][0];
      if(num_sides[i][1]>largest_right)
        largest_right=num_sides[i][1];
  }

  for(int i=0; i<array_length;i++)
  {
    while(num_sides[i][0]<largest_left)
    {
      string_numbers[i]="0"+string_numbers[i];
      num_sides[i][0]++;
    }
    while(num_sides[i][1]<largest_right)
    {
      string_numbers[i]+="0";
      num_sides[i][1]++;
    }
  }

  for(int i=0;i<array_length;i++)
  {
    if(string_numbers[i].length()==1+largest_left+largest_right)
      continue;
    else
      string_numbers[i].insert(num_sides[i][0],".");
  }

  std::string final = "";
  int carry_over = 0;
  for(int i=string_numbers[0].length()-1;i>=0;i--)
  {
    int total_for_place=0;
    bool is_decimal=false;
    for(int j=0;j<array_length;j++)
    {
      if(string_numbers[j][i]=='.')
      {
        is_decimal=true;
        break;
      }
      else
      {
        total_for_place+=string_numbers[j][i]-'0';
      }
    }
    if(is_decimal == true)
        continue;
    total_for_place+=carry_over%10;
    carry_over/=10;
    final.insert(0, std::to_string(total_for_place%10));
    total_for_place/=10;
    carry_over+=total_for_place;
  }
  if(carry_over!=0)
    final=std::to_string(carry_over)+final;

  if(largest_right!=0)
    final.insert(largest_left, ".");

  return final;
}
