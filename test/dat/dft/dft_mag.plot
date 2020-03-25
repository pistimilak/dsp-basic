# Istvan Milak
# DFT plot
# $ gnuplot -p dft.plot

reset
set terminal canvas size 1024,768
set output 'dft_mag.html'
set size 1,1
set multiplot
set size 1.0,0.5
set origin 0,0.5
plot 'dft_input_signal.dat' with lines lc rgb 'black'
set origin 0,0
plot 'dft_output_mag.dat' with lines lc rgb 'green'
