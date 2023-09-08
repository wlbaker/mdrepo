
require( fNonlinear )
require( colorRamps )
# require( xlsx )

isr_recurrencePlot <- function (x, m, d, end.time, eps, nt = 10, doplot = TRUE, ...) 
{
    colors <- blue2red(20)
    
    if (class(x) == "timeSeries") 
        x = as.vector(x)
    series = as.ts(x)
    w = (0:(m - 1)) * d
    .dist = function(i, j) {
        sum((series[i + w] - series[j + w])^2)
    }
    .checkEmbParms(series, m, d)
    if (eps <= 0) 
        stop("eps must be positive")
    nt = as.integer(nt)
    if (nt <= 0) 
        nt = 1
    n = length(series) - (m - 1) * d
    if (end.time > n) 
        end.time = n
    eps = eps^2
    xyz = .embeddPSR(series, m = m, d = d)[1:end.time, ]
    
    if (doplot) {
        plot(0, xlim = c(0, end.time), ylim = c(0, end.time), 
            type = "n", ... )
        for (i in seq(1, end.time, by = nt)) for (j in seq(i, 
            end.time, by = nt)) {
                d <- .dist(i,j)
                if ( d < eps) {
                    q <- (d/2) + 1
                    if( q > length(colors) ) {
                        q <- length(colors)
                    }
                    q <- length(colors) - q + 1
                    
                    points(c(i, j), c(j, i), pch='.', cex=2, col=colors[q] )
                }
            }
    }
    invisible()
}



recurPlots <- function( v, width, inc, m=2, d=1, row_width=12, ...  ) {
   
  len <- length(v) - inc
  cnt <- 1
  
  for( start in seq(from=1,to=len,by=inc) ) {
     
     if( cnt > row_width ) {
        break;
     }
        
     print( paste("   ", start) )
     end <- start + inc
     
     label <- paste( "RRI", start, "to", end )
     isr_recurrencePlot( v[start:end], m=m, d=d, end.time=10000, eps=8, xlab=label, ... )
     
     cnt <- cnt + 1
  }
  
  if( cnt <= row_width ) {
        for( i in cnt:row_width ) {
            plot.new()
        }
  }
}

generateRecurrencePdf <- function( pdfname, data, filelist ) {
    pdf( file=pdfname, width=32, height=24 )
    par( mfrow=c(8,12) )

    cnt <- 1
    for( fname in filelist ) {
        print( paste(cnt, "processing", fname) )
        
        v <- data[[cnt]]
        
        recurPlots( v, 2000, 2000, d=2, main=fname )
        cnt = cnt + 1
    }
    
    dev.off()
}

generateRecurrenceDerivativeComparison <- function( pdfname, v ) {
     pdf( file=pdfname, width=32, height=24 )
     par( mfrow=c(8,12) )
 
         print( paste(cnt, "processing", fname) )
         
         recurPlots( v, 2000, 2000, d=2, eps=64, main="v" )
         
         zerov <- v - mean(v)
         integrated_v <- c()
         
         integrated_v[1] <- 0
         for( i in c(2:(length(v)-1) ) ) integrated_v[i] <- integrated_v[i-1] + zerov[i]
         recurPlots( dv, 2000, 2000, d=2, eps=32, main="integrated-32" )

    len = length(v) 
    dv = v[2:(len-1)] - v[1:(len-2)]
         recurPlots( dv, 2000, 2000, d=2, eps=32, main="dv-32" )

   len = length(dv)
   ddv = dv[2:(len-1)] - dv[1:(len-2)]
         recurPlots( ddv, 2000, 2000, d=2, eps=32, main="ddv-32" )
 
     dev.off()
}


generateRecurrenceDerivativeComparison( "c:/tmp/deriv-1.pdf", control_data[[1]])
generateRecurrenceDerivativeComparison( "c:/tmp/vagal-1.pdf", vagal_data[[1]])
