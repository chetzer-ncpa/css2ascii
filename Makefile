TYPE=exe
NAME=css2ascii
VERSION=2
SUBVERSION=0
DEBUG=-ggdb
override INCPATH=include
override DEPENDENCIES=
OBJECTS=anyoption binaryreader util css_base cssfield cssstructure wfdisc site

LIBINSTDIR=/usr/local/lib
EXEINSTDIR=/usr/local/bin
override SOURCES=$(wildcard *.cpp)
override OBJECTS=$(SOURCES:.cpp=.o)
override INCDIR=$(foreach ipath,$(INCPATH),-I$(ipath))
override LIBDIR=$(foreach lib,$(DEPENDENCIES),-l$(lib))
override LIBINSTDIR=/usr/local/lib
override EXEINSTDIR=/usr/local/bin
#
# Set default values for compiler and flags
CXX=g++
BUILD_NUMBER_FILE=.nextbuildnumber

ifeq ($(TYPE),exe)
 CXXFLAGS=-c -Wall $(DEBUG)
else
 CXXFLAGS=-fpic -c -Wall $(DEBUG)
endif

ifeq ($(TYPE),lib)
 LDFLAGS=-shared
else
 LDFLAGS= 
endif

ifeq ($(TYPE),exe)
 INSTDIR=$(EXEINSTDIR)
else
 INSTDIR=$(LIBINSTDIR)
endif

LINKCOMMAND1=
LINKCOMMAND2=
LINKCOMMAND3=

ifeq ($(TYPE),lib)
 TARGET=lib$(NAME).so$(VERSION) lib$(NAME).so
 TARGET0=lib$(NAME).so$(VERSION)
 TARGET1=$(basename $(TARGET0))
 TARGET2=$(basename $(TARGET1))
 TARGET3=$(basename $(TARGET2))
 LINKCOMMAND1=ln -fs $(INSTDIR)/$(TARGET0) $(INSTDIR)/$(TARGET1)
 LINKCOMMAND2=ln -fs $(INSTDIR)/$(TARGET1) $(INSTDIR)/$(TARGET2)
 LINKCOMMAND3=ln -fs $(INSTDIR)/$(TARGET2) $(INSTDIR)/$(TARGET3)
else ifeq ($(TYPE),static)
 TARGET=lib$(NAME).a
 TARGET0=$(TARGET)
else
 TARGET=$(NAME)
 TARGET0=$(TARGET)
endif

.PHONY: clean tidy install tar

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(LIBDIR) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCDIR) $< -o $@

clean:
	rm -rf *.o $(TARGET) *.so *.so.*

tidy:
	rm -rf *.o *.so

install:
	$(MAKE) tidy
	ln -fs $(CURDIR)/$(TARGET0) $(INSTDIR)
	$(LINKCOMMAND1)
	$(LINKCOMMAND2)
	$(LINKCOMMAND3)

tar:
	tar cvzfh $(NAME).$(VERSION).$(SUBVERSION).tar.gz include/*.h $(SOURCES) Makefile

