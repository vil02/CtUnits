FROM gitpod/workspace-base:2023-04-18-03-19-46

USER root

RUN apt-get update \
  && apt-get install -y --no-install-recommends \
  cmake \
  libboost-all-dev \
  cppcheck \
  clang-tidy \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

USER guest
