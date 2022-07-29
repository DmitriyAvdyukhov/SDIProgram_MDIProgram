#pragma once
#include <QtWidgets>

#include "doc_window.h"

class QMenu;
class QMdiArea;
class QSignalMapper;
class DocWindow;

class MDIProgram : public QMainWindow
{
  Q_OBJECT
public:
  MDIProgram(QWidget* p_wgt = nullptr);
private slots:
  void slotChangeWindowTitle(const QString&);

private slots:
  void slotNewDoc();
  void slotLoad();
  void slotSave();
  void slotSaveAs();
  void slotAbout();
  void slotWindows();
  void slotSetActiveSubWindow(QWidget*);

private:
  QMdiArea* p_ma_;
  QMenu* p_menu_;
  QSignalMapper* p_sig_mapper_;

  DocWindow* CreateNewDoc();
  QAction* CreateNewFileAction();
  QAction* CreateOpenFileAction();
  QAction* CreateSaveFileAction();
  void AddMenuHelp();
};


