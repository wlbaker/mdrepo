require(png)

    # they switched the cables...duh
	f19a <- c( "1198-CVP-1-2014-02-19_095500.png",
			  "1198-CVP-1-2014-02-19_101000.png",
			  "1198-CVP-1-2014-02-19_102500.png",
			  "1198-CVP-1-2014-02-19_104000.png",
			  "1198-CVP-1-2014-02-19_110500.png",
			  "1198-CVP-1-2014-02-19_112000.png",
			  "1198-CVP-1-2014-02-19_113500.png",
			  "1198-CVP-1-2014-02-19_114500.png"
	)
	
	f19e <- c( "1198-EKG0-2014-02-19_095500.png",
			  "1198-EKG0-2014-02-19_101000.png",
			  "1198-EKG0-2014-02-19_102500.png",
			  "1198-EKG0-2014-02-19_104000.png",
			  "1198-EKG0-2014-02-19_110500.png",
			  "1198-EKG0-2014-02-19_112000.png",
			  "1198-EKG0-2014-02-19_113500.png",
			  "1198-EKG0-2014-02-19_114500.png"
	)
	
	f22a <- c( "1279-ABP-2014-02-26_100500.png",
 			 "1279-ABP-2014-02-26_102500.png",
  			 "1279-ABP-2014-02-26_104000.png",
  			 "1279-ABP-2014-02-26_105500.png",
  			 "1279-ABP-2014-02-26_111000.png",
  			 "1279-ABP-2014-02-26_112500.png",
  			 "1279-ABP-2014-02-26_114000.png",
  			 "1279-ABP-2014-02-26_115500.png"
  			 )
  			 
	f22e <- c( "1279-EKG0-2014-02-26_100500.png",
 			 "1279-EKG0-2014-02-26_102500.png",
  			 "1279-EKG0-2014-02-26_104000.png",
  			 "1279-EKG0-2014-02-26_105500.png",
  			 "1279-EKG0-2014-02-26_111000.png",
  			 "1279-EKG0-2014-02-26_112500.png",
  			 "1279-EKG0-2014-02-26_114000.png",
  			 "1279-EKG0-2014-02-26_115500.png"
  			 )
  			 
	f25a <- c( "1064-ABP-2014-03-05_100500.png",
 			 "1064-ABP-2014-03-05_102500.png",
  			 "1064-ABP-2014-03-05_104000.png",
  			 "1064-ABP-2014-03-05_105500.png",
  			 "1064-ABP-2014-03-05_111000.png",
  			 "1064-ABP-2014-03-05_112500.png",
  			 "1064-ABP-2014-03-05_114000.png",
  			 "1064-ABP-2014-03-05_115500.png"
  			 )
  	
	f25e <- c( "1064-EKG0-2014-03-05_100500.png",
 			 "1064-EKG0-2014-03-05_102500.png",
  			 "1064-EKG0-2014-03-05_104000.png",
  			 "1064-EKG0-2014-03-05_105500.png",
  			 "1064-EKG0-2014-03-05_111000.png",
  			 "1064-EKG0-2014-03-05_112500.png",
  			 "1064-EKG0-2014-03-05_114000.png",
  			 "1064-EKG0-2014-03-05_115500.png"
  			 )
  	
  	
	f23a <- c( 
 			 "1268-ABP-2014-02-27_102500.png",
  			 "1268-ABP-2014-02-27_104000.png",
  			 "1268-ABP-2014-02-27_105500.png",
  			 "1268-ABP-2014-02-27_111000.png",
  			 "1268-ABP-2014-02-27_112500.png",
  			 "1268-ABP-2014-02-27_114000.png",
  			 "1268-ABP-2014-02-27_115500.png",
  			 "1268-ABP-2014-02-27_121000.png"
  			 # "1268-ABP-2014-02-27_122500.png"
  			 )
  			 
	f23e <- c( 
 			 "1268-EKG0-2014-02-27_102500.png",
  			 "1268-EKG0-2014-02-27_104000.png",
  			 "1268-EKG0-2014-02-27_105500.png",
  			 "1268-EKG0-2014-02-27_111000.png",
  			 "1268-EKG0-2014-02-27_112500.png",
  			 "1268-EKG0-2014-02-27_114000.png",
  			 "1268-EKG0-2014-02-27_115500.png",
  			 "1268-EKG0-2014-02-27_121000.png"
  			 # "1268-EKG0-2014-02-27_122500.png"
  			 )

  	f19abp <- paste("c:/tmp/", f19a, sep="")
  	f19ecg <- paste("c:/tmp/", f19e, sep="")

  	f22abp <-  paste("V:/tmp/", f22a, sep="")
  	f22ecg <-  paste("V:/tmp/", f22e, sep="")
  	
  	f23abp <-  paste("V:/tmp/", f23a, sep="")
  	f23ecg <-  paste("V:/tmp/", f23e, sep="")
  	
  	f25abp <-  paste("V:/tmp/", f25a, sep="")
  	f25ecg <-  paste("V:/tmp/", f25e, sep="")
  	
  	ecgs <- c( f19ecg,  f22ecg,  f23ecg,  f25ecg )
  	abps <- c( f19abp,  f22abp,  f23abp,  f25abp )
    cnt <- 1


send_all <- function( filelist ) { 
	par(mar=c(0,0,0,0), xpd=NA, mgp=c(0,0,0), oma=c(0,0,0,0), ann=F)
    par( mfrow=c(4,8) )

    for( fname in filelist ) {
        print( paste(cnt, "processing recurr", fname) )
        
		plot.new()
		plot.window(0:1, 0:1)
        if( file.exists( fname ) ) {
        	img = readPNG(fname)
        	
        	usr<-par("usr")    
			rasterImage(img, usr[1], usr[3], usr[2], usr[4])
        } else {
        	print("**missing")
        }
    }
}
    
with_pdf <- TRUE
pdf_file <- "v:/tmp/out.pdf"
 
if( with_pdf ) {
 #   pdf( file=pdfname, width=32, height=24 )
#	pdf( file=pdf_file, paper="USr", width=10, height=7.5 )  # USr for US Rotated, i.e., landscape
	pdf( file=pdf_file, paper="special", width=17, height=11 )  # USr for US Rotated, i.e., landscape
}

send_all( ecgs )
send_all( abps )

if( with_pdf ) {
	dev.off()
	shell.exec(pdf_file)
}
