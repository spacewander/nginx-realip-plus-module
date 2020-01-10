OPENRESTY_PREFIX?=/usr/local/openresty
DESTDIR?=$(OPENRESTY_PREFIX)/site/lualib
INSTALL ?= install

test = t/

.PHONY: all test install

install:
	$(INSTALL) -d $(DESTDIR)/resty/
	$(INSTALL) -m664 lib/resty/* $(DESTDIR)/resty

test:
	luacheck lib/resty
	PATH=$(OPENRESTY_PREFIX)/nginx/sbin:$$PATH prove -r $(test)
