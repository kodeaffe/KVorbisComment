/***************************************************************************
                          kvorbiscomment.cpp  -  description
                             -------------------
    begin                : Fre Dez  7 10:23:00 CET 2001
    copyright            : (C) 2001 by sebastian henschel
    email                : s.henschel@berlin.de
 ***************************************************************************/

/***************************************************************************
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 ***************************************************************************/

#include <qdir.h>
#include <qprinter.h>
#include <qpainter.h>
#include <qclipboard.h>

#include <kiconloader.h>
#include <kmessagebox.h>
#include <kfiledialog.h>
#include <kmenubar.h>
//#include <kstatusbar.h>
#include <klocale.h>
#include <kconfig.h>
#include <kstdaction.h>
#include <kaccel.h>
#include <kpopupmenu.h>
#include <kpushbutton.h>

#include "kvorbiscomment.h"
#include "kvorbiscommentview.h"
#include "kvorbiscommentdoc.h"
#include "commentsfiledlg.h"

#define ID_STATUS_MSG 1

KVorbisCommentApp::KVorbisCommentApp (QWidget* , const char* name) : KMainWindow (0, name)
{
  config = kapp->config ();

	//initStatusBar ();
	initActions ();
	initDocument ();
	initView ();
	
	readOptions ();

	// disable actions at startup
	fileSave->setEnabled (false);
	fileSaveAs->setEnabled (false);
	//filePrint->setEnabled (false);
	editCut->setEnabled (false);
	editCopy->setEnabled (false);
	editPaste->setEnabled (false);
	replaceComments->setEnabled (false);
	appendComments->setEnabled (false);
}

KVorbisCommentApp::~KVorbisCommentApp (){ }



void KVorbisCommentApp::initActions ()
{
  //fileNewWindow = new KAction(i18n("New &Window"), 0, 0, this, SLOT(slotFileNewWindow()), actionCollection(),"file_new_window");
  //fileNew = KStdAction::openNew(this, SLOT(slotFileNew()), actionCollection());
  fileOpen = KStdAction::open(this, SLOT(slotFileOpen()), actionCollection());
  fileOpenRecent = KStdAction::openRecent(this, SLOT(slotFileOpenRecent(const KURL&)), actionCollection());
  fileSave = KStdAction::save(this, SLOT(slotFileSave()), actionCollection());
  fileSaveAs = KStdAction::saveAs(this, SLOT(slotFileSaveAs()), actionCollection());
  //fileClose = KStdAction::close(this, SLOT(slotFileClose()), actionCollection());
  //filePrint = KStdAction::print(this, SLOT(slotFilePrint()), actionCollection());
  fileQuit = KStdAction::quit(this, SLOT(slotFileQuit()), actionCollection());
  editCut = KStdAction::cut(this, SLOT(slotEditCut()), actionCollection());
  editCopy = KStdAction::copy(this, SLOT(slotEditCopy()), actionCollection());
  editPaste = KStdAction::paste(this, SLOT(slotEditPaste()), actionCollection());
  viewToolBar = KStdAction::showToolbar(this, SLOT(slotViewToolBar()), actionCollection());
//  viewStatusBar = KStdAction::showStatusbar(this, SLOT(slotViewStatusBar()), actionCollection());



  //fileNewWindow->setStatusText(i18n("Opens a new application window"));
  //fileNew->setStatusText(i18n("Creates a new document"));
  fileOpen->setStatusText(i18n("Opens an existing document"));
  fileOpenRecent->setStatusText(i18n("Opens a recently used file"));
  fileSave->setStatusText(i18n("Saves the actual document"));
  fileSaveAs->setStatusText(i18n("Saves the actual document as..."));
  //fileClose->setStatusText(i18n("Closes the actual document"));
  //filePrint ->setStatusText(i18n("Prints out the actual document"));
  fileQuit->setStatusText(i18n("Quits the application"));
  editCut->setStatusText(i18n("Cuts the selected section and puts it to the clipboard"));
  editCopy->setStatusText(i18n("Copies the selected section to the clipboard"));
  editPaste->setStatusText(i18n("Pastes the clipboard contents to actual position"));
  viewToolBar->setStatusText(i18n("Enables/disables the toolbar"));
  //viewStatusBar->setStatusText(i18n("Enables/disables the statusbar"));

  // use the absolute path to your kvorbiscommentui.rc file for testing purpose in createGUI();
  createGUI();

	// actions concerning the comments "file"
	KPopupMenu* commentsMenu = new KPopupMenu ();
	replaceComments = new KAction (i18n ("&Replace"), KAccel::stringToKey (tr ("Ctrl+R")), this, SLOT (slotReplaceComments ()), actionCollection ());
	replaceComments->plug (commentsMenu);
	appendComments = new KAction (i18n ("&Append"), KAccel::stringToKey (tr ("Ctrl+A")), this, SLOT (slotAppendComments ()), actionCollection ());
	appendComments->plug (commentsMenu);
	commentsMenu->insertSeparator ();
	editComments = new KAction (i18n ("&Edit"), KAccel::stringToKey (tr ("Ctrl+E")), this, SLOT (slotEditComments ()), actionCollection ());
	editComments->plug (commentsMenu);
	menuBar ()->insertItem (i18n ("&Comments"), commentsMenu, -1, 2);
}


/*
void KVorbisCommentApp::initStatusBar()
{
  ///////////////////////////////////////////////////////////////////
  // STATUSBAR
  // TODO: add your own items you need for displaying current application status.
  statusBar()->insertItem(i18n("Ready."), ID_STATUS_MSG, 1);
}
*/



void KVorbisCommentApp::initDocument ()
{
  doc = new KVorbisCommentDoc (this, "kVorbisCommentDoc");
  doc->newDocument ();
}



void KVorbisCommentApp::initView ()
{ 
	view = new KVorbisCommentView (this, "kVorbisCommentView");
	doc->addView (view);
	setCentralWidget (view);	
	setCaption (doc->URL ().fileName (), false);
	connect (view->replaceCommentsButton, SIGNAL (clicked ()), this, SLOT (slotReplaceComments ()));
	connect (view->appendCommentsButton, SIGNAL (clicked ()), this, SLOT (slotAppendComments ()));
	connect (kapp->clipboard (), SIGNAL (dataChanged ()), this, SLOT (slotClipboardChanged ()));

	// init dialog for the comments "file"
	commentsFileDlg  = new CommentsFileDlg (this, "commentsFileDlg");
	commentsFileDlg->setCaption (i18n ("Edit Comments File"));
	commentsFileDlg->hide ();
}



void KVorbisCommentApp::openDocumentFile (const KURL& url)
{
//  slotStatusMsg(i18n("Opening file..."));

	if (doc->saveModified ())
	{
		if (doc->openDocument (url))
		{
			fileOpenRecent->addURL (url);
			setCaption (url.fileName ());
			replaceComments->setEnabled (true);
			appendComments->setEnabled (true);
			fileSave->setEnabled (false);
			view->saveButton->setEnabled (false);
		}
	}

//  slotStatusMsg(i18n("Ready."));
}



KVorbisCommentDoc *KVorbisCommentApp::getDocument () const
{
  return doc;
}



void KVorbisCommentApp::saveOptions ()
{	
  config->setGroup("General Options");
  config->writeEntry("Geometry", size());
  config->writeEntry("Show Toolbar", viewToolBar->isChecked());
//  config->writeEntry("Show Statusbar",viewStatusBar->isChecked());
  config->writeEntry("ToolBarPos", (int) toolBar("mainToolBar")->barPos());
  fileOpenRecent->saveEntries(config,"Recent Files");

	// options for the comments "file"
	config->setGroup ("Comments File");
	config->writeEntry ("Tags", commentsFileDlg->tags ());
}



void KVorbisCommentApp::readOptions ()
{	
  config->setGroup("General Options");

  // bar status settings
  bool bViewToolbar = config->readBoolEntry("Show Toolbar", true);
  viewToolBar->setChecked(bViewToolbar);
  slotViewToolBar();

//  bool bViewStatusbar = config->readBoolEntry("Show Statusbar", true);
//  viewStatusBar->setChecked(bViewStatusbar);
//  slotViewStatusBar();

  // bar position settings
  KToolBar::BarPosition toolBarPos;
  toolBarPos=(KToolBar::BarPosition) config->readNumEntry("ToolBarPos", KToolBar::Top);
  toolBar("mainToolBar")->setBarPos(toolBarPos);
	
  // initialize the recent file list
  fileOpenRecent->loadEntries(config,"Recent Files");

  QSize size=config->readSizeEntry("Geometry");
  if(!size.isEmpty())
  {
    resize(size);
  }

	// options for the comments "file"
	config->setGroup ("Comments File");
	commentsFileDlg->setTags (config->readListEntry ("Tags"));
}



void KVorbisCommentApp::saveProperties (KConfig *_cfg)
{
  if(doc->URL().fileName()!=i18n("Untitled") && !doc->isModified())
  {
    // saving to tempfile not necessary
  }
  else
  {
    KURL url=doc->URL();	
    _cfg->writeEntry("filename", url.url());
    _cfg->writeEntry("modified", doc->isModified());
    QString tempname = kapp->tempSaveName(url.url());
    QString tempurl= KURL::encode_string(tempname);
    KURL _url(tempurl);
    doc->saveDocument(_url);
  }
}



void KVorbisCommentApp::readProperties (KConfig* _cfg)
{
  QString filename = _cfg->readEntry("filename", "");
  KURL url(filename);
  bool modified = _cfg->readBoolEntry("modified", false);
  if(modified)
  {
    bool canRecover;
    QString tempname = kapp->checkRecoverFile(filename, canRecover);
    KURL _url(tempname);
  	
    if(canRecover)
    {
		if (doc->openDocument(_url))
		{
			doc->setModified();
			setCaption(_url.fileName(),true);
			QFile::remove(tempname);
		}
    }
  }
  else
  {
    if(!filename.isEmpty())
    {
      if (doc->openDocument(url))
		{
			setCaption(url.fileName(),false);
		}
    }
  }
}		



bool KVorbisCommentApp::queryClose ()
{
  return doc->saveModified();
}



bool KVorbisCommentApp::queryExit ()
{
  saveOptions();
  return true;
}


/*
void KVorbisCommentApp::slotFileNewWindow ()
{
  slotStatusMsg(i18n("Opening a new application window..."));
	
  KVorbisCommentApp *new_window= new KVorbisCommentApp();
  new_window->show();

  slotStatusMsg(i18n("Ready."));
}



void KVorbisCommentApp::slotFileNew()
{
  slotStatusMsg(i18n("Creating new document..."));

  if(!doc->saveModified())
  {
     // here saving wasn't successful

  }
  else
  {	
    doc->newDocument();		
    setCaption(doc->URL().fileName(), false);
  }

  slotStatusMsg(i18n("Ready."));
}
*/



void KVorbisCommentApp::slotFileOpen ()
{
//  slotStatusMsg(i18n("Opening file..."));
	
	KURL url = KFileDialog::getOpenURL (":", i18n ("*.ogg|Ogg files"), this, i18n ("Open File..."));
	if(!url.isEmpty())
	{
		openDocumentFile (url);
	}

//  slotStatusMsg(i18n("Ready."));
}



void KVorbisCommentApp::slotFileOpenRecent (const KURL& url)
{
//  slotStatusMsg(i18n("Opening file..."));
	
	openDocumentFile (url);

//  slotStatusMsg(i18n("Ready."));
}



void KVorbisCommentApp::slotFileSave ()
{
//  slotStatusMsg(i18n("Saving file..."));
	
	if (doc->saveDocument (doc->URL ()))
	{
		fileSave->setEnabled (false);
		view->saveButton->setEnabled (false);
	}

//  slotStatusMsg(i18n("Ready."));
}



void KVorbisCommentApp::slotFileSaveAs ()
{
//  slotStatusMsg(i18n("Saving file with a new filename..."));

	KURL url = KFileDialog::getSaveURL (":", i18n ("*.ogg|Ogg files"), this, i18n ("Save as..."));
	if (!url.isEmpty ())
	{
		if (doc->saveDocument (url))
		{
			doc->setURL (url);
			setCaption(url.fileName(),doc->isModified());
			fileOpenRecent->addURL(url);
			fileSave->setEnabled (false);
			view->saveButton->setEnabled (false);
		}
	}

//  slotStatusMsg(i18n("Ready."));
}



/*
void KVorbisCommentApp::slotFileClose ()
{
  slotStatusMsg(i18n("Closing file..."));
	
  close();

  slotStatusMsg(i18n("Ready."));
}



void KVorbisCommentApp::slotFilePrint ()
{
//  slotStatusMsg(i18n("Printing..."));

  QPrinter printer;
  if (printer.setup(this))
  {
    view->print(&printer);
  }

//  slotStatusMsg(i18n("Ready."));
}
*/



void KVorbisCommentApp::slotFileQuit()
{
//  slotStatusMsg(i18n("Exiting..."));

  saveOptions();
  // close the first window, the list makes the next one the first again.
  // This ensures that queryClose() is called on each window to ask for closing
  KMainWindow* w;
  if(memberList)
  {
    for(w=memberList->first(); w!=0; w=memberList->first())
    {
      // only close the window if the closeEvent is accepted. If the user presses Cancel on the saveModified() dialog,
      // the window and the application stay open.
      if(!w->close())
	break;
    }
  }	
}



void KVorbisCommentApp::slotEditCut ()
{
//  slotStatusMsg(i18n("Cutting selection..."));

	editPaste->setEnabled (true);
	view->cut ();

//  slotStatusMsg(i18n("Ready."));
}



void KVorbisCommentApp::slotEditCopy ()
{
//  slotStatusMsg(i18n("Copying selection to clipboard..."));

	editPaste->setEnabled (true);
	view->copy ();

//  slotStatusMsg(i18n("Ready."));
}



void KVorbisCommentApp::slotEditPaste ()
{
//  slotStatusMsg(i18n("Inserting clipboard contents..."));

	view->paste ();

//  slotStatusMsg(i18n("Ready."));
}

void KVorbisCommentApp::slotViewToolBar ()
{
//  slotStatusMsg(i18n("Toggling toolbar..."));

  if(!viewToolBar->isChecked())
  {
    toolBar("mainToolBar")->hide();
  }
  else
  {
    toolBar("mainToolBar")->show();
  }		

//  slotStatusMsg(i18n("Ready."));
}



/*
void KVorbisCommentApp::slotViewStatusBar()
{
  slotStatusMsg(i18n("Toggle the statusbar..."));

  if(!viewStatusBar->isChecked())
  {
    statusBar()->hide();
  }
  else
  {
    statusBar()->show();
  }

  slotStatusMsg(i18n("Ready."));
}


void KVorbisCommentApp::slotStatusMsg(const QString &text)
{
  statusBar()->clear();
  statusBar()->changeItem(text, ID_STATUS_MSG);
}
*/



void KVorbisCommentApp::slotReplaceComments ()
{
	view->setTags (commentsFileDlg->tags (), false);
}



void KVorbisCommentApp::slotAppendComments ()
{
	view->setTags (commentsFileDlg->tags (), false, false);
}



void KVorbisCommentApp::slotEditComments ()
{
	commentsFileDlg->show ();
}



void KVorbisCommentApp::slotClipboardChanged ()
{
	if (!kapp->clipboard ()->text ().isEmpty ())
	{
		editCopy->setEnabled (true);
		editCut->setEnabled (true);
		editPaste->setEnabled (true);
	}
	else
	{
		editPaste->setEnabled (false);
	}
}
