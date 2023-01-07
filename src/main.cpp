#include <QApplication>

#include "controller/controller.h"
#include "model/model.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  calculator::model::Model model;
  calculator::controller::Controller controller(&model);
  calculator::view::View view(&controller);
  view.Start();
  return application.exec();
}
