#!/bin/bash

if [[ -z "$LLUTILS_HOME" ]] ; then
  echo "LLUTILS_HOME not set" ; exit
fi

if [[ ! -d "$LLUTILS_HOME" ]] ; then
  echo "LLUTILS_HOME directory does not exist" ; exit
fi

if [[ -z "$LLUTILS_DATA" ]] ; then
  echo "LLUTILS_DATA not set" ; exit
fi

if [[ ! -d "$LLUTILS_DATA" ]] ; then
  echo "LLUTILS_DATA directory does not exist" ; exit
fi

$LLUTILS_HOME/build/benchmark/${1} --benchmark_out_format=csv --benchmark_out=$LLUTILS_DATA/${1}.csv 2>/dev/null | tee $LLUTILS_DATA/${1}.txt

$LLUTILS_HOME/tools/plot_results.sh ${1}

