FROM ubuntu:latest

RUN apt-get update && apt-get install --no-install-recommends -y g++ gcc make cmake valgrind cppcheck doxygen graphviz libgtest-dev clang && apt-get clean && rm -rf /var/lib/apt/lists/*
