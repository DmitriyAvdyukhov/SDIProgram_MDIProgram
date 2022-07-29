#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sdi_program.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  SetMenu();
  SetToolBar();
  SetDockWidget();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::SetMenu()
{
  menuBar()->addMenu(CreateMenuFile());
  menuBar()->addMenu(CreateMenuEdit());
  menuBar()->addMenu(CreateMenuView());
  menuBar()->addMenu(CreateMenuHelp());
}

QMenu* MainWindow::CreateMenuFile()
{
  QMenu* p_menu = new QMenu("&File");
  p_menu->addAction("&Open");
  p_menu->addAction(CreateActionSave());
  p_menu->addAction("&New", this, SLOT(CreateSDIProgram()));
  p_menu->addAction("&Print");
  p_menu->addAction("&Quit", qApp, SLOT(quit()),QKeySequence("CTRL+Q"));
  return p_menu;
}

QMenu* MainWindow::CreateMenuEdit()
{
  QMenu* p_menu1 = new QMenu("&Edit");
  p_menu1->addAction("&Cut");
  p_menu1->addAction("&Copy");
  p_menu1->addAction("&Paste");
  p_menu1->addAction("&Undo");
  p_menu1->addAction("&Redo");
  p_menu1->addAction("&Find");
  p_menu1->addAction("&Replace");
  p_menu1->addAction("&Delete");
  return p_menu1;
}

QMenu* MainWindow::CreateMenuView()
{
  QMenu* p_menu = new QMenu("&View");
  p_menu->addAction("&Zoom");
  return p_menu;
}

QMenu* MainWindow::CreateMenuHelp()
{
  QMenu* p_menu = new QMenu("&Help");
  p_menu->addAction("&Help");
  p_menu->addAction("&About");
  return p_menu;
}

QAction* MainWindow::CreateActionSave()
{
  QAction* p_save = new QAction("File save action", 0);
  p_save->setText("&Save");
  p_save->setShortcut(QKeySequence("CTRL+S"));
  p_save->setToolTip("Save Document");
  p_save->setStatusTip("Save the file to disck");
  p_save->setWhatsThis("Save thr file to disck");
  p_save->setIcon(QPixmap("Y:/source_qt/Image/Linux.png"));
  connect(p_save, SIGNAL(triggered()), SLOT(slotSave()));
  return p_save;
}

QToolBar* MainWindow::CreateToolBar()
{
  QToolBar* p_tbr = new QToolBar("Lincker ToolBar");

  p_tbr->addAction(QPixmap("Y:/source_qt/Image/Linux.png"), "Linux", this, SLOT(slotNoImpl()));
  p_tbr->addAction(QPixmap("Y:/source_qt/Image/MacOSX.png"), "MacOSX", this, SLOT(slotNoImpl()));
  p_tbr->addSeparator();
  p_tbr->addAction(QPixmap("Y:/source_qt/Image/Android.png"), "Android", this, SLOT(slotNoImpl()));
  return p_tbr;
}

void MainWindow::SetToolBar()
{
  addToolBar(Qt::TopToolBarArea, CreateToolBar());
}

 QDockWidget* MainWindow::CreateDockWidget()
 {
   QDockWidget* p_dock = new QDockWidget("My Dock", this);
   QLabel* p_lbl = new QLabel("Label in Dock", p_dock);
   p_dock->setWidget(p_lbl);
   //разрешение на расположение dock
   p_dock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea
                           | Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
   return p_dock;
 }

 void MainWindow::SetDockWidget()
 {
   addDockWidget(Qt::LeftDockWidgetArea, CreateDockWidget());
 }

 void MainWindow::CreateSDIProgram()
 {
   SDIProgram* program = new SDIProgram(this);
   QPropertyAnimation* p_animation = new QPropertyAnimation(program, "geometry");
   p_animation->setDuration(2000);
   p_animation->setStartValue(QRect(900, 480, 300, 200));
   p_animation->setEndValue(QRect(1800, 400, 350, 250));
   p_animation->setEasingCurve(QEasingCurve::InSine);
   p_animation->start();
   program->show();
 }
