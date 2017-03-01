/***************************************************************************
                          kvorbiscommentview.h  -  description
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

#ifndef KVORBISCOMMENTVIEW_H
#define KVORBISCOMMENTVIEW_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif 

#include "editcomments.h"

class KVorbisCommentDoc;

/** The KVorbisCommentView class provides the view widget for the KVorbisCommentApp instance.
	*
	*	@author sebastian henschel	
	*/

class KVorbisCommentView : public EditComments
{
Q_OBJECT

public:
    KVorbisCommentView (QWidget *parent = 0, const char *name=0);
    ~KVorbisCommentView();

/**
	*	returns a pointer to the document connected to the view instance. Mind that this method requires a KVorbisCommentApp instance as a parent
	* widget to get to the window document pointer by calling the KVorbisCommentApp::getDocument() method.
	*
	* @see KVorbisCommentApp#getDocument
	*/
    KVorbisCommentDoc *getDocument() const;


/**
	*	contains the implementation for printing functionality
	*/
    void print(QPrinter *pPrinter);

/**
	*	updates the view of the application
	*/
  void update ();

/**
	*	pastes the contens of the clipboard into the focussed lineedit
	*/
  void paste ();

/**
	*	copies the marked text from the focussed lineedit into the clipboard
	*/
  void copy ();

/**
	*	cuts the marked text from the focussed lineedit into the clipboard
	*/
  void cut ();
	
private:
/**
	*	called when something is dragged onto the view
	*/
  void dragEnterEvent (QDragEnterEvent *event);

/**
	*	called when something is dropped onto the view
	*/
  void dropEvent (QDropEvent *event);

private slots:
/**
	* called when the save button is hit
	*/
  void slotSave();

/**
	* called when any of the items of the view is changed
	*/
  void slotItemChanged();
};

#endif // KVORBISCOMMENTVIEW_H
