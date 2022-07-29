#include "mdi_program.h"

//---------class MDIProgram---------------------

MDIProgram::MDIProgram(QWidget* p_wgt) : QMainWindow(p_wgt)
{   
  QAction* p_new = CreateNewFileAction();
  QAction* p_open = CreateOpenFileAction();
  QAction* p_save = CreateSaveFileAction();

  QToolBar* p_tb_file = new QToolBar("File Operations");
  p_tb_file->addAction(p_new);
  p_tb_file->addAction(p_open);
  p_tb_file->addAction(p_save);
  addToolBar(Qt::TopToolBarArea, p_tb_file);

  QMenu* p_menu = new QMenu("&File");
  p_menu->addAction(p_new);
  p_menu->addAction(p_open);
  p_menu->addAction(p_save);
  p_menu->addAction("Save &As...", this, SLOT(slotSaveAs()));
  p_menu->addSeparator();
  p_menu->addAction("&Quit", qApp,
                    SLOT(closeAllWindows()), QKeySequence("CTRL+Q"));

  menuBar()->addMenu(p_menu);
  p_menu_ = new QMenu("&Windows");
  menuBar()->addMenu(p_menu_);
  connect(p_menu_, SIGNAL(aboutToShow()), SLOT(slotWindows()));
  menuBar()->addSeparator();
  AddMenuHelp();

  p_ma_ = new QMdiArea(this);
  p_ma_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  p_ma_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

  setCentralWidget(p_ma_);

  p_sig_mapper_ = new QSignalMapper(this);
  connect(p_sig_mapper_, SIGNAL(mapped(QWidget*)),
          this, SLOT(slotSetActiveSubWindow(QWidget*)));

  statusBar()->showMessage("Ready", 3000);
}

QAction* MDIProgram::CreateNewFileAction()
{
  QAction* p_act = new QAction("New File", 0);
  p_act->setText("&New");
  p_act->setShortcut(QKeySequence("CTRL+N"));
  p_act->setToolTip("New Document");
  p_act->setStatusTip("Create a new file");
  p_act->setWhatsThis("Create a new file");
  p_act->setIcon(QPixmap("Y:/source_qt/Image/docs.png"));
  connect(p_act, SIGNAL(triggered()), SLOT(slotNewDoc()));
  return p_act;
}

QAction* MDIProgram::CreateOpenFileAction()
{
  QAction* p_act = new QAction("Open File", 0);
  p_act->setText("&Open");
  p_act->setShortcut(QKeySequence("CTRL+O"));
  p_act->setToolTip("Open Document");
  p_act->setStatusTip("Open an exesting  file");
  p_act->setWhatsThis("Open an exesting file");
  p_act->setIcon(QPixmap("Y:/source_qt/Image/open_folder.png"));
  connect(p_act, SIGNAL(triggered()), SLOT(slotLoad()));
  return p_act;
}

QAction* MDIProgram::CreateSaveFileAction()
{
  QAction* p_act = new QAction("Save File", 0);
  p_act->setText("&Save");
  p_act->setShortcut(QKeySequence("CTRL+S"));
  p_act->setToolTip("Save Document");
  p_act->setStatusTip("Save the file to disk");
  p_act->setWhatsThis("Save the file to disk");
  p_act->setIcon(QPixmap("Y:/source_qt/Image/floppy-disk.png"));
  connect(p_act, SIGNAL(triggered()), SLOT(slotSave()));
  return p_act;
}

void MDIProgram::AddMenuHelp()
{
  QMenu* p_menu = new QMenu("&Help");
  p_menu->addAction("&About", this, SLOT(slotAbout()), Qt::Key_F1);
  menuBar()->addMenu(p_menu);
}

DocWindow* MDIProgram::CreateNewDoc()
{
  DocWindow* p_doc = new DocWindow;   
  p_doc->setWindowTitle("Unnamed Document");
  p_doc->setWindowIcon(QPixmap("Y:/source_qt/Image/file.png"));
  connect(p_doc,
          SIGNAL(changeWindowTitle(const QString&)),
          SLOT(slotChangeWindowTitle(const QString&)));

  QMdiSubWindow* p_sub = new QMdiSubWindow(p_ma_);
  p_sub->setWidget(p_doc);
  p_sub->setAttribute(Qt::WA_DeleteOnClose);
  p_ma_->addSubWindow(p_sub);

  return p_doc;
}

void MDIProgram::slotNewDoc()
{
  CreateNewDoc()->show();
}

void MDIProgram::slotLoad()
{
  DocWindow* p_doc = CreateNewDoc();
  p_doc->slotLoad();
  p_doc->show();
}

void MDIProgram::slotSave()
{ 
  DocWindow* p_doc = static_cast<DocWindow*>(p_ma_->activeSubWindow()->widget());
  if (p_doc)
    {
      p_doc->slotSave();
    }
}

void MDIProgram::slotSaveAs()
{
  DocWindow* p_doc = qobject_cast<DocWindow*>(p_ma_->activeSubWindow()->widget());
  if (p_doc)
    {
      p_doc->slotSaveAs();
    }
}

void MDIProgram::slotAbout()
{
  QMessageBox::about(this, "Applacation", "MDI Program Exampel");
}

void MDIProgram::slotWindows()
{
  p_menu_->clear();

  QAction* p_act = p_menu_->addAction("&Cascade",
                                      p_ma_,
                                      SLOT(cascadeSubWindows()));
  p_act->setEnabled(!p_ma_->subWindowList().isEmpty());

  p_act = p_menu_->addAction("&Tile",
                             p_ma_,
                             SLOT(tileSubWindows()));
  p_act->setEnabled(!p_ma_->subWindowList().isEmpty());

  p_menu_->addSeparator();

  QList<QMdiSubWindow*> list_doc = p_ma_->subWindowList();
  for(int i = 0; i < list_doc.size(); ++i)
    {
      p_act = p_menu_->addAction(list_doc.at(i)->windowTitle());
      p_act->setCheckable(true);
      p_act->setChecked(p_ma_->activeSubWindow() == list_doc.at(i));
      connect(p_act, SIGNAL(triggerd()), p_sig_mapper_, SLOT(map()));
      p_sig_mapper_->setMapping(p_act, list_doc.at(i));
    }
}

void MDIProgram::slotSetActiveSubWindow(QWidget* p_wgt)
{
  if (p_wgt)
    {
      p_ma_->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(p_wgt));
    }
}

void MDIProgram::slotChangeWindowTitle(const QString& str)
{
  qobject_cast<DocWindow*>(sender())->setWindowTitle(str);;
}

