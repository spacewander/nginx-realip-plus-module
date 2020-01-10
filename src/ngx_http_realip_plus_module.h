#ifndef NGX_HTTP_REALIP_PLUS_MODULE_H
#define NGX_HTTP_REALIP_PLUS_MODULE_H

#include <ngx_http.h>


#if !(NGX_HTTP_REALIP)
#error "realip module is required by this module"
#endif


extern ngx_module_t  ngx_http_realip_plus_module;


typedef struct {
    unsigned int disabled:1;
} ngx_http_realip_plus_main_conf_t;


#endif /* NGX_HTTP_REALIP_PLUS_MODULE_H */
