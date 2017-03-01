/***************************************************************************
                          editcomments.h  -  description
                             -------------------
    begin                : Sat Dec 22 2001
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

#ifndef EDITCOMMENTS_H
#define EDITCOMMENTS_H

#include "editcommentswidget.h"

/**
	*	a widget to handle the editing of tags/comments.
	*	it uses EditCommentsWidget for the user interface and adds some code to handle the lineedits
	* and the combobox.
	*
	*	@author sebastian henschel
	*/

class EditComments : public EditCommentsWidget
{
Q_OBJECT

public: 
	EditComments (QWidget* parent, const char* name);
	~EditComments ();

/**
	*	enables the appropriate child widgets
	*/
  void enableWidgets();

/**
	*  set the tags in the dialog
	*
	*	@param QStringList every even item of the list contains the name of the tag and every odd item contains the value of the tag
	*	@param bool determine, if the save button is enabled after settings the tags, default is true
	*	@param	bool	determine, if the content of the lineedits and the combobox should be cleared before setting the (tags) tags, default is true
	*/
  void setTags (QStringList tagList, bool cannotSave = true, bool clear = true);

/**
	*	returns the tags out of the dialog
	*
	* @return a QStringList containing the tags in the form described above
	*/
  QStringList tags ();

public slots:
/**
	* dispatch the id of the selected comboitem and take the appropriate action
	*
	*	@param int the id of the selected comboitem
	*/
  void slotDispatchComboSelection (int id);

/**
	*	remove the current combo item
	*/
  void slotRemoveCurrentComboItem ();

signals:
/**
	*	is emitted when an item of the widget was changed
	*/
  void itemChanged ();

private:
/**
	*	list which contains the values of the tags from the corresponding combobox
	*/
  QStringList *variableTagValues;

/**
	*	id which tells the previously selected combo item (for saving the previous value of the corresponding lineedit
	*/
  int variableComboPrevId;

/**
	*	saves the tag from the variable lineedit
	*/
  void saveVariableTagValue ();

/**
	*	appends a variable tag which is a new item in the combolist and a new string in the list of tag values
	*	in surplus it sets the corresponding lineedit to the given value
	*
	*	@param QString which represents the name of the tag (combolist item)
	*	@param QString which represents the value of the tag (string in variableTagValues)
	*/
  void appendVariableTag (const QString &name, const QString &value);

/**
	*	removes all variable tags from the widget
	*/
  void removeVariableTags ();

/**
	*	clears all lineedits
	*/
  void clearLineEdits ();

private slots:
/**
	*	is activated if the contents of a child are changed. emits the signal itemChanged.
	*/
  void slotItemChanged ();
};

#endif
