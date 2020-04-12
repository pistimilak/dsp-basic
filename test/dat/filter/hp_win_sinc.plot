# Istvan Milak
# High-pass windowed sinc filter plot
# $ gnuplot -p hp_win_sinc.plot

reset
set terminal canvas size 1024,768
set output 'hp_win_sinc.html'
set size 1,1
set multiplot
set size 0.5,0.5
set origin 0,0.5
plot 'hp_input_signal.dat' with lines lc rgb 'black'
set origin 0.5,0.5
plot 'hp_win_sinc_filter.dat' with lines lc rgb 'red'
set origin 0,0
plot 'hp_conv_output.dat' with lines lc rgb 'blue'