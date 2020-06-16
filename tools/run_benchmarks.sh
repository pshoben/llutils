$LLUTILS_HOME/build/benchmark/benchmark_llutils --benchmark_out_format=csv --benchmark_out=$LLUTILS_DATA/benchmark_llutils.csv | tee $LLUTILS_DATA/benchmark_llutils.txt
python3 $LLUTILS_HOME/tools/plot_results.py --input-file=${LLUTILS_DATA}/benchmark_llutils.csv --output-folder=${LLUTILS_DATA}

