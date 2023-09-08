install.packages("quantmod")
install.packages("animation")
library(quantmod)
library(animation)

getSymbols("GS") 

chartSeries(GS) 


ani.options(interval = 0.05)
saveGIF({

    for(i in 1:20){  
    candleChart(GS,multi.col=TRUE,theme='white',yrange=c(0,1200));
      GS = GS+rnorm(3,50)  ; # replace this with something interesting.
}

}, movie.name = "animation.gif", img.name = "Rplot", convert = "convert", 
    cmd.fun = system, clean = TRUE)
    