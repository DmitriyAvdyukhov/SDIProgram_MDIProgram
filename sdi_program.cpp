#include "sdi_program.h"

//-----------SDIProgrm--------------

SDIProgram::SDIProgram(QWidget*p_wgt) : QMainWindow(p_wgt)
{
  DocWindow* p_doc = new DocWindow;
  SetPalette(p_doc);
  SetMenu(p_doc);
  setCentralWidget(p_doc);
  connect(p_doc, SIGNAL(changeWindowTitle(const QString&))
          , SLOT(slotChangeWindowTitle(const QString&)));
  statusBar()->showMessage("Ready", 2000);
}



void SDIProgram::SetMenu(QWidget*p_wgt)
{
  menuBar()->addMenu(CreateMenuFile(p_wgt));
  menuBar()->addMenu(CreateMenuHelp());
}

QMenu* SDIProgram::CreateMenuFile(QWidget*p_wgt)
{
  QMenu* p_menu = new QMenu("&File");
  p_menu->addAction("&Open...", p_wgt, SLOT(slotLoad()),QKeySequence("CTRL+O"));
  p_menu->addAction("&Save...", p_wgt, SLOT(slotSave()),QKeySequence("CTRL+S"));
  p_menu->addAction("&Save As...", p_wgt, SLOT(slotSaveAs()));
  p_menu->addSeparator();
  p_menu->addAction("&Close", this, SLOT(close()),QKeySequence("CTRL+F4"));
  p_menu->addAction("&Quit", qApp, SLOT(quit()),QKeySequence("CTRL+Q"));
  return p_menu;
}

QMenu* SDIProgram::CreateMenuHelp(QWidget*p_wgt)
{
  QMenu* p_menu = new QMenu("&Help");
  p_menu->addAction("&About", this, SLOT(slotAbout()), Qt::Key_F1);
  return p_menu;
}

void SDIProgram::slotAbout()
{
  QMessageBox::about(this, "Application", "SDI Program Example");
}

void SDIProgram::slotChangeWindowTitle(const QString& str)
{
  setWindowTitle(str);
}

void SDIProgram::SetPalette(QWidget*p_wgt)
{
  QPalette* p_palette = new QPalette(p_wgt->palette());
  p_palette->setColor(QPalette::Text, Qt::red);
  p_palette->setColor(QPalette::Active, QPalette::Base, Qt::blue);
  p_wgt->setPalette(*p_palette);
}


