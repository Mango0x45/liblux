#!/bin/sh

find . -name '*.[03]' -exec aspell --home-dir=./ --mode=nroff --ignore-case check {} \;
