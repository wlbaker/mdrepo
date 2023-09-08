# create standard filters

Color <- J("java.awt.Color")
model <- J("idea.tsoffline.AppModel")
canvas = model$getActiveCanvas()

app$deleteFilter("aap-bw80")

bw80_json <- '{ "name" : "Butterworth", "order" : 8, "fs" : 500, "type" : "lowpass", "cutoff": 40 }'
ma5_json <- '{ "name" : "Moving Average", "order" : 5, "fs" : 500 }'
ma9_json <- '{ "name" : "Moving Average", "order" : 9, "fs" : 500 }'

bw80 <- app$createFilter("aap-bw80", bw80_json )
ma5 <- app$createFilter("aap-ma5", ma5_json )
ma9 <- app$createFilter("aap-ma9", ma9_json )

# band layout data structure
# {"bandName", "bandId", "bandWeight", "yScale", "yTranslate"})


std_layout <- '[
	{ "bandName" : "band0", "bandId" : 0, "bandWeight" : 0.25, "yScale" : 1.0, "yTranslate": 0.0 },
	{ "bandName" : "band1", "bandId" : 1, "bandWeight" : 0.25, "yScale" : 1.0, "yTranslate": 0.0 },
	{ "bandName" : "band2", "bandId" : 2, "bandWeight" : 0.5, "yScale" : 1.0, "yTranslate": 0.0 }
]'

canvas$clear()
canvas$setDisplayLayout( std_layout )

aop <- app$getSignalByName("AoP")
if( is.null(aop) ) {
	aop <- app$getSignalByName( "ABP-2" )
}

aop$applyFilter( bw80 )

d1_aop <- app$derivative( aop, "d{AoP}/dt" )
d1_aop$applyFilter( ma9 )

d2_aop <- app$derivative( d1_aop, "d2{AoP}/dt2" )


band0 = canvas$getBand( "band0" )
band1 = canvas$getBand( "band1" )
band2 = canvas$getBand( "band2" )

canvas$addReferenceLine( band0, 0.0 )

canvas$moveSignalToBand( band0, d2_aop )
canvas$moveSignalToBand( band1, d1_aop )
canvas$moveSignalToBand( band2, aop )
