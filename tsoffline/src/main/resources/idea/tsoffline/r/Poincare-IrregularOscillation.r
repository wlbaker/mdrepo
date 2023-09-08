#
# DIALOG TIMERANGE
# DIALOG SIGNAL
# DIALOG PROMPT Y_LAG
#

require( ggplot2 )

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
data_sig <- app$getParam("SIGNAL", "selection" )
y_lag <- app$getParam("PROMPT", "Y_LAG" )

class(y_lag) <- "numeric"

sig_name <- data_sig$getAlias()

xydata <- data_sig$getDataInRange( startSecs, stopSecs)
y <- data$Y( xydata )
n <- length(y)

yy <- y[(y_lag+1):n] - y[1:(n-y_lag)]
n <- length(yy)

xx <- yy[ 2:n ]
length(yy) <- length(xx)


subject <- app$getSubject()
title <- paste("Poincare:", subject)
app$createPlot( title )


sub_title <- paste("Signal:", sig_name, " lag:", y_lag, " time: [", startSecs, ",", stopSecs, "]", sep="" )

# plot( x=xx, y=yy, 
#	xlab=paste(sig_name, "[x]", sep=""), 
#	ylab=paste(sig_name, "[x+",y_lag,"]", sep=""), 
#	main=paste( title ), 
#	sub=sub_title	)

df <- data.frame( xx, yy)

p <- ggplot( df, aes(x=xx,y=yy) )
p <- p + geom_jitter(aes(x = xx, y=yy), position = position_jitter(width = .00025, height=0.00025), alpha = 0.5) 
print(p)

