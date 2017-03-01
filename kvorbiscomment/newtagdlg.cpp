#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './newtagdlg.ui'
**
** Created: Sun Jan 20 13:30:42 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "newtagdlg.h"

#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a NewTagDlg which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
NewTagDlg::NewTagDlg( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "NewTagDlg" );
    resize( 196, 118 ); 
    setCaption( i18n( "Add New Tag" ) );
    NewTagDlgLayout = new QGridLayout( this ); 
    NewTagDlgLayout->setSpacing( 0 );
    NewTagDlgLayout->setMargin( 0 );

    Frame13 = new QFrame( this, "Frame13" );
    Frame13->setFrameShape( QFrame::StyledPanel );
    Frame13->setFrameShadow( QFrame::Raised );
    Frame13->setLineWidth( 0 );
    Frame13Layout = new QVBoxLayout( Frame13 ); 
    Frame13Layout->setSpacing( 6 );
    Frame13Layout->setMargin( 0 );

    Frame11 = new QFrame( Frame13, "Frame11" );
    Frame11->setFrameShape( QFrame::StyledPanel );
    Frame11->setFrameShadow( QFrame::Raised );
    Frame11->setLineWidth( 0 );
    Frame11Layout = new QHBoxLayout( Frame11 ); 
    Frame11Layout->setSpacing( 6 );
    Frame11Layout->setMargin( 5 );

    tagLabel = new QLabel( Frame11, "tagLabel" );
    tagLabel->setLineWidth( 0 );
    tagLabel->setText( i18n( "Name" ) );
    Frame11Layout->addWidget( tagLabel );

    tagEdit = new QLineEdit( Frame11, "tagEdit" );
    Frame11Layout->addWidget( tagEdit );
    Frame13Layout->addWidget( Frame11 );

    Line1 = new QFrame( Frame13, "Line1" );
    Line1->setFrameStyle( QFrame::HLine | QFrame::Sunken );
    Frame13Layout->addWidget( Line1 );

    Frame12 = new QFrame( Frame13, "Frame12" );
    Frame12->setFrameShape( QFrame::StyledPanel );
    Frame12->setFrameShadow( QFrame::Raised );
    Frame12->setLineWidth( 0 );
    Frame12Layout = new QHBoxLayout( Frame12 ); 
    Frame12Layout->setSpacing( 6 );
    Frame12Layout->setMargin( 5 );

    okButton = new QPushButton( Frame12, "okButton" );
    okButton->setText( i18n( "&OK" ) );
    okButton->setDefault( TRUE );
    Frame12Layout->addWidget( okButton );

    cancelButton = new QPushButton( Frame12, "cancelButton" );
    cancelButton->setText( i18n( "&Cancel" ) );
    Frame12Layout->addWidget( cancelButton );
    Frame13Layout->addWidget( Frame12 );

    NewTagDlgLayout->addWidget( Frame13, 0, 0 );

    // signals and slots connections
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
NewTagDlg::~NewTagDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

#include "newtagdlg.moc"
