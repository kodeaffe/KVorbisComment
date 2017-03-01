/***************************************************************************
                          kvorbiscommentdoc.cpp  -  description
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

/***************************************************************************
 *
 *		vcedit.[hc] are lifted from the vorbis-tools-rc3 package. many thanks for that.
 *
 ***************************************************************************/

// for malloc () / string-operations when calling vorbis_comment_add_tag
#include <stdlib.h>
#include <string.h>

#include <qdir.h>
#include <qwidget.h>

#include <klocale.h>
#include <kmessagebox.h>
#include <kio/job.h>
#include <kio/netaccess.h>
#include <ktempfile.h>

#include "kvorbiscommentdoc.h"
#include "kvorbiscomment.h"
#include "kvorbiscommentview.h"

QList<KVorbisCommentView> *KVorbisCommentDoc::pViewList = 0L;

KVorbisCommentDoc::KVorbisCommentDoc(QWidget *parent, const char *name) : QObject(parent, name)
{
	if (!pViewList)
	{
		pViewList = new QList<KVorbisCommentView> ();
	}
	pViewList->setAutoDelete(true);

	tagList = new QStringList ();
}

KVorbisCommentDoc::~KVorbisCommentDoc () { }



void KVorbisCommentDoc::addView (KVorbisCommentView *view)
{
  pViewList->append(view);
}



void KVorbisCommentDoc::removeView (KVorbisCommentView *view)
{
  pViewList->remove (view);
}



void KVorbisCommentDoc::setURL (const KURL &url)
{
  doc_url=url;
}



const KURL& KVorbisCommentDoc::URL () const
{
  return doc_url;
}



void KVorbisCommentDoc::slotUpdateAllViews (KVorbisCommentView *sender)
{
  KVorbisCommentView *w;
  if (pViewList)
  {
    for (w = pViewList->first (); w!=0; w = pViewList->next ())
    {
      if (w!=sender) w->repaint();
    }
  }
}



bool KVorbisCommentDoc::saveModified ()
{
  bool completed=true;

  if (modified)
  {
    KVorbisCommentApp *win = (KVorbisCommentApp *) parent ();
    int want_save = KMessageBox::warningYesNoCancel(win,
                                         i18n("The current file has been modified.\n"
                                              "Do you want to save it?"),
                                         i18n("Warning"));
    switch(want_save)
    {
      case KMessageBox::Yes:
           if (doc_url.fileName() == i18n("Untitled"))
           {
             win->slotFileSaveAs();
           }
           else
           {
             saveDocument (URL ());
       	   };

       	   deleteContents();
           completed=true;
           break;

      case KMessageBox::No:
           setModified(false);
           deleteContents();
           completed=true;
           break;

      case KMessageBox::Cancel:
           completed=false;
           break;

      default:
           completed=false;
           break;
    }
  }
  return completed;
}



void KVorbisCommentDoc::closeDocument ()
{
  deleteContents();
}



bool KVorbisCommentDoc::newDocument ()
{
  modified=false;
  doc_url.setFileName(i18n("Untitled"));

  return true;
}



bool KVorbisCommentDoc::openDocument (const KURL& url, const char *format /*=0*/)
{
  QString tmpfile;
	if (KIO::NetAccess::download (url, tmpfile))
	{
		int i;
		vcedit_state *state;
		vorbis_comment *vc;
		FILE* vorbisfile = fopen (tmpfile, "rb");
		state = vcedit_new_state ();

		// open vorbis file
		if (vcedit_open (state, vorbisfile) < 0)
		{
			QString msg (i18n ("Vorbis says: "));
			msg += vcedit_error (state);
			KMessageBox::detailedSorry (0, i18n ("Sorry, but the selected file is no valid Ogg Vorbis file!"), msg, i18n ("Invalid File"));
			return false;
		}

		// append the comments to the list of tags
		vc = vcedit_comments (state);
		tagList->clear();
		QString tmp;
		int index;
		for (i = 0; i < vc->comments; i++)
		{
			tmp = vc->user_comments[i];			
			index = tmp.find ('=');
			if (index != -1)
			{				
				tagList->append (QString::fromUtf8 (tmp.left (index)));
				tagList->append (QString::fromUtf8 (tmp.mid (index + 1)));
			}
		}
		updateViews ();

		// clean up
		vcedit_clear (state);
		fclose (vorbisfile);
		KIO::NetAccess::removeTempFile (tmpfile);

		doc_url = url;
		modified = false;
		setURL (url);
		return true;
	}
	else
	{
		return false;
	}
}



bool KVorbisCommentDoc::saveDocument (const KURL& url, const char *format /*=0*/)
{
	vcedit_state *state;
	vorbis_comment *vc;
	FILE *in, *out;
	QString filenameIn;
	KTempFile fileOut;

	setTags (pViewList->first ()->tags ());

	// prepare vorbis
	state = vcedit_new_state ();	
	if (!KIO::NetAccess::download (URL (), filenameIn)) return false;
	in = fopen (filenameIn, "rb");
	if (vcedit_open (state, in) < 0)
	{
			QString msg (i18n ("Vorbis says: "));
			msg += vcedit_error (state);
			KMessageBox::detailedSorry (0, i18n ("Sorry, could not open the file!"), msg, i18n ("Invalid File"));		
			return false;
	}
	vc = vcedit_comments (state);

	// clear and add comments
	vorbis_comment_clear (vc);
	vorbis_comment_init (vc);
	addComments (vc);

	// write comments
	out = fopen (fileOut.name (), "wb");
	if (vcedit_write (state, out) < 0)
	{
		QString msg (i18n ("Vorbis says: "));
		msg += vcedit_error (state);
		KMessageBox::detailedSorry (0, i18n ("Sorry, could not write comments!"), msg, i18n ("File Not Written"));		
		return false;
	}

	// clean up
	fclose (in);
	fclose (out);

	bool retVal = true;
	if (!KIO::NetAccess::upload (fileOut.name (), url))
	{
		KMessageBox::sorry (0, i18n ("Sorry, could not write comments!\nAre the permissions set correctly?"), i18n ("File Not Written"));		
		retVal = false;
	 }
	else
	{
		modified = false;
	}

	KIO::NetAccess::removeTempFile (filenameIn);	
	fileOut.unlink ();
	vcedit_clear (state);
	return retVal;
}



void KVorbisCommentDoc::deleteContents()
{
}



void KVorbisCommentDoc::updateViews ()
{
	KVorbisCommentView *view;
	for (view = pViewList->first (); view != 0; view = pViewList->next ())
	{
		view->update ();
	}
}



void KVorbisCommentDoc::setTags (QStringList list)
{
		tagList->clear ();		
		*tagList = list;
		modified = true;
}



void KVorbisCommentDoc::addComments (vorbis_comment *vc)
{
	char *name, *value;
	QCString utfName, utfValue;
	uint len;
	for (QStringList::Iterator it = tagList->begin(); it != tagList->end(); it++)
	{
		// construct name as a char*
		utfName = (*it).utf8 ();
		len =  utfName.length () + 1;
		name = (char *) malloc (sizeof (char) * len);
		strncpy (name, utfName, len);

		// construct value as a char*
		it++;
		utfValue = (*it).utf8 ();
		len = utfValue.length () + 1;
		value = (char *) malloc (sizeof (char) * len);
		strncpy (value, utfValue, len);

		// do the actual adding
		vorbis_comment_add_tag (vc, name, value);
		
		free (name);
		free (value);
	}
}



QStringList KVorbisCommentDoc::tags ()
{
	return *tagList;
}