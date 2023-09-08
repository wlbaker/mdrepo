#
# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM X-Axis 
# DIALOG SIGNAL WAVEFORM Y-Axis 
# DIALOG PROMPT PHASE_SHIFT
#

require( ggplot2 )

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
x_sig <- app$getParam("SIGNAL", "X-Axis" )
y_sig <- app$getParam("SIGNAL", "Y-Axis" )
y_lag <- app$getParam("PROMPT", "PHASE_SHIFT" )

class(y_lag) <- "numeric"

sig_name <- x_sig$getAlias()

xydata <- x_sig$getDataInRange( startSecs, stopSecs)
xx <- data$Y( xydata )
xydata <- y_sig$getDataInRange( startSecs, stopSecs)
yy <- data$Y( xydata )
length(yy) <- length(xx)


subject <- app$getSubject()
title <- paste("Coherence:", subject)
app$createPlot( title )


sub_title <- paste("Signal:", sig_name, " lag:", y_lag, " time: [", startSecs, ",", stopSecs, "]", sep="" )

# plot( x=xx, y=yy, 
#	xlab=paste(sig_name, "[x]", sep=""), 
#	ylab=paste(sig_name, "[x+",y_lag,"]", sep=""), 
#	main=paste( title ), 
#	sub=sub_title	)

df <- data.frame( xx, yy)

p <- ggplot( df, aes(x=xx,y=yy) )
p <- p + xlab(x_sig$getAlias())
p <- p + ylab(y_sig$getAlias())
p <- p + geom_path() 
print(p)

