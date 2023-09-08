/* File : example.h */

#include <cstdio>
#include <iostream>

class SerialIO {
public:
	virtual ~SerialIO() { std::cout << "SerialIO::~SerialIO()" << std:: endl; }
	virtual void send( const char *buf, int len) { std::cout << "SerialIO::send(" << buf << ")" << std::endl; }
};


class PistaDev {
private:
	SerialIO *_callback;
public:
	PistaDev(): _callback(0) {}
	~PistaDev() { delSerialIO(); }
	void delSerialIO() { delete _callback; _callback = 0; }
	void setSerialIO(SerialIO *cb) { delSerialIO(); _callback = cb; }
	void send(const char *buf, int len) { if (_callback) _callback->send( buf, len); }
};

