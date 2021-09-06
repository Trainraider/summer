# SPDX-License-Identifier: GPL-2.0-only

# Just some shorthand calls to meson

.PHONY: compile install test fsan clean format

compile: | build
	meson compile -C build $(ARGS)

install: | release
	meson install -C release $(ARGS)

# Running plain `make` is sometimes required before testing.
# select test suit: `make test ARGS='--suite O0'`
test: | build
	-meson test -C build $(ARGS)
	less +G build/meson-logs/testlog.txt

fsan: | asan
	meson compile -C asan

clean:
	-rm -r build
	-rm -r release
	-rm -r asan

clean-full:
	-rm -r build
	-rm -r release
	-rm -r asan
	-rm -r subprojects/testing
	-rm -r subprojects/types

build:
	meson setup build --buildtype=debug
	cp build/compile_commands.json compile_commands.json

release:
	meson setup release --buildtype=release

asan:
	CFLAGS=-fsanitize=address,undefined LDFLAGS=-fsanitize=address,undefined\
		meson setup asan --buildtype=debug

format: | build
	ninja -C build clang-format

