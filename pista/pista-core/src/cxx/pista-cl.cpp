
#include <iostream>
#include "pista-cl.h"
#include <stdio.h>

using namespace pistax;
#include "config.h"

extern "C" const char *getPistaVersion() {
	return Pista_VERSION;
}

using namespace std;

PistaCl& PistaCl::getInstance() {
   static PistaCl instance;  // Guaranteed to be destoryed.  Instantiated on first use.
   return instance;
}

PistaCl::PistaCl() {
    pista_init( &ctx );
}

int PistaCl::driver_count( ) {
	return pista_dev_count( ctx );
}

int PistaCl::service_count( ) {
	return pista_service_count( ctx );
}

int PistaCl::run( ) {
	return pista_run( ctx );
}

int PistaCl::stop( ) {
	return pista_exit( ctx );
}

int PistaCl::tick( ) {
	return pista_tick( ctx );
}

pista_context *PistaCl::c_inst() {
    return ctx;
}

/**

 s_name: short name for the plugin.

 s_lib: full path to the file name of the plugin.  If this value is NULL, then the path is inferred from the environment
 variable PISTA_PLUGIN_DIR, together with the library short name, s_name.

*/

int PistaCl::loadPlugin(const char *s_name, const char *s_lib) {
    
    return pista_load_plugin( ctx, s_name, s_lib );
}

PistaDriver *PistaCl::driver(int idx) {
    
	pista_dev_driver *c_driver = pista_dev_by_idx( ctx, idx );
    if( c_driver != NULL ) {
            return new PistaDriver( c_driver );
    }
    return NULL;
}

PistaService *PistaCl::service(int idx) {
    
	pista_discovery_service *c_service = pista_service_by_idx( ctx, idx );
    // printf("pista_service_by_idx returned: %lx\n", (unsigned long)c_service);

    if( c_service != NULL ) {
            return new PistaService( c_service );
    }
    return NULL;
}

PistaDriver *PistaCl::driver(const char *name) {
	pista_dev_driver *c_driver = pista_find_driver(ctx, name);
    if( c_driver != NULL ) {
            return new PistaDriver( c_driver );
    }
    return NULL;
}

PistaService *PistaCl::service(const char *name) {
	pista_discovery_service *c_service = pista_find_service(ctx, name);
    if( c_service != NULL ) {
            return new PistaService( c_service );
    }
    return NULL;
}

void PistaCl::unbufferStdio()
{
    setbuf( stdout, NULL );
    setbuf( stderr, NULL );
}

