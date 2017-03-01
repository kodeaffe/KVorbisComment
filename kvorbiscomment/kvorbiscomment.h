/***************************************************************************
                          kvorbiscomment.h  -  description
                             -------------------
    begin                : Fre Dez  7 10:23:00 CET 2001
    copyright            : (C) 2002 by sebastian henschel
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

#ifndef KVORBISCOMMENT_H
#define KVORBISCOMMENT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kapp.h>
#include <kmainwindow.h>
#include <kaction.h>

class KVorbisCommentDoc;
class KVorbisCommentView;
class CommentsFileDlg;

/**
	*	the application class of KVorbisComment
	*
	*	@author sebastian henschel
	*/

class KVorbisCommentApp : public KMainWindow
{
Q_OBJECT

friend class KVorbisCommentView;

public:
    KVorbisCommentApp(QWidget* parent=0, const char* name=0);
    ~KVorbisCommentApp();

/**
	*	opens a file specified by commandline option
	*/
    void openDocumentFile(const KURL& url=0);

/**
	*	returns a pointer to the current document connected to the KTMainWindow instance and is used by
	* the View class to access the document object's methods
	*/	
    KVorbisCommentDoc *getDocument() const;
	
public slots:
/**
	*	open a new application window by creating a new instance of KVorbisCommentApp
	*/
//    void slotFileNewWindow();

/**
	*	clears the document in the actual view to reuse it as the new document
	*/
//    void slotFileNew();

/**
	*	open a file and load it into the document
	*/
    void slotFileOpen();

/**
	*	opens a file from the recent files menu
	*/
    void slotFileOpenRecent(const KURL& url);

/**
	*	save a document
	*/
    void slotFileSave();

/**
	*	save a document by a new filename
	*/
    void slotFileSaveAs();

/**
	*	asks for saving if the file is modified, then closes the actual file and window
	*/
    //void slotFileClose();

/**
	*	print the actual file
	*/
    //void slotFilePrint();

/**
	*	closes all open windows by calling close() on each memberList item until the list is empty, then quits the application.
	* If queryClose() returns false because the user canceled the saveModified() dialog, the closing breaks.
	*/
    void slotFileQuit();

/**
	*	put the marked text/object into the clipboard and remove
	*	it from the document
	*/
    void slotEditCut();

/**
	*	put the marked text/object into the clipboard
	*/
    void slotEditCopy();

/**
	*	paste the clipboard into the document
	*/
    void slotEditPaste();

/**
	*	toggles the toolbar
	*/
    void slotViewToolBar();

/**
	*	toggles the statusbar
	*/
    //void slotViewStatusBar();

/**
	*	changes the statusbar contents for the standard label permanently, used to indicate current actions.
	* @param text the text that is displayed in the statusbar
	*/
    //void slotStatusMsg(const QString &text);

/**
	*	opens a dialog to edit the comments "file"
	*/
  void slotEditComments ();

/**
	*	replaces the tags in the view by the tags given in the comments "file"
	*/
  void slotReplaceComments ();

/**
	*	appends the tags in the comments "file" to the tags in the view.
	*	tags in the view are overwritten if necessary
	*/
  void slotAppendComments ();

protected:
/**
	*	save general Options like all bar positions and status as well as the geometry and the recent file list to the configuration file
	*/ 	
    void saveOptions();

/**
	*	read general Options again and initialize all variables like the recent file list
	*/
    void readOptions();

/**
	* initializes the KActions of the application
	*/
    void initActions();

/**
	*	sets up the statusbar for the main window by initialzing a statuslabel.
	*/
    //void initStatusBar();

/**
	*	initializes the document object of the main window that is connected to the view in initView().
	* @see initView();
	*/
    void initDocument();

/**
	*	creates the centerwidget of the KTMainWindow instance and sets it as the view
	*/
    void initView();

/**
	*	queryClose is called by KTMainWindow on each closeEvent of a window. Against the
	* default implementation (only returns true), this calles saveModified() on the document object to ask if the document shall
	* be saved if Modified; on cancel the closeEvent is rejected.
	*/
    virtual bool queryClose();

/**
	*	queryExit is called by KTMainWindow when the last window of the application is going to be closed during the closeEvent().
	* Against the default implementation that just returns true, this calls saveOptions() to save the settings of the last window's	
	* properties.
	*/
    virtual bool queryExit();

/**
	*	saves the window properties for each open window during session end to the session config file, including saving the currently
	* opened file by a temporary filename provided by KApplication.
	*/
    virtual void saveProperties(KConfig *_cfg);

/**
	*	reads the session config file and restores the application's state including the last opened files and documents by reading the
	* temporary files saved by saveProperties()
	*/
    virtual void readProperties(KConfig *_cfg);

private:
/**
	*	the configuration object of the application
	*/
    KConfig *config;

/**
	*	view is the main widget which represents the working area.
	*/
    KVorbisCommentView *view;

/**
	*	doc represents your the document and is created only once
	*/
    KVorbisCommentDoc *doc;

// KAction pointers to enable/disable actions
    KAction* fileNewWindow;
    KAction* fileNew;
    KAction* fileOpen;
    KRecentFilesAction* fileOpenRecent;
    KAction* fileSave;
    KAction* fileSaveAs;
    KAction* fileClose;
    KAction* filePrint;
    KAction* fileQuit;
    KAction* editCut;
    KAction* editCopy;
    KAction* editPaste;
    KToggleAction* viewToolBar;
    KToggleAction* viewStatusBar;

/**
	*	action for editing the contents of the "comments file"
	*/
  KAction *editComments;

/**
	*	action for replacing the tags in the view by the tags from the comments "file"
	*/
  KAction *replaceComments;

/**
	* action for appending the tags in the comments "file" to the tags in the view
	*/
  KAction *appendComments;

/**
	* dialog to edit the comments "file"
	*/
  CommentsFileDlg *commentsFileDlg;

private slots:
/**
	*	called when the contents of the clipboard have changed
	*/
  void slotClipboardChanged ();
};
 
#endif // KVORBISCOMMENT_H
