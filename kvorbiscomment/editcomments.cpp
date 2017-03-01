/***************************************************************************
                          editcomments.cpp  -  description
                             -------------------
    begin                : Sat Dec 22 2001
    copyright            : (C) 2001 by sebastian henschel
    email                : s.henschel@berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <qstringlist.h>
#include <qlabel.h>
#include <qevent.h>
#include <qobjectlist.h>

#include <klineedit.h>
#include <kcombobox.h>
#include <kpushbutton.h>

#include "editcomments.h"
#include "newtagdlg.h"

EditComments::EditComments (QWidget* parent, const char* name) : EditCommentsWidget (parent, name)
{
	variableTagValues = new QStringList ();
	variableComboPrevId = 0;

	connect (variableCombo, SIGNAL (activated (int)), this, SLOT (slotDispatchComboSelection (int)));
	connect (variableRemoveButton, SIGNAL (clicked ()), this, SLOT (slotRemoveCurrentComboItem ()));

	QObjectList *l = queryList ("KLineEdit");
	QObjectListIt it (*l);
	QObject *obj;
	while ((obj = it.current ()) != 0 )
	{
        ++it;
        connect (((KLineEdit *) obj), SIGNAL (textChanged (const QString &)), this, SLOT (slotItemChanged ()));
    }
    delete l;
}

EditComments::~EditComments () { }



void EditComments::enableWidgets ()
{
	QObjectList *l = queryList ("KLineEdit", "^fixed");
	QObjectListIt it (*l);
	QObject *obj;
	while ((obj = it.current ()) != 0 )
	{
        ++it;
        ((KLineEdit *) obj)->setEnabled (true);
    }
    delete l;

	variableCombo->setEnabled (true);
	replaceCommentsButton->setEnabled (true);
	appendCommentsButton->setEnabled (true);
}



void EditComments::setTags (QStringList tagList, bool cannotSave = true, bool clear = true)
{
	if (clear)
	{
		clearLineEdits ();
		removeVariableTags ();
	}

	QString name, value;
	for (QStringList::Iterator it = tagList.begin (); it != tagList.end (); it++)
	{
		name = (*it).upper ();
		it++;
		value = *it;

		if (name == "TITLE") fixedEditTitle->setText (value);
		else if (name == "VERSION") fixedEditVersion->setText (value);
		else if (name == "ALBUM") fixedEditAlbum->setText (value);
		else if (name == "TRACKNUMBER") fixedEditTracknumber->setText (value);
		else if (name == "ARTIST") fixedEditArtist->setText (value);
		else if (name == "PERFORMER") fixedEditPerformer->setText (value);
		else if (name == "ORGANIZATION") fixedEditOrganization->setText (value);
		else if (name == "DESCRIPTION") fixedEditDescription->setText (value);
		else if (name == "GENRE") fixedEditGenre->setText (value);
		else if (name == "DATE") fixedEditDate->setText (value);
		else if (name == "LOCATION") fixedEditLocation->setText (value);
		else if (name == "COPYRIGHT") fixedEditCopyright->setText (value);
		else if (name == "CONTACT") fixedEditContact->setText (value);
		else if (name == "ISRC") fixedEditIsrc->setText (value);
		else if (name == "DISCID") fixedEditDiscid->setText (value);
		else appendVariableTag (name, value);
	}

	if (saveButton->isEnabled () == true && cannotSave) saveButton->setEnabled (false);

	enableWidgets ();
}



QStringList EditComments::tags ()
{
	QStringList data;

	saveVariableTagValue ();

	QObjectList *lineEdits = queryList ("KLineEdit", "^fixed");
	QObjectListIt lineEditIt (*lineEdits);
	QObjectList *labels = queryList ("QLabel");
	QObjectListIt labelIt (*labels);
	QObject *lineEdit, *label;

	while ((lineEdit = lineEditIt.current ()) != 0)
	{		
		if (!((KLineEdit *) lineEdit)->text ().isEmpty ())
		{
			label = labelIt.current ();
			data.append (((QLabel *) label)->text ());
			data.append (((KLineEdit *) lineEdit)->text ());
		}
		++lineEditIt;
		++labelIt;
	}
	delete lineEdits;
	delete labels;

	QStringList::Iterator it;
	for (int i = 1; i < variableCombo->count (); i++)
	{
		it = variableTagValues->at (i - 1);
		if (!(*it).isEmpty ())
		{
			data.append (variableCombo->text (i));
			data.append (*it);
		}
	}

	return data;
}



void EditComments::slotDispatchComboSelection (int id)
{
	saveVariableTagValue ();

	if (id == 0) // add new tag
	{
		if (variableRemoveButton->isEnabled () == true) variableRemoveButton->setEnabled (false);
		if (variableEdit->isEnabled () == true) variableEdit->setEnabled (false);
		variableEdit->setText ("");

		NewTagDlg dlg (this, "newTagDlg", true);
		if (dlg.exec ())
		{
			QString name (dlg.tagEdit->text ()), value ("");
			appendVariableTag (name.upper (), value);
		}
		variableComboPrevId = variableCombo->currentItem ();
	}
	else // activate button, input and set text
	{
		if (variableRemoveButton->isEnabled () == false) variableRemoveButton->setEnabled (true);
		if (variableEdit->isEnabled () == false) variableEdit->setEnabled (true);
		variableEdit->setText (*variableTagValues->at (id - 1));
		variableComboPrevId = id;		
	}
}



void EditComments::slotRemoveCurrentComboItem ()
{
	if (variableCombo->currentItem () != 0) // do not delete the "add button"
	{
		variableTagValues->remove (variableTagValues->at (variableCombo->currentItem () - 1));
		variableCombo->removeItem (variableCombo->currentItem ());

		if (variableCombo->currentItem () == -1) variableCombo->setCurrentItem (variableCombo->count () - 1);

		int current = variableCombo->currentItem ();
		if (current <= 0)
		{
			variableEdit->setText ("");
			variableEdit->setEnabled (false);
			variableRemoveButton ->setEnabled (false);
		}
		else		
		{
			variableEdit->setText (*variableTagValues->at (variableCombo->currentItem () - 1));
		}
		variableComboPrevId = current;
	}
}



void EditComments::slotItemChanged ()
{
	if (saveButton->isEnabled () == false) saveButton->setEnabled (true);
	emit (itemChanged ());
}



void EditComments::saveVariableTagValue ()
{
		if (variableComboPrevId > 0)
		{
			QStringList::Iterator it = variableTagValues->at (variableComboPrevId - 1);
			it = variableTagValues->remove (it);
			variableTagValues->insert (it, variableEdit->text ());
		}
}



void EditComments::appendVariableTag (const QString &name, const QString &value)
{
	variableCombo->insertItem (name);
	variableCombo->setCurrentItem (variableCombo->count () - 1);
	variableEdit->setText (value);
	variableTagValues->append (value);

	if (variableEdit->isEnabled () == false) variableEdit->setEnabled (true);
	if (variableRemoveButton->isEnabled () == false) variableRemoveButton->setEnabled (true);
}



void EditComments::removeVariableTags ()
{
	QString name (variableCombo->text (0)); // save "Add..." string
	variableCombo->clear ();
	variableCombo->insertItem (name);
	variableEdit->setText ("");
	variableTagValues->clear ();
	variableComboPrevId = 0;

	if (variableEdit->isEnabled () == true) variableEdit->setEnabled (false);
	if (variableRemoveButton->isEnabled () == true) variableRemoveButton->setEnabled (false);
}



void EditComments::clearLineEdits ()
{
	QObjectList *l = queryList ("KLineEdit", "^fixed");
	QObjectListIt it (*l);
	QObject *obj;
	while ((obj = it.current ()) != 0 )
	{
        ++it;
        ((KLineEdit *) obj)->setText ("");
    }
    delete l;
}