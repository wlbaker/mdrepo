
# DIALOG TIMERANGE
# DIALOG SIGNAL WAVEFORM SignalToGraph
# DIALOG SIGNAL MEASUREMENT Beat_Segmentation
#

require( grid )
require( gridExtra )

startSecs <- app$getParam("TIMERANGE", "startSecs" )
stopSecs <- app$getParam("TIMERANGE", "stopSecs" )
deltaSecs <- stopSecs - startSecs
data_sig <- app$getParam("SIGNAL", "SignalToGraph" )
r_markers <- app$getParam("SIGNAL", "Beat_Segmentation" )

#	gui$showMessage( message )

sig_name <- data_sig$getAlias()
deltaSecs <- stopSecs - startSecs

#	gui$showMessage( message )

update <- function( stopSecs ) {
	startSecs <- stopSecs - deltaSecs
	
	xydata <- r_markers$getDataInRange( startSecs, stopSecs)
	start_times <- data$X( xydata )
	if( length(start_times) < 2 ) {
		return
	}

	fiducial_lead <- 0.1
	fiducial_lag  <- 0.1
	
	xx <- data_sig$getTimesInRange( start_times[1] - fiducial_lead, start_times[2] - fiducial_lag )
	yy <- data_sig$getValuesInRange( start_times[1] - fiducial_lead, start_times[2] - fiducial_lag )

	xx <- xx - xx[1]
	
	n <- length(yy)
	y5 <- ( yy[1:(n-4)] + yy[ 2:(n-3)] + yy[ 3:(n-2)] + yy[ 2:(n-1)] + yy[ 1:n ])/5
	dpdt <- (y5[2:length(y5)] - y5[ 1:(length(y5)-1) ])
	dpdt <- ( dpdt[1:(n-4)] + dpdt[ 2:(n-3)] + dpdt[ 3:(n-2)] + dpdt[ 2:(n-1)] + dpdt[ 1:n ])/5
	dpdt <- dpdt * data_sig$getSampleRate()
	yy <- yy[ 11:(length(yy)) ]
	y5 <- y5[ 11:(length(y5)) ]
	
	n <- length( dpdt )
	length( xx ) <- n
	length( y5 ) <- n
	length( yy ) <- n
	
	par( mfcol=c(1,2) )
	par(mar = c(5, 4, 4, 2) ) 

	yrange <- c( 30, 120 )
	z1range <- c(-600,3000)

	lower_pressure = as.integer(min(y5,na.rm=TRUE))
	upper_pressure = as.integer(max(y5,na.rm=TRUE))
	step_pressure = as.integer((upper_pressure - lower_pressure)/2)
	plabs=seq( lower_pressure, upper_pressure, step_pressure )
	blabs= 18*plabs - 180
	
	df <- data.frame(time=xx,pressure=y5,dpdt=dpdt, yyy=(18*y5-180)) 	
	p1 <- ggplot( df, aes(x=time,y=dpdt))+
    		geom_line( color='white', aes(y=0))+
    		geom_line( color='green')+
    		geom_line( color='red',aes(y=yyy))+
    		xlab("") + ylim(-800,1700) + 
    		scale_x_continuous()+
 xlab("Time") +
    		scale_y_continuous(breaks=blabs,labels=plabs,limits=c(-800,1700)) +
    		theme_dramatic_black(base_size = 16, base_family = "Garamond")

	# p1 <- p1 +  annotate("text", label = "plot mpg vs. wt", x = -1, y = 15, size = 8, colour = "red")
	events <- data.frame(
  		x = c(1, 1, 2, 2, 1.5),
  		y = c(1, 2, 1, 2, 1.5),
  		text = c("bottom-left", "bottom-right", "top-left", "top-right", "center")
	)

	p1 <- p1 + ylab("dP/dt                                               Pressure")
	p1 <- p1 + theme(axis.title.y = element_text(angle=90))
	
	p1 <- p1 + theme(axis.title.x = element_text(face="bold", size=26),
           axis.text.x  = element_text(angle=90, vjust=0.5, size=26))

	
	nbeats <- length(start_times)

	xx <- data_sig$getTimesInRange( start_times[1] - fiducial_lead, start_times[nbeats] - fiducial_lag )
	yy <- data_sig$getValuesInRange( start_times[1] - fiducial_lead, start_times[nbeats] - fiducial_lag )

	n <- length(yy)
	y5 <- ( yy[1:(n-4)] + yy[ 2:(n-3)] + yy[ 3:(n-2)] + yy[ 2:(n-1)] + yy[ 1:n ])/5
	dpdt <- (y5[2:length(y5)] - y5[ 1:(length(y5)-1) ])
	dpdt <- dpdt * data_sig$getSampleRate()
	zz <- dpdt
	n <- length( dpdt )
	length( xx ) <- n
	length( y5 ) <- n
	length( yy ) <- n
	
	df <- data.frame(time=xx,pressure=y5,dpdt=zz) 	
	df$seq <- as.integer(1 + 24* ( c(0:(n-1)) / n))
	df$colseq <- GRADIENT_HEAT[df$seq]
	
	overtop <- data.frame(x=c(30,100),y=c(0,0))
	p2 <- ggplot( df, aes(x=pressure,y=dpdt))+
    		geom_path( alpha=0.5, color=df$colseq )+
    		geom_line( color='#6090FF', data=overtop, aes(x=x,y=y) ) +
    		scale_x_continuous()+
    		xlab("Pressure (mmHg)") +
    		xlim( 30,100 ) + ylim(-1200,1200) +
    		theme_dramatic_black(base_size = 16, base_family = "Garamond")

	p2 <- p2 + ylab("dP/dt") + theme(axis.title.y = element_text(angle=90))
	p2 <- p2 + theme(axis.title.x = element_text(face="bold", size=26),
           axis.text.x  = element_text(angle=90, vjust=0.5, size=26))

	# print( p2 )

	# multiplot( p1, p2, cols=2 )
	#Plot Footer
	footer_text <- paste("    ",subject,sig_name,startSecs)
	footer_sig <- Sys.Date() # format(Sys.Date(), "%S")
	my_g1 <- grobTree(rectGrob(gp=gpar(fill="#000000",col=NA)),
                  linesGrob(unit(c(.02, .98), "npc"), unit(1, "npc"),
                            gp = gpar(col = 'lightgrey', lwd = 2)),
                  textGrob(footer_text,x=0,hjust=0,gp=gpar(col="darkorange",fontsize=8,fontface="bold")),
                  textGrob(footer_sig,x=1,hjust=1.2,gp=gpar(col="darkorange",fontsize=8)))

	allplot <- grid.arrange(ncol=2,p1,p2,bottom=my_g1)
	grid.draw(allplot)
}

subject <- app$getSubject()
app$createPlot( paste("CUSTOM:", subject, sig_name) )
update( stopSecs )

