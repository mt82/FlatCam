ROOT_INCDIR	= `root-config --incdir`
ROOT_LIBS	= `root-config --libs`
CFLAGS		= -fPIC -pedantic -Wall -std=c++11
LDFLAGS 	= -shared
TARGET_LIB 	= libHadMtx.so
CXX		= g++

SRCS 		= MHadMtx.cxx MHadMtxDict.cxx
OBJS 		= $(SRCS:.cxx=.o)

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(ROOT_LIBS) 

%.o: %.cxx
	$(CXX) $(CFLAGS) -o $@ -c $< -I. -I$(ROOT_INCDIR) $(ROOT_LIBS)

%Dict.cxx: %.h LinkDef.h
	rootcling $@ $< LinkDef.h

clean:
	rm -fr *.o *.so *Dict.cxx
