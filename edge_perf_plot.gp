set grid
set key left top
set terminal png size 800,600

set title "Execution duration for PageRank algorithm, depending on edges count"

set xlabel "Edges count"
set ylabel "Execution duration (s)"

set datafile separator ";"
plot "output/by_edges.txt" using 3:5 with linespoint