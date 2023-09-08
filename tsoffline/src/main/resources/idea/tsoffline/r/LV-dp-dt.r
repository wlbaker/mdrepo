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

dpdt <- (yvals[1:(length(yvals)-1)] - yvals[ 2:length(yvals) ])/0.002
# sig$getSampleWidth()

subject <- app$getSubject()
title <- paste( sig$getAlias(), "-dP/dt: ", subject, sep="")

app$createPlot( title )

xx <- yvals[1:(length(yvals)-1)]
yy <- dpdt[1:(length(yvals)-1)]

plot( xx, yy, main=title )
