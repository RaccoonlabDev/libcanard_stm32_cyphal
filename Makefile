# Copyright (c) 2023 Dmitry Ponomarev
# Distributed under the MIT License, available in the file LICENSE.
# Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
LIBPARAMS_DIR:=${ROOT_DIR}/Libs/libparams

all: ubuntu_minimal ubuntu_publisher_example

define build_example
	$(info Build example $(1)...)
	mkdir -p build/examples/$(1)
	cd build/examples/$(1) && cmake ../../../examples/$(1) && make -s
endef


ubuntu_minimal:
	$(call build_example,ubuntu_minimal)

ubuntu_publisher_example:
	$(call build_example,ubuntu_publisher_example)

generage_dsdl:
	if [ ! -d "build/nunavut_out" ]; then echo "not exist"; fi
	mkdir -p build/nunavut_out
	./scripts/nnvg_generate_c_headers.sh build/nunavut_out

clone_dependencies:
	mkdir -p build
	if [ ! -d "${LIBPARAMS_DIR}" ]; then git clone --depth 1 --branch v0.8.4 https://github.com/PonomarevDA/libparams.git ${LIBPARAMS_DIR}; fi

clean:
	rm -rf build/examples/

distclean:
	rm -rf build/
