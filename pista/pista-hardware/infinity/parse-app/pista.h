#include <stdint.h>
#include <inttypes.h>

struct pista_item_desc {
    const char *loc;
    const char *code;
    const char *desc;
    const char *unit;
    int subtyp;
    int precision;

    int spp;
    int freq;

    double m;
    double b;

    int offset;
    int count;
};

struct pista_stream_desc {
    int32_t stream_id;
    int32_t field_cnt;
    struct  pista_item_desc *desc;
};

struct pista_data_packet {
    int64_t tm;  /* this may be redundant with the payload...that's OK..dont want to parse the payload to get tm */
    int32_t stream_id;
    int32_t field_cnt;
    struct pista_item_desc *desc;
    int32_t payload_sz;
    void   *payload;
};


