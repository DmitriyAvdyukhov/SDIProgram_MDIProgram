#pragma once

#include <QtWidgets>

class DocWindow : public QTextEdit
{
  Q_OBJECT
public:
  DocWindow(QWidget*p_wgt = nullptr);
signals:
  void changeWindowTitle(const QString&);

public slots:
  void slotLoad();
  void slotSave();
  void slotSaveAs();

private:
  QString file_name_;
};
