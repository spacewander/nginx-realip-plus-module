#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include "ngx_http_realip_plus_module.h"


static void *ngx_http_realip_plus_create_main_conf(ngx_conf_t *cf);
static char *ngx_http_realip_plus_init_main_conf(ngx_conf_t *cf, void *conf);

static ngx_http_module_t ngx_http_realip_plus_module_ctx = {
    NULL,                                    /* preconfiguration */
    NULL,                                    /* postconfiguration */

    ngx_http_realip_plus_create_main_conf,  /* create main configuration */
    ngx_http_realip_plus_init_main_conf,    /* init main configuration */

    NULL,                                    /* create server configuration */
    NULL,                                    /* merge server configuration */

    NULL,                                    /* create location configuration */
    NULL                                     /* merge location configuration */
};


ngx_module_t ngx_http_realip_plus_module = {
    NGX_MODULE_V1,
    &ngx_http_realip_plus_module_ctx,    /* module context */
    NULL,                                /* module directives */
    NGX_HTTP_MODULE,                     /* module type */
    NULL,                                /* init master */
    NULL,                                /* init module */
    NULL,                                /* init process */
    NULL,                                /* init thread */
    NULL,                                /* exit thread */
    NULL,                                /* exit process */
    NULL,                                /* exit master */
    NGX_MODULE_V1_PADDING
};


static void *
ngx_http_realip_plus_create_main_conf(ngx_conf_t *cf)
{
    ngx_http_realip_plus_main_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_realip_plus_main_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    /*
     * set by ngx_pcalloc():
     *
     *     conf->disabled = 0;
     */
    return conf;
}


static char *
ngx_http_realip_plus_init_main_conf(ngx_conf_t *cf, void *conf)
{
    return NGX_CONF_OK;
}


ngx_int_t
ngx_http_realip_plus_disable_real_ip(ngx_http_request_t *r)
{
    ngx_http_realip_plus_main_conf_t   *rpmcf;

    ngx_log_error(NGX_LOG_INFO, ngx_cycle->log, 0,
                  "realip plus module disable set_real_ip_from");

    rpmcf = ngx_http_get_module_main_conf(r, ngx_http_realip_plus_module);
    rpmcf->disabled = 1;

    return NGX_OK;
}
