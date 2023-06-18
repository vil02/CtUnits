FROM gitpod/workspace-base

RUN apt-get install -y --no-install-recommends \
  libboost-all-dev \
  cppcheck \
  clang-tidy
