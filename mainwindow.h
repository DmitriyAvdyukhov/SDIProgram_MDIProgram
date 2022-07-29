#pragma once

#include <QMainWindow>
#include <QtWidgets>
#include "doc_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void SetMenu();
  void SetToolBar();
  void SetDockWidget();

  QMenu* CreateMenuFile();
  QMenu* CreateMenuEdit();
  QMenu* CreateMenuView();
  QMenu* CreateMenuHelp();

  QAction* CreateActionSave();
  QToolBar* CreateToolBar();
  QDockWidget* CreateDockWidget();

public slots:
  void CreateSDIProgram();
private:
  Ui::MainWindow *ui;
};

