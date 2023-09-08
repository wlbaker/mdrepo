# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM SignalToGraph
# DIALOG PROMPT FIDUCIAL_LEAD FIDUCIAL_LAG RANGE_HIGH RANGE_LOW ZERO_FIRST_POS
#
# option color-scale-by-length
# option no-ecg marker
# option no-mean-in-red
#


require( gridExtra )
require( ggplot2 )

#
# patch the arrangelist print function
#
require( grid )
print.arrangelist <- function (x, ...) 
lapply(x, function(.x) {
    grid.newpage()
    grid.draw(.x)
}, ...)

#
# Set default values for fiducial_lead, fiducial_lag, and plot_range
#
fiducial_lead <- -0.20
fiducial_lag <- -0.20
fiducial_lead <- app$getParam("PROMPT", "FIDUCIAL_LEAD" )
fiducial_lag <- app$getParam("PROMPT", "FIDUCIAL_LAG" )
class(fiducial_lead) <- "numeric"
class(fiducial_lag) <- "numeric"

range_high <- app$getParam("PROMPT", "RANGE_HIGH" )
range_low <- app$getParam("PROMPT", "RANGE_LOW" )
zero_first <- app$getParam("PROMPT", "ZERO_FIRST_POS" )
if( zero_first >= 1 ) {
	zero_first <- TRUE
} else {
	zero_first <- FALSE
}


plot_range <- c(range_low,range_high)

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
data_sig <- app$getParam("SIGNAL", "SignalToGraph" )

sig_name <- data_sig$getAlias()

if( is.null( data_sig ) ) {
	data_sig <- data$getSignal( NULL, NULL, "LVP" )
}

if( is.null( data_sig ) ) {
	message <-paste("Could not find data signal:", sig_name)
	gui$showMessage( message )
	stop(message)
}

#
# Tweak graph parameters to accommodate known signals
#

sig_name <- data_sig$getAlias()

g <- data.frame( NAME="AoP", LEAD=0.05, LAG=0.05 , RANGE_LOW=0, RANGE_HIGH=150, stringsAsFactors=FALSE )
# g <- rbind( g, list("ECG", -0.20, -0.20, -1.2, 1.4 ) )
g <- rbind( g, list("PAP", -0.05, -0.05, 0, 40 ) )
g <- rbind( g, list("RVP", -0.15, -0.15, 0, 40 ) )
g <- rbind( g, list("Fluid", -0.15, -0.15, 0, 40 ) )
g <- rbind( g, list("Resp", -0.15, -0.15, -50, 10 ) )


idx = which( g$NAME == sig_name )
if( length(idx) > 0 ) {
	fiducial_lead <- g$LEAD[idx]
	fiducial_lag <- g$LAG[idx]
	
	plot_range <- c( g$RANGE_LOW[idx], g$RANGE_HIGH[idx] )
}

#
#
#

r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation")
if( is.null( r_markers ) ) {
	r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation: PT1")
}
if( is.null( r_markers ) ) {
	gui$showMessage("Could not find ECG Segmentation information.")
	stop("Could not find ECG Segmentation")
}

xydata <- r_markers$getDataInRange( startSecs, stopSecs)
times <- data$X( xydata )
data_segs <- data$getSegments( times, data_sig, fiducial_lead, fiducial_lag )

# convert list elements to number arrays
seg_list <- lapply( as.list(data_segs ), as.list, simplify=TRUE )
n_beats <- length(seg_list)

# fix the length of each element to be exactly 600
seg_flush <- lapply( seg_list, function(x) { 
	length(x) <- 600 
	return(x)
	} )


subject <- app$getSubject()
app$createPlot( paste("Ensemble Average", subject) )

xx <- seq( 0, 599*0.002, 0.002 )

# save.image( "c:/tmp/im1.RData" )

mm <- NA
tot <- rep(0,600)
one <- rep(1,600)
idx <- 0

# x=0, main=paste( subject ), type='l', 

pl1 <- ggplot( ) + 
	xlim(0,1.2) +
	ylim(plot_range) + 
	labs(x=NULL,y=sig_name)+
	theme(plot.margin = unit(c(0.5, 0.2, 0, 0.2), "cm")) +  # top, right, bottom, left
	theme(legend.position="none",axis.text.x=element_blank(),axis.ticks.x=element_blank())
	
#	sub=paste(" lead:", fiducial_lead, "lag:", fiducial_lag, "start:", startSecs, "end:", stopSecs, "beats:", n_beats  ), 

for( beat in seg_flush ) {
	zero <- beat[1]
	
	r <- !is.na(beat)
	if( is.na( zero ) ) {
		# skip
	} else {
		if( is.na(mm) ) {
			mm[r] <- beat[ r ]
		} else {
			mm[r] <- mm[r] + beat[ r ]
		}
		if( sum(r) > 300 ) {
			tot[r] <- tot[r] + one[ r ]
			idx <- idx + 1
			if( zero_first ) {
				beat <- beat - zero
			}
			pl1 <- pl1 + geom_line( data=data.frame(xx,beat), aes(x=xx,y=beat), color="gray" )
		}
	} 
}

ea_mean <- mm/ tot
if( zero_first ) {
	ea_mean <- ea_mean - ea_mean[1]
}
pl1 <- pl1 + geom_line( data=data.frame(xx=xx,yy=ea_mean), aes(x=xx,y=yy), color='red' )


	# xlab( paste( "Ensemble Average:", sig_name) ) + 
pl2 <- ggplot( ) + 
	xlim(0,1.2) +
	labs(x=NULL,y="Variance")+
	theme(plot.margin = unit(c(0, 0.2, 0, 0.2), "cm")) +  # top, right, bottom, left
	theme(legend.position="none",axis.text.x=element_blank(),axis.ticks.x=element_blank())

for( beat in seg_flush ) {
	zero <- beat[1]
	
	r <- !is.na(beat)
	if( is.na( zero ) ) {
		# skip
	} else {
		if( sum(r) > 300 ) {
			tot[r] <- tot[r] + one[ r ]
			idx <- idx + 1
			if( zero_first ) {
				yy <- beat - zero
			} else {
				yy <- beat - ea_mean
			}
			ff <- (c(1:length(xx)) %% 2) == 1
			yyff <- yy[ff]
			xxff <- xx[ff]
			pl2 <- pl2 + geom_point( data=data.frame(xx=xxff,yy=yyff), aes(x=xx,y=yy,stroke=0.1),alpha=1/8 )
		}
	} 
}

pl <- list( pl1, pl2 )

# rm( mm, tot, one, idx, ea_mean, n_beats )
# rm( fiducial_lead, fiducial_lag, plot_range )
# rm( g, xydata )  # hmm...xx,yy not found
# rm( times, data_segs, seg_list, seg_flush)

# g <- marrangeGrob(pl, nrow=2, ncol=1, heights=c(2,1), widths=c(1))
# g <- grid.arrange( pl1, pl2, nrow=2, ncol=1, heights=c(2,1), widths=c(1) )
g <- marrangeGrob(pl, nrow=2, ncol=1, heights=c(2,1), 
	widths=c(1),
	bottom=paste( "Ensemble Average:", sig_name),
	top=NULL
	)
print( g )

