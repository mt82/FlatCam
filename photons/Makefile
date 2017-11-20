ROOT_INCDIR	= `root-config --incdir`
ROOT_LIBS	= `root-config --libs`
CFLAGS		= -fPIC -pedantic -Wall -std=c++11
CXX		= g++
SRCS 		= generate_photons.cxx 
TARGET	 	= $(SRCS:.cxx=)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CFLAGS) -o $@ $^ -I. -I$(ROOT_INCDIR) $(ROOT_LIBS)

clean:
	rm -fr $(TARGET)
