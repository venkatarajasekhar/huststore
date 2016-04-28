#ifndef __hustdb_ha_write_handler_20150730104912_h__
#define __hustdb_ha_write_handler_20150730104912_h__

#include "hustdb_ha_handler_base.h"

#define HUSTDB_METHOD_PUT        1
#define HUSTDB_METHOD_DEL        2
#define HUSTDB_METHOD_HSET       3
#define HUSTDB_METHOD_HDEL       4
#define HUSTDB_METHOD_SADD       5
#define HUSTDB_METHOD_SREM       6
#define HUSTDB_METHOD_TB_PUT     7
#define HUSTDB_METHOD_TB_UPDATE  8
#define HUSTDB_METHOD_TB_DELETE  9

#define HUSTDB_PROTO_BINARY      0
#define HUSTDB_PROTO_JSON        1

typedef enum
{
	STATE_WRITE_MASTER1,
	STATE_WRITE_MASTER2
} hustdb_write_state_t;

typedef struct
{
	hustdb_ha_ctx_t base;
	hustdb_write_state_t state;
	int error_count;
	int skip_error_count; // for del
	ngx_http_subrequest_peer_t * error_peer;
	uint32_t ttl;
	// param
	ngx_bool_t key_in_body;
	ngx_bool_t has_tb;
	ngx_bool_t check_body_len;
	uint8_t proto;
} ngx_http_hustdb_ha_write_ctx_t;

typedef ngx_int_t (*hustdb_ha_start_write_t)(
    ngx_bool_t support_post_only,
    ngx_bool_t key_in_body,
    ngx_bool_t has_tb,
    ngx_bool_t check_body_len,
    ngx_str_t * backend_uri,
    ngx_http_request_t *r);

ngx_int_t hustdb_ha_start_post(
    ngx_bool_t support_post_only,
    ngx_bool_t key_in_body,
    ngx_bool_t has_tb,
    ngx_bool_t check_body_len,
    ngx_str_t * backend_uri,
    ngx_http_request_t *r);
ngx_int_t hustdb_ha_start_del(
    ngx_bool_t support_post_only,
    ngx_bool_t key_in_body,
    ngx_bool_t has_tb,
    ngx_bool_t check_body_len,
    ngx_str_t * backend_uri,
    ngx_http_request_t *r);

ngx_int_t hustdb_ha_write_handler(
    uint8_t method,
    ngx_bool_t support_post_only,
    ngx_bool_t key_in_body,
    ngx_bool_t has_tb,
    ngx_bool_t check_body_len,
    ngx_str_t * backend_uri,
    ngx_http_request_t *r,
    hustdb_ha_start_write_t start_write);

#endif // __hustdb_ha_write_handler_20150730104912_h__
