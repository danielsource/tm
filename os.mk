build_dir := ./build

ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
    build_dir := $(build_dir)/windows
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CCFLAGS += -D AMD64
        build_dir := $(build_dir)-x64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CCFLAGS += -D AMD64
            build_dir := $(build_dir)-x64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CCFLAGS += -D IA32
            build_dir := $(build_dir)-x64
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
        build_dir := $(build_dir)/linux
    else
        ifeq ($(UNAME_S),Darwin)
            CCFLAGS += -D OSX
            build_dir := $(build_dir)/macos
        else
            build_dir := $(build_dir)/unknown
        endif
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CCFLAGS += -D AMD64
        build_dir := $(build_dir)-x64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CCFLAGS += -D IA32
        build_dir := $(build_dir)-x86
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CCFLAGS += -D ARM
        build_dir := $(build_dir)-arm
    endif
endif
