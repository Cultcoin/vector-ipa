
/* $Id: decode.h 2610 2010-07-01 08:17:20Z alor $ */

#ifndef __DECODE_H
#define __DECODE_H

#include <proto.h>
#include <packet.h>
#include <hook.h>
#include <pcap/pcap.h>

/* layer canonical name */

enum {
   IFACE_LAYER  = 1,
   LINK_LAYER   = 2,
   NET_LAYER    = 3,
   PROTO_LAYER  = 4,
   APP_LAYER    = 5,       /* special case for the middleware decoder. don't use it */
   APP_LAYER_TCP = 51,
   APP_LAYER_UDP = 52,
};

#define FUNC_DECODER(func) void * func(u_char *buf, u_int16 buflen, int *len, struct packet_object *po)
#define FUNC_DECODER_PTR(func) void * (*func)(u_char *buf, u_int16 buflen, int *len, struct packet_object *po)

#define DECODE_DATALEN   buflen
#define DECODE_DATA      buf
#define DECODED_LEN      *len
#define PACKET           po

#define EXECUTE_DECODER(x) do{ \
   if (x) \
      x(DECODE_DATA+DECODED_LEN, DECODE_DATALEN-DECODED_LEN, len, PACKET); \
}while(0)

#define DECLARE_REAL_PTR_END(x,y) u_char *x = po->DATA.data; \
                                  u_char *y = x + po->DATA.len

/* exported functions */

void decode_captured(u_char *u, const struct pcap_pkthdr *pkthdr, const u_char *pkt);
void add_decoder(u_int8 level, u_int32 type, FUNC_DECODER_PTR(decoder));
void del_decoder(u_int8 level, u_int32 type);
void * get_decoder(u_int8 level, u_int32 type);


#endif

/* EOF */

// vim:ts=3:expandtab

