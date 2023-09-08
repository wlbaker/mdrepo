
n_beats <- 10

g <- data.frame( NAME="AoP", LEAD=-0.25, LAG=-0.25 , stringsAsFactors=FALSE )
g <- rbind( g, list("LVP",  -0.25, -0.25) )
g <- rbind( g, list( "PAP", -0.25, -0.25 ) )
g <- rbind( g, list( "RVP", -0.25, -0.25 ) )
g <- rbind( g, list( "RAP", -0.25, -0.25 ) )
# g <- rbind( g, list("Fluid", -0.25, -0.25 ) )

r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation")
if( is.null( r_markers ) ) {
	r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation: PT1")
}
if( is.null( r_markers ) ) {
	gui$showMessage("Could not find ECG Segmentation information.")
	stop("Could not find ECG Segmentation")
}


f <- function( sig_name, lead_time, lag_time ) {
	data_sig <- data$getSignal( NULL, NULL, sig_name )
	if( is.null( data_sig ) ) {
		message <-paste("Could not find data signal:", sig_name)
		gui$showMessage( message )
		stop(message)
	}
	data_segs <- data$getSegments( r_markers, data_sig, lead_time, lag_time )
	# convert list elements to number arrays
	data_list <- lapply( as.list(data_segs ), as.list, simplify=TRUE )
}


##
## CLEANUP
#
# weed out the beats that are too short or too long
#

t <- lapply( data_list, length )
class(t)<-"numeric"
sel <- (t > 100 & t < 600)
data_list <- data_list[sel]

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

# fix the length of each element to be exactly 600
data_flush <- lapply( data_sort, function(x) { 
	length(x) <- 600 
	return(x)
	} )

subject <- app$getSubject()
app$createPlot( paste("Waterfall:", subject) )

xx <- seq( 0, 599*0.002, 0.002 ) + lead_time

s3d <- scatterplot3d( x=lead_time, y=0, z=z_min, highlight.3d=TRUE, 
	xlim=c(lead_time,1.2), ylim=c(0,n_beats), zlim=c(z_min,z_max), angle=80,
	col.axis="blue", col.grid="lightblue", 
	xlab=paste("Time(s) -- lead:", lead_time, " lag:", lag_time), zlab=sig_name, ylab="Beat Number",
	main=paste(sig_name, "Traces", subject ) )

idx <- 0
for( seg in data_flush ) {

    idx <- idx+1
	yy <- rep( idx, length(xx) )
	
	if( idx < n_beats ) {
		s3d$points3d(x <- xx, y <- yy, z <- seg, type='l', col='gray14' ) # palette()[idx])
	}
}


