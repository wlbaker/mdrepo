# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM LVPdpdt.Source.Signal
# DIALOG SIGNAL MEASUREMENT ECG.Segmentation.Signal
# DIALOG PROMPT Layer.Name LVP(dp/dt).Max.Code LVP(dp/dt).Min.Code

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )

pressure_sig <- app$getParam("SIGNAL", "LVPdpdt.Source.Signal" )
seg_sig <- app$getParam("SIGNAL", "ECG.Segmentation.Signal" )

layer_name <- app$getParam("PROMPT", "Layer.Name" )
max_code <- app$getParam("PROMPT", "LVP(dp/dt).Max.Code" )
min_code <- app$getParam("PROMPT", "LVP(dp/dt).Min.Code" )

#
# Functions
#

update_annotations <- function( layer, source, f ) {
	model <- J("idea.tsoffline.AppModel")
	
	canvas <- app$getCanvas()
	zeroMs <- canvas$getStartTime()
	
	n <- nrow(f)
		
	for( ii in c(1:n) ) {
		node <- f$s_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode(max_code)
			event$setValue( f$p_max[ii] )
			node <- model$addAnnotationWithRelativeTime(layer, event, f$p_tm_max[ii], TRUE);
		}		
		# node$addAttribute("PEAK[LVP(dp/dt)]", D(f$p_max[ii]) );
		node$addAttribute("LVET", D(f$p_tm_min[ii] - f$p_tm_max[ii]) );

		node <- f$d_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode(min_code)		
			event$setValue( f$p_min[ii] )
			node <- model$addAnnotationWithRelativeTime(layer, event, f$p_tm_min[ii], TRUE);	
		}		
	}
	layer$setVisible( TRUE);
}

#
# Main
#

# create new markers for upper and lower extremes in each beat

find_minmax_times <- function( rwave_times, pressure, tmvals, sample_rate, startSecs, stopSecs ) {
	
	#
	# subset the pressure signal
	#
	range <- which( tmvals >= startSecs & tmvals <= stopSecs )
	pressure <- pressure[range]
	tmvals <- tmvals[range]

	#
	# subset the rwaves
	#
	rwave_times <- rwave_times[ rwave_times >= startSecs & rwave_times <= stopSecs ]

	# it's ok to use the same time for both of these.  The algorithm will figure it out
	# that we want the narrowest interval.  The Min and Max are nowhere close to the
	# endpoints

	p_tm_max <- data$getTimeOfMax( pressure, tmvals, rwave_times, rwave_times )

	# find min between MAX and next R wave	
	p_tm_min <- data$getTimeOfMin( pressure, tmvals, p_tm_max, rwave_times )
	
	
	# same range as finding the time...	
	p_max <- data$getValueAt( pressure, tmvals, p_tm_max )
	p_min <- data$getValueAt( pressure, tmvals, p_tm_min )
	
	# handle last partial beat that might have different a length of features 
	tot <- min( length( p_tm_max), length(p_max), length(p_tm_min), length(p_min) )
	length( p_tm_max ) <- tot
	length( p_max ) <- tot
	length( p_tm_min ) <- tot
	length( p_min ) <- tot

	data.frame( p_tm_max, p_max, p_tm_min, p_min )
}

init_b2b_peaks <- function(layer, pressure_sig, seg_sig, startSecs, stopSecs) { 
	layer$addAttribute( "@pressure_sig", pressure_sig )
	# layer$addAttribute( "@seg_sig", seg_sig )
	
	xydata <- seg_sig$getData( )
	rwave_times <- data$X( xydata )

	sig_name <- pressure_sig$getAlias()
	sample_rate <- pressure_sig$getSampleRate()
	
	xydata <- pressure_sig$getData( )
	tmvals <- data$X( xydata )
	pressure <- data$Y( xydata )

	s <- find_minmax_times( rwave_times, pressure, tmvals, sample_rate, startSecs, stopSecs )
	s$max_node = NULL
	s$min_node = NULL	 
	 
	layer$addAttribute("@update", "update_b2b_step2" );
	
	update_annotations( layer, sig_name, s )
}

color <- pressure_sig$getDefaultColor()
layer <- create_annotation_layer( layer_name, color, "B2B-step2part1.r" )
layer$addAttribute("@enum_by", "none" )
layer$addAttribute("@displayState", "3");
layer$addAttribute( "@maxCode", max_code )
layer$addAttribute( "@minCode", min_code )

init_b2b_peaks( layer, pressure_sig, seg_sig, startSecs, stopSecs )

rm( pressure_sig, seg_sig )
rm( startSecs, stopSecs )
rm( layer_name, color, max_code, min_code )

