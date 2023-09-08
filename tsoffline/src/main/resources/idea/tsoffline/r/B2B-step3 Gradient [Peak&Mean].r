# DIALOG TIMERANGE
# DIALOG SIGNAL MEASUREMENT LVP(dp/dt).Segmentation.Signal
# DIALOG PROMPT LVP(dp/dt).Max.Code LVP(dp/dt).Min.Code
# DIALOG SIGNAL WAVEFORM LVP.Minus.AoP.Signal
# DIALOG PROMPT Output.Layer.Name

# outputs:
# - Peak Instantaneous Gradient: PEAK[LVP-AoP] --> Gpk
# - Mean Positive Gradient: _MEANP[LVP-AoP] -> Gmean

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )

seg_sig <- app$getParam("SIGNAL", "LVP(dp/dt).Segmentation.Signal" )
max_code <- app$getParam("PROMPT", "LVP(dp/dt).Max.Code" )
min_code <- app$getParam("PROMPT", "LVP(dp/dt).Min.Code" )

gradient_sig <- app$getParam("SIGNAL", "LVP.Minus.AoP.Signal" )

layer_name <- app$getParam("PROMPT", "Output.Layer.Name" )

#
# Functions
#

update_annotations_step3 <- function( layer, f ) {
	model <- J("idea.tsoffline.AppModel")
	
	canvas <- app$getCanvas()
	zeroMs <- canvas$getStartTime()
	
	n <- nrow(f)
		
	for( ii in c(1:n) ) {
	
		# Gpk
		node <- f$Gpk_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("Gpk")
			node <- model$addAnnotationWithRelativeTime(layer, event, f$Gpk_tm[ii], TRUE)
			node$addAttribute("@ref_sig", layer$getAttribute( "@gradient_sig" ) )
		}		
		node$setY( f$Gpk[ii] );

		# Gmean
		node <- f$Gmean_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("_Gmean")
			node <- model$addAnnotationWithRelativeTime(layer, event, f$Gmean_tm[ii], TRUE);
			node$addAttribute("@ref_sig", layer$getAttribute( "@gradient_sig" ) )
		}		
		node$setY( f$Gmean[ii] );


	}
	layer$setVisible( TRUE);
}

#
# Main
#

# create new markers for upper and lower extremes in each beat


init_b2b_step3 <- function(layer, gradient_sig, seg_sig, startSecs, stopSecs) { 
	layer$addAttribute( "@gradient_sig", gradient_sig )
	layer$addAttribute( "@seg_sig", seg_sig )
	
	nodes <- data$getNodesInRange( seg_sig, startSecs, stopSecs )
	n <- nodes$size()
	
	seg_start <- 0
	seg_end <- 0
	pos <- 1
	for( idx in c(0:(n-1)) ) {
		class(idx) <- "integer"
		anno <- nodes$get(idx)

		entry <- anno$getAttribute("item")
		code = entry$getCode()
		
		if( code == max_code ) {
			seg_start[pos] <- anno$getX()
		}
		
		if( code == min_code ) {
			seg_end[pos] <- anno$getX()
			pos <- pos + 1			
		}
	}
	
	length(seg_end) <- length(seg_start)
	
	# Get gradient signal	
	xydata <- gradient_sig$getDataInRange( startSecs, stopSecs )
	gradient_x <- data$X( xydata )
	gradient_y <- data$Y( xydata )

	Gpk_tm <- data$getTimeOfMax( gradient_y,gradient_x, seg_start, seg_end )
	Gpk    <- data$getMax( gradient_y, gradient_x, seg_start, seg_end )

	Gmean_tm <- seg_start
	Gmean    <- data$getPositiveMean( gradient_y, gradient_x, seg_start, seg_end )
	
	# GTmean computed, but not currently saved or used
	GTmean    <- data$getMean( gradient_y, gradient_x, seg_start, seg_end )

	s <- data.frame( Gpk_tm, Gpk, Gmean_tm, Gmean, GTmean )
	s$Gpk_node = NULL
	s$Gmean_node = NULL	 
	s$GTmean_node = NULL  # sanity check: total positive and negative	 
	 
	layer$addAttribute("@update", "update_b2b_ref_value" );
	
	update_annotations_step3( layer, s )
}

color <- gradient_sig$getDefaultColor()
color <- J("java/awt/Color")$RED
layer <- create_annotation_layer( layer_name, color, "B2B-step3.r" )
init_b2b_step3( layer, gradient_sig, seg_sig, startSecs, stopSecs )

rm( gradient_sig, seg_sig )
rm( startSecs, stopSecs )
rm( layer_name, color, max_code, min_code )

