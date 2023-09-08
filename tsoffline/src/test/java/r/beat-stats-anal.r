load("C:\\opt\\study\\rubal\\REBOA-036-ABP-2.RData")


par( mfrow=c(2,1) )

plot( y=pressure, x=tmvals, xlim=c(2,12), ylim=c(40,100), type='l' )
abline( v=rwave_times, col='green' )
abline( v=dpdt_min, col='red' )
abline( v=systol_start, col='orange' )
points( y=(dpdt / 50 + 60), x=tmvals[1:(length(dpdt))], col='black', typ='l' )

rri_dpdt <- dpdt_max[2:1001] - dpdt_max[1:1000]

plot( rri, xlim=c(1,100), typ='l', ylim=c(0.5,0.7) )
points( rri )
points( rri_dpdt, col='red' )
lines( rri_dpdt, col='red' )
