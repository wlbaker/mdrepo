#
#
#

startSecs <- 0
stopSecs <- 90000

r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation")
if( is.null( r_markers ) ) {
	gui$showMessage("Could not find ECG Segmentation information.")
	stop("Could not find ECG Segmentation")
}

xydata <- r_markers$getDataInRange( startSecs, stopSecs)

r_x <- data$X( xydata )
r_y <- data$Y( xydata )

pressure_layer <- data$getSignal( NULL, NULL, "L dist")
if( is.null( pressure ) ) {
	gui$showMessage("Could not find L dist.")
	stop("Could not find L dist")
}

xydata <- pressure_layer$getDataInRange( r_x[1], r_x[2] )
pressure_x <- data$X( xydata )
pressure_y <- data$Y( xydata )

app$createPlot( paste("Demo 3:", app$getSubject() ) )

par( mar=c(4,4,2,2) )
par( mfrow=c(3,3) )

for( sig in sigs ) {


	# ***************************************************
	# Extract first beat
	# ***************************************************
	r_x <- c( 0, 5)

	xybeat <- sig$getDataInRange( r_x[1], r_x[2])
	xx <- data$X( xybeat )
	yy <- data$Y( xybeat )

	plot( x=xx, y=yy, typ='l', 
		xlab=paste("Beat at pos:", r_x[1], "to", r_x[2]), 
		ylab="")

	# ***************************************************
	# Spectrum of first beat
	# ***************************************************


	## Examples from Venables & Ripley
	## spec.pgram
	spectrum(yy)
	spectrum(yy, spans = 3)
}
#	spectrum(yy, spans = c(3,3))
#	spectrum(yy, spans = c(3,5))

