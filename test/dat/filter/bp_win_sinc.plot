# Istvan Milak
# Band-pass windowed sinc filter plot
# $ gnuplot -p lp_win_sinc.plot

reset
set terminal canvas size 1024,768
set output 'bp_win_sinc.html'
set size 1,1
set multiplot
set size 0.5,0.5
set origin 0,0.5
plot 'bp_input_signal.dat' with lines lc rgb 'black'
set origin 0.5,0.5
plot 'bp_win_sinc_filter.dat' with lines lc rgb 'red'
set origin 0,0
plot 'bp_conv_output.dat' with lines lc rgb 'blue'