# ACLOCAL_AMFLAGS = -I m4

# WLB NOTE: cannot use -fstack-protector-all 
X_CPPFLAGS = -Wall -fms-extensions -I$(srcdir)/src -I$(srcdir)/src/hardware -fPIC -D__BUILD_DATE=\"$$(date +'%Y%m%d.%H%M%S')\"

if DEBUG
AM_CFLAGS = -g3 -O0
AM_CPPFLAGS = ${X_CPPFLAGS} -g3 -O0
else
AM_CFLAGS = -O2
AM_CPPFLAGS = ${X_CPPFLAGS} -O2
endif


lib_LTLIBRARIES = libpista.la
HWLIBS = -Wl,-Bdynamic 

libprotobuf_c_LIBS = -lprotobuf-c   
# libyajl_LIBS = -Wl,-Bdynamic -L /usr/lib/arm-linux-gnueabihf -lyajl
libyajl_LIBS = -lyajl
libexpat_LIBS = -lexpat

LIBS = -Wl,-Bstatic -lprotobuf-c ${libexpat_LIBS} -Wl,-Bdynamic ${libexpat_LIBS}

# FIXME: looks like android build needs a little work or at least docs
# PISTA_LIB_LDFLAGS = -L/home/bbaker/git/pista/platform/android-19/lib
PISTA_LIB_LDFLAGS =

libpista_la_SOURCES = \
	src/pista.c \
	src/pista-internal.c \
	src/dump.c \
	src/log.c \
	src/std.c

if HAVE_LIBSERIALPORT
libpista_la_SOURCES += \
	src/lspIO.c
HWLIBS += -lserialport
endif

if NEED_ZEROMQ
libpista_la_SOURCES += \
	src/pista_zeromq.c
endif

if HW_BMP180
libpista_la_SOURCES += \
	src/hardware/bmp180/bmp180.h \
	src/hardware/bmp180/bmp180.c \
	src/hardware/bmp180/bmp180-api.h \
	src/hardware/bmp180/bmp180-api.c \
	src/model/bmp180.pb-c.c
endif

if HW_MEDSYS3
libpista_la_SOURCES += \
	src/hardware/medsys3/medsys3.h \
	src/hardware/medsys3/medsys3.c \
	src/hardware/medsys3/medsys3-api.c \
	src/model/medsys3.pb-c.c
endif

if HW_HT70
libpista_la_SOURCES += \
	src/hardware/ht70/ht70.h \
	src/hardware/ht70/ht70.c \
	src/hardware/ht70/ht70-api.c \
	src/hardware/ht70/ht70-base64.c \
	src/model/ht70.pb-c.c

if HAVE_EXPAT
LIBS += $(EXPAT_LIBS)
endif
endif

if HW_IMP731
libpista_la_SOURCES += \
	src/hardware/imp731/imp731.h \
	src/hardware/imp731/imp731.c \
	src/hardware/imp731/imp731-api.c \
	src/model/imp731.pb-c.c
endif

if HW_U3
libpista_la_SOURCES += \
	src/hardware/u3/u3.h \
	src/hardware/u3/u3.c \
	src/hardware/u3/u3stream.c \
	src/hardware/u3/api.h \
	src/hardware/u3/api.c \
	src/model/u3.pb-c.c
endif

if HW_DT
libpista_la_SOURCES += \
	src/hardware/dt/api.h \
	src/hardware/dt/api.c
##	src/model/dt.pb-c.c
endif

if HW_SIMU
libpista_la_SOURCES += \
	src/hardware/simu/simu.h \
	src/hardware/simu/simu-api.c \
	src/model/simu.pb-c.c
endif

if HW_MCCUL
libpista_la_SOURCES += \
	src/hardware/mcc-ul/mcc-ul.h \
	src/hardware/mcc-ul/mcc-ul.c \
	src/model/mccul.pb-c.c
HWLIBS += -lcbw64
endif

if HW_PROPAQM
libpista_la_SOURCES += \
	src/hardware/propaqm/propaqm.h \
	src/hardware/propaqm/propaqm.c \
	src/hardware/propaqm/ztr_parser.c \
	src/hardware/propaqm/ztr_dump.c \
	src/model/propaqm.pb-c.c

if HAVE_AVAHICLIENT
#libpista_la_SOURCES += \
	#src/service/propaq_disc/pp_api.c \
	#src/service/propaq_disc/pp_discover.c
#HWLIBS += $(AVAHICLIENT_LIBS)
endif

endif

LIBS += $(HWLIBS)


libpista_la_LIBADD = $(LIBOBJS)

libpista_la_LDFLAGS = $(PISTA_LIB_LDFLAGS)

libpista_la_LDFLAGS += -no-undefined

library_includedir = $(includedir)

library_include_HEADERS = include/pista.h

pkgconfdir = $(libdir)/pkgconfig
pkgconf_DATA = pista.pc

EXTRA_DIST = \
	Doxyfile

# TESTS = tests
# 
# check_PROGRAMS = ${TESTS}




BUILD_EXTRA =
INSTALL_EXTRA =
CLEAN_EXTRA =

if BINDINGS_CXX

lib_LTLIBRARIES += bindings/cxx/libpistacxx.la

bindings_cxx_libpistacxx_la_SOURCES = \
	bindings/cxx/pista-cl.cpp  \
	bindings/cxx/pista-dev.cpp  \
 	bindings/cxx/pista-driver.cpp  \
	bindings/cxx/pista-evt.cpp \
	bindings/cxx/pista-cm.cpp \
	bindings/cxx/pista-pkt.cpp \
	bindings/cxx/pista-str.cpp \
	bindings/cxx/pista-disc.cpp \
	bindings/cxx/pista-service.cpp

if HAVE_LIBSERIALPORT
bindings_cxx_libpistacxx_la_SOURCES += bindings/cxx/lspio-cm.cpp
endif

if HAVE_BOOST_ASIO
bindings_cxx_libpistacxx_la_SOURCES += bindings/cxx/boost-cm.cpp
endif

bindings_cxx_libpistacxx_la_LIBADD = libpista.la
bindings_cxx_libpistacxx_la_LDFLAGS = -version-info $(PISTA_LIB_VERSION) -no-undefined

bindings_cxx_libpistacxx_la_includedir = $(includedir)/libpistacxx
bindings_cxx_libpistacxx_la_include_HEADERS = \
	bindings/cxx/pista-cl.h

# WLB...we have two ... a pkgconf and a pkgconfig
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = bindings/cxx/libpistacxx.pc

doxy/xml/index.xml: include/libpista/libpista.h
	$(AM_V_GEN)cd $(srcdir) && BUILDDIR=$(abs_builddir)/ doxygen Doxyfile 2>/dev/null

# bindings/pistax.i: bindings/cxx/pistax.timestamp
# bindings/cxx/pista-cl.h: bindings/cxx/pistax.timestamp

bindings/cxx/pistax.timestamp: $(srcdir)/bindings/cxx/pista-cl.h
	$(AM_V_at)touch $@

# bindings/cxx/pistax.timestamp: $(srcdir)/bindings/cxx/pista-cl.h
#	$(AM_V_GEN)$(PYTHON) $(srcdir)/bindings/cxx/enums.py doxy/xml/index.xml
#	$(AM_V_at)touch $@

# WLB...a real FIXME here
bindings/cxx/pista-cl.lo: bindings/cxx/pista-cl.cpp bindings/cxx/pista-dev.cpp $(library_include_HEADERS) $(nodist_library_include_HEADERS)

cxx-clean:
	rm -rf doxy/
	rm -rf bindings/cxx/doxy/

# BUILD_EXTRA += cxx-build
# INSTALL_EXTRA += cxx-install
CLEAN_EXTRA += cxx-clean

endif

CPPXMLDOC = bindings/cxx/doxy/xml/index.xml

$(CPPXMLDOC): bindings/cxx/include/libpistacxx/libpistacxx.hpp
	$(AM_V_GEN)cd $(srcdir)/bindings/cxx && BUILDDIR=$(abs_builddir)/bindings/cxx/ doxygen Doxyfile 2>/dev/null

PISTA_SWG = bindings/pista.i
PISTA_SWGX = bindings/pistax.i

if BINDINGS_PYTHON

PDIR = bindings/python
PYPISTAX_SRC = $(abs_srcdir)/$(PDIR)
PYPISTAX_PY = $(abs_srcdir)/$(PDIR)/pypistax.py
PYPISTAX_CXX = $(abs_srcdir)/$(PDIR)/pistax_wrap.cxx

python-build: $(PDIR)/timestamp

python-quietclean:
	$(AM_V_at)cd $(PDIR) && $(PYTHON) $(abs_srcdir)/$(PDIR)/setup.py --quiet clean --all 3>&1 1>&2 2>&3 \
		| grep -v "can.t clean it"; true

$(PYPISTAX_CXX): bindings/pistax.i
	mkdir -p $(PDIR)
	echo $(AM_V_GEN)swig -c++ -py3 -threads -python -I$(srcdir)/include -I$(srcdir)/bindings/cxx -I$(srcdir) -I$(builddir)/include -Ibindings/cxx -outdir $(PYPISTAX_SRC)  -o $@ $<
	$(AM_V_GEN)swig -c++ -py3 -threads -python -I$(srcdir)/include -I$(srcdir)/bindings/cxx -I$(srcdir) -I$(builddir)/include -Ibindings/cxx -outdir $(PYPISTAX_SRC)  -o $@ $<

$(PDIR)/timestamp: $(PYPISTAX_CXX) $(library_include_HEADERS)
	$(AM_V_at)$(MAKE) python-quietclean
	$(AM_V_GEN)cd $(PDIR) && $(PYTHON) $(abs_srcdir)/$(PDIR)/setup.py --quiet build 3>&1 1>&2 2>&3 \
		| grep -v "command line option.*Wstrict-prototypes"; true
	$(AM_V_at)touch $(PDIR)/timestamp

$(DESTDIR)$(prefix):
	$(MKDIR_P) $@

python-install: $(DESTDIR)$(prefix)
	cd $(PDIR) && $(PYTHON) $(abs_srcdir)/$(PDIR)/setup.py --quiet install --prefix $(prefix) `test "$(DESTDIR)" && echo --root=$(DESTDIR)`

python-clean:
	$(AM_V_at)$(MAKE) python-quietclean
	$(AM_V_at)rm -f $(PDIR)/timestamp
	$(AM_V_at)rm -rf $(PDIR)/doxy/

python-doc:
	$(AM_V_at)cd $(srcdir)/$(PDIR) && BUILDDIR=$(abs_builddir)/$(PDIR)/ doxygen Doxyfile 2>/dev/null

BUILD_EXTRA += python-build
INSTALL_EXTRA += python-install
CLEAN_EXTRA += python-clean

endif

if BINDINGS_JAVA

#
# ... -cp bindings/java/gen$(PATH_SEPARATOR)bindings/java/ref/RXTXcomm.jar
# PATH_SEPERATOR is a good idea...but our path separater changes from : to ; depending on the tool
# cygwin/mingw uses :, while javac.exe is ;
#
if WINDOWS_BUILD
# JAVAC_RXTX_CP=bindings/java/bin\;bindings/java/ref/RXTXcomm.jar 
JAVAC_RXTX_CP=bindings/java/bin\;bindings/java/ref/jSerialComm-2.0.2.jar 
else
# JAVAC_RXTX_CP=bindings/java/bin:bindings/java/ref/RXTXcomm.jar 
JAVAC_RXTX_CP=bindings/java/bin:bindings/java/ref/jSerialComm-2.0.2.jar 
endif

JDIR = bindings/java
JPISTA_GEN = $(JDIR)/gen
JPISTA_INTF = $(JDIR)/intf
JPISTA_BIN = $(JDIR)/bin

JPISTA_JPKG = org.pista
JPISTAX_JPKG = org.pistax
JPISTA_PKG = org/pista
JPISTAX_PKG = org/pistax
JPISTA_SRC = $(JPISTA_GEN)/$(JPISTA_PKG)
JPISTAX_SRC = $(JPISTA_GEN)/$(JPISTAX_PKG)
JPISTA_GLUE = $(JDIR)/intf/$(JPISTAX_PKG)
JPISTA_CXX = $(JDIR)/pista_wrap.cxx
JPISTAX_CXX = $(JDIR)/pistax_wrap.cxx
JPISTA_SO = .libs/libjpista.so
JPISTAX_SO = .libs/libjpistax.so
JPISTA_JAR = $(JDIR)/jpista.jar

JSRC = $(JPISTA_SRC)/*.java $(JPISTAX_SRC)/*.java $(JPISTA_GLUE)/*.java

java-build: $(JPISTA_JAR) $(JPISTA_SO) $(JPISTAX_SO)

$(JDOC): bindings/swig/doc.py $(CPPXMLDOC)
	$(AM_V_at)test -d $(JPISTA_SRC) || $(MKDIR_P) $(JPISTA_SRC)
	$(AM_V_GEN)python $< java $(CPPXMLDOC) > $@

# $(AM_V_at)make java-clean
$(JPISTA_CXX): bindings/pista.i $(library_include_HEADERS)
	mkdir -p $(JPISTA_SRC)
	$(AM_V_GEN)swig -c++ -java -package $(JPISTA_JPKG) \
		-I$(srcdir)/include -I$(srcdir)/bindings/cxx -I$(srcdir) -I$(builddir)/include -Ibindings/cxx -outdir $(JPISTA_SRC) -o $@ $<

$(JPISTAX_CXX): bindings/pistax.i $(library_include_HEADERS)
	mkdir -p $(JPISTAX_SRC)
	$(AM_V_GEN)swig -c++ -java -package $(JPISTAX_JPKG) \
		-I$(srcdir)/include -I$(srcdir)/bindings/cxx -I$(srcdir) -I$(builddir)/include -Ibindings/cxx -outdir $(JPISTAX_SRC) -o $@ $<


$(JPISTA_JAR): $(JPISTA_CXX) $(JPISTAX_CXX)
	mkdir -p $(JPISTA_BIN)
	$(AM_V_GEN)$(JAVAC) -cp $(JAVAC_RXTX_CP) -sourcepath $(JPISTA_GEN) -d $(JPISTA_BIN) $(JPISTA_SRC)/*.java $(JPISTAX_SRC)/*.java 
	$(AM_V_GEN)$(JAVAC) -cp $(JAVAC_RXTX_CP) -sourcepath $(JPISTA_INTF) -d $(JPISTA_BIN) $(JPISTA_GLUE)/*.java
	$(AM_V_at)jar cf $(JPISTA_JAR) -C $(JPISTA_BIN) $(JPISTA_PKG) -C $(JPISTA_BIN) $(JPISTAX_PKG)

$(JPISTA_SO): $(JPISTA_CXX) $(library_include_HEADERS)
	$(AM_V_GEN)$(CXXCOMPILE) $(LDFLAGS) -L.libs -L$(srcdir)/bindings/cxx/.libs  -L $(srcdir)/src/hardware/mcc-ul -L/usr/lib64 \
		-fno-strict-aliasing -fPIC -shared $(JPISTA_CXX) -Wl,-Bstatic -lpista -lpistacxx -Wl,-Bdynamic ${libprotobuf_c_LIBS} ${libyajl_LIBS} ${libwebsockets_LIBS} ${HWLIBS} ${EXPAT_CFLAGS} -Wl,-Bstatic ${EXPAT_LIBS} -Wl,-Bdynamic -o $(JPISTA_SO) -lcrypto -lm -lz -lssl


$(JPISTAX_SO): $(JPISTAX_CXX) bindings/cxx/libpistacxx.la $(library_include_HEADERS)
	$(AM_V_GEN)$(CXXCOMPILE) $(LDFLAGS) -L.libs -L$(srcdir)/bindings/cxx/.libs -L $(srcdir)/src/hardware/mcc-ul -L/usr/lib64 \
		-fno-strict-aliasing -fPIC -shared $(JPISTA_CXX) $(JPISTAX_CXX) -Wl,-Bstatic -lpista -lpistacxx -Wl,-Bdynamic ${libexpat_LIBS} ${libprotobuf_c_LIBS} ${libyajl_LIBS} ${libwebsockets_LIBS} ${HWLIBS} ${EXPAT_CFLAGS} -Wl,-Bstatic ${EXPAT_LIBS} -Wl,-Bdynamic -o $(JPISTAX_SO) -lcrypto -lm -lz -lssl


java-install:
	$(INSTALL) -d $(libdir)/jni
	$(INSTALL) $(JPISTA_SO) -t $(libdir)/jni
	$(INSTALL) $(JPISTAX_SO) -t $(libdir)/jni
	$(INSTALL) -d $(datadir)/java
	$(INSTALL) $(JPISTA_JAR) -t $(datadir)/java

java-clean:
	$(AM_V_at)rm -f $(JPISTA_CXX) $(JPISTAX_CXX)
	$(AM_V_at)rm -f $(JPISTA_SRC)/*.java
	$(AM_V_at)rm -f $(JPISTA_JAR)
	$(AM_V_at)rm -f $(JPISTA_SO)
	$(AM_V_at)rm -rf $(JPISTA_BIN)
	$(AM_V_at)rm -rf $(JPISTA_GEN)
	$(AM_V_at)rm -rf $(JDIR)/doxy/

java-doc:
	$(AM_V_at)cd $(srcdir)/$(JDIR) && BUILDDIR=$(abs_builddir)/$(JDIR)/ doxygen Doxyfile 2>/dev/null

BUILD_EXTRA += java-build
INSTALL_EXTRA += java-install
CLEAN_EXTRA += java-clean

endif

all-local: $(BUILD_EXTRA)
install-exec-local: $(INSTALL_EXTRA)
clean-local: $(CLEAN_EXTRA)

MAINTAINERCLEANFILES = ChangeLog

.PHONY: ChangeLog
ChangeLog:
	git --git-dir $(top_srcdir)/.git log > ChangeLog || touch ChangeLog

dist-hook: ChangeLog

