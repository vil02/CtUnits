FROM gitpod/workspace-base

RUN sudo apt-get update \
  && sudo apt-get install -y --no-install-recommends \
  cmake \
  libboost-all-dev \
  cppcheck \
  clang-tidy
