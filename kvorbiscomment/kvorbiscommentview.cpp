/***************************************************************************
                          kvorbiscommentview.cpp  -  description
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

#include <qprinter.h>
#include <qpainter.h>
#include <qstringlist.h>
#include <qdragobject.h>

#include <klocale.h>
#include <klistview.h>
#include <kurl.h>
#include <klineedit.h>
#include <kpushbutton.h>

#include "kvorbiscommentview.h"
#include "kvorbiscommentdoc.h"
#include "kvorbiscomment.h"

KVorbisCommentView::KVorbisCommentView (QWidget *parent, const char *name) : EditComments (parent, name)
{
	setBackgroundMode(PaletteBase);
	setAcceptDrops (true);

	connect (saveButton, SIGNAL (clicked ()), this, SLOT (slotSave ()));
	connect (this, SIGNAL (itemChanged ()), this, SLOT (slotItemChanged ()));
}

KVorbisCommentView::~KVorbisCommentView () { }



KVorbisCommentDoc *KVorbisCommentView::getDocument () const
{
  KVorbisCommentApp *theApp = (KVorbisCommentApp *) parentWidget ();
  return theApp->getDocument ();
}



void KVorbisCommentView::print (QPrinter *pPrinter)
{
  QPainter printpainter;
  printpainter.begin(pPrinter);
  printpainter.end();
}



void KVorbisCommentView::update ()
{
	setTags (getDocument ()->tags ());
}



void KVorbisCommentView::slotSave ()
{
	KVorbisCommentDoc *doc = getDocument ();
	if (doc->saveDocument (doc->URL ()))
	{
		saveButton->setEnabled (false);
	}
}



void KVorbisCommentView::slotItemChanged ()
{
	getDocument ()->setModified (true);

	KVorbisCommentApp *theApp = (KVorbisCommentApp *) parentWidget ();
	theApp->fileSave->setEnabled (true);
	theApp->fileSaveAs->setEnabled (true);
}



void KVorbisCommentView::dragEnterEvent (QDragEnterEvent *event)
{
  event->accept (QTextDrag::canDecode(event));
}



void KVorbisCommentView::dropEvent (QDropEvent *event)
{
	QString text;
	if (QTextDrag::decode (event, text) )
	{
		KURL url (text);
		KVorbisCommentApp *theApp = (KVorbisCommentApp *) parentWidget ();
		theApp->openDocumentFile (url);
	}
}



void KVorbisCommentView::cut ()
{
	if (kapp->focusWidget ()->isA ("KLineEdit")) ((KLineEdit *) kapp->focusWidget ())->cut ();
}



void KVorbisCommentView::copy ()
{
		if (kapp->focusWidget ()->isA ("KLineEdit")) ((KLineEdit *) kapp->focusWidget ())->copy ();
}



void KVorbisCommentView::paste ()
{
	if (kapp->focusWidget ()->isA ("KLineEdit")) ((KLineEdit *) kapp->focusWidget ())->paste ();
}
