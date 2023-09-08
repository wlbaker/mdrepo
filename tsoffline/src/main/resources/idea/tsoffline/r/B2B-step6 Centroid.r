## Centroid algorithm from https://en.wikipedia.org/wiki/Locating_the_center_of_mass
## To find I_x and I_y, https://en.wikipedia.org/wiki/Second_moment_of_area
## I_z = I_x + I_y by the perpendicular axis theorem: https://en.wikipedia.org/wiki/Second_moment_of_area
##
# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM MULTISELECT CentroidX.Signal
# DIALOG SIGNAL WAVEFORM OPTIONAL CentroidY.Signal
# DIALOG SIGNAL MEASUREMENT Beat.Segmentation.Signal
# ?# DIALOG PROMPT Layer.Name LVP(dp/dt).Max.Code LVP(dp/dt).Min.Code

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )

x_sigs <- app$getParam("SIGNAL", "CentroidX.Signal" )
y_sig <- app$getParam("SIGNAL", "CentroidY.Signal" )
seg_sig <- app$getParam("SIGNAL", "Beat.Segmentation.Signal" )

B2B_centroid <- function( xx, yy ) {

	n = length(xx)
	x0 <- xx[1]
	y0 <- yy[1]
	
	a <- 0
	signedArea <- 0
	
	Cx <- 0
	Cy <- 0
	
	for( i in c(2:n) ) {
		x1 = xx[i]
		y1 = yy[i]
		
		a <- x0*y1 - x1*y0
        signedArea <- signedArea + a
        Cx <- Cx + (x0 + x1)*a
        Cy <- Cy + (y0 + y1)*a		
		x0 <- x1
		y0 <- y1
	}
	
	signedArea <- signedArea * 0.5
    Cx = Cx / (6.0*signedArea)
    Cy = Cy / (6.0*signedArea)
    
    c(Cx, Cy)
}


B2B_moment <- function( xx, yy, Cx, Cy ) {
	n = length(xx)
	x0 <- xx[1] - Cx
	y0 <- yy[1] - Cy
	
	I_x <- 0;
	I_y <- 0;
	for( i in c(2:n) ) {
		x1 <- xx[i] - Cx
		y1 <- yy[i] - Cy
		
     	I_x <- I_x + (y0*y0 + y0*y1 + y1*y1) * (x1 * y0 - x0 * y1);
     	I_y <- I_y + (x0*x0 + x0*x1 + x1*x1) * (x1 * y0 - x0 * y1);
     	
     	x0 <- x1
		y0 <- y1
    }
    
    I_x <- (I_x/12)/1000000
    I_y <- (I_y/12)/1000000
    
    I_z = I_x + I_y
    
    c(I_x,I_y)
 }


init_centroids <- function(seg_sig, x_sig, y_sig, startSecs, stopSecs) { 
	# layer$addAttribute( "@centroid_seg_sig", seg_sig )
	
	rwave_nodes <- seg_sig$getNodesInRange( startSecs, stopSecs )

	n <- rwave_nodes$size()
	if( n <= 0 ) {
		return
	}
	
	seg_start <- 0
	seg_end <- 0
	pos <- 1
	
	prev_node <- rwave_nodes$get( int(0) )
	for( idx in c(1:(n-1)) ) {
		next_node <- rwave_nodes$get( int(idx) )

		a = prev_node$getX()
		b = next_node$getX()
		
		xx = x_sig$getValuesInRange( a, b)
		yy = y_sig$getValuesInRange( a, b)

		centroid = data$JAVA_centroid(xx,yy)
		moment = data$JAVA_moment(xx,yy, centroid[1], centroid[2])
		next_node$addAttribute("centroid_x", D(centroid[1]) )		
		next_node$addAttribute("centroid_y", D(centroid[2]) )		
		next_node$addAttribute("moment_x", D(moment[1]) )		
		next_node$addAttribute("moment_y", D(moment[2]) )
		
		prev_node = next_node;
	}
	
}

# with( vizre0, for( i in c(1:length(x_sigs)) ) { cat("1\n") } )
for( i in c(1:length(x_sigs)) ) {
	x_sig = x_sigs[[i]]
	data$init_centroids(seg_sig, x_sig, y_sig, startSecs, stopSecs)
}

rm(x_sigs, seg_sig, startSecs, stopSecs)
