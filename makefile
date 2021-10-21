SRCDIR=src
LIBDIR=lib
BINDIR=bin
INCLUDEDIR=include
CC=gcc
AR=ar
CFLAGS=-Wall -pedantic -I$(INCLUDEDIR)
LDFLAGS=-L$(LIBDIR)
EXEC=serveurHTTP


all : $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC) : $(LIBDIR)/libreseau.a $(SRCDIR)/main.o $(SRCDIR)/serveur.o
	$(CC) -o $@ $(SRCDIR)/main.o $(SRCDIR)/serveur.o $(LDFLAGS) -lreseau
    
$(LIBDIR)/libreseau.a : $(SRCDIR)/reseau.o
	$(AR) -r $@ $^
    
$(SRCDIR)/%.o : $(SRCDIR)/%.c 
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	rm -rf $(BINDIR)/${EXEC}
	rm -rf $(LIBDIR)/*.a
	rm -rf $(SRCDIR)/*.o
	rm -rf ${BINDIR}/*
