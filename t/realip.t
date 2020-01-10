use Test::Nginx::Socket::Lua;
use Cwd qw(cwd);

repeat_each(1);

plan 'no_plan';

my $pwd = cwd();
my $tmp_dir = html_dir();

add_block_preprocessor(sub {
    my $block = shift;

    my $http_config = $block->http_config || '';
    my $init_by_lua_block = $block->init_by_lua_block || 'require "resty.core"';

    $http_config .= <<_EOC_;

    lua_package_path "$pwd/lib/?.lua;$pwd/t/lib/?.lua;../lua-resty-lrucache/lib/?.lua;;";
_EOC_

    $block->set_value("http_config", $http_config);

    if (!defined $block->error_log) {
        $block->set_value("no_error_log", "[error]");
    }

    if (!defined $block->request) {
        $block->set_value("request", "GET /t");
    }

});

log_level('debug');
no_long_string();
check_accum_error_log();
run_tests();

__DATA__

=== TEST 1: disable real ip
--- http_config
    init_worker_by_lua_block {
        local realip = require "resty.realip"
        assert(realip.disable_real_ip())
    }
--- config
    set_real_ip_from 127.0.0.1;
    real_ip_header    X-Forwarded-For;
    location = /t {
        content_by_lua_block {
            ngx.say(ngx.var.remote_addr)
        }
    }
--- more_headers
X-Forwarded-For: 1.1.1.1
--- response_body
127.0.0.1
