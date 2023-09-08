# DIALOG TIMERANGE
# DIALOG SIGNAL ANNOTATION beat_segmentation
# DIALOG SIGNAL WAVEFORM ART.Signal

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )

pressure_sig <- app$getParam("SIGNAL", "ART.Signal" )
r_markers <- app$getParam("SIGNAL", "beat_segmentation" )
dest_layer_name <- "PSeg"

#
# Functions
#

calculate_dpdt <- function( pressure, sample_rate ) {
	n <- length(pressure)
	dpdt <- (pressure[2:length(pressure)] - pressure[ 1:(length(pressure)-1) ])
	dpdt <- dpdt * sample_rate
	dpdt
}

create_layer <- function( dest_layer_name ) {
	color <- J("java/awt/Color")$RED
	
	# model <- J("idea.tsoffline.AppModel")
	canvas <- app$getCanvas()
	
	layer <- canvas$getAnnotationLayer( dest_layer_name )
	if( is.null( layer ) ) { 
		layer <- canvas$addAnnotationLayer( dest_layer_name, color, "BEAT-STATS-SINGLE.r" )
	}
	
	layer
}

update_annotations <- function( layer, source, f ) {
	model <- J("idea.tsoffline.AppModel")
	
	canvas <- app$getCanvas()
	zeroMs <- canvas$getStartTime()
	
	n <- length(f$systol_start)
	# n <- max( 20, f$systol_start )
	for( ii in c(1:n) ) {
		node <- f$s_node[ii]
		# gui$showMessage( paste("update_annotations", ii, length(node)) )
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("S")
			node <- model$addAnnotationWithRelativeTime(layer, event, f$systol_start[ii], TRUE);
		}		
		node$addAttribute("sys_mean", D(f$systol_mean[ii]) );
		node$addAttribute("aop_mean", D(f$aop_mean[ii]) );
		node$addAttribute("systolic", D(f$systolic[ii]) );
		node$addAttribute("pulse_pressure", D(f$pulse_pressure[ii]) );

		node <- f$d_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("D")		
			node <- model$addAnnotationWithRelativeTime(layer, event, f$diastol_start[ii], TRUE);	
		}		
		node$addAttribute("dia_mean", D(f$diastol_mean[ii]) );
		node$addAttribute("diastolic", D(f$diastolic[ii]) );
	}
	layer$setVisible( TRUE);
}

#
# Main
#

# create subsets of source data corresponding to time selection

find_markers <- function( rwave_times, pressure, tmvals, sample_rate, startSecs, stopSecs ) {
	r <- which( tmvals >= startSecs & tmvals <= stopSecs )
	pressure <- pressure[r]
	tmvals <- tmvals[r]

	# start_beat <- which(rwave_times >= startSecs)[1]
	rwave_times <- rwave_times[ rwave_times >= startSecs & rwave_times <= stopSecs ]

	# smooth pressure and create dpdt
	n <- length(pressure)
	pressure <- ( pressure[1:(n-4)] + pressure[ 2:(n-3)] + pressure[ 3:(n-2)] + pressure[ 2:(n-1)] + pressure[ 1:n ])/5
	dpdt <- calculate_dpdt( pressure, sample_rate )
	systol_start <- data$getDiastolTime( pressure, tmvals, rwave_times )

	# it's ok to use the same time for both of these.  The algorithm will figure it out
	# that we want the narrowest interval.  The Min and Max are nowhere close to the
	# endpoints

	dpdt_tm_max <- data$getTimeOfMax( dpdt, tmvals, systol_start, systol_start )
	dpdt_tm_min <- data$getTimeOfMin( dpdt, tmvals, systol_start, systol_start )
	dpdt_max <- data$getMax( dpdt, tmvals, systol_start, systol_start )
	dpdt_min <- data$getMin( dpdt, tmvals, systol_start, systol_start )


	# here we need shorter intervals since the diastole is close to the end of the
	# interval
	diastol_start <- dpdt_tm_min
	
	# truncate systol_start ... may be one longer than diastol_start
	length( systol_start ) <- length(diastol_start )
	# gui$showMessage( paste("data.frame", length(systol_start), length(diastol_start), length(dpdt_tm_max), length(dpdt_max), length(dpdt_tm_min), length(dpdt_min)) )
	data.frame( systol_start, diastol_start, dpdt_tm_max, dpdt_max, dpdt_tm_min, dpdt_min )
}

compute_stats <- function( pressure, tmvals, sample_rate, systol_start, diastol_start ) {
	systol_mean <- data$getMean( pressure, tmvals, systol_start, diastol_start )
	diastol_mean <- data$getMean( pressure, tmvals, diastol_start, systol_start )
	aop_mean <- data$getMean( pressure, tmvals, systol_start, systol_start )

	systolic <- data$getMax( pressure, tmvals, systol_start, diastol_start )
	diastolic <- data$getMin( pressure, tmvals, diastol_start, systol_start )
	pulse_pressure <- systolic - diastolic

	n <- length(systol_start)
	rri <- systol_start[2:n]-systol_start[1:(n-1)]
	length(rri) <- n  # add a NA at the end so all the vectors are the same length

	# beat_no <- c(1:n) + start_beat - 1

	# truncate rows as necessary
	tot = length(diastolic)
	length(systol_start) = tot
	length(systolic) = tot
	length(diastol_start) = tot
	length(diastolic) = tot
	length(pulse_pressure) = tot
	length(aop_mean) = tot
	length(systol_mean) = tot
	length(diastol_mean) = tot

	# gui$showMessage( paste("data.frame2", length(systol_start), length(systolic), length(diastol_start), length(diastolic), length(pulse_pressure), length(aop_mean), length(systol_mean), length(diastol_mean) ) )
	data.frame( systol_start, systolic, diastol_start, diastolic, pulse_pressure, aop_mean, systol_mean, diastol_mean )
}

init_beatstats <- function(layer, pressure_sig, startSecs, stopSecs) { 
	layer$addAttribute( "@pressure_sig", pressure_sig )
	
	if( is.null( pressure_sig ) ) {
		gui$showMessage("Could not find signal.")
		stop("Could not find signal")
	}

	if( is.null( r_markers ) ) {
		gui$showMessage("Could not find beat segmentation information.")
		stop("Could not find beat segmentation")
	}

	xydata <- r_markers$getData( )
	rwave_times <- data$X( xydata )


	sig_name <- pressure_sig$getAlias()
	sample_rate <- pressure_sig$getSampleRate()
	xydata <- pressure_sig$getData( )
	tmvals <- data$X( xydata )
	pressure <- data$Y( xydata )

	s <- find_markers( rwave_times, pressure, tmvals, sample_rate, startSecs, stopSecs )
	f <- compute_stats( pressure, tmvals, sample_rate, s$systol_start, s$diastol_start )
	f$s_node = NULL
	f$d_node = NULL
	 
	layer$addAttribute("@script", "BEAT-STATS-SINGLE.r" );
	layer$addAttribute("@update", "update_beatstats" );
	
	update_annotations( layer, sig_name, f )
}

update_beatstats <- function(layer, xpos) { 
	if( is.null( layer ) ) {
		layer <- app$getParam("UPDATE", "layer" )
	}
	
	pressure_sig <- layer$getAttribute("@pressure_sig")
	
	if( is.null( pressure_sig ) ) {
		gui$showMessage("Could not find signal.")
		stop("Could not find signal")
	}

	anno_sig <- layer$getAttribute("sig")

	sample_rate <- pressure_sig$getSampleRate()
	sig_name <- pressure_sig$getAlias()
	xydata <- pressure_sig$getData( )
	tmvals <- data$X( xydata )
	pressure <- data$Y( xydata )

	gui$showMessage( paste("update_beatstats", startSecs, stopSecs) )
	# f <- find_markers( rwave_times, pressure, tmvals, sample_rate, startSecs, stopSecs )
	
	nodes <- data$getNodesInRange( anno_sig, xpos - 5, xpos + 5 )
	
	## FIXME: create systol_start and diastol_start arrays
	
	f <- compute_stats( pressure, tmvals, sample_rate, systol_start, diastol_start )
	update_annotations( layer, sig_name, f )
}

layer <- create_layer( dest_layer_name )
init_beatstats( layer, pressure_sig, startSecs, stopSecs )

rm( pressure_sig )
rm( dest_layer_name )

