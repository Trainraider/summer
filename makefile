# SPDX-License-Identifier: GPL-2.0-only
# Full license at https://spdx.org/licenses/GPL-2.0.html

# Just some convenient scripts for working with meson/ninja

RM = -yes | rm

ROOTCHECK = @echo;\
	if [[ $EUID -ne 0 ]]; then\
		echo "error: you cannot perform this operation unless you are root.";\
		exit 1;\
	fi

.PHONY: compile install uninstall test fsan clean format

compile: build
	meson compile -C build $(ARGS)

install: release
	meson install -C release $(ARGS)

uninstall: release
	$(ROOTCHECK)
	ninja -C release uninstall

# Running plain `make` is sometimes required before testing.
# select test suit: `make test ARGS='--suite O0'`
test: build
	-meson test -C build $(ARGS)
	less +G build/meson-logs/testlog.txt

fsan: asan
	meson compile -C asan

clean:
	$(RM) -r build
	$(RM) -r release
	$(RM) -r asan

clean-full:
	$(RM) -r build
	$(RM) -r release
	$(RM) -r asan
	$(RM) -r subprojects/testing
	$(RM) -r subprojects/types

build:
	meson setup build --buildtype=debug
	cp build/compile_commands.json compile_commands.json

release:
	meson setup release --buildtype=release

asan:
	CFLAGS=-fsanitize=address,undefined LDFLAGS=-fsanitize=address,undefined\
		meson setup asan --buildtype=debug

format: build
	ninja -C build clang-format

