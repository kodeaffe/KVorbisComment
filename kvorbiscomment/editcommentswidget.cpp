#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './editcommentswidget.ui'
**
** Created: Sun Jan 20 13:30:44 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "editcommentswidget.h"

#include <kcombobox.h>
#include <klineedit.h>
#include <qframe.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a EditCommentsWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
EditCommentsWidget::EditCommentsWidget( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "EditCommentsWidget" );
    resize( 441, 506 ); 
    setCaption( i18n( "Form1" ) );
    EditCommentsWidgetLayout = new QGridLayout( this ); 
    EditCommentsWidgetLayout->setSpacing( 0 );
    EditCommentsWidgetLayout->setMargin( 0 );

    Frame39 = new QFrame( this, "Frame39" );
    Frame39->setFrameShape( QFrame::StyledPanel );
    Frame39->setFrameShadow( QFrame::Raised );
    Frame39Layout = new QHBoxLayout( Frame39 ); 
    Frame39Layout->setSpacing( 6 );
    Frame39Layout->setMargin( 1 );

    Frame17 = new QFrame( Frame39, "Frame17" );
    Frame17->setFrameShape( QFrame::StyledPanel );
    Frame17->setFrameShadow( QFrame::Raised );
    Frame17->setLineWidth( 0 );
    Frame17Layout = new QVBoxLayout( Frame17 ); 
    Frame17Layout->setSpacing( 0 );
    Frame17Layout->setMargin( 5 );

    labelTitle = new QLabel( Frame17, "labelTitle" );
    labelTitle->setText( i18n( "TITLE" ) );
    Frame17Layout->addWidget( labelTitle );

    labelVersion = new QLabel( Frame17, "labelVersion" );
    labelVersion->setText( i18n( "VERSION" ) );
    Frame17Layout->addWidget( labelVersion );

    labelAlbum = new QLabel( Frame17, "labelAlbum" );
    labelAlbum->setText( i18n( "ALBUM" ) );
    Frame17Layout->addWidget( labelAlbum );

    labelTracknumber = new QLabel( Frame17, "labelTracknumber" );
    labelTracknumber->setText( i18n( "TRACKNUMBER" ) );
    Frame17Layout->addWidget( labelTracknumber );

    labelArtist = new QLabel( Frame17, "labelArtist" );
    labelArtist->setText( i18n( "ARTIST" ) );
    Frame17Layout->addWidget( labelArtist );

    labelPerformer = new QLabel( Frame17, "labelPerformer" );
    labelPerformer->setText( i18n( "PERFORMER" ) );
    Frame17Layout->addWidget( labelPerformer );

    labelOrganization = new QLabel( Frame17, "labelOrganization" );
    labelOrganization->setText( i18n( "ORGANIZATION" ) );
    Frame17Layout->addWidget( labelOrganization );

    labelDescription = new QLabel( Frame17, "labelDescription" );
    labelDescription->setText( i18n( "DESCRIPTION" ) );
    Frame17Layout->addWidget( labelDescription );

    labelGenre = new QLabel( Frame17, "labelGenre" );
    labelGenre->setText( i18n( "GENRE" ) );
    Frame17Layout->addWidget( labelGenre );

    labelDate = new QLabel( Frame17, "labelDate" );
    labelDate->setText( i18n( "DATE" ) );
    Frame17Layout->addWidget( labelDate );

    labelLocation = new QLabel( Frame17, "labelLocation" );
    labelLocation->setText( i18n( "LOCATION" ) );
    Frame17Layout->addWidget( labelLocation );

    labelCopyright = new QLabel( Frame17, "labelCopyright" );
    labelCopyright->setText( i18n( "COPYRIGHT" ) );
    Frame17Layout->addWidget( labelCopyright );

    labelContact = new QLabel( Frame17, "labelContact" );
    labelContact->setText( i18n( "CONTACT" ) );
    Frame17Layout->addWidget( labelContact );

    labelIsrc = new QLabel( Frame17, "labelIsrc" );
    labelIsrc->setText( i18n( "ISRC" ) );
    Frame17Layout->addWidget( labelIsrc );

    labelDiscid = new QLabel( Frame17, "labelDiscid" );
    labelDiscid->setText( i18n( "DISCID" ) );
    Frame17Layout->addWidget( labelDiscid );

    variableCombo = new KComboBox( FALSE, Frame17, "variableCombo" );
    variableCombo->insertItem( i18n( "Add New Tag..." ) );
    variableCombo->setEnabled( FALSE );
    Frame17Layout->addWidget( variableCombo );
    Frame39Layout->addWidget( Frame17 );

    Frame18 = new QFrame( Frame39, "Frame18" );
    Frame18->setFrameShape( QFrame::StyledPanel );
    Frame18->setFrameShadow( QFrame::Raised );
    Frame18->setLineWidth( 0 );
    Frame18Layout = new QVBoxLayout( Frame18 ); 
    Frame18Layout->setSpacing( 0 );
    Frame18Layout->setMargin( 5 );

    fixedEditTitle = new KLineEdit( Frame18, "fixedEditTitle" );
    fixedEditTitle->setEnabled( FALSE );
    fixedEditTitle->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditTitle );

    fixedEditVersion = new KLineEdit( Frame18, "fixedEditVersion" );
    fixedEditVersion->setEnabled( FALSE );
    fixedEditVersion->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditVersion );

    fixedEditAlbum = new KLineEdit( Frame18, "fixedEditAlbum" );
    fixedEditAlbum->setEnabled( FALSE );
    fixedEditAlbum->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditAlbum );

    fixedEditTracknumber = new KLineEdit( Frame18, "fixedEditTracknumber" );
    fixedEditTracknumber->setEnabled( FALSE );
    fixedEditTracknumber->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditTracknumber );

    fixedEditArtist = new KLineEdit( Frame18, "fixedEditArtist" );
    fixedEditArtist->setEnabled( FALSE );
    fixedEditArtist->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditArtist );

    fixedEditPerformer = new KLineEdit( Frame18, "fixedEditPerformer" );
    fixedEditPerformer->setEnabled( FALSE );
    fixedEditPerformer->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditPerformer );

    fixedEditOrganization = new KLineEdit( Frame18, "fixedEditOrganization" );
    fixedEditOrganization->setEnabled( FALSE );
    fixedEditOrganization->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditOrganization );

    fixedEditDescription = new KLineEdit( Frame18, "fixedEditDescription" );
    fixedEditDescription->setEnabled( FALSE );
    fixedEditDescription->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditDescription );

    fixedEditGenre = new KLineEdit( Frame18, "fixedEditGenre" );
    fixedEditGenre->setEnabled( FALSE );
    fixedEditGenre->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditGenre );

    fixedEditDate = new KLineEdit( Frame18, "fixedEditDate" );
    fixedEditDate->setEnabled( FALSE );
    fixedEditDate->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditDate );

    fixedEditLocation = new KLineEdit( Frame18, "fixedEditLocation" );
    fixedEditLocation->setEnabled( FALSE );
    fixedEditLocation->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditLocation );

    fixedEditCopyright = new KLineEdit( Frame18, "fixedEditCopyright" );
    fixedEditCopyright->setEnabled( FALSE );
    fixedEditCopyright->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditCopyright );

    fixedEditContact = new KLineEdit( Frame18, "fixedEditContact" );
    fixedEditContact->setEnabled( FALSE );
    fixedEditContact->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditContact );

    fixedEditIsrc = new KLineEdit( Frame18, "fixedEditIsrc" );
    fixedEditIsrc->setEnabled( FALSE );
    fixedEditIsrc->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditIsrc );

    fixedEditDiscid = new KLineEdit( Frame18, "fixedEditDiscid" );
    fixedEditDiscid->setEnabled( FALSE );
    fixedEditDiscid->setAcceptDrops( FALSE );
    Frame18Layout->addWidget( fixedEditDiscid );

    Frame36 = new QFrame( Frame18, "Frame36" );
    Frame36->setFrameShape( QFrame::StyledPanel );
    Frame36->setFrameShadow( QFrame::Raised );
    Frame36->setLineWidth( 0 );
    Frame36Layout = new QHBoxLayout( Frame36 ); 
    Frame36Layout->setSpacing( 0 );
    Frame36Layout->setMargin( 0 );

    variableEdit = new KLineEdit( Frame36, "variableEdit" );
    variableEdit->setEnabled( FALSE );
    variableEdit->setAcceptDrops( FALSE );
    Frame36Layout->addWidget( variableEdit );
    QSpacerItem* spacer = new QSpacerItem( 1, 20, QSizePolicy::Maximum, QSizePolicy::Minimum );
    Frame36Layout->addItem( spacer );

    variableRemoveButton = new QPushButton( Frame36, "variableRemoveButton" );
    variableRemoveButton->setEnabled( FALSE );
    variableRemoveButton->setText( i18n( "&Remove" ) );
    Frame36Layout->addWidget( variableRemoveButton );
    Frame18Layout->addWidget( Frame36 );
    Frame39Layout->addWidget( Frame18 );

    EditCommentsWidgetLayout->addWidget( Frame39, 0, 0 );

    buttonFrame = new QFrame( this, "buttonFrame" );
    buttonFrame->setFrameShape( QFrame::StyledPanel );
    buttonFrame->setFrameShadow( QFrame::Raised );
    buttonFrameLayout = new QHBoxLayout( buttonFrame ); 
    buttonFrameLayout->setSpacing( 6 );
    buttonFrameLayout->setMargin( 11 );

    saveButton = new QPushButton( buttonFrame, "saveButton" );
    saveButton->setEnabled( FALSE );
    saveButton->setText( i18n( "&Save" ) );
    buttonFrameLayout->addWidget( saveButton );
    QSpacerItem* spacer_2 = new QSpacerItem( 40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    buttonFrameLayout->addItem( spacer_2 );

    replaceCommentsButton = new QPushButton( buttonFrame, "replaceCommentsButton" );
    replaceCommentsButton->setEnabled( FALSE );
    replaceCommentsButton->setText( i18n( "&Replace Comments" ) );
    buttonFrameLayout->addWidget( replaceCommentsButton );

    appendCommentsButton = new QPushButton( buttonFrame, "appendCommentsButton" );
    appendCommentsButton->setEnabled( FALSE );
    appendCommentsButton->setText( i18n( "&Append Comments" ) );
    buttonFrameLayout->addWidget( appendCommentsButton );

    EditCommentsWidgetLayout->addWidget( buttonFrame, 1, 0 );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
EditCommentsWidget::~EditCommentsWidget()
{
    // no need to delete child widgets, Qt does it all for us
}

#include "editcommentswidget.moc"
