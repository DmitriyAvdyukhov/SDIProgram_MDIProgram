#pragma once

#include <QtWidgets>
#include "doc_window.h"

class SDIProgram : public QMainWindow
{
  Q_OBJECT
public:
  SDIProgram(QWidget*p_wgt = nullptr);
  void SetMenu(QWidget*p_wgt = nullptr);
  void SetPalette(QWidget*p_wgt = nullptr);

  QMenu* CreateMenuFile(QWidget*p_wgt = nullptr);
  QMenu* CreateMenuHelp(QWidget*p_wgt = nullptr);

private slots:
  void slotAbout();
  void slotChangeWindowTitle(const QString&);
};

