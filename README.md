<!-- vi: tw=80
  -->
# `liblux`

## Overview

`liblux` is a minimal C library (C++ compatible) for interacting with screen
brightness levels on Linux systems.  The library offers a simple to use and well
documented API for getting and setting screen brightness using both raw values
and percentages.

## Compilation

Compilation of the library is extremely simple, but will require you to have the
`tup` build system installed:

```
$ tup           # To build the library
# make install  # To install the library, requires root privileges
```

After compilation and installation, you will be able to build programs using the
`liblux` library that are dynamically or statically linked.

## Documentation

All library functions are documented via manual pages.  After installing the
library using the above commands, the manual pages will be installed on your
system and you’ll be able to read the documentation using the `man` command as
such:

```
$ man luxget  # To view documentation for the luxget(3) function
```

If you prefer to view documentation in your browser (why?), all manuals are also
available over at [my website][1].  [Here][2] is the link to view the manual
providing an overview of the entire library, for example.

[1]: https://thomasvoss.com/man
[2]: https://thomasvoss.com/man/lux.h.0.html
