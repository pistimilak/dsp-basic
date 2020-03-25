# Istvan Milak
# DFT ECG plot
# $ gnuplot -p dft_ecg.plot

reset
set terminal canvas size 1024,768
set output 'dft_ecg.html'
set size 1,1
set multiplot
set size 0.5,0.5
set origin 0,0.5
plot 'dft_ecg_input_signal.dat' with lines lc rgb 'black'
set origin 0,0
plot 'dft_ecg_output_rex.dat' with lines lc rgb 'green'
set origin 0.5,0
plot 'dft_ecg_output_imx.dat' with lines lc rgb 'green'
set origin 0.5,0.5
plot 'idft_ecg_output_signal.dat' with lines lc rgb 'red'