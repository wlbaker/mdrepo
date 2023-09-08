library( rJava )
library( xlsx )

baseDir <- "V:/HiFi Research/2. Waveform Analysis ISR/meetings/"
dataFile <- "2017-01-19aa Chart in Microsoft PowerPoint.xlsx"

f <- paste( baseDir, dataFile, sep="" )

df <- read.xlsx( f, sheetIndex=1 )
# trunc time to 0.001 resolution
df$time <- (as.integer( (df$time + 0.0005) *1000))/1000.0

df$phase <- NA
df$phase[ df$time == 0.1 ] <- 2
df$phase[ df$time == 0.214 ] <- 3
df$phase[ df$time == 0.348 ] <- 6
df$phase[ df$time == 0.422 ] <- 7
df$phase[ df$time == 0.450 ] <- 8
df$phase[ df$time == 0.496 ] <- 9
df$phase[ df$time == 0.506 ] <- 10
df$phase[ df$time == 0.516 ] <- 11
df$phase[ df$time == 0.7 ] <- 12
# df$phase[ df$time == 0.6 ] <- 13
df$phase[ df$time == 1.3 ] <- 19
df$phase[ df$time == 1.4 ] <- 20

# number the sections
df$seq <- NA
seq <- 1
n <- length(df$phase)
for( i in c(1:n) ) {
	if( !is.na(df$phase[i]) ) {
		seq <- seq + 1
	}
	df$seq[i] <- seq
}
  
beat <- subset( df, time < 1.4 )

msg <- ""
dx <- 0
dy <- 0

msg[1] <- "Falling Diastolic"
dx[1] <- -3; dy[1] <- 3

msg[2] <- "Begin LVET" # "PreEjection IVCT artifact"
dx[2] <- 2; dy[2] <- 6

msg[3] <- "Early Ejection (peak P/dt)"
dx[3] <- 2; dy[3] <- 5

msg[4] <- "AoPs"
dx[4] <- 3; dy[4] <- 3

msg[5] <- "Onset Reflection Wave"  # Onset Reflection (zero crossing)
dx[5] <- 3; dy[5] <- 3

msg[6] <- "Incisura"  # "Zero Crossing"
dx[6] <- 0; dy[6] <- 0

msg[7] <- "Post Incisura"  # "2nd dP/dt max"
dx[7] <- 0; dy[7] <- 0

msg[8] <- "Reflection and Elastance"  # "AoP dP/dt (zero crossing)"
dx[8] <- 0; dy[8] <- 0

msg[9] <- "Exponential Decline AoP"  # Runoff
dx[9] <- -2; dy[9] <- -5

msg[10] <- "IVCT artifact"  # end diastole
dx[10] <- -2; dy[10] <- -5

x <- beat$time
y <- beat$AoP
z <- beat$dPdt
palette <- colorRampPalette(c("blue", "red"))( 12 )
colors <- palette[beat$seq]

par( mfcol=c(1,2) )
par(mar = c(5, 4, 4, 2) ) 

yrange <- c( 30, 120 )
z1range <- c(-600,3000)

plot( x, y, typ='l', xlab='Time', ylab='AoP', col=colors, ylim=yrange )  # first plot
par(new = TRUE)
plot( x, z, type = "l", axes = FALSE, bty = "n", xlab = "", ylab = "", col='red', ylim=z1range)
# axis(side=4, at = pretty(zrange))
# mtext("dP/dt", side=4 )

par(mar = c(5, 2, 4, 4) )  # Leave space for z axis
z2range <- c(-1000,1000)

plot( y, z, xlab='AoP', ylab='', typ='l', ylim=z2range, yaxt = 'n', xlim=c(50,120), col=colors )



# number two!
# par( mfrow=c(3,4) )
par( mfcol=c(1,2) )
par(mar = c(5, 4, 4, 2) )
 
plot( x, y, typ='l', xlab='Time', ylab='AoP', col=colors, xlim=c(0,1.4), ylim=yrange )  # first plot
par(new = TRUE)
plot( x, z, type = "l", axes = FALSE, bty = "n", xlab = "", ylab = "", col='red', xlim=c(0,1.4), ylim=z1range)

plot( NA, NA, xlab='AoP', ylab='', typ='l', ylim=z1range, yaxt = 'n', xlim=c(50,120) )
for( i in c(1:10) ) {
	seg <- subset( beat, seq==i)
	xx <- seg$time
	yy <- seg$AoP
	zz <- seg$dPdt
	# plot( y, z, col=palette[i], typ='l', xlim=c(50,120), ylim=zrange, xlab=msg[i] )
	lines( yy, zz, col=palette[i] )
	points( yy[1], zz[1], col='black' )
	x1 <- mean(yy)
	y1 <- mean(yy)
	x2 <- x1 + 3*dx[i]
	y2 <- y1 + 100*dy[i]
	text( x2, y2, msg[i] )
	cat( "dx=", dx[i], " dy=", dy[i], " text=", msg[i], "\n" )
	
	lines( x=c(x1,x2), y=c(y1,y2), col='black' )
}
