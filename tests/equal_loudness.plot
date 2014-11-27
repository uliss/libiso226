set terminal pdf enhanced
set output 'equal_loudness.pdf'

set title "Equal loudness curves"
set logscale x 2
set grid xtics ytics mxtics mytics
set xtics 125, 2, 16000
set xtics add ("16" 16, "31.5" 31.5, "64" 64)
#set mxtics 6


set xrange [16:16000]
set xlabel "Frequency, Hz"
set ylabel "SPL, db"
set style line 1 lt 2 lw 3
#set key box linestyle 1

plot "phon_90.txt" title "90 phon" with lines,\
     "phon_80.txt" title "80 phon" with lines,\
     "phon_70.txt" title "70 phon" w l,\
     "phon_60.txt" title "60 phon" w l,\
     "phon_50.txt" title "50 phon" w l,\
     "phon_40.txt" title "40 phon" w l,\
     "phon_30.txt" title "30 phon" w l,\
     "phon_20.txt" title "20 phon" w l
