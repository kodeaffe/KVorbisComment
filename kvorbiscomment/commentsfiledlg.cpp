/***************************************************************************
                          commentsfiledlg.cpp  -  description
                             -------------------
    begin                : Sun Jan 6 2002
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

#include <qlayout.h>
#include <qstringlist.h>
#include <qframe.h>

#include "commentsfiledlg.h"
#include "editcomments.h"



CommentsFileDlg::CommentsFileDlg (QWidget* parent, const char* name) : KDialog (parent, name)
{
	edit = new EditComments (this, "editCommentsFileDlg");
	edit->buttonFrame->hide (); // hide "save"-, "replace" and "append"-buttons
	edit->enableWidgets ();
	
	QGridLayout  *grid = new QGridLayout (this, 0, 0 );
	grid->addWidget (edit, 0, 0);
}



CommentsFileDlg::~CommentsFileDlg() {}



void CommentsFileDlg::setTags (QStringList list)
{
 	edit->setTags (list);
}



QStringList CommentsFileDlg::tags ()
{
	return edit->tags ();
}
