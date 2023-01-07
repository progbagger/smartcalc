#include <QApplication>

#include "controller/controller.h"
#include "model/model.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  s21::model::Model model;
  s21::controller::Controller controller(&model);
  s21::view::View view(&controller);
  view.Start();
  return application.exec();
}
