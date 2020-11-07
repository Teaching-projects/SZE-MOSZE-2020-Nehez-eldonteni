FROM ubuntu:latest

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y g++ gcc make cmake valgrind git cppcheck doxygen graphviz libgtest-dev clang && apt-get clean && rm -rf /var/lib/apt/lists/*
