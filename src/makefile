ID$@IR =../include
IDIR =../include
CC= g++
CFLAGS=-I$(IDIR)  -fprofile-arcs -fpermissive 
PROGRAM_GCOV =
ODIR=../obj
#TEST_ODIR=../Test/obj
LDIR =../src
#DIR_TESTS=../Test
#TEST_EXE= Proxy_Test 
LIBS=

PROGRAM = aracne

_HEADERS = parser.h spider.h comm.h
HEADERS = $(patsubst %,$(IDIR)/%,$(_HEADERS))

_OBJECTS = parser.o spider.o comm.o main.o
OBJECTS = $(patsubst %,$(ODIR)/%,$(_OBJECTS))

_TESTS =  
TESTS = $(patsubst %,$(DIR_TESTS)/%,$(_TESTS))

$(ODIR)/%.o: %.cpp $(HEADERS) 
	$(CC) -c -o $@ $< $(CFLAGS)  $(LIBS)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(TEST_EXE) : $(TESTS) 
	$(CC) -o $@ --coverage $^ $(CFLAGS)

program: $(PROGRAM) test gcov project

test: $(TEST_EXE)
	cp $(LDIR)/*.gcno $(ODIR)

run:
	./$(PROGRAM) 

run_test:
	./$(TEST_EXE)
.PHONY: clean

gcov:
	gcov $(PROGRAM_GCOV).gcda

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(PROGRAM) $(TEST_EXE)

clean_coverage:
	rm -f *.gcno *.gcda *.gcov

clean_all:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ && rm -f *.gcno *.gcda *.gcov $(PROGRAM) $(TEST_EXE)
