/****************************************************************************
** Form interface generated from reading ui file './newtag.ui'
**
** Created: Sat Dec 22 21:59:11 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef NEWTAGDLG_H
#define NEWTAGDLG_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;

class NewTagDlg : public QDialog
{ 
    Q_OBJECT

public:
    NewTagDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~NewTagDlg();

    QFrame* Frame13;
    QFrame* Frame11;
    QLabel* tagLabel;
    QLineEdit* tagEdit;
    QFrame* Line1;
    QFrame* Frame12;
    QPushButton* okButton;
    QPushButton* cancelButton;

protected:
    QGridLayout* NewTagDlgLayout;
    QVBoxLayout* Frame13Layout;
    QHBoxLayout* Frame11Layout;
    QHBoxLayout* Frame12Layout;
};

#endif // NEWTAGDLG_H
