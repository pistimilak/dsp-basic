# Istvan Milak
# Running sum plot
# $ gnuplot -p rsum.plot

reset
set terminal canvas size 1024,768
set output 'rsum.html'
set size 1,1
set multiplot
set size 0.5,0.5
set origin 0,0.5
plot 'rsum_input_signal.dat' with lines lc rgb 'black'
set origin 0.5,0.5
plot 'rsum_output_signal.dat' with lines lc rgb 'red'



