# DIALOG TIMERANGE
# DIALOG SIGNAL

startSecs <- 0
stopSecs <- 250

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
sig <- app$getParam("SIGNAL", "selection" )

if( is.null( sig ) ) {
	gui$showMessage("Could not find signal.")
	stop("Could not find signal")
}

xydata <- sig$getDataInRange( startSecs, stopSecs)
yvals <- data$Y( xydata )

n <- length(yvals)
yvals <- ( yvals[1:(n-4)] + yvals[ 2:(n-3)] + yvals[ 3:(n-2)] + yvals[ 2:(n-1)] + yvals[ 1:n ])/5
dpdt <- (yvals[1:(length(yvals)-1)] - yvals[ 2:length(yvals) ])/0.002
# sig$getSampleWidth()

subject <- app$getSubject()
title <- paste( sig$getAlias(), "-dP/dt: ", subject, sep="")

app$createPlot( title )

xx <- yvals[1:(length(yvals)-1)]
yy <- dpdt[1:(length(yvals)-1)]

plot( xx, yy, main=title, typ='l' )

# plot( xx, yy, main=title, typ='l' )

# par( mfrow=c(2,1) )
# plot( xx, main=paste( "5Pt Filtered:", sig$getAlias() ), typ='l' )
# plot( yy, main="dP/dt", typ='l', ylim=c(-800,1500) )
