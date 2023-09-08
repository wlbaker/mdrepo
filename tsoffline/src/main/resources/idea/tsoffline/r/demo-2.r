
app$open()
canvas <- app$getCanvas()
canvas$resetLayout()
canvas$addBand( as.integer(1), 0.3 )
canvas$addBand( as.integer(2), 0.3 )
canvas$addBand( as.integer(3), 0.3 )
canvas$reset()

sig_names <- c("1hz", "5hz", "25hz")
x0 <- c(1:10001) / 500  # 10 secs of data

# sig_loc <- sig_names[1]
idx <- 1
yy <- list()
sigs <- list()
for( sig_loc in sig_names ) {
	dest_sig <- data$createDataSignal( "DERIVED", "waveform", sig_loc )
	
	dest_sig$setSampleRate( I(500) )
	dest_sig$setSamplesPerPacket( I(100) )

	mult <- 5 ** idx
	
	yy[[idx]] <- 20 * sin(x0 * pi * mult )
	sigs[[idx]] <- dest_sig 
	
	dest_sig$addData( x0, yy[[idx]] )
	
	dest_sig$setBandId( as.integer(idx) )
	canvas$addSignalLayer( as.integer(idx), dest_sig$getLayer() )
	idx <- idx + 1
}

app$createPlot("Demo 2")

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

