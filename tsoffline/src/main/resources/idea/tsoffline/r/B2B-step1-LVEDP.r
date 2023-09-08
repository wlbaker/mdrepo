# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM LVP.Source.Signal
# DIALOG SIGNAL MEASUREMENT ECG.Segmentation.Signal
# DIALOG PROMPT LVEDP.Name

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )

pressure_sig <- app$getParam("SIGNAL", "LVP.Source.Signal" )
seg_sig <- app$getParam("SIGNAL", "ECG.Segmentation.Signal" )

layer_name <- app$getParam("PROMPT", "LVEDP.Name" )

#
# Functions
#

update_annotations_step1 <- function( layer, source, f ) {
	model <- J("idea.tsoffline.AppModel")
	
	canvas <- app$getCanvas()
	zeroMs <- canvas$getStartTime()
	
	n <- nrow(f)
		
	for( ii in c(1:n) ) {
		node <- f$lvep_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("LVEDP")
			node <- model$addAnnotationWithRelativeTime(layer, event, f$tm_lvedp[ii], TRUE);
		}		
		node$setY( f$p_lvedp[ii] );

	}
	layer$setVisible( TRUE);
}

#
# Main
#

# create new markers for upper and lower extremes in each beat

init_b2b_lvedv <- function(layer, pressure_sig, seg_sig, startSecs, stopSecs) {
 
	rwave_times <- seg_sig$getTimesInRange( startSecs, stopSecs )
	
	#
	# subset the rwaves
	#
	tm_lvedp <- rwave_times - 0.020
	
	# same range as finding the time...	
	p_lvedp <- pressure_sig$getValueAt( tm_lvedp )
	
	s <- data.frame( tm_lvedp, p_lvedp )
	s$lvep_node <- NULL

	layer$addAttribute( "@pressure_sig", pressure_sig )
	layer$addAttribute( "@seg_sig", seg_sig )
	
	sig_name <- pressure_sig$getAlias()
	
	layer$addAttribute("@update", "update_b2b_ref_value" );	
	update_annotations_step1( layer, sig_name, s )
}

color <- pressure_sig$getDefaultColor()
layer <- create_annotation_layer( layer_name, color, "B2B-step1-LVEDP.r" )
layer$addAttribute("@enum_by", "none" )
layer$addAttribute("@displayState", "3");
init_b2b_lvedv( layer, pressure_sig, seg_sig, startSecs, stopSecs )

rm( pressure_sig, seg_sig )
rm( startSecs, stopSecs )
rm( layer_name, color, max_code, min_code )

