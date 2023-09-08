# DIALOG TIMERANGE
# DIALOG SIGNAL
#
# option color-scale-by-length
# option no-ecg marker
# option no-mean-in-red
#
# http://stackoverflow.com/questions/7714677/r-scatterplot-with-too-many-points
#

require( scatterplot3d )
require( colorRamps )

fiducial_lead <- -0.15
fiducial_lag <- -0.15
plot_range <- c(-50,150)

# 010617 WLB --> TBD: I do not understand this feature.  Explain in comments before re-enabling.
resp_offset <- 0

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
data_sig <- app$getParam("SIGNAL", "selection" )

if( is.null( data_sig ) ) {
	data_sig <- data$getSignal( NULL, NULL, "LVP" )
}

if( is.null( data_sig ) ) {
	message <-paste("Could not find data signal:", sig_name)
	gui$showMessage( message )
	stop(message)
}

sig_name <- data_sig$getAlias()

g <- data.frame( NAME="AoP", LEAD=0.05, LAG=0.05 , RANGE_LOW=0, RANGE_HIGH=150, stringsAsFactors=FALSE )
g <- rbind( g, list("ECG", -0.20, -0.20, -3, 0.5 ) )
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

r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation")
if( is.null( r_markers ) ) {
	r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation: PT1")
}
if( is.null( r_markers ) ) {
	gui$showMessage("Could not find ECG Segmentation information.")
	stop("Could not find ECG Segmentation")
}

xydata <- r_markers$getDataInRange( startSecs, stopSecs)
times <- data$X( xydata )
data_segs <- data$getSegments( times, data_sig, fiducial_lead, fiducial_lag )

resp_sig <- data$getSignal( NULL, NULL, "Resp")
if( is.null( resp_sig ) ) {
	gui$showMessage("Could not find respiratory information.")
	ramp <- "gray"
} else {
	resp_segs <- data$getSegments( times, resp_sig, fiducial_lead, fiducial_lag )
	resp_list <- lapply( as.list(resp_segs ), as.list, simplify=TRUE )
	resp_max <- max(as.numeric( lapply( resp_list, max ) ))
	resp_min <- min(as.numeric( lapply( resp_list, min ) ))
	resp_range <- resp_max - resp_min
	ramp <- blue2green(100)
	ramp <- paste( ramp, "33", sep="" )  # concatenate an alpha
}


# convert list elements to number arrays
seg_list <- lapply( as.list(data_segs ), as.list, simplify=TRUE )

n_beats <- length(seg_list)

# fix the length of each element to be exactly 600
seg_flush <- lapply( seg_list, function(x) { 
	length(x) <- 600 
	return(x)
	} )


subject <- app$getSubject()
app$createPlot( paste("Ensemble Average", subject) )

xx <- seq( 0, 599*0.002, 0.002 )

# save.image( "c:/tmp/im1.RData" )

mm <- NA
tot <- rep(0,600)
one <- rep(1,600)
idx <- 0

plot( x=0, main=paste( subject ), type='l', 
	xlim=c(0,0.6), ylim=plot_range, 
	xlab=paste( "Ensemble Average:", sig_name), 
	sub=paste("roff: ", resp_offset, " lead:", fiducial_lead, "lag:", fiducial_lag, "start:", startSecs, "end:", stopSecs, "beats:", n_beats  ), 
	ylab="Pressure" )

resp_idx <- 0
for( beat in seg_flush ) {
	zero <- beat[1]
	
	# skip beats before our offset
	resp_idx <- resp_idx + 1
	if( resp_idx <= resp_offset ) {
		next
	}		
	
	# plot-0 four lines to get the color
	resp_y <- resp_list[[ resp_idx - resp_offset ]] - resp_min
	col_idx <- as.integer( resp_y * 99 / resp_range) + 1
	col_b2g <- ramp[col_idx]
	
	r <- !is.na(beat)
	if( is.na( zero ) ) {
		# skip
	} else {
		if( is.na(mm) ) {
			mm[r] <- beat[ r ]
		} else {
			mm[r] <- mm[r] + beat[ r ]
		}
		if( sum(r) < 100 ) {
			color <- "green"
		} else {
			
			tot[r] <- tot[r] + one[ r ]
			idx <- idx + 1
			# lines(x <- xx, y <- beat, col="gray", pch=20)
			lines(x <- xx, y <- beat, col=col_b2g, pch=20)
		}
	} 
}


app$createPlot( paste("Ensemble Average - Mean", subject) )

ramp <- blue2green(100)
plot( x=0, main=paste( subject ), type='l', 
	xlim=c(0,0.6), ylim=c(-20,20), 
	xlab=paste( "Ensemble Average - Mean:", sig_name), 
	sub=paste("roff: ", resp_offset, " lead:", fiducial_lead, "lag:", fiducial_lag, "start:", startSecs, "end:", stopSecs, "beats:", n_beats  ), 
	ylab="Pressure" )

ea_mean <- mm/ tot

resp_idx <- 0
for( beat in seg_flush ) {
	zero <- beat[1]

	# skip beats before our offset
	resp_idx <- resp_idx + 1
	if( resp_idx <= resp_offset ) {
		next
	}		
	
	# plot-1 four lines to get the color
	resp_y <- resp_list[[ resp_idx - resp_offset ]] - resp_min
	col_idx <- as.integer( resp_y * 99 / resp_range) + 1
	col_b2g <- ramp[col_idx]
	
	r <- !is.na(beat)
	if( is.na( zero ) ) {
		# skip
	} else {
		if( sum(r) > 100 ) {
			idx <- idx + 1
			delta_y <- beat - ea_mean
			points(x <- xx, y <- delta_y, col=col_b2g, pch='.')

			systol <- max(beat, na.rm=TRUE)
			x_sys <- which(beat==systol)
			# points( x=xx[x_sys], y=rep(systol, length(x_sys) ), col='blue', pch='.' )
			
			# points( x=xx[x_sys], y=delta_y[x_sys], col='blue', pch='.' )

		}
	} 
}

# Show the mean in red
# points(x <- xx, y <- mm/ tot, col='red', pch=20) 
# abline( v=-fiducial_lead, col='blue' )
