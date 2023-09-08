CFLAGS = -I ../..
LIBS = -lntar
TESTNAME = test007

$(TESTNAME): $(TESTNAME).c
	$(CC) $(CFLAGS) $(TESTNAME).c $(LIBS) -o $@

clean:
	rm -f $(TESTNAME) *.o core