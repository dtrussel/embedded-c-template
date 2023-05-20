# embedded-c-template

![Build Status](https://github.com/dtrussel/embedded-c-template/actions/workflows/build.yml/badge.svg)

This is an example for an embedded C/C++ project targeting ARM architecture and using an x86_64 host. It is intended to serve a starting point for how to layout your project for cross-compilation, unit testing on the host and automated documentation. Modern embedded toolchains can be quite complex and also require some tool/setup boilerplate which can be tedious if one has to write it from scratch.

The example project is named `mbed`. It uses a "dockerized" [build environment](https://github.com/dtrussel/embedded-c-cpp-builder)
