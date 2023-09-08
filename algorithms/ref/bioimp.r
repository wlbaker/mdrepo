 t <- read.csv( "S:/USERS/William.Baker/RESEARCH/2015 - Bioimpedance/two-days.csv", header=TRUE )
t$Z <- (t$V1 - t$V2)/t$V2