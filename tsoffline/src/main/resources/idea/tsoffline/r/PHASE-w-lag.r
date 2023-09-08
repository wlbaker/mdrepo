# DIALOG TIMERANGE
# DIALOG SIGNAL

source( "src/main/resources/idea/tsoffline/r/PHASE-5pt-smooth-video.r" )

lag <- 30
xx     <- yvals[(1+ lag):n]
yy     <- dpdt[1:(n-lag)]

vid$setDataArray( app$getCanvas(), tmvals, xx, yy )
