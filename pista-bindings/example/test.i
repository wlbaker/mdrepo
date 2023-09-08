%module test

%apply (char *STRING, size_t LENGTH) { (const char data[], size_t len) }
%inline %{
void binaryChar1(const char data[], size_t len) {
  printf("len: %d data: ", len);
  for (size_t i=0; i<len; ++i)
    printf("%x ", data[i]);
  printf("\n");
}

class CP {
    public:
	int write( const char data[], size_t len );
};

%}


