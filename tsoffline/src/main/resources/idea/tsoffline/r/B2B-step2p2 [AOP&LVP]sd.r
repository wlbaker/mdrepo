# DIALOG TIMERANGE
# DIALOG SIGNAL MEASUREMENT LVP(dp/dt).Segmentation.Signal
# DIALOG PROMPT LVP(dp/dt).Max.Code LVP(dp/dt).Min.Code
# DIALOG SIGNAL WAVEFORM AoP.Signal
# DIALOG SIGNAL WAVEFORM LVP.Signal
# DIALOG PROMPT Output.Layer.Name

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )

aop_sig <- app$getParam("SIGNAL", "AoP.Signal" )
lvp_sig <- app$getParam("SIGNAL", "LVP.Signal" )
seg_sig <- app$getParam("SIGNAL", "LVP(dp/dt).Segmentation.Signal" )

layer_name <- app$getParam("PROMPT", "Output.Layer.Name" )
color <- J("java/awt/Color")$RED
max_code <- app$getParam("PROMPT", "LVP(dp/dt).Max.Code" )
min_code <- app$getParam("PROMPT", "LVP(dp/dt).Min.Code" )

# outputs:
# - AoPd
# - AoPs
# - LVPs
# - Peak to Peak Gradient: _P2P[LVPs,AoPs] -->  _Pk-Pk

#
# Functions
#

update_annotations_step2part2 <- function( layer, f ) {
	model <- J("idea.tsoffline.AppModel")
	
	canvas <- app$getCanvas()
	zeroMs <- canvas$getStartTime()
	
	n <- nrow(f)
		
	for( ii in c(1:n) ) {
	
		# AOPd
		node <- f$AOPd_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("AoPd")
			node <- model$addAnnotationWithRelativeTime(layer, event, f$AoPd_tm[ii], TRUE)
			node$addAttribute("@ref_sig", layer$getAttribute( "@aop_sig" ) )
		}		
		node$setY( f$AoPd[ii] );

		# AOPs
		node <- f$AOPs_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("AoPs")
			node <- model$addAnnotationWithRelativeTime(layer, event, f$AoPs_tm[ii], TRUE);
			node$addAttribute("@ref_sig", layer$getAttribute( "@aop_sig" ) )
		}		
		node$setY( f$AoPs[ii] );

		# LVPs
		node <- f$LVPs_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("LVPs")		
			node <- model$addAnnotationWithRelativeTime(layer, event, f$LVPs_tm[ii], TRUE);	
			node$addAttribute("@ref_sig", layer$getAttribute( "@lvp_sig" ) )
		}		
		node$setY( f$LVPs[ii] );
		node$addAttribute( "Pk-Pk", D(f$LVPs[ii] - f$AoPs[ii]) );
		
	}
	layer$setVisible( TRUE);
}

#
# Main
#

# create new markers for upper and lower extremes in each beat


init_b2b_step2part2 <- function(layer, lvp_sig, aop_sig, seg_sig, startSecs, stopSecs) { 
	layer$addAttribute( "@lvp_sig", lvp_sig )
	layer$addAttribute( "@aop_sig", aop_sig )
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
	
	AoPd_tm <- seg_start
	# n <- length(seg_start)
	
	xydata <- aop_sig$getDataInRange( startSecs, stopSecs )
	aop_x <- data$X( xydata )
	aop_y <- data$Y( xydata )
	# same for LVPs	
	xydata <- lvp_sig$getDataInRange( startSecs, stopSecs )
	lvp_x <- data$X( xydata )
	lvp_y <- data$Y( xydata )

	#
	# seg_start: array of segment start times
	# seg_end: corresponding array of segment end times
	# 
	AoPd    <- data$getValueAt( aop_y, aop_x, seg_start )
	AoPs_tm <- data$getTimeOfMax( aop_y, aop_x, seg_start, seg_end )
	AoPs    <- data$getMax( aop_y, aop_x, seg_start, seg_end )

	LVPs_tm <- data$getTimeOfMax( lvp_y, lvp_x, seg_start, seg_end )
	LVPs    <- data$getMax( lvp_y, lvp_x, seg_start, seg_end )
	
	# handle last partial beat that might have different a length of features 
	tot <- min( length( AoPs_tm), length(AoPs), length(LVPs_tm), length(LVPs) )
	length( AoPs_tm ) <- tot
	length( AoPs ) <- tot
	length( LVPs_tm ) <- tot
	length( LVPs ) <- tot

	s <- data.frame( LVPs_tm, LVPs, AoPs_tm, AoPs, AoPd_tm, AoPd )
	s$AOPd_node = NULL
	s$AOPs_node = NULL
	s$LVPs_node = NULL	 
	 
	layer$addAttribute("@update", "update_b2b_step2p2" );
	
	update_annotations_step2part2( layer, s )
}

layer <- create_annotation_layer( layer_name, color, "B2B-step2part2.r" )
layer$addAttribute("@displayState", "3");
init_b2b_step2part2( layer, lvp_sig, aop_sig, seg_sig, startSecs, stopSecs )

rm( aop_sig, seg_sig )
rm( startSecs, stopSecs )
rm( layer_name, color, max_code, min_code )

