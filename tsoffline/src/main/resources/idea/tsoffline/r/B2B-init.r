# Beat 2 Beat analysis
#
# file for common functions
#

update_b2b_gmean <- function(layer, prev, node, next_node ) { 
	gradient_sig = layer$getAttribute( "@gradient_sig" )
	seg_sig = layer$getAttribute( "@seg_sig" )
	maxCode = layer$getAttribute( "@maxCode" )
	minCode = layer$getAttribute( "@minCode" )
	
	if( is.null(seg_sig) || is.null(gradient_sig) ) {
		gui$showMessage( "update_b2b_gmean INTERNAL ERROR: could not find required sig")
	}
	
	# gui$showMessage( paste("update_b2b_gmean: checking max/min codes" ) )
	if( is.null( maxCode ) || (length(maxCode) == 0) ) {
		maxCode = "+dP/dt"
	}
	if( is.null( minCode ) || (length(minCode) == 0) ) {
		minCode = "-dP/dt"
	}
		
	Dplus  = seg_sig$getNodeBeforeOrEqual( node$getX() );
	if( is.null( Dplus ) || (length(Dplus) == 0 ) ) {
		gui$showMessage( "update_b2b_gmean WARNING: no previous Dplus")
		node$setY(-9999.0 )
		return()
	}
	
	t <- Dplus$getAttribute("txt")
	if( is.null(t) || (length(t) == 0 ) ) {
		gui$showMessage( paste("update_b2b_gmean WARNING: no text?", Dplus$toString()) )
		Dplus$dump()
		# ERROR: wrong layer?
		return()
	}
	
	if( Dplus$getAttribute("txt") == minCode ) {
		Dplus = seg_sig$getNodeAfter( Dplus$getX() );
	}
	if( Dplus$getAttribute("txt") == maxCode ) {
		# looks good!
	} else {
		gui$showMessage( "update_b2b_gmean WARNING: unexpected node not maxCode")
		node$setY(-9999.0 )
		return()
	}
	Dminus = seg_sig$getNodeAfter( Dplus$getX() );
	if( !is.null(Dminus) && (Dminus$getAttribute("txt") == minCode) ) {
		# looks good!
	} else {
		gui$showMessage( "update_b2b_gmean WARNING: unexpected node not minCode")
		node$setY(-9999.0 )
		return()
	}
	
	seg_start <- Dplus$getX()
	seg_end <- Dminus$getX()
	
	# gradient sig
	xydata <- gradient_sig$getDataInRange( seg_start, seg_end )
	gradient_x <- data$X( xydata )
	gradient_y <- data$Y( xydata )
	
	gmean    <- data$getPositiveMean( gradient_y, gradient_x, seg_start, seg_end )
	node$setY( gmean )
}

update_b2b_ref_value <- function(layer, prev_node, node, next_node ) { 
	
	if( is.null(node) ) {
		cat( "zzz got null node\n")
		return()
	}
	
	sig <- node$getAttribute("@ref_sig")
	if( is.null(sig) ) {
		sig <- layer$getAttribute("@pressure_sig")
	}
	if( is.null(sig) ) {
		cat( "zzz update_b2b_refvalue has no REF!\n")
		return()
	}
	# gui$showMessage( paste("update_b2b_ref_value: ", sig$toString() ) )
	
	if( node$getAttribute("txt") == "_Gmean" ) {
		# might call it a programming error...sent to this update
		# gui$showMessage( paste("update_b2b_ref_value: get _Gmean!" ) )
		# seg_sig <- layer$getAttribute("@seg_sig")
		# gui$showMessage( paste("zzz call update_b2b_gmean:", seg_sig$getLayer()$getName() ) )
		update_b2b_gmean( layer, prev, node, next_node )
		return()
	}
	
	y <- sig$getValueAt( node$getX() )	
	node$setY( y )
	
	if( !is.null( next_node ) ) {
		attr <- node$getAttribute("LVET" );
		if( !is.null(attr) ) { 
			node$addAttribute("LVET", D(next_node$getX() - node$getX() ) );
		}
	}
	
	if( !is.null(prev_node) ) {
		attr <- prev_node$getAttribute("LVET" );
		if( !is.null(attr) ) { 
			prev_node$addAttribute("LVET", D(node$getX() - prev_node$getX() ) );
		}
	}
	
# cleanup of existing data
#	attr <- node$getAttribute("PEAK[LVP(dp/dt)]" );
#	if( !is.null(attr) ) { 
#		node$addAttribute("PEAK[LVP(dp/dt)]", NULL );
#	}
# cleanup of existing data
#	attr <- node$getAttribute("data_y" );
#	if( !is.null(attr) ) { 
#		node$addAttribute("data_y", NULL );
#	}
	
}

update_b2b_step2 <- function(layer, prev, node, next_node) { 
	update_b2b_ref_value( layer, prev, node, next_node )	
}

update_b2b_step2p2 <- function(layer, prev, node, next_node) { 
	
	# gui$showMessage("step2p2: updating ref")
	update_b2b_ref_value(layer, prev, node, next_node)	
	
	# two possibilities: LVPs followed by AoPs...or AoPs followed by LVPs
	# LVPs has a Pk-Pk attribute
	lvps_txt <- node$getAttribute("txt")
	if( lvps_txt == "LVPs" ) {
		v <- NULL
		if( !is.null(prev) ) {
			txt <- prev$getAttribute("txt")
			if( txt == "AoPs") { 
				v <- D(node$getY() - prev$getY())
			}
		}
		node$addAttribute("Pk-Pk", v );
	}
	
	# LVPs has a Pk-Pk attribute
	aops_txt <- node$getAttribute("txt")
	if( aops_txt == "AoPs" ) {
		v <- NULL
		if( !is.null(prev) ) {
			txt <- prev$getAttribute("txt")
			if( txt == "LVPs") { 
				v <- D(prev$getY() - node$getY())
				prev$addAttribute("Pk-Pk", v );
			}
		}
		node$addAttribute("Pk-Pk", NULL );  # Cleanup: AoPs should never have Pk-Pk
	}
	
	# LVPs has a Pk-Pk attribute
	aops_txt <- node$getAttribute("txt")
	if( aops_txt == "AoPd" ) {
		node$addAttribute("Pk-Pk", NULL );  # CLEANUP: AoPd should never have Pk-Pk
	}
}


update_b2b_step4 <- function(layer, prev, node, next_node ) { 
	aop_sig = layer$getAttribute( "@aop_sig" )
	lvp_sig = layer$getAttribute( "@lvp_sig" )
	seg_sig = layer$getAttribute( "@seg_sig" )
	
	Dplus  = seg_sig$getNodeBeforeOrEqual( node$getX() );
	Dminus = seg_sig$getNodeAfter( node$getX() );
	Dend   = seg_sig$getNodeAfter( Dminus$getX() );

	if( is.null(Dplus) || is.null(Dminus) ) {
		node$addAttribute("AOPmean", NULL)
		node$addAttribute("AOPsm", NULL)
		node$addAttribute("AOPdm", NULL)
		node$addAttribute("LVPsm", NULL)
		node$addAttribute("LVPdm", NULL)
	} else {
		AOPmean <- NULL	
		if( !is.null(Dend) ) {
			AOPmean  <- aop_sig$getMean( Dplus$getX(), Dend$getX() )
		}
		AOPsm    <- aop_sig$getMean( Dplus$getX(), Dminus$getX() )
		AOPdm    <- aop_sig$getMean( Dminus$getX(), Dend$getX() )
	
		LVPsm    <- lvp_sig$getMean( Dplus$getX(), Dminus$getX() )
		LVPdm    <- lvp_sig$getMean( Dminus$getX(), Dend$getX() )
		
		node$addAttribute("AOPmean", D(AOPmean) )
		node$addAttribute("AOPsm", D(AOPsm) )
		node$addAttribute("AOPdm", D(AOPdm) )
		node$addAttribute("LVPsm", D(LVPsm) )
		node$addAttribute("LVPdm", D(LVPdm) )
	}
}

update_b2b_step5 <- function(layer,  prev, node, next_node ) { 
	
	fluid_sig <- layer$getAttribute("@fluid_sig")
	ltv_sig <- layer$getAttribute("@ltv_sig")
	seg_sig <- layer$getAttribute("@seg_sig")

	txt <- node$getAttribute("txt")
	if( txt == "V" ) {
		Fpk      <- fluid_sig$getValueAt( node$getX() )
		node$setY( Fpk )
	} else if( txt == "_LTVmean" ) {
		Dplus  = seg_sig$getNodeBeforeOrEqual( node$getX() );
		Dminus = seg_sig$getNodeAfter( node$getX() );
		
		if( is.null(Dplus) || is.null(Dminus) ) {
			# nothing to do!
		} else {
			cat( "D+/D- = ", Dplus$getX(), "/", Dminus$getX(), " --> node.x=", node$getX(), "\n" )
			LtVzero  <- ltv_sig$getValueAt( Dplus$getX() )
			LtVmean  <- ltv_sig$getMean( Dplus$getX(), Dminus$getX() ) - LtVzero

			node$setY( LtVmean )
			node$addAttribute("_LtVzero", D(LtVzero) )
		}
	}

}


