local base = require("resty.core.base")
local NGX_OK = base.FFI_OK
local ffi = require "ffi"
local C = ffi.C

ffi.cdef[[
typedef intptr_t ngx_int_t;
ngx_int_t
ngx_http_realip_plus_disable_real_ip(ngx_http_request_t *r);
]]

local _M = {}

local get_request
do
    if base.get_request then
        get_request = base.get_request
    else
        -- old version of OpenResty doesn't have this method
        -- code below is copied from the latest OpenResty
        local ok, exdata

        ok, exdata = pcall(require, "thread.exdata")
        if ok and exdata then
            function get_request()
                local r = exdata()
                if r ~= nil then
                    return r
                end
            end

        else
            local getfenv = getfenv

            function get_request()
                return getfenv(0).__ngx_req
            end
        end
    end
end


function _M.disable_real_ip()
    local r = get_request()
    if not r then
        error("no request found")
    end

    local rc = C.ngx_http_realip_plus_disable_real_ip(r)
    return rc == NGX_OK
end


return _M
