#!/bin/bash -l 
msg="=== $BASH_SOURCE :"

./check.sh 
[ $? -ne 0 ] && echo $msg check failed && exit 1


#SY=50
#SY=100
#SY=5000
#SY=10000
SY=50000

export OPTICKS_EMBEDDED_COMMANDLINE_EXTRA="--rngmax 10"

cmd="G4OpticksTest $PWD/gdml/G4Opticks_$SY.gdml macros/muon_noIO.mac"

echo $cmd
eval $cmd 

