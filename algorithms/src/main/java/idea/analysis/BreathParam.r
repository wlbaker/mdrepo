bparam <- function( vol, fco2 ) {
    
    vol = na.omit( vol )
    fco2 = na.omit( fco2 )
    
    t = vol
    t2 = t^2
    t3 = t^3
    t4 = t^4
    t5 = t^5
    t6 = t^6
    t7 = t^7

    fit1 = lm( fco2~t + t2 + t3 + t4 + t5 + t6 + t7 )

    plot( vol, fco2 )
    lines( fit1$fit ~ vol )

}

sderiv <- function( y, x ) {

         

}

# bparam( eco2r$VOL, eco2r$FCO2 )
 bparam( tm, eco2r$FCO2 )
 