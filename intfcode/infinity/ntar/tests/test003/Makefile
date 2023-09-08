CFLAGS = -I ../..
LIBS = -lntar
TESTNAME = test003

$(TESTNAME): $(TESTNAME).c
	$(CC) $(CFLAGS) $(TESTNAME).c $(LIBS) -o $@

clean:
	rm -f $(TESTNAME) *.o core