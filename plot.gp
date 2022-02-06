set grid
set key left top
set terminal png size 800,600

set title "Execution duration for PageRank algorithm, depending on nodes count"

set xlabel "Nodes count"
set ylabel "Execution duration (s)"

set datafile separator ";"
plot "output/performance.txt" using 1:3 with linespoint