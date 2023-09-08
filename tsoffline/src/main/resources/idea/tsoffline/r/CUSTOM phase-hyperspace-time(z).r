
# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM SignalToGraph
# DIALOG SIGNAL MEASUREMENT Beat_Segmentation
#

require( scatterplot3d )
require( scales )  # alpha

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
deltaSecs <- stopSecs - startSecs
data_sig <- app$getParam("SIGNAL", "SignalToGraph" )
r_markers <- app$getParam("SIGNAL", "Beat_Segmentation" )

angle <- 10

#	gui$showMessage( message )

sig_name <- data_sig$getAlias()
deltaSecs <- stopSecs - startSecs

#	gui$showMessage( message )

update <- function( stopSecs ) {
	startSecs <- stopSecs - deltaSecs
	
	xydata <- r_markers$getDataInRange( startSecs, stopSecs)
	start_times <- data$X( xydata )
	if( length(start_times) < 2 ) {
		return
	}

	fiducial_lead <- 0.25
	fiducial_lag  <- 0.25
	
	xx <- data_sig$getTimesInRange( start_times[1] - fiducial_lead, start_times[2] - fiducial_lag )
	yy <- data_sig$getValuesInRange( start_times[1] - fiducial_lead, start_times[2] - fiducial_lag )

	xx <- xx - xx[1]
	
	n <- length(yy)
	y5 <- ( yy[1:(n-4)] + yy[ 2:(n-3)] + yy[ 3:(n-2)] + yy[ 2:(n-1)] + yy[ 1:n ])/5
	dpdt <- (y5[2:length(y5)] - y5[ 1:(length(y5)-1) ])
	dpdt <- ( dpdt[1:(n-4)] + dpdt[ 2:(n-3)] + dpdt[ 3:(n-2)] + dpdt[ 2:(n-1)] + dpdt[ 1:n ])/5
	dpdt <- dpdt * data_sig$getSampleRate()
	yy <- yy[ 11:(length(yy)) ]
	y5 <- y5[ 11:(length(y5)) ]
	
	n <- length( dpdt )
	length( xx ) <- n
	length( y5 ) <- n
	length( yy ) <- n
	
	
	palette <- colorRampPalette(c("blue", "red"))( n )
	colors <- palette[ c(1:n) ]

	# par( mfcol=c(1,2) )
	par(mar = c(5, 4, 4, 2) ) 

	yrange <- c( 30, 120 )
	z1range <- c(-600,3000)

	lower_pressure = as.integer(min(y5,na.rm=TRUE))
	upper_pressure = as.integer(max(y5,na.rm=TRUE))
	step_pressure = as.integer((upper_pressure - lower_pressure)/2)
	plabs=seq( lower_pressure, upper_pressure, step_pressure )
	blabs= 18*plabs - 160
	
	df <- data.frame(time=xx,pressure=y5,dpdt=dpdt) 	
	s3d <- scatterplot3d( x=df$pressure, z=df$dpdt, y=df$time,  
		angle=angle, pch=16, color='white', ylim=c(0,0.5), xlim=c(30,110), zlim=c(-500,1000), 
		col.axis="blue", col.grid="lightblue", 
		ylab="Time", xlab="Pressure", zlab="dP/dt", 
		main=paste(sig_name, "Traces", subject ) )
	
	nbeats <- length(start_times) - 1

	for( ii in c(2:nbeats) ) {
		xx <- data_sig$getTimesInRange( start_times[ii] - fiducial_lead, start_times[ii+1] - fiducial_lag )
		xx <- xx - xx[1]
		yy <- data_sig$getValuesInRange( start_times[ii] - fiducial_lead, start_times[ii+1] - fiducial_lag )

		n <- length(yy)
		y5 <- ( yy[1:(n-4)] + yy[ 2:(n-3)] + yy[ 3:(n-2)] + yy[ 2:(n-1)] + yy[ 1:n ])/5
		dpdt <- (y5[2:length(y5)] - y5[ 1:(length(y5)-1) ])
		dpdt <- dpdt * data_sig$getSampleRate()
		zz <- dpdt
		n <- length( dpdt )
		length( xx ) <- n
		length( y5 ) <- n
		length( yy ) <- n
		
		df <- data.frame(time=xx,pressure=y5,dpdt=zz) 	
		s3d$points3d( x=df$pressure, z=df$dpdt, y=df$time, highlight.3d=TRUE, col=alpha('black',0.2), pch=16, fill=TRUE )
	}

}

subject <- app$getSubject()
app$createPlot( paste("CUSTOM:", subject, sig_name) )
update( stopSecs )

