#include "doc_window.h"

DocWindow::DocWindow(QWidget* p_wgt) : QTextEdit(p_wgt)
{}

void DocWindow::slotLoad()
{
  QString str = QFileDialog::getOpenFileName();
  if (str.isEmpty())
    {
      return;
    }

  QFile file(str);
  if (file.open(QIODevice::ReadOnly))
    {
      QTextStream stream(&file);
      setPlainText(stream.readAll());
      file.close();
      file_name_ = str;
      emit changeWindowTitle(file_name_);
    }
}

void DocWindow::slotSaveAs()
{
  QString str = QFileDialog::getSaveFileName(0, file_name_);
  if (!str.isEmpty())
    {
      file_name_= str;
      slotSave();
    }
}

void DocWindow::slotSave()
{
  if (file_name_.isEmpty())
    {
      slotSaveAs();
      return;
    }
  QFile file(file_name_);
  if(file.open(QIODevice::WriteOnly))
    {
      QTextStream(&file) << toPlainText();
      file.close();
      emit changeWindowTitle(file_name_);
    }
}

