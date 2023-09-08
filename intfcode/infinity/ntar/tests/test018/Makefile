CFLAGS = -I ../..
LIBS = -lntar
TESTNAME = test018

$(TESTNAME): $(TESTNAME).c
	$(CC) $(CFLAGS) $(TESTNAME).c $(LIBS) -o $@

clean:
	rm -f $(TESTNAME) *.o core