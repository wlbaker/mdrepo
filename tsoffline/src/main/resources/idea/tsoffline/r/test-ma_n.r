
#app$open()
#canvas <- app$getCanvas()
#canvas$resetLayout()
#canvas$addBand( as.integer(1), 0.3 )
#canvas$addBand( as.integer(2), 0.3 )
#canvas$addBand( as.integer(3), 0.3 )
#canvas$reset()

sig_names <- c("1-in-20", "1-in-10", "1-in-5")
sig_mod <- c(20,10,5)
x0 <- c(1:10001)
x_tm <- c(1:10001) / 500

idx <- 1
yy <- list()
sigs <- list()
for( sig_loc in sig_names ) {
	dest_sig <- data$createDataSignal( "DERIVED", "waveform", sig_loc )
	
	dest_sig$setSampleRate( I(500) )
	dest_sig$setSamplesPerPacket( I(100) )

	y <- rep(0,length(x0))
	y[ (x0 %% sig_mod[idx]) == 1 ] <- 10
	
	dest_sig$addData( x_tm, y )
		
	# dest_sig$setBandId( as.integer(idx) )
	# canvas$addSignalLayer( as.integer(idx), dest_sig$getLayer() )

	yy[[idx]] <- y
	sigs[[idx]] <- dest_sig 
	
	idx <- idx + 1
}

app$clearPendingPlots()
app$createPlot("Test MA_n")

par( mar=c(4,4,2,2) )
par( mfrow=c(3,3) )

for( sig in sigs ) {

	tm0 <- 0
	tm1 <- 0.2

	xy <- sig$getDataInRange( tm0, tm1)
	x_tm <- data$X( xy )
	y_ori <- data$Y( xy )

	sig_ma3 <- MA3( sig )	
	xy <- sig_ma3$getDataInRange( tm0, tm1)
	y_ma3 <- data$Y( xy )

	sig_ma5 <- MA5( sig )	
	xy <- sig_ma5$getDataInRange( tm0, tm1)
	y_ma5 <- data$Y( xy )

	plot( x=x_tm, y=y_ori, typ='l', 
		xlab=paste("Signal:", tm0, "to", tm1), 
		ylab="")

	n_m3 <- length(y_ma3)
	n_m5 <- length(y_ma5)
	lines( x=x_tm[1:n_m3], y=y_ma3, col='blue' )
	lines( x=x_tm[1:n_m5], y=y_ma5, col='green' )

}

app$showPlots()

