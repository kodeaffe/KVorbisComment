/***************************************************************************
                          kvorbiscommentdoc.h  -  description
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

#ifndef KVORBISCOMMENTDOC_H
#define KVORBISCOMMENTDOC_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif 

#include <qobject.h>
#include <qstring.h>
#include <qlist.h>

#include <kurl.h>

#include "vcedit.h"

class KVorbisCommentView;

/**
	*	KVorbisCommentDoc provides a document object for a document-view model.
	*
	*	@author sebastian henschel
	*/

class KVorbisCommentDoc : public QObject
{
Q_OBJECT

public:
/**
	*	Constructor for the fileclass of the application
	*/
    KVorbisCommentDoc (QWidget *parent, const char *name=0);

/**
	*	Destructor for the fileclass of the application
	*/
    ~KVorbisCommentDoc();

/**
	*	adds a view to the document which represents the document contents. Usually this is your main view.
	*/
    void addView(KVorbisCommentView *view);

/**
	*	removes a view from the list of currently connected views
	*/
    void removeView(KVorbisCommentView *view);

/**
	*	sets the modified flag for the document after a modifying action on the view connected to the document.
	*/
    void setModified(bool _m=true){ modified=_m; };

/**
	*	returns if the document is modified or not. Use this to determine if your document needs saving by the user on closing.
	*/
    bool isModified(){ return modified; };

/**
	*	"save modified" - asks the user for saving if the document is modified
	*/
    bool saveModified();	

/**
	*	deletes the document's contents
	*/
    void deleteContents();

/**
	*	initializes the document generally
	*/
    bool newDocument();

/**
	*	closes the acutal document
	*/
    void closeDocument();

/**
	*	loads the document by filename and format and emits the updateViews() signal
	*/
    bool openDocument(const KURL& url, const char *format=0);

/**
	*	saves the document under filename and format.
	*/	
    bool saveDocument(const KURL& url, const char *format=0);

/**
	*	returns the KURL of the document
	*/
    const KURL& URL() const;

/**
	*	sets the URL of the document
	*/
	  void setURL(const KURL& url);

/**
	*	sets the values of the tags of the document
	*
	*	@param QStringList the list which contains the tags (<name0>,<value0>,<name1>,<value1>,<name2>,...)
	*/
  void setTags (QStringList list);

/**
	*	returns the list with the tags from the document
	*/
  QStringList tags ();
	
/**
	*	the list of the views currently connected to the document
	*/
    static QList<KVorbisCommentView> *pViewList;	

public slots:
/**
	*	calls repaint() on all views connected to the document object and is called by the view by which the document has been changed.
	* As this view normally repaints itself, it is excluded from the paintEvent.
	*/
    void slotUpdateAllViews(KVorbisCommentView *sender);
 	
private:
/**
	*	updates all views of this document
	*/
  void updateViews ();

/**
	*	function which adds the tagList to the vorbis_comments
	*
	*	@see tagList
	*/
  void addComments (vorbis_comment *vc);

/**
	*	the modified flag of the current document
	*/
    bool modified;

    KURL doc_url;

/**
	*	list with the tags
	*/
  QStringList *tagList;
};
#endif // KVORBISCOMMENTDOC_H
