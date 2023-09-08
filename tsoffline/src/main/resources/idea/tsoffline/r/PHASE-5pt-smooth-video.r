# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM Display.Signal
# DIALOG SIGNAL MEASUREMENT Segmentation.Signal

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
display_sig <- app$getParam("SIGNAL", "Display.Signal"  )
seg_sig <- app$getParam("SIGNAL", "Segmentation.Signal"  )

#
# Tweak graph parameters to accommodate known signals
#

sig_name <- display_sig$getAlias()

plot_range <- c( 30, 130, -900, 1300 )
 
g <- data.frame( NAME="L dist", X0=-120, X1=250 , Y0=-6000, Y1=6000, stringsAsFactors=FALSE )
g <- rbind( g, list("LVP", -120, 250, -6000, 6000 ) )
g <- rbind( g, list("L prox", 20, 180, -3500, 3500 ) )
g <- rbind( g, list("AoP", 20, 180, -3500, 3500 ) )
g <- rbind( g, list("ECG", -1.0, 3.5, -400, 350 ) )


idx = which( g$NAME == sig_name )
if( length(idx) > 0 ) {
	fiducial_lead <- g$LEAD[idx]
	fiducial_lag <- g$LAG[idx]
	
	plot_range <- c( g$X0[idx], g$X1[idx], g$Y0[idx], g$Y1[idx] )
}

#	gui$showMessage( paste(sig_name, plot_range[1], plot_range[3]) )

#
#
#

# if not real-time...
# xydata <- display_sig$getDataInRange( startSecs, stopSecs)
# else if real-time...get all the data
xydata <- display_sig$getData( )
#endif

tmvals <- data$X( xydata )
yvals <- data$Y( xydata )

n <- length(yvals)
yvals <- ( yvals[1:(n-4)] + yvals[ 2:(n-3)] + yvals[ 3:(n-2)] + yvals[ 2:(n-1)] + yvals[ 1:n ])/5
dpdt <- (yvals[2:length(yvals)] - yvals[ 1:(length(yvals)-1) ])
dpdt <- dpdt * display_sig$getSampleRate()

subject <- app$getSubject()

n      <- length(yvals) - 5
tmvals <- tmvals[1:n]
xx     <- yvals[1:n]
yy     <- dpdt[1:n]

vid <- app$createPhaseSpaceVideo( subject )
vid$setSubject( subject )
vid$setDisplaySignal( display_sig )
vid$setCentroidSignal( seg_sig )
vid$setDataArray( app$getCanvas(), tmvals, xx, yy )
vid$setPhasespaceSize( plot_range[1], plot_range[2], plot_range[3], plot_range[4] )

