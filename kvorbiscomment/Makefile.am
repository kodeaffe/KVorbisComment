####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = kvorbiscomment
kvorbiscomment_SOURCES = commentsfiledlg.cpp vcedit.c newtagdlg.ui editcomments.cpp editcommentswidget.ui kvorbiscommentview.cpp kvorbiscommentdoc.cpp kvorbiscomment.cpp main.cpp 
kvorbiscomment_LDADD   = -logg -lvorbis $(LIB_KFILE) $(LIB_KDEUI) $(LIB_KDECORE) $(LIB_QT) $(LIBSOCKET)


EXTRA_DIST = main.cpp kvorbiscomment.cpp kvorbiscomment.h kvorbiscommentdoc.cpp kvorbiscommentdoc.h kvorbiscommentview.cpp kvorbiscommentview.h kvorbiscomment.desktop lo32-app-kvorbiscomment.png lo16-app-kvorbiscomment.png editcommentswidget.ui editcomments.cpp editcomments.h newtagdlg.ui vcedit.c vcedit.h commentsfiledlg.cpp commentsfiledlg.h 

install-data-local:
	$(mkinstalldirs) $(kde_appsdir)/Applications/
	$(INSTALL_DATA) $(srcdir)/kvorbiscomment.desktop $(kde_appsdir)/Applications/kvorbiscomment.desktop
	$(mkinstalldirs) $(kde_icondir)/locolor/32x32/apps/
	$(INSTALL_DATA) $(srcdir)/lo32-app-kvorbiscomment.png $(kde_icondir)/locolor/32x32/apps/kvorbiscomment.png
	$(mkinstalldirs) $(kde_icondir)/locolor/16x16/apps/
	$(INSTALL_DATA) $(srcdir)/lo16-app-kvorbiscomment.png $(kde_icondir)/locolor/16x16/apps/kvorbiscomment.png

uninstall-local:
	-rm -f $(kde_appsdir)/Applications/kvorbiscomment.desktop
	-rm -f $(kde_icondir)/locolor/32x32/apps/kvorbiscomment.png
	-rm -f $(kde_icondir)/locolor/16x16/apps/kvorbiscomment.png

####### kdevelop will overwrite this part!!! (end)############
# this 10 paths are KDE specific. Use them:
# kde_htmldir       Where your docs should go to. (contains lang subdirs)
# kde_appsdir       Where your application file (.kdelnk) should go to. 
# kde_icondir       Where your icon should go to.
# kde_minidir       Where your mini icon should go to.
# kde_datadir       Where you install application data. (Use a subdir)
# kde_locale        Where translation files should go to.(contains lang subdirs)
# kde_cgidir        Where cgi-bin executables should go to.
# kde_confdir       Where config files should go to.
# kde_mimedir       Where mimetypes should go to.
# kde_toolbardir    Where general toolbar icons should go to.
# kde_wallpaperdir  Where general wallpapers should go to.

# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

METASOURCES = AUTO

# the library search path. 
kvorbiscomment_LDFLAGS = $(all_libraries) $(KDE_RPATH)

rcdir = $(kde_datadir)/kvorbiscomment
rc_DATA = kvorbiscommentui.rc

messages: rc.cpp
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/kvorbiscomment.pot; \
	fi

