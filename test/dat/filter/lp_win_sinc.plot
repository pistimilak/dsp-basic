# Istvan Milak
# Low-pass windowed sinc filter plot
# $ gnuplot -p lp_win_sinc.plot

reset
set terminal canvas size 1024,768
set output 'lp_win_sinc.html'
set size 1,1
set multiplot
set size 0.5,0.5
set origin 0,0.5
plot 'lp_input_signal.dat' with lines lc rgb 'black'
set origin 0.5,0.5
plot 'lp_win_sinc_filter.dat' with lines lc rgb 'red'
set origin 0,0
plot 'lp_conv_output.dat' with lines lc rgb 'blue'