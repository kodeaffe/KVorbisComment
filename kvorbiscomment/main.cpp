/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Fre Dez  7 10:23:00 CET 2001
    copyright            : (C) 2002 by sebastian henschel
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

#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include "kvorbiscomment.h"

static const char *description =
	I18N_NOOP("KVorbisComment\nThis is a GUI for vorbiscomment RC3. vorbiscomment is a program from the vorbis-tools package\nto edit the tags of an Ogg Vorbis file.\nAnd, by the way, this is my first real application for KDE. :)");
	
	
static KCmdLineOptions options[] =
{
  { "+[File]", I18N_NOOP("file to open"), 0 },
  { 0, 0, 0 }
};

int main(int argc, char *argv[])
{

	KAboutData aboutData( "kvorbiscomment", I18N_NOOP("KVorbisComment"),
		VERSION, description, KAboutData::License_GPL,
		"(c) 2002, sebastian henschel", 0, 0, "s.henschel@berlin.de");
	aboutData.addAuthor("sebastian henschel",0, "s.henschel@berlin.de");
	KCmdLineArgs::init( argc, argv, &aboutData );
	KCmdLineArgs::addCmdLineOptions( options );

  KApplication app;
 
  if (app.isRestored())
  {
    RESTORE(KVorbisCommentApp);
  }
  else 
  {
    KVorbisCommentApp *kvorbiscomment = new KVorbisCommentApp (0, "kVorbisComment");
    kvorbiscomment->show();

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
		
		if (args->count())
		{
        kvorbiscomment->openDocumentFile(args->arg(0));
		}

		args->clear();
  }

  return app.exec();
}  
