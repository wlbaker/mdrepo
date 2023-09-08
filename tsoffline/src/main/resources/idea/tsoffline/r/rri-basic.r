# DIALOG TIMERANGE
# %DIALOG SIGNAL

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
# data_sig <- app$getParam("SIGNAL", "selection" )

r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation")
if( is.null( r_markers ) ) {
	r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation: PT1")
}
if( is.null( r_markers ) ) {
	gui$showMessage("Could not find ECG Segmentation information.")
	stop("Could not find ECG Segmentation")
}

# convert list elements to number arrays
r_pos <- data$getXValuesInRange( r_markers, startSecs, stopSecs )
n <- length(r_pos)
rri = r_pos[ 2:n ] - r_pos[ 1:(n-1) ]

# convert to millis
rri = rri * 1000


subject <- app$getSubject()
app$createPlot( paste("RRI Plot:", subject) )

# par( mfrow=c(1,2) )
par( mar=c(2,4,2,2) )
layout( matrix( c(1,2),1,2,byrow=TRUE), widths=c(3,1) )
tm <- seq(1,n-1)
plot( x=tm, y=rri, type='l', xlab="", ylab=paste(subject, "RRI (ms)"), ylim=c(300,1500) )
boxplot( rri, ylim=c(300,1500) )

# app$showPlots()

