<CsoundSynthesizer>
<CsOptions>
--opcode-lib=iso226@CMAKE_SHARED_LIBRARY_SUFFIX@ -d -odac
</CsOptions>
<CsInstruments>


sr = 44100
ksmps = 1024
nchnls = 2
0dbfs = 1.0

instr 1
     kndx init 20
     kspl init 0
     kinc init 100
     kmax init 10000
     
     printks "\n", 0
     
     loop1:
         kspl phon2spl 70, kndx
         printks "phon2spl(%.3f, %i) == %.3f\n", 0, 70, kndx, kspl
         kphon spl2phon kspl, kndx
         printks "spl2phon(%.3f, %i) == %.3f\n", 0, kspl, kndx, kphon
         
         printks "%5i\n", 0, kndx
     loop_lt kndx, 100, 1000, loop1     
endin

instr 2
    indx init 20

    loop:
        ispl phon2spli 60, indx
        prints "phon2spl(%f, %i) == %f\n", 60, indx, ispl
        iphon spl2phoni ispl, indx
        prints "spl2phon(%f, %i) == %f\n", ispl, indx, iphon
    loop_lt indx, 100, 1200, loop
endin

</CsInstruments>
<CsScore>
i 2 0 0
i 1 0 1
</CsScore>
</CsoundSynthesizer>
;example by victor lazzarini

<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
