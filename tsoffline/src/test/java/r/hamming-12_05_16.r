par( mfrow=c(2,3) )

sig5hz1s500sr<- rep( c(rep(0,50,), rep(1,50)), 5 ) - 0.5
sig5hz1s500sr <- rep( c(rep(0,50,), rep(1,50)), 5 ) - 0.5
plot( sig5hz1s500sr, typ='l')
spectrum( sig5hz1s500sr )


par( mfrow=c(3,3) )
sig <- ts(sig5hz1s500sr, start=0, frequency=500)
plot( sig, typ='l')
# spectrum( sig, detrend=FALSE, taper=0.0 )
# spectrum( sig, xlim=c(0,50) )
spec <- spectrum( sig, xlim=c(0,50), detrend=FALSE, taper=0.0, typ='s' )
barplot( spec$spec, typ='l', xlim=c(0,50) )

plot( spec.taper(sig, p=.5), typ='l' )
spec2 <- spectrum( sig, xlim=c(0,50), detrend=FALSE, taper=0.5, typ='S' )
barplot( spec2$spec, typ='l', xlim=c(0,50) )
