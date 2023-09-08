#
# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM SignalToGraph
# DIALOG SIGNAL MEASUREMENT Beat_Segmentation
# DIALOG PROMPT Sort_By_Length[T/F]
#

require( scatterplot3d )
require( scales )

sort_by_length <- FALSE
lead_time <- -0.25
lag_time <- -0.15


startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
deltaSecs <- stopSecs - startSecs
data_sig <- app$getParam("SIGNAL", "SignalToGraph" )
r_markers <- app$getParam("SIGNAL", "Beat_Segmentation" )

s <- app$getParam("PROMPT", "Sort_By_Length[T/F]" )
if( "T" == toupper(s) ) {
	sort_by_length <- TRUE
}

#	gui$showMessage( message )

sig_name <- data_sig$getAlias()

g <- data.frame( NAME="AoP", LEAD=0.05, LAG=0.05 , stringsAsFactors=FALSE )
g <- rbind( g, list("LVP", -0.15, 0.0) )


idx = which( g$NAME == sig_name )
if( length(idx) > 0 ) {
	sig_name = g$NAME[idx]
	lead_time <- g$LEAD[idx]
	lag_time <- g$LAG[idx]
}

update <- function( stopSecs ) {
	startSecs <- stopSecs - deltaSecs
	
	xydata <- r_markers$getDataInRange( startSecs, stopSecs)
	start_times <- data$X( xydata )
	if( length(start_times) == 0 ) {
		return
	}
	end_tms <- start_times
	n_beats <- length(start_times)
	if( n_beats > 100 ) {
		decim_mult <- as.integer(length(start_times)/100)
		idx <- (c(1:n_beats) %% decim_mult) == 0
		start_times <- start_times[idx]
	}
	length( start_times ) <- length( start_times ) - 1  # the last one is an end time
	
	freq <- data_sig$getSampleRate()
	data_segs <- data$getSegments( start_times, end_tms, data_sig, lead_time, lag_time )

	# convert list elements to number arrays
	data_list <- lapply( as.list(data_segs ), as.list, simplify=TRUE )
	n_beats <- length(data_list)

	##
	## CLEANUP
	#
	# weed out the beats that are too short or too long
	#

	t <- lapply( data_list, length )
	class(t)<-"numeric"
	sel <- (t > 100 & t < 600)
	data_list <- data_list[sel]
	n_beats <- length(data_list)

	##
	## SORT
	##
	#
	# arrange the list into increasing order
	#
	data_sort <- data_list    # default
	if( sort_by_length ) {
		aopl <- 0
		idx <- 0
		for( a in data_list ) {
 			idx <- idx + 1
 			aopl[idx] <- length(a)
		}
		# write.csv(aopl, "c:/tmp/aopl.csv")
		permu <- order(aopl)
		data_sort <- data_list[permu]
	}

	z_max <-  max( simplify2array( lapply( data_sort, max ) ) )
	z_min <-  min( simplify2array( lapply( data_sort, min ) ) )

	nn <- 1.2*freq
	# fix the length of each element to be exactly 600
	data_flush <- lapply( data_sort, function(x) { 
		length(x) <- nn 
		return(x)
	} )


	step <- 1/freq
	xx <- seq( 0, (nn-1)*step, step ) + lead_time

	waterfall_sub <- paste("LL[", lead_time, ",", lag_time, "] SS[", startSecs, ",", stopSecs, "] beats:", n_beats, sep=""  ) 

	s3d <- scatterplot3d( x=lead_time, y=0, z=z_min, highlight.3d=TRUE, 
		xlim=c(lead_time,1.2), ylim=c(0,n_beats), zlim=c(z_min,z_max), angle=80,
		col.axis="blue", col.grid="lightblue", 
		xlab="Time", sub=waterfall_sub, zlab=sig_name, ylab="Beat Number",
		main=paste(sig_name, "Traces", subject ) )

	idx <- 0
	for( seg in data_flush ) {

    	idx <- idx+1
		yy <- rep( idx, length(xx) )
	
		if( idx <= n_beats ) {
			s3d$points3d(x <- xx, y <- yy, z <- seg, type='l', col=alpha('black',0.5) ) # palette()[idx])
		}
	}
	
}

subject <- app$getSubject()
app$createPlot( paste("Waterfall:", subject) )
update( stopSecs )

