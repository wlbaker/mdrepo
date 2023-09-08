# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM ABP.Signal
# DIALOG SIGNAL WAVEFORM CVP.Signal
# DIALOG SIGNAL MEASUREMENT Compression.Segmentation.Signal

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )

abp_sig <- app$getParam("SIGNAL", "ABP.Signal" )
cvp_sig <- app$getParam("SIGNAL", "CVP.Signal" )
comp_sig <- app$getParam("SIGNAL", "Compression.Segmentation.Signal" )

#
# Functions
#

update_annotations_cpp <- function( layer, f ) {
	model <- J("idea.tsoffline.AppModel")
	
	canvas <- app$getCanvas()
	zeroMs <- canvas$getStartTime()
	
	n <- nrow(f)
		
	for( ii in c(1:n) ) {
	
		dt <- f$dt
		c  = comp_sig$getNodeBeforeOrEqual( dt[ii] );
		
		if( is.null(c) ) {
			# not expected
		}		
		c$addAttribute("CPP", D(f$CPP[ii]) )
		c$addAttribute("CPPC", D(f$CPPC[ii]) )
		c$addAttribute("CPPD", D(f$CPPD[ii]) )
		
	}
	layer$setVisible( TRUE);
}


#
# Main
#

# Get Compression info
	xydata <- comp_sig$getDataInRange( startSecs, stopSecs )
	comp_x <- data$X( xydata )
	comp_y <- data$Y( xydata )

# Get ABP signal	
	xydata <- abp_sig$getDataInRange( startSecs, stopSecs )
	abp_x <- data$X( xydata )
	abp_y <- data$Y( xydata )

# Get CVP signal	
	xydata <- cvp_sig$getDataInRange( startSecs, stopSecs )
	cvp_x <- data$X( xydata )
	cvp_y <- data$Y( xydata )

abp_means  <- data$getMean( abp_y, abp_x, comp_x, comp_x )
cvp_means  <- data$getMean( cvp_y, cvp_x, comp_x, comp_x )

abp_cmeans  <- data$getMean( abp_y, abp_x, comp_x, comp_x + 0.3 )
cvp_cmeans  <- data$getMean( cvp_y, cvp_x, comp_x, comp_x + 0.3 )

abp_dmeans  <- data$getMean( abp_y, abp_x, comp_x - 0.3, comp_x )
cvp_dmeans  <- data$getMean( cvp_y, cvp_x, comp_x - 0.3, comp_x )

cpp_means <- (abp_means - cvp_means)/10
cpp_cmeans <- (abp_cmeans - cvp_cmeans)/10
cpp_dmeans <- (abp_dmeans - cvp_dmeans)/10

f <- data.frame( dt=comp_x, beat=seq(1,length(abp_means)), ABP=(abp_means/10), CVP=(cvp_means/10), CPP=cpp_means, CPPC=cpp_cmeans, CPPD=cpp_dmeans )

fname <- paste("c:/tmp/cpp-",app$getSubject(),".csv",sep="")
write.csv( f, fname, col.names=TRUE, row.names=FALSE )
update_annotations_cpp( comp_sig$getLayer(), f )
