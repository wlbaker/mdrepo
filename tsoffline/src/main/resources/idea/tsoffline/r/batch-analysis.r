root <- "\\\\AISRA7SVR1131\\ISR_PROTOCOL_A_17_01_RUBAL\\Swine Part 1"
root <- "U:\\ISR_PROTOCOL_A_17_01_RUBAL\\Swine Part 1"
animals <- list.files(root)
data_dir <- paste( root, animals, sep="\\")

dats <- paste( list.files( data_dir[1], "*.dat", full.names=TRUE), sep="\\" )
app$open( dats[1] )

app$runAnalysis( "ECG Segmentation" )