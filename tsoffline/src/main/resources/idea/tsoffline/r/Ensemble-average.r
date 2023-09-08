# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM SignalToGraph
# DIALOG SIGNAL MEASUREMENT Beat_Segmentation
# DIALOG PROMPT Align_First_Pt[T/F]
#
# option color-scale-by-length
# option no-ecg marker
# option no-mean-in-red
#

require( scales )

fiducial_lead <- -0.15
fiducial_lag <- -0.15
plot_range <- c(30,120)
align_first_pt <- FALSE

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
deltaSecs <- stopSecs - startSecs
data_sig <- app$getParam("SIGNAL", "SignalToGraph" )
r_markers <- app$getParam("SIGNAL", "Beat_Segmentation" )
s <- app$getParam("PROMPT", "Align_First_Pt[T/F]" )
if( "T" == toupper(s) ) {
	align_first_pt <- TRUE
}

sig_name <- data_sig$getAlias()

g <- data.frame( NAME="AoP", LEAD=0.05, LAG=0.05 , RANGE_LOW=0, RANGE_HIGH=150, stringsAsFactors=FALSE )
g <- rbind( g, list("ECG", -0.20, -0.20, 0.2, 1.4 ) )
g <- rbind( g, list("PAP", -0.05, -0.05, 0, 40 ) )
g <- rbind( g, list("RVP", -0.15, -0.15, 0, 40 ) )
g <- rbind( g, list("Fluid", -0.15, -0.15, 0, 40 ) )
g <- rbind( g, list("Resp", -0.15, -0.15, -50, 10 ) )


idx = which( g$NAME == sig_name )
if( length(idx) > 0 ) {
	fiducial_lead <- g$LEAD[idx]
	fiducial_lag <- g$LAG[idx]
	
	plot_range <- c( g$RANGE_LOW[idx], g$RANGE_HIGH[idx] )
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
		decim_mult <- as.integer(length(start_times)/50)
		idx <- (c(1:n_beats) %% decim_mult) == 0
		start_times <- start_times[idx]
	}
	length( start_times ) <- length( start_times ) - 1  # the last one is an end time
	
	data_segs <- data$getSegments( start_times, end_tms, data_sig, fiducial_lead, fiducial_lag )

	# convert list elements to number arrays
	seg_list <- lapply( as.list(data_segs ), as.list, simplify=TRUE )
	n_beats <- length(seg_list)

	freq <- data_sig$getSampleRate()
	nn <- 1.2*freq

	# fix the length of each element to be exactly 600
	seg_flush <- lapply( seg_list, function(x) { 
		length(x) <- nn 
		return(x)
		} )

	xx <- seq( 0, (nn-1)*0.002, 0.002 )

	mm <- NA
	tot <- rep(0,nn)
	one <- rep(1,nn)
	idx <- 0

	plot( x=0, main=paste( subject ), type='l', 
		xlim=c(0,0.6), ylim=plot_range, 
		xlab=paste( "Ensemble Average:", sig_name), 
		sub=paste("LL[", fiducial_lead, ",", fiducial_lag, "] SS[", startSecs, ",", stopSecs, "] beats:", n_beats, sep=""  ), 
		ylab="Pressure" )

	first_pt_mean <- 0
	idx <- 0
	for( beat in seg_flush ) {
		zero <- beat[1]
		if( is.na( zero ) ) {
			# skip
		} else {
			first_pt_mean <- first_pt_mean + zero
			idx <- idx + 1
		}
	}
	first_pt_mean <- first_pt_mean / idx
	
	idx <- 1
	ramp <- grey_pal(0.8, 0.1)(length(start_times))
	for( beat in seg_flush ) {
		zero <- beat[1]
	
		r <- !is.na(beat)
		if( is.na( zero ) ) {
			# skip
		} else {
			if( is.na(mm) ) {
				mm[r] <- beat[ r ]
			} else {
				mm[r] <- mm[r] + beat[ r ]
			}
			tot[r] <- tot[r] + one[ r ]
			color <- "gray"
			if( sum(r) < 300 ) {
				color <- "green"
			}
			yy <- beat
			if( align_first_pt ) {
				yy <- beat - zero + first_pt_mean
			}
			lines(x <- xx, y <- yy, col=ramp[idx])
			idx <- idx + 1
		} 
	}
	
	# Show the mean in red
	lines(x <- xx, y <- mm/ tot, col='red', lwd=3) 
	abline( v=-fiducial_lead, col='blue' )
}

subject <- app$getSubject()
app$createPlot( paste("Ensemble Average", subject) )
update( stopSecs )

