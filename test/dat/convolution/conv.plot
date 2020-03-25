
# Istvan Milak
# Convolution plot
# $ gnuplot -p conv.plot

reset
set terminal canvas size 1024,768
set output 'conv.html'
set size 1,1
set multiplot
set size 0.5,0.5
set origin 0,0.5
plot 'conv_input_signal.dat' with lines lc rgb 'black'
set origin 0.5,0.5
plot 'conv_impulse_response.dat' with lines lc rgb 'red'
set origin 0,0
plot 'conv_output_signal.dat' with lines lc rgb 'blue'