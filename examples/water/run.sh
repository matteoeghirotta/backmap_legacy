#!/usr/bin/env bash

#EXE='gdb --args ../../src/backmap'
EXE='../../src/backmap'

#$EXE -t tip4p.xyz 01_water_cg_f55000.dump
$EXE -t tip4p.xyz 01_water_cg.dump -v 3
