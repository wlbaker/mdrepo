plotlya <- function( base="c:/tmp/7392-lya", pts=1024, m=2, J=4, W=80) {
    fname <- paste( base, pts, m, J, W, sep="-" )
    fname <- paste( fname, "txt", sep="." )
    par( mfrow=c(4,1) )
    par( mar=c(2,4,2,1) )
    l0 = read.table( file=fname, sep="\t", header=F, colClasses=c("numeric","numeric","numeric","numeric" ))
    ts.plot( l0$V1, ylab="Lyapunov" )
    mtext( paste("LYAPUNOV m=", m , " J=", J, " W=", W, "  PTS=", pts, sep="" ) )
    ts.plot( l0$V2, ylab="fit-error" )
    ts.plot( l0$V3, ylab="pts-to-stable" )
    ts.plot( l0$V4, ylab="Asymptope" )
    # dev.print(win.graph)
}
