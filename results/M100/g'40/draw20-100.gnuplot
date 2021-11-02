set datafile separator ','
set style line 100 lt 1 lc rgb "grey" lw 0.5 
set key left
set terminal svg size 800,600 enhanced font 'Segoe UI,10' background rgb 'white'
set output 'M100g40G20100.svg'
set style line 101 lw 2 lt rgb "#ff0000" # style for targetValue (1) (pink)
set style line 102 lw 2 lt rgb "#6600ff" # style for measuredValue (2) (light blue)
set style line 103 lw 2 lt rgb "#33cc33" # style for secondYAxisValue (3) (limegreen)
set style line 108 lw 2 lt rgb "#ff00ff" # style for secondYAxisValue (3) (limegreen)
set style line 105 lw 2 lt rgb "#ffcc00" # style for secondYAxisValue (3) (limegreen)
set style line 106 lw 2 lt rgb "#000000" # style for secondYAxisValue (3) (limegreen)
set style line 107 lw 2 lt rgb "#660033" # style for secondYAxisValue (3) (limegreen)
set style line 104 lw 2 lt rgb "#669999" # style for secondYAxisValue (3) (limegreen)

set grid ls 100
set title "|M|=100 , |g\'|=40"
set xlabel '|G|'
set ylabel 'Tiempo(ms)'
plot 'table20-100.csv' using 1:2 title 'NextClosure' with linespoints ls 101, 'table20-100.csv' using 1:3 title 'Lindig' with linespoints ls 102, 'table20-100.csv' using 1:4 with linespoints  title 'Inherit-Concepts' ls 104,'table20-100.csv' using 1:5 with linespoints title 'InClose' ls 105, 'table20-100.csv' using 1:6 with linespoints title 'Bordat' ls 106, 'table20-100.csv' using 1:7 with linespoints title 'Godin' ls 107, 'table20-100.csv' using 1:8 with linespoints title 'Norris' ls 103
