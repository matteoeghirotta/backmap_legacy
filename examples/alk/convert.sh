#!/usr/bin/env bash                                                                     
molc=beads

# Convert
# lldb -- \
../../src/backmap -t $molc/align1_alk.xyz -t $molc/align2_alk.xyz -t $molc/align3_alk.xyz \
-o dodecane molc01.dump


