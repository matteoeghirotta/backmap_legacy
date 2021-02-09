#!/usr/bin/env bash

molc=beads
# lldb --
../../src/backmap -t $molc/alk1_align.xyz -t $molc/alk2_align.xyz \
 -o butane_whole but_s01_04.last.dump
