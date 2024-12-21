
# Script Gnuplot pour tracer les résultats
set terminal pngcairo size 800,600
set output "output.png"  # Définir le fichier de sortie

set title "Comparaison des solutions numérique et exacte"
set xlabel "x"
set ylabel "u(x)"
set grid

# Tracer les courbes
plot "u_k.data" using 1:2 with lines title "Condition initiale (u_k)", \
     "u_kp1_final.data" using 1:2 with lines linecolor rgb "blue" title "Solution numérique (u_kp1)", \
     "u_ref_exact.data" using 1:2 with lines linecolor rgb "red" title "Solution exacte (u_ref)", \
     "u_kp1_gs_final.data" using 1:2 with lines linecolor rgb "green" title "Solution Gauss-Seidel (u_kp1_gs)"
