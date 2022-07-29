#include "mainwindow.h"
#include "doc_window.h"
#include "mdi_program.h"
#include "sdi_program.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

//  SDIProgram p;
//  p.show();

  MDIProgram m;
  m.show();
  return a.exec();
}
