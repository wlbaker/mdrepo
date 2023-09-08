#
# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM SignalToGraph
# DIALOG SIGNAL MEASUREMENT Beat_Segmentation
#

require( grid )
require( gridExtra )

sort_by_length <- FALSE
lead_time <- -0.25
lag_time <- -0.15

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
deltaSecs <- stopSecs - startSecs
data_sig <- app$getParam("SIGNAL", "SignalToGraph" )
r_markers <- app$getParam("SIGNAL", "Beat_Segmentation" )

sig_name <- data_sig$getAlias()

g <- data.frame( NAME="AoP", LEAD=0.05, LAG=0.05 , stringsAsFactors=FALSE )
g <- rbind( g, list("LVP", -0.15, 0.0) )


idx = which( g$NAME == sig_name )
if( length(idx) > 0 ) {
	sig_name = g$NAME[idx]
	lead_time <- g$LEAD[idx]
	lag_time <- g$LAG[idx]
}

update <- function( stopSecs ) {
	startSecs <- stopSecs - deltaSecs
	
	xydata <- r_markers$getDataInRange( startSecs, stopSecs)
	start_times <- data$X( xydata )
	if( length(start_times) < 2 ) {
		return
	}
	end_tms <- start_times
	n_beats <- length(start_times)
	if( n_beats > 100 ) {
		decim_mult <- as.integer(length(start_times)/100)
		idx <- (c(1:n_beats) %% decim_mult) == 0
		start_times <- start_times[idx]
	}
	length( start_times ) <- length( start_times ) - 1  # the last one is an end time
	
	freq <- data_sig$getSampleRate()
	data_segs <- data$getSegments( start_times, end_tms, data_sig, lead_time, lag_time )

	# convert list elements to number arrays
	data_list <- lapply( as.list(data_segs ), as.list, simplify=TRUE )
	n_beats <- length(data_list)

	##
	## CLEANUP
	#
	# weed out the beats that are too short or too long
	#

	t <- lapply( data_list, length )
	class(t)<-"numeric"
	sel <- (t > 100 & t < 600)
	data_list <- data_list[sel]
	n_beats <- length(data_list)

	##
	## SORT
	##
	#
	# arrange the list into increasing order
	#
	data_sort <- data_list    # default
	if( sort_by_length ) {
		aopl <- 0
		idx <- 0
		for( a in data_list ) {
 			idx <- idx + 1
 			aopl[idx] <- length(a)
		}
		permu <- order(aopl)
		data_sort <- data_list[permu]
	}

	z_max <-  max( simplify2array( lapply( data_sort, max ) ) )
	z_min <-  min( simplify2array( lapply( data_sort, min ) ) )

	nn <- 1.2*freq
	# fix the length of each element to be exactly 600
	data_flush <- lapply( data_sort, function(x) { 
		length(x) <- nn 
		return(x)
	} )

	step <- 1/freq
	xx <- seq( 0, (nn-1)*step, step ) + lead_time

	waterfall_sub <- paste("LL[", lead_time, ",", lag_time, "] SS[", startSecs, ",", stopSecs, "] beats:", n_beats, sep=""  ) 

	p1 <- ggplot() + # df, aes(x=time,y=dpdt))+
    		xlab("") + ylab("") + ylim(z_min,z_max) + 
    		scale_x_continuous()+
    		theme_dramatic_black(base_size = 16, base_family = "Garamond")

	nn <- length(data_flush)
	xoff <- cos( pi*80/180)/250
	yoff <- sin( pi*80/180)/25

	dd <- data.frame( x=c(lead_time, lead_time+80*xoff), y=c(z_min,z_min+80*yoff) )
	p1 <- p1 + geom_path( data=dd, col='white', aes(x=x, y=y ) )
	
	idx <- 1
	palette <- colorRampPalette(c("blue", "darkorange"))( length(data_flush) )
	for( seg in data_flush ) {

		dd <- data.frame( time=(xx + (nn - idx)*xoff), pressure=(seg + (nn - idx)*yoff) ) 
		cc <- palette[idx]
		p1 <- p1 + geom_path( data=dd, col=cc, aes(x=time, y=pressure ) ) # 
		idx <- idx + 1
	}
	
	#Plot Footer
	footer_text <- paste("    Waterfall - black",subject,sig_name,startSecs)
	footer_sig <- Sys.Date() # format(Sys.Date(), "%S")
	my_g1 <- grobTree(rectGrob(gp=gpar(fill="#000000",col=NA)),
                  linesGrob(unit(c(.02, .98), "npc"), unit(1, "npc"),
                            gp = gpar(col = 'lightgrey', lwd = 2)),
                  textGrob(footer_text,x=0,hjust=0,gp=gpar(col="darkorange",fontsize=8,fontface="bold")),
                  textGrob(footer_sig,x=1,hjust=1.2,gp=gpar(col="darkorange",fontsize=8)))
	
	allplot <- grid.arrange(ncol=1,p1,bottom=my_g1)
	grid.draw(allplot)
}

subject <- app$getSubject()
app$createPlot( paste("Waterfall:", subject) )
update( stopSecs )

