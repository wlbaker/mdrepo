
base <- "V:/HiFi Research/5. ISR - (Baker & Salinas)/BAMC 485 (Normal) R-Ex"

dat_files <- c( "4685(rest)_160830_1556_w_001.dat", 
				"4685(feet-up)_160830_1602_w_001.dat", 
				"4685(exercise)_160830_1616_w_001.dat" )

app$close()

for( f in dat_files ) {

	canv <- app$load( f )
	canv$setDisplay( "1,1,2" )
	canv$setDomainSecs( 30 )
	
	canv$addSignal( 0, "Tape#09" )
	canv$setRange( 0, -3, -1 )

	canv$addSignal( 1, "Tape#03" )
	canv$setRange( 1, -100, 500 )
	 
	canv$setRange( 2, -60, 180 )
	
	anal$addAnalysis( "ECG Segmentation", null, "Tape#09" )
	
	dest <- gsub(".dat", ".xml", f)
	app$save( dest )
	
	app$close()
}

