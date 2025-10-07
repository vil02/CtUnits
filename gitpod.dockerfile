FROM gitpod/workspace-base:2025-10-06-13-14-25

USER root

RUN apt-get update \
  && apt-get install -y --no-install-recommends \
  clang-format=1:14.0-55~exp2 \
  clang-tidy=1:14.0-55~exp2 \
  cmake=3.22.1-1ubuntu1.22.04.2 \
  cppcheck=2.7-1 \
  libboost-all-dev=1.74.0.3ubuntu7 \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

USER gitpod
