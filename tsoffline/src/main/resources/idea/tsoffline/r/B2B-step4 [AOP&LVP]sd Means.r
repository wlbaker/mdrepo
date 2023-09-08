# DIALOG TIMERANGE
# DIALOG SIGNAL MEASUREMENT LVP(dp/dt).Segmentation.Signal
# DIALOG PROMPT LVP(dp/dt).Max.Code LVP(dp/dt).Min.Code
# DIALOG SIGNAL WAVEFORM AoP.Signal
# DIALOG SIGNAL WAVEFORM LVP.Signal
# DIALOG PROMPT Output.Layer.Name

# outputs:
# - AoPmean
# - AOPsm
# - AOPdm
# - LVPsm
# - LVPdm
#
# refrences
# - LVP(dp/dt) signal as ref_sig
# - aop_sig
# - lvp_sig

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )

seg_sig <- app$getParam("SIGNAL", "LVP(dp/dt).Segmentation.Signal" )
max_code <- app$getParam("PROMPT", "LVP(dp/dt).Max.Code" )
min_code <- app$getParam("PROMPT", "LVP(dp/dt).Min.Code" )

aop_sig <- app$getParam("SIGNAL", "AoP.Signal" )
lvp_sig <- app$getParam("SIGNAL", "LVP.Signal" )

layer_name <- app$getParam("PROMPT", "Output.Layer.Name" )

#
# Functions
#

update_annotations_step4 <- function( layer, f ) {
	model <- J("idea.tsoffline.AppModel")
	
	canvas <- app$getCanvas()
	zeroMs <- canvas$getStartTime()
	
	n <- nrow(f)
		
	for( ii in c(1:n) ) {
	
		node <- f$means_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("_means")
			node <- model$addAnnotationWithRelativeTime(layer, event, f$beat_tm[ii], TRUE)
			# node$addAttribute("@aop_sig", layer$getAttribute( "@aop_sig" ) )
		}		
		node$addAttribute("AOPmean", D(f$AOPmean[ii]) )
		node$addAttribute("AOPsm", D(f$AOPsm[ii]) )
		node$addAttribute("AOPdm", D(f$AOPdm[ii]) )
		node$addAttribute("LVPsm", D(f$LVPsm[ii]) )
		node$addAttribute("LVPdm", D(f$LVPdm[ii]) )
	}
	layer$setVisible( TRUE);
}

#
# Main
#

# create new markers for upper and lower extremes in each beat


init_b2b_step4 <- function(layer, aop_sig, lvp_sig, seg_sig, startSecs, stopSecs) { 
	layer$addAttribute( "@aop_sig", aop_sig )
	layer$addAttribute( "@lvp_sig", lvp_sig )
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
	
	# Get AOP signal	
	xydata <- aop_sig$getDataInRange( startSecs, stopSecs )
	aop_x <- data$X( xydata )
	aop_y <- data$Y( xydata )
	
	# Get LVP signal	
	xydata <- lvp_sig$getDataInRange( startSecs, stopSecs )
	lvp_x <- data$X( xydata )
	lvp_y <- data$Y( xydata )

	beat_tm <- seg_start
	AOPmean  <- data$getMean( aop_y, aop_x, seg_start, seg_start )
	AOPsm    <- data$getMean( aop_y, aop_x, seg_start, seg_end )
	AOPdm    <- data$getMean( aop_y, aop_x, seg_end, seg_start )
	LVPsm    <- data$getMean( lvp_y, lvp_x, seg_start, seg_end )
	LVPdm    <- data$getMean( lvp_y, lvp_x, seg_end, seg_start )

	s <- data.frame( beat_tm, AOPmean, AOPsm, AOPdm, LVPsm, LVPdm )
	s$mean_node = NULL
	 
	layer$addAttribute("@update", "update_b2b_step4" );
	
	update_annotations_step4( layer, s )
}

color <- lvp_sig$getDefaultColor()  # really only used for the button color at the top of the screen
layer <- create_annotation_layer( layer_name, color, "B2B-step4.r" )
init_b2b_step4( layer, aop_sig, lvp_sig, seg_sig, startSecs, stopSecs )

rm( aop_sig, lvp_sig, seg_sig )
rm( startSecs, stopSecs )
rm( layer, layer_name, color, max_code, min_code )

