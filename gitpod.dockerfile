FROM gitpod/workspace-base:2023-12-27-09-44-38

USER root

RUN apt-get update \
  && apt-get install -y --no-install-recommends \
  cmake=3.22.1-1ubuntu1.22.04.1 \
  libboost-all-dev=1.74.0.3ubuntu7 \
  cppcheck=2.7-1 \
  clang-tidy=1:14.0-55~exp2 \
  clang-format=1:14.0-55~exp2 \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

USER gitpod
