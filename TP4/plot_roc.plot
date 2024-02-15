set terminal png size 600,400
set output "roc_curve.png"
set title "Courbe ROC"
set xlabel "Taux de faux positif (FPR)"
set ylabel "Taux de vrai positif (TPR)"
set xrange [0:1]
set yrange [0:1]
plot "roc_data.dat" using 2:3 with lines title 'ROC'