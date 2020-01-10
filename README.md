# nginx-realip-plus-module

This module provides extra feature based on official `http_realip_module`.

## installation

```bash
./configure ... \
    --add-module=path/to/nginx-realip-plus-module \
    --with-http_realip_module
```

The `--with-http_realip_module` is required to build this module.

## feature

Read `t/` to know how to use the new feature.

```lua
local realip = require "resty.realip"
assert(realip.disable_real_ip())
```

### disable_real_ip

**syntax:** `ok = realip.disable_real_ip()`
**context:** *init_worker_by_lua*

Disale `set_real_ip_from` directive globally.
