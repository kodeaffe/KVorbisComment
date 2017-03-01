/***************************************************************************
                          commentsfiledlg.h  -  description
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

#ifndef COMMENTSFILEDLG_H
#define COMMENTSFILEDLG_H

#include <kdialog.h>

class EditComments;

/**
	*	a dialog where the user can modify the contents of the comments "file".
	*	it contains an instance of the class EditComments, because this class provides most of the
	*	functionality needed.
	*
	*	@author sebastian henschel
	*/

class CommentsFileDlg : public KDialog
{
public: 
	CommentsFileDlg (QWidget* parent, const char* name);
	~CommentsFileDlg ();

/**
	*	set the tags in the dialog
	*
	*	@param QStringList every even item of the list contains the name of the tag and every odd item contains the value of the tag
	*/
  void setTags (QStringList list);

/**
	*	returns the tags out of the dialog
	*	
	*	@return a QStringList containing the tags in the form described above
	*/
  QStringList tags ();

private:
/**
	*	edit is _the_ widget of the dialog
	*/
	EditComments *edit;
};

#endif
