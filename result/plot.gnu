set terminal postscript eps color enhanced
#set size 0.7, 0.6
set key top outside

# nci
set title "NCI"
set xlabel "#search node"
set autoscale x
set ylabel "TSS mean"
set autoscale y
plot "nci/correct.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "red" title "exact DFS"
replot "nci/bfs.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "red" title "exact BFS"
replot "nci/bandit_dag_1.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "blue" title "bandit DAG:1"
replot "nci/bandit_dag_10.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "blue" title "bandit DAG:10"
replot "nci/bandit_tree_1.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "green" title "bandit TREE:1"
replot "nci/bandit_tree_10.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "green" title "bandit TREE:10"

set output "nci/image/count_all.eps"
replot

set output "nci/image/count_detail.eps"
set xrange [0:3000]
replot

set out

set title "NCI"
set xlabel "time[s]"
set autoscale x
set ylabel "TSS mean"
set autoscale y
plot "nci/correct.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "red" title "exact DFS"
replot "nci/bfs.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "red" title "exact BFS"
replot "nci/bandit_dag_1.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "blue" title "bandit DAG:1"
replot "nci/bandit_dag_10.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "blue" title "bandit DAG:10"
replot "nci/bandit_tree_1.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "green" title "bandit TREE:1"
replot "nci/bandit_tree_10.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "green" title "bandit TREE:10"

set output "nci/image/time_all.eps"
replot

set output "nci/image/time_detail.eps"
set xrange [0:30]
replot

set out

# aids
set title "AIDS"
set xlabel "#search node"
set autoscale x
set ylabel "TSS mean"
set autoscale y

plot "aids/correct.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "red" title "exact DFS"
replot "aids/bfs.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "red" title "exact BFS"
replot "aids/bandit_dag_1.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "blue" title "bandit DAG:1"
replot "aids/bandit_dag_10.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "blue" title "bandit DAG:10"
replot "aids/bandit_tree_1.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "green" title "bandit TREE:1"
replot "aids/bandit_tree_10.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "green" title "bandit TREE:10"

set output "aids/image/count_all.eps"
replot

set output "aids/image/count_detail.eps"
set xrange [0:6000]
replot

set out

set title "AIDS"
set xlabel "time[s]"
set autoscale x
set ylabel "TSS mean"
set autoscale y
plot "aids/correct.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "red" title "exact DFS"
replot "aids/bfs.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "red" title "exact BFS"
replot "aids/bandit_dag_1.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "blue" title "bandit DAG:1"
replot "aids/bandit_dag_10.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "blue" title "bandit DAG:10"
replot "aids/bandit_tree_1.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "green" title "bandit TREE:1"
replot "aids/bandit_tree_10.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "green" title "bandit TREE:10"

set output "aids/image/time_all.eps"
replot

set output "aids/image/time_detail.eps"
set xrange [0:30]
replot

set out

# cas
set title "CAS"
set xlabel "#search node"
set autoscale x
set ylabel "TSS mean"
set autoscale y
plot "cas/correct.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "red" title "exact DFS"
replot "cas/bfs.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "red" title "exact BFS"
replot "cas/bandit_dag_1.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "blue" title "bandit DAG:1"
replot "cas/bandit_dag_10.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "blue" title "bandit DAG:10"
replot "cas/bandit_tree_1.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "green" title "bandit TREE:1"
replot "cas/bandit_tree_10.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "green" title "bandit TREE:10"

set output "cas/image/count_all.eps"
replot

set output "cas/image/count_detail.eps"
set xrange [0:17000]
replot

set out

set title "CAS"
set xlabel "time[s]"
set autoscale x
set ylabel "TSS mean"
set autoscale y
plot "cas/correct.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "red" title "exact DFS"
replot "cas/bfs.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "red" title "exact BFS"
replot "cas/bandit_dag_1.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "blue" title "bandit DAG:1"
replot "cas/bandit_dag_10.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "blue" title "bandit DAG:10"
replot "cas/bandit_tree_1.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "green" title "bandit TREE:1"
replot "cas/bandit_tree_10.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "green" title "bandit TREE:10"

set output "cas/image/time_all.eps"
replot

set output "cas/image/time_detail.eps"
set xrange [0:80]
replot

set out

# cpdb
set title "CPDB"
set xlabel "#search node"
set autoscale x
set ylabel "TSS mean"
set autoscale y
plot "cpdb/correct.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "red" title "exact DFS"
replot "cpdb/bfs.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "red" title "exact BFS"
replot "cpdb/bandit_dag_1.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "blue" title "bandit DAG:1"
replot "cpdb/bandit_dag_10.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "blue" title "bandit DAG:10"
replot "cpdb/bandit_tree_1.dat" using 2:3 with linespoints lw 2 pt 5 lc rgb "green" title "bandit TREE:1"
replot "cpdb/bandit_tree_10.dat" using 2:3 with linespoints lw 2 pt 9 lc rgb "green" title "bandit TREE:10"

set output "cpdb/image/count_all.eps"
replot

set output "cpdb/image/count_detail.eps"
set xrange [0:30]
replot

set out

set title "CPDB"
set xlabel "time[s]"
set autoscale x
set ylabel "TSS mean"
set autoscale y
plot "cpdb/correct.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "red" title "exact DFS"
replot "cpdb/bfs.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "red" title "exact BFS"
replot "cpdb/bandit_dag_1.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "blue" title "bandit DAG:1"
replot "cpdb/bandit_dag_10.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "blue" title "bandit DAG:10"
replot "cpdb/bandit_tree_1.dat" using 1:3 with linespoints lw 2 pt 5 lc rgb "green" title "bandit TREE:1"
replot "cpdb/bandit_tree_10.dat" using 1:3 with linespoints lw 2 pt 9 lc rgb "green" title "bandit TREE:10"

set output "cpdb/image/time_all.eps"
replot

set output "cpdb/image/time_detail.eps"
set xrange [0:0.2]
replot
