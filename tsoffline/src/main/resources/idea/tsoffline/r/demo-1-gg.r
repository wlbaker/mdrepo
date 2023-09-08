# DIALOG TIMERANGE
# DIALOG SIGNAL

require(ggplot2)

#
# Get the user selected values for time range and signal...L prox
#

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
sig <- app$getParam("SIGNAL", "selection" )
sig_name <- sig$getAlias()

# ***************************************************
# I'll want the rwave markers
# ***************************************************

r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation")
if( is.null( r_markers ) ) {
	r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation: PT1")
}
if( is.null( r_markers ) ) {
	gui$showMessage("Could not find ECG Segmentation information.")
	stop("Could not find ECG Segmentation")
}

xydata <- r_markers$getDataInRange( startSecs, stopSecs)

r_x <- data$X( xydata )
r_y <- data$Y( xydata )


# ***************************************************
# create a plot
# ***************************************************

app$createPlot( paste("Demo:", sig_name ) )


# ***************************************************
# plot raw data selection
# ***************************************************

xydata <- sig$getDataInRange( startSecs, stopSecs)
xx <- data$X( xydata )
yy <- data$Y( xydata )

gg1 <- ggplot( data.frame(x=xx, y=yy) ) + 
	geom_line() +  
	xlab(sig_name) +
	geom_vline( data=r_x, color='blue' )

# ***************************************************
# Show a spectrum of the whole enchilada
# ***************************************************

yy <- ts( yy - mean(yy), start=0, frequency=500)

spec <- spectrum(yy, plot=FALSE )
gg2 <- ggplot( data.frame(f=spec$freq,spec=spec$spec), aes(x=f,y=spec)) + geom_bar( stat="identity" ) +  xlim(0,50)
spec <- spectrum(yy, spans=c(3,5), plot=FALSE )
gg3 <- ggplot( data.frame(f=spec$freq,spec=spec$spec), aes(x=f,y=spec)) + geom_bar( stat="identity" ) +  xlim(0,50)


# ***************************************************
# Extract first beat
# ***************************************************

xybeat <- sig$getDataInRange( r_x[1], r_x[2])
xx <- data$X( xybeat )
yy <- data$Y( xybeat )

yy <- ts( yy - mean(yy), start=0, frequency=500)

plot( x=xx, y=yy, typ='l', 
	xlab=paste("Beat at pos:", r_x[1], "to", r_x[2]), 
	ylab="")

# ***************************************************
# Spectrum of first beat
# ***************************************************



plot( spec.taper(yy, p=.1), typ='l' )

## Examples from Venables & Ripley
## spec.pgram
# -- spectrum(yy, typ='S') # this one is rather ragged
spec <- spectrum(yy, spans = 3, typ='S')
#! barplot( spec$spec, typ='l', xlim=c(0,50) )
bar0 <- ggplot( data=data.frame(f=spec2$freq,s=spec2$spec), aes(x=f,y=s)) + geom_bar(stat="identity") + xlim(0,50)
my_integral <- cumsum( spec$spec ) 
int0 <- ggplot( my_integral, aes(x=f,y=s)) + geom_line() + xlim(0,50)

# spectrum(yy, spans = c(3,3), typ='S')
# spectrum(yy, spans = c(3,5), typ='S')
plot( spec.taper(yy, p=.5), typ='l' )
spectrum(yy, xlim=c(0,50), detrend=FALSE, taper=0.5, typ='S', main="TAPER=0.5, WITHOUT DETREND" )
spectrum(yy, xlim=c(0,50), detrend=TRUE, taper=0.5, typ='S', main="TAPER=0.5, WITH DETREND" )

multiplot( gg1, gg2, gg3, bar0, int0, cols=3)
