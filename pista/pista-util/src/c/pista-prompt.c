#include <stdio.h>
#include <string.h>
// #include <ctype.h>
// #include <dlfcn.h>

#include <pista.h>
#include <libserialport.h>

//#include <linenoise.h>
//#define READLINE linenoise
#include <readline/readline.h>
#define READLINE readline

#define TOK_SEP  " \t\r\n"

struct pista_context *pctx;

void app_init()
{
    pista_init( &pctx );
}

int event_dumper( void *cb, struct pista_data_packet *pkt)
{
    pista_dump_packet( pkt );
    return PISTA_OK;
}

struct pista_dev_driver *(*init_func)( struct pista_context *ctx );

int main( int argc, char *argv[] ) {
    
    char *line;
    struct pista_dev_inst devs[10];
    struct lws *wsss[10];
    int    tot_devs=0;
    int    tot_wss = 0;

    app_init();

    while( (line = readline("pista> ")) != NULL ) {
        // printf("request: %s\n", line );
        char *tok = strtok(line, TOK_SEP );
        if( tok == NULL ) continue;
        int n = strlen(tok);
        
        if( strncmp( tok, "quit", n) == 0 ) {
            break;
        } else if( strncmp( tok, "create", n) == 0 ) {
            char * s_name = strtok(NULL, TOK_SEP );
            if( s_name == NULL ) {
                printf("Usage: create [driver_name]\n");
                continue;
            }
            struct pista_dev_driver *driver = pista_find_driver( pctx, s_name );
            if( driver == NULL ) {
                printf("Could not find driver: %s\n", s_name );
                continue;
            }

            struct pista_dev_inst *di = &devs[tot_devs];
            int ret = pista_allocate( driver, di );
            if( ret != PISTA_OK ) {
                printf("allocate error: %d\n", ret );
                continue;
            }
            tot_devs++;

            pista_set_event_handler( di, event_dumper, NULL );


            printf("use \"attach\" to connect a data port.\n");
        } else if( strncmp( tok, "config", n) == 0 ) {

            char * s_driver = strtok(NULL, TOK_SEP );
            char * s_idx    = strtok(NULL, TOK_SEP );
            char * s_baud   = strtok(NULL, TOK_SEP );
            char * s_parity = strtok(NULL, TOK_SEP );
            char * s_datab  = strtok(NULL, TOK_SEP );
            char * s_stopb  = strtok(NULL, TOK_SEP );
            if( s_stopb == NULL ) {
                printf("Usage: config [driver] [idx] [baud] [parity] [datab] [stopb]\n");
                continue;
            }
            struct pista_dev_driver *driver = pista_find_driver( pctx, s_driver );
            if( driver == NULL ) {
                printf("Could not find driver: %s\n", s_driver );
                continue;
            }

            int d_idx = atoi(s_idx);
            struct pista_dev_inst *di = pista_dev_inst_from_idx( driver, d_idx );
            if( di == NULL ) {
                printf("Could not find %s/%d\n", s_driver, d_idx );
            }

            int ok = pista_config_lspIO( di, atoi(s_baud), *s_parity, atoi(s_datab), atoi(s_stopb), 0 );
            if( ok != PISTA_OK ) {
                printf("Could not configure baud=%d,parity=%c,datab=%d,stopb=%d: OK=%d\n", 
                        atoi(s_baud), *s_parity, atoi(s_datab), atoi(s_stopb), ok );
                continue;
            }

        } else if( strncmp( tok, "list", n) == 0 ) {
            int count = pista_dev_count( pctx );

            printf("  %-8.8s %-30.30s %6s\n", "Driver", "Long Name", "APIVER" );
            printf("  %-8.8s %-30.30s %6s\n", "--------", "-----------------------------", "------" );
            for(int i = 0; i < count; i++ ) {
                struct pista_dev_driver *driver = pista_dev_by_idx( pctx, i);
                printf("  %-8.8s %-30.30s %6d\n", driver->name, driver->longname, driver->api_version );

                int inst_count = pista_dev_inst_count( driver );
                for( int j = 0; j < inst_count; j++ ) {
                    struct pista_dev_inst *di = pista_dev_inst_from_idx( driver, j );
                    printf("    [%d] connected?\n", j+1 );
                }
            }
        } else if( strncmp( tok, "listi", n) == 0 ) {
            int count = pista_dev_count( pctx );

            printf("    %-4.4s %-8.8s %s\n", "INST", "Driver  ", "Status" );
            printf("    %-4.4s %-8.8s %s\n", "----", "--------", "--------------" );
            for(int i = 0; i < count; i++ ) {
                struct pista_dev_driver *driver = pista_dev_by_idx( pctx, i);
                if( driver == NULL ) {
                    printf("    <BAD DRIVER: %d>\n", i );
                    continue;
                }
                int inst_count = pista_dev_inst_count( driver );
                for( int j = 0; j < inst_count; j++ ) {
                    struct pista_dev_inst *di = pista_dev_inst_from_idx( driver, j );
                    if( di == NULL ) {
                        printf("    <BAD INST: %d/%d %s>\n", i,j, driver->name );
                    } else {
                        if( di->driver == NULL ) {
                            printf("    <BAD DRIVER LINK: %d/%d %s>\n", i,j, driver->name );
                            di->driver = driver;
                        }
                        printf("    [%d]  %-8.8s connected?\n", j+1, di->driver->name );
                    }
                }
            }
        } else if( strncmp( tok, "load", n) == 0 ) {
            char * s_name = strtok(NULL, TOK_SEP );
            char * s_path = strtok(NULL, TOK_SEP );
            if( s_name == NULL ) {
                printf("Usage: load <name> [<so>]\n");
                continue;
            }
            int ok = pista_load_plugin( pctx, s_name, s_path );
            if( ok != PISTA_OK ) {
                printf("Could not load plugin: %s\n", s_name );
            }
        } else if( strncmp( tok, "set", n) == 0 ) {
            char *s_name  = strtok(NULL, TOK_SEP );
            char *s_idx   = strtok(NULL, TOK_SEP );
            char *s_param = strtok(NULL, TOK_SEP );
            char *s_value = strtok(NULL, TOK_SEP );
            if( s_name == NULL || s_idx == NULL || s_param == NULL || s_value == NULL ) {
                printf("usage: set [name] [inst_idx] [param] [value]\n");
                continue;
            }
            struct pista_dev_driver *driver = pista_find_driver( pctx, s_name );
            if( driver == NULL ) {
                printf("Could not find driver: %s\n", s_name );
                continue;
            }

            int d_idx = atoi(s_idx);
            struct pista_dev_inst *pdi = pista_dev_inst_from_idx( driver, d_idx );
            if( pdi == NULL ) {
                printf("Could not find %s/%d\n", s_name, d_idx );
            }

            int ok = pista_set_dev_option( pdi, s_param, s_value );
        } else if( strncmp( tok, "attach", n) == 0 ) {
            char *s_name = strtok(NULL, TOK_SEP );
            char *s_idx = strtok(NULL, TOK_SEP );
            char *s_port = strtok(NULL, TOK_SEP );
            if( s_name == NULL || s_idx == NULL || s_port == NULL) {
                printf("usage: attach <driver_name> <inst_idx> <port>\n");
                continue;
            }
            struct pista_dev_driver *driver = pista_find_driver( pctx, s_name );
            if( driver == NULL ) {
                printf("Could not find driver: %s\n", s_name );
                continue;
            }

            int d_idx = atoi(s_idx);
            struct pista_dev_inst *di = pista_dev_inst_from_idx( driver, d_idx );
            if( di == NULL ) {
                printf("Could not find %s/%d\n", s_name, d_idx );
            }

            int ok = pista_attach_lspIO( di, s_port );
            if( ok != PISTA_OK ) {
                printf("Could not attach %s/%d to %s: %d\n", s_name, d_idx, s_port, ok );
            }

            ok = pista_config_lspIO( di, 38400, 'N', 8, 1, 0 );
            if( ok != PISTA_OK ) {
                printf("Could not config %s/%d to %s: %d\n", s_name, d_idx, s_port, ok );
            }

        } else if( strncmp( tok, "detach", n) == 0 ) {
            printf("NOT READY: detach <driver_name> <inst_idx>\n");
        } else if( strncmp( tok, "poll", n) == 0 ) {

            int count = pista_dev_count( pctx );
            for(int i = 0; i < count; i++ ) {
                struct pista_dev_driver *driver = pista_dev_by_idx( pctx, i);

                int inst_count = pista_dev_inst_count( driver );
                for( int j = 0; j < inst_count; j++ ) {
                    struct pista_dev_inst *di = pista_dev_inst_from_idx( driver, j );
                    printf("Polling device: %s/%d\n", di->driver->name, j);
                    pista_poll_lspIO( di );
                }
            }
        } else if( strncmp( tok, "port", n) == 0 ) {
            char *s_action = strtok(NULL, TOK_SEP );
            char *s_typ = strtok(NULL, TOK_SEP );
            if( s_action == NULL || (strcmp(s_action,"add") != 0) ) {
                printf("Usage: port add [ws]\n");
                continue;
            }
            if( s_typ == NULL || (strcmp(s_typ, "ws") != 0) ) {
                printf("Usage: port add [ws]\n");
                continue;
            }
            wsss[tot_wss++] = NULL;
        } else if( strncmp( tok, "ports", n) == 0 ) {
            struct sp_port **pports;
            enum sp_return ret = sp_list_ports( &pports );
            if( ret != SP_OK ) {
                printf("Error retrieving ports: %d\n", ret );
                continue;
            }

            printf("  %-14.14s %-14.14s %-30.30s %s\n", "Type", "Name", "Description", "Transport" );
            printf("  %-14.14s %-14.14s %-30.30s %s\n", "----", "----", "----------------------------", "--------------" );

            int idx = 0;
            struct sp_port *port = pports[idx++];
            while( port != NULL ) {
                char *name = sp_get_port_name( port );
                char *desc = sp_get_port_description( port );
                enum sp_transport trans = sp_get_port_transport( port );
                if( name == NULL ) break;
                if( desc == NULL ) desc = "?";
                printf("  %-14.14s %-14.14s %-30.30s %d\n", "libserialport", name, desc, trans);
                port = pports[idx++];
            }
            sp_free_port_list(pports);
            printf("  %-14.14s %-14.14s %-30.30s %s\n", "libwebsocket", "ws0", "wss://192.168.50.1", "wss");
            printf("  %-14.14s %-14.14s %-30.30s %s\n", "libwebsocket", "ws1", "https://192.168.50.1", "https");
        } else if( strncmp( tok, "poll", n) == 0 ) {
        } else if( strncmp( tok, "tick", n) == 0 ) {
            pista_tick( pctx );
        } else {
            printf("Unrecognized command.\n");
        }
    }

    pista_exit( pctx );
}

