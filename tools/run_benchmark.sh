$LLUTILS_HOME/build/benchmark/${1} --benchmark_out_format=csv --benchmark_out=$LLUTILS_DATA/${1}.csv 2>/dev/null | tee $LLUTILS_DATA/${1}.txt
python3 $LLUTILS_HOME/tools/plot_results.py --input-file=${LLUTILS_DATA}/${1}.csv
python3 $LLUTILS_HOME/tools/plot_results.py --input-file=${LLUTILS_DATA}/${1}.csv --ignore-name=v1 # don't plot the baseline

echo "" > $LLUTILS_DATA/summary_${1}.md
echo "## summary" >> $LLUTILS_DATA/summary_${1}.md
echo "" >> $LLUTILS_DATA/summary_${1}.md
echo "|function version       | RMS                  | Big O                      |"  >> $LLUTILS_DATA/summary_${1}.md
echo "|:----------------------|---------------------:|:--------------------------:|"  >> $LLUTILS_DATA/summary_${1}.md

egrep 'BigO|RMS' $LLUTILS_DATA/${1}.txt | sed -s 's/unsigned /unsigned_/g' | awk '!(NR%2){print$0p}{p=$0}' | awk '{printf("| %s | %s | %s %s |\n",$1,$2,$9,$10);}' >> $LLUTILS_DATA/summary_${1}.md

echo "" >> $LLUTILS_DATA/${1}.txt
echo "## reference architecture" >> $LLUTILS_DATA/${1}.txt
echo "$(gcc --version | head -1)" >> $LLUTILS_DATA/${1}.txt
echo "$(uname -a)" >> $LLUTILS_DATA/${1}.txt
#echo "$(lscpu)" >> $LLUTILS_DATA/${1}.txt
#echo "$(cat /proc/meminfo)" >> $LLUTILS_DATA/${1}.txt


