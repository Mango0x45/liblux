#!/bin/sh

find . -name '*.3*' -exec \
	aspell --home-dir=./ --mode=nroff --ignore-case check {} \;
