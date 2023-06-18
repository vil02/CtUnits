# CtUnits

[![ubuntu_build](https://github.com/vil02/CtUnits/actions/workflows/ubuntu_build.yml/badge.svg)](https://github.com/vil02/CtUnits/actions/workflows/ubuntu_build.yml)
[![static_analysis](https://github.com/vil02/CtUnits/actions/workflows/static_analysis.yml/badge.svg)](https://github.com/vil02/CtUnits/actions/workflows/static_analysis.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=vil02_CtUnits&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=vil02_CtUnits)
[![CodeFactor](https://www.codefactor.io/repository/github/vil02/ctunits/badge)](https://www.codefactor.io/repository/github/vil02/ctunits)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/97b689747b6d49f2b223df82529cdd2a)](https://www.codacy.com/gh/vil02/CtUnits/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=vil02/CtUnits&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/github/vil02/CtUnits/branch/master/graph/badge.svg?token=B1LD8I1WYH)](https://codecov.io/github/vil02/CtUnits)

Compilte-time utilites for dealing with quantities with units.
Example [`meters_and_inches.cpp`](./examples/meters_and_inches/meters_and_inches.cpp) illustrates the basic usage.

The class [`Quantity`](./CtUnits/ctu/Quantity.hpp) allows to represent values with _arbitrary_ long list of units in rational powers.

[`CtUnits`](./CtUnits/) heavily relies on [Boost.Mp11](https://www.boost.org/doc/libs/master/libs/mp11/doc/html/mp11.html).
The [`tests`](./tests/) require [Boost.Test](https://github.com/boostorg/test).

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/vil02/CtUnits)
