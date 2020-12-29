#!/usr/bin/env bash

rm -f npb_substrate.0*
../../src/backmap -t npb/align1_bin.xyz -t npb/align2_naph.xyz -t npb/align3_phe.xyz \
-o npb_substrate npb_substrate.dump
