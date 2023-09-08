/**
 * @file
 *
 * Bindings for C++ interface to [PISTA].
 */

/**
 * @defgroup grp_cxx_bindings C++ Bindings
 *
 * Bindings for C++ interface to [PISTA].
 *
 * <p>This C++ interface is the basis for SWIG generated bindings to other languages.
 *
 * @{
 */


#ifndef PISTA_CL_H
#define PISTA_CL_H

#if defined(SWIG)

#ifdef PISTA_API
#undef PISTA_API
#endif
#define PISTA_API

#else
#include <string>
#include <cctype>
#include "pista.h"
#endif


namespace pistax
{

/*
 * forwared and external declarations
 */

class PISTA_API PistaDev;

extern "C" const char *getPistaVersion();

class PISTA_API PistaDescriptor {
	const ProtobufCFieldDescriptor *fd;
public:
	PistaDescriptor( const ProtobufCFieldDescriptor *fd);

	const char *getLoc();
	int getSPP();
	int getFreq();
};

class PISTA_API PistaStream {
	const pista_data_packet *pkt;

public:
	PistaStream( const pista_data_packet *pkt );

	const char *getPackageName();
	int getDescriptorCount( );
	PistaDescriptor getDescriptorByIdx( int idx );
};

class PISTA_API PistaDataPacket {
	const pista_data_packet *pkt;
public:
	PistaDataPacket( pista_data_packet *pkt );
	~PistaDataPacket( );

	int64_t getTm( );
	int getStreamID( );
	int getDescriptorCount();

	const ProtobufCFieldDescriptor *_getDescriptor( int field_idx );
	PistaDescriptor getDescriptor( int field_idx );

	const char *getDescriptorLoc( int field_idx );
	int getFieldSubtyp( int field_idx );
	int getFieldQuantifier( int field_idx );

	int getInt( int field_idx );
	int getLong( int field_idx );
	float getFloat( int field_idx );
	char *getString( int field_idx );

    char  *getByteArray( int field_idx, size_t *sz );
	int   *getIntArray( int field_idx, size_t *len );
	float *getFloatArray( int field_idx, size_t *len );
	double *getDoubleArray( int field_idx, size_t *len );

    const pista_data_packet *_packet( ); // { return pkt; }
};

class PISTA_API PistaEventHandler {

public:
	PistaEventHandler( );

	virtual ~PistaEventHandler() { }
	virtual int event( PistaDev *dev, PistaDataPacket *pkt ) = 0;
	// virtual int event( int eventTyp, const char *name, void *data ) = 0;

	// void attach( PistaDev *dev );
};

class PISTA_API PistaCommHandler {

public:
	PistaCommHandler();

	virtual ~PistaCommHandler();
	virtual int open( );
	virtual int config(int baud, int datab, int stopb, char parity );
	virtual int write( const char data[], size_t len) = 0;
	virtual int close();
};

/**
 * A device instance.
 */
class PISTA_API PistaDev {
private:
	pista_dev_inst *di;  //
    PistaEventHandler *event_h;
    PistaCommHandler *comm_h;

public:
	PistaDev( pista_dev_inst *di );


	PistaStream getStream( int streamId );

	int connect();
	int disconnect();

	int setOption( const char *key, const char *val);
	enum pista_dev_status getStatus( );

	// int getConfig( const char *key );
	// ? int getCapabilities( );
	
	int handle( const char data[], size_t len );

	void attach( commfunc_t writer, void *comm_priv );
	void attach( eventfunc_t writer, void *event_priv );
	void attach( PistaEventHandler *h );
	void attach( PistaCommHandler *comm );
	PistaDataPacket *poll( int sid );
    int dump( pista_dump_flags flags);

    pista_dev_inst *c_inst();

// protected:
	// friend class PistaDriver;
	int sendEvent( PistaDataPacket *cxxpkt );

};

class PISTA_API PistaDiscoveryHandler {

public:
	PistaDiscoveryHandler();

	virtual ~PistaDiscoveryHandler();
    virtual void discovery( int64_t tm, int event_type, const char *name, const char *url ) = 0;
};

class PISTA_API PistaService {

private:
    PistaDiscoveryHandler *discovery_h;

public:
    const char *name( );      // registered name: mccul, simu, etc, (cxx/java use only?)
    const char *longname( );  // a user friendly name from the driver

	void attach( discoveryfunc_t writer, void *discovery_priv );
	void attach( PistaDiscoveryHandler *disc );

    int start();
    int stop();
	int tick( );

private:
    static void discovery_eventfunc( const void *priv, const struct pista_discovery_info *pdi );  /// Callback function with C binding for Pista
	friend class PistaCl;

	PistaService( pista_discovery_service *c_service );
	pista_discovery_service *c_service;
};

class PISTA_API PistaDriver {
public:

    const char *name( );      // registered name: mccul, simu, etc, (cxx/java use only?)
    const char *longname( );  // a user friendly name from the driver

    PistaDev *allocate( );
    void      release( PistaDev *dev );

	// void capabilities();  -- not ready
    int probe( PistaCommHandler *h );

    // FIXME: I really don't want the arr_len...only for SWIG
    int verify( const char data[], size_t len, int dat_len );

    pista_dev_driver *c_inst();

private:
	friend class PistaCl;

	PistaDriver( pista_dev_driver *c_driver );
	pista_dev_driver *c_driver;

};

/**
 * This class is conceptionally the top level PISTA class for C++.
 * The handle to this singleton class is obtained through the static getInstance() call.
 *
 */
class PISTA_API PistaCl {
	
	// static PistaCl *inst;
	pista_context *ctx = NULL;

public:
	static PistaCl &getInstance();

    int loadPlugin(const char *s_name, const char *s_lib);

	int          driver_count();
	PistaDriver *driver(int idx);
	PistaDriver *driver( const char *name );

	int          service_count();
	PistaService *service(int idx);
	PistaService *service( const char *name );

	int run( );
	int tick( );
	int stop( );

    pista_context *c_inst();

    /**
     * Some languages (Java) allocate their own buffers for stdout.  Asking the C library to unbuffer
     * it's stdout  and stderr will result in the ability to mix C and Java output.  This can be
     * particularly useful in debugging.
     *
     */
    void unbufferStdio();
private:
        PistaCl(); // constructor

        // C++ 03
        // ========
        // Dont forget to declare these two. You want to make sure they
        // are unacceptable otherwise you may accidentally get copies of
        // your singleton appearing.
       
#if !defined(SWIG)
	// swig generated code doesnt like functions that are referenced but not implemented
        PistaCl(PistaCl const&);              // Don't Implement
        void operator=(PistaCl const&); // Don't implement
#endif

        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
        // PistaCl(PistaCl const&)               = delete;
        // void operator=(PistaCl const&)  = delete;
};


#ifdef HAVE_LIBSERIALPORT
struct sp_port; // simple forward declaration

class PISTA_API LspCOMM : public PistaCommHandler {
	sp_port *port;

public:
	LspCOMM( const char *name );

	LspCOMM( sp_port *port ) { this->port = port; }

	virtual ~LspCOMM();

	virtual int open( );
	virtual int config(int baud, int datab, int stopb, char parity );
	virtual int write( const char data[], size_t len);
	virtual int close();

    virtual void test(PistaDev *dev);
};
#endif

#ifdef HAVE_BOOSTCOMM
class PISTA_API BoostCOMM : public PistaCommHandler {
    void *vp;

public:
	BoostCOMM( const char *name );

	virtual ~BoostCOMM() { std::cout << "BoostCOMM::~BoostCOMM()" << std:: endl; }

	virtual int open( );
	virtual int config(int baud, int datab, int stopb, char parity );
	virtual int write( const char data[], size_t len);
	virtual int close();

    virtual void test(PistaDev *dev);
};
#endif

} // end namespace

/**
 * @}
 */

#endif
