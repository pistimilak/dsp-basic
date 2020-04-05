# Istvan Milak
# CDFT plot
# $ gnuplot -p cdft.plot

reset
set terminal canvas size 1024,768
set output 'cdft.html'
set size 1,1
set multiplot
set size 0.5,0.5
set origin 0,0.5
plot 'cdft_sig_input_rex.dat' with lines lc rgb 'red'
set origin 0.5,0.5
plot 'cdft_sig_input_imx.dat' with lines lc rgb 'red'
set origin 0,0
plot 'cdft_sig_output_rex.dat' with lines lc rgb 'green'
set origin 0.5,0
plot 'cdft_sig_output_imx.dat' with lines lc rgb 'green'