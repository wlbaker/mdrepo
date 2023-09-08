
#include <yajl/yajl_parse.h>  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

#include "propaqm.h"

static void usage(const char * progname)  
{  
    fprintf(stderr, "%s: reformat json from stdin\n"  
            "usage:  json_reformat [options]\n"  
            "    -a show annotation records\n"  
            "    -t show trend records\n"  
            "    -s show snap records\n"  
            "    -p show patient records\n"  
            "    -w show waveform records\n"  
            "    -m minimize json rather than beautify (default)\n"  
            "    -u allow invalid UTF8 inside strings during parsing\n",  
            progname);  
    exit(1);  
  
}  
  
int process_file( yajl_handle hand, char *fname ) {
    yajl_status stat;  
    int retval = 0;  
    size_t rd = 0;
    int count = 0;

    unsigned char fileData[1024 + 2];

    FILE *fd = fopen(fname, "r" );
    // FILE fd = stdin;
  
    for (;;) {  
        rd = fread((void *) fileData, 1, sizeof(fileData) - 2, fd );  
  
        if (rd == 0) {  
            if (!feof(fd)) {  
                fprintf(stderr, "error on file read.\n");  
                retval = 1;  
            }  
            break;  
        }  
        fileData[rd] = 0;  
        
        if( rd < 1024) {
            // printf("rd=%d\n", rd);
            count += rd; // debug breakable
        }
  
        stat = yajl_parse(hand, fileData, rd);  
  
        if (stat != yajl_status_ok) break;  
    }  
  
    stat = yajl_complete_parse(hand);  
  
    if (stat != yajl_status_ok) {  
        unsigned char * str = yajl_get_error(hand, 1, fileData, rd);  
        fprintf(stderr, "%s", (const char *) str);  
        yajl_free_error(hand, str);  
        retval = 1;  
    }  
  
    return retval;
}  

extern bool PROPAQM_dumpflag;
extern int  PROPAQM_verbose;
int main(int argc, char ** argv)  
{  
    struct pista_dev_inst ctx;
    struct pista_dev_driver drv;
    PROPAQM_init( NULL, &drv);
    PROPAQM_allocate( &propaqm_driver_info , &ctx);

    PROPAQM_dumpflag = true;
    PROPAQM_initDumper( NULL );
    
    // yajl_handle zws_hand;  
    yajl_handle ztr_hand;  

    yajl_handle curr_hand;  

    /* generator config */  
    int retval = 0;  
    int a = 1;  
  
    /* ok.  open file.  let's read and parse */  
    // zws_hand = yajl_alloc(&zws_callbacks, NULL, (void *)&ctx );  
    ztr_hand = yajl_alloc(&ztr_callbacks, NULL, (void *)&ctx );  

    // curr_hand = zws_hand;
    curr_hand = ztr_hand;

    // yajl_config(hand, yajl_allow_comments, 1);  
    // yajl_config(hand, yajl_allow_trailing_garbage, 1);  
 
    // yajl_config(zws_hand, yajl_allow_multiple_values, 1);  
    yajl_config(ztr_hand, yajl_allow_multiple_values, 1);  
  
    /* check arguments.*/  
    while (a < argc ) {  
        unsigned int i;  

        if( argv[a][0] == '-') {
            for ( i=1; i < strlen(argv[a]); i++) {  
                switch (argv[a][i]) {  
                    case 'a':  
                        PROPAQM_dump_set_file( "annotation", stdout );
                        break;
                    case 'p':  
                        PROPAQM_dump_set_file( "patient", stdout );
                        break;
                    case 's':  
                        PROPAQM_dump_set_file( "snap", stdout );
                        PROPAQM_dump_set_file( "tsnap", stdout );
                        break;
                    case 't':  
                        PROPAQM_dump_set_file( "trend", stdout );
                        break;
                    case 'u':  
                        // yajl_config(zws_hand, yajl_dont_validate_strings, 1);  
                        yajl_config(ztr_hand, yajl_dont_validate_strings, 1);  
                        break;  
                    case 'w':  
                        // curr_hand = zws_hand;
                        PROPAQM_dump_set_file( "wave", stdout );
                        break;
                    case 'v':  
                        // PROPAQM_verbose++;
                        PROPAQM_ztr_set_verbose(1);
                        break;
                    default:  
                        fprintf(stderr, "unrecognized option: '%c'\n\n",  
                                argv[a][i]);  
                        usage(argv[0]);  
                }  
            }
        } else {
            retval += process_file(curr_hand, argv[a]);
        }
        ++a;  

    }  
  
    yajl_free(ztr_hand);  
    // yajl_free(zws_hand);  

    return retval;  
}

