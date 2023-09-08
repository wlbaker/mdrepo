#
# DIALOG TIMERANGE
# DIALOG SIGNAL MEASUREMENT Indicator
# DIALOG FEATURE Indicator Feature_Name
#

require(ggplot2)

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
deltaSecs <- stopSecs - startSecs
marker_sig <- app$getParam("SIGNAL", "Indicator" )
feature_name <- app$getParam("FEATURE", "Feature_Name" )

sig_name <- marker_sig$getAlias()
max_centroid_size <- 5000

update <- function( stopSecs ) {
	startSecs <- stopSecs - deltaSecs
	
	nodes <- marker_sig$getNodesInRange( startSecs, stopSecs)
	
	sz <- nodes$size()
	
	tm <- data$getXFromNodes(nodes )
	df <- data.frame(tm)
	idx <- 1
	for( f in feature_name ) {
		col_name = paste( "col", idx, sep="")
		# gui$showMessage( paste("get attributes from node feature name: ", f) )
		df[[col_name]] <- data$getAttributeFromNodes(nodes, f)
		
		df[[col_name]][which(df[[col_name]] > max_centroid_size )] <- NA		
		idx <- idx + 1
	}
	
	# gui$showMessage( "TRENDS--next!" )
	## df$moment_y <- 1000.0 * df$moment_y
	## df$moment_z <- (df$moment_x + df$moment_y/2)
	p <- ggplot(data=df )
	p <- p + ylab("")
	# colors <- c("blue","green","yellow")
	idx <- 1
	for( f in feature_name ) {
		col_name = paste( "col", idx, sep="")
		# gui$showMessage( paste("feature name: ", ff) )
		p <- p + geom_line( aes_string(x="tm",y=col_name), color="black" )
		idx <- idx + 1
	}
	## p <- p + geom_line( aes_string(x="tm",y="moment_z"), color="red" )
	p <- p + xlab( paste("SS[", startSecs, ",", stopSecs, "]", sep="")  )
	print(p)
	
}

subject <- app$getSubject()
app$createPlot( paste("Trend:", subject, sig_name) )
update( stopSecs )

