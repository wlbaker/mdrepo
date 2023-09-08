# DIALOG TIMERANGE
# DIALOG SIGNAL MEASUREMENT LVP(dp/dt).Segmentation.Signal
# DIALOG PROMPT LVP(dp/dt).Max.Code LVP(dp/dt).Min.Code
# DIALOG SIGNAL WAVEFORM LtVel.Signal
# DIALOG SIGNAL WAVEFORM Fluid.Signal
# DIALOG PROMPT Output.Layer.Name

# outputs:
# - LtVmean
# - Fpk - V-wave
#
# inputs:
# - LVP(dp/dt) signal as ref_sig
# - ltv_sig
# - fluid_sig

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )

seg_sig <- app$getParam("SIGNAL", "LVP(dp/dt).Segmentation.Signal" )
max_code <- app$getParam("PROMPT", "LVP(dp/dt).Max.Code" )
min_code <- app$getParam("PROMPT", "LVP(dp/dt).Min.Code" )

ltv_sig <- app$getParam("SIGNAL", "LtVel.Signal" )
fluid_sig <- app$getParam("SIGNAL", "Fluid.Signal" )

layer_name <- app$getParam("PROMPT", "Output.Layer.Name" )

#
# Functions
#

update_annotations_step5 <- function( layer, f ) {
	model <- J("idea.tsoffline.AppModel")
	
	canvas <- app$getCanvas()
	zeroMs <- canvas$getStartTime()
	
	n <- nrow(f)
		
	for( ii in c(1:n) ) {
	
		node <- f$ltv_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("_LTVmean")
			node <- model$addAnnotationWithRelativeTime(layer, event, f$beat_tm[ii], TRUE)
		}		
		node$setY( f$LtVmean[ii] )
		node$addAttribute("_LtVzero", D(f$LtVzero[ii]) )
		
		node <- f$fpk_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("V")
			node <- model$addAnnotationWithRelativeTime(layer, event, f$Fpk_tm[ii], TRUE)
		}		
		node$setY( f$Fpk[ii] )
		
		node <- f$fltvpeak_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("PkLVel")
			node <- model$addAnnotationWithRelativeTime(layer, event, f$LtVPeak_tm[ii], TRUE)
		}		
		node$setY( f$LtVPeak[ii] )
		
		node <- f$crossing_node[ii]
		if( is.null(node) ) {
			event <- .jnew( "idea.ts.TsoAnnotationEntryType" )
			event$setCode("X")
			node <- model$addAnnotationWithRelativeTime(layer, event, f$LtVcrossing_tm[ii], TRUE)
		}		
		node$setY( 1 )
	}
	layer$setVisible( TRUE);
}

#
# Main
#

# create new markers for upper and lower extremes in each beat


init_b2b_step5 <- function(layer, ltv_sig, fluid_sig, seg_sig, startSecs, stopSecs) { 
	layer$addAttribute( "@ltv_sig", ltv_sig )
	layer$addAttribute( "@fluid_sig", fluid_sig )
	layer$addAttribute( "@seg_sig", seg_sig )
	
	# gui$showMessage("getting nodes in seg signal.")
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
	
	# Get fluid signal	
	xydata <- fluid_sig$getDataInRange( startSecs, stopSecs )
	fluid_x <- data$X( xydata )
	fluid_y <- data$Y( xydata )
	
	# Get LVP signal	
	xydata <- ltv_sig$getDataInRange( startSecs, stopSecs )
	ltv_x <- data$X( xydata )
	ltv_y <- data$Y( xydata )

	beat_tm  <- seg_start
	LtVzero  <- data$getValueAt( ltv_y, ltv_x, seg_start )
	
	# **** Find peak of LtV
	LtVPeak_tm   <- data$getTimeOfMax( ltv_y, ltv_x, seg_start, seg_end )
	LtVPeak      <- data$getValueAt( ltv_y, ltv_x, LtVPeak_tm ) - LtVzero

	# **** Find zero crossing: by starting at the peak, we improve handling of a noisy signal
	LtVcrossing_tm   <- data$getTimeOfCrossing( ltv_y, ltv_x, LtVPeak_tm, seg_end, LtVzero )

	LtVmean  <- data$getMean( ltv_y, ltv_x, seg_start, LtVcrossing_tm ) - LtVzero
	
	# **** Find peak of Fluid, ADJUST for delay in V'wave: default 100ms windo.
	Fpk_tm   <- data$getTimeOfMax( fluid_y, fluid_x, seg_end + 0.100, seg_end + 0.200 )
	Fpk      <- data$getValueAt( fluid_y, fluid_x, Fpk_tm )

	n <- length(beat_tm) - 1
	length(beat_tm) <- n
	length(LtVcrossing_tm) <- n
	length(LtVPeak_tm) <- n
	length(LtVPeak) <- n
	length(LtVzero) <- n
	length(LtVmean) <- n
	length(Fpk_tm) <- n
	length(Fpk) <- n
	
	s <- data.frame( beat_tm, LtVzero, LtVmean, Fpk_tm, Fpk, LtVPeak_tm, LtVPeak, LtVcrossing_tm )
	s$fpk_node = NULL
	s$ltv_node = NULL
	s$ltvpeak_node = NULL
	s$crossing_node = NULL
	 
	layer$addAttribute("@update", "update_b2b_step5" );
	
	update_annotations_step5( layer, s )
}

color <- fluid_sig$getDefaultColor()  # really only used for the button color at the top of the screen
layer <- create_annotation_layer( layer_name, color, "B2B-step5.r" )
init_b2b_step5( layer, ltv_sig, fluid_sig, seg_sig, startSecs, stopSecs )

rm( ltv_sig, fluid_sig, seg_sig )
rm( startSecs, stopSecs )
rm( layer, layer_name, color, max_code, min_code )

