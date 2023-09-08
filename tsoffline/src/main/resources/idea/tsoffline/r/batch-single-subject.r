#
# pragma async 
#

# base <- "V:/HiFi Research/5. ISR - (Baker & Salinas)/data/BAMC 485 (Normal) R-Ex"
base <- "V:/HiFi Research/5. ISR - (Baker & Salinas)/data/BAMC 4685 Normal [R,E] (35yo M)"
sess_file <- "4685(rest)_160830_1556.xml"
dat_file <- "4685(rest)_160830_1556_w_001.dat"

app$close()
app$cd( base )
app$open( sess_file )

app$createPlot( paste("Single Batch:", app$getSubject() ) )
app$showPlots()
app$runR( "/idea/tsoffline/r/rri-basic.r" ) 
app$runR( "/idea/tsoffline/r/overlapped-beats-ecg.r" )
app$runR( "/idea/tsoffline/r/overlapped-beats-pap.r" )
app$runR( "/idea/tsoffline/r/overlapped-beats.r" )
app$runR( "/idea/tsoffline/r/waterfall-v2.r" )

workspace <- gsub( ".xml", ".R", sess_file )

save.image( workspace )
