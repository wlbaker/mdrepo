library( xlsx )
# DIALOG SIGNAL

startTime <- app$getParam("CANVAS", "startDate" )

pressure_sig <- app$getParam("SIGNAL", "selection" )

if( is.null( pressure_sig ) ) {
	gui$showMessage("Could not find signal.")
	stop("Could not find signal")
}

r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation")
if( is.null( r_markers ) ) {
	r_markers <- data$getSignal( NULL, NULL, "ECG Segmentation: PT1")
}
if( is.null( r_markers ) ) {
	gui$showMessage("Could not find ECG Segmentation information.")
	stop("Could not find ECG Segmentation")
}

user_markers <- data$getSignal( NULL, NULL, "MKR #")

if( is.null( user_markers ) ) {
	gui$showMessage("Could not find MRK # signal")
	stop("Could not find MRK # signal")
}

xydata <- user_markers$getData( )
mark_yy <- data$Y( xydata )

xydata <- r_markers$getData( )
rwave_times <- data$X( xydata )


sig_name <- pressure_sig$getAlias()
sample_rate <- pressure_sig$getSampleRate()
xydata <- pressure_sig$getData( )
tmvals <- data$X( xydata )
pressure <- data$Y( xydata )

n <- length(pressure)
pressure <- ( pressure[1:(n-4)] + pressure[ 2:(n-3)] + pressure[ 3:(n-2)] + pressure[ 2:(n-1)] + pressure[ 1:n ])/5
dpdt <- (pressure[2:length(pressure)] - pressure[ 1:(length(pressure)-1) ])
dpdt <- dpdt * sample_rate

systol_start <- data$getDiastolTime( pressure, tmvals, rwave_times )

# it's ok to use the same time for both of these.  The algorithm will figure it out
# that we want the narrowest interval.  The Min and Max are nowhere close to the
# endpoints

dpdt_tm_max <- data$getTimeOfMax( dpdt, tmvals, systol_start, systol_start )
dpdt_tm_min <- data$getTimeOfMin( dpdt, tmvals, systol_start, systol_start )
dpdt_max <- data$getMax( dpdt, tmvals, systol_start, systol_start )
dpdt_min <- data$getMin( dpdt, tmvals, systol_start, systol_start )


# here we need shorter intervals since the diastole is close to the end of the
# interval
diastol_start <- dpdt_tm_min

systol_mean <- data$getMean( pressure, tmvals, systol_start, diastol_start )
diastol_mean <- data$getMean( pressure, tmvals, diastol_start, systol_start )
aop_mean <- data$getMean( pressure, tmvals, systol_start, systol_start )

systolic <- data$getMax( pressure, tmvals, systol_start, diastol_start )
diastolic <- data$getMin( pressure, tmvals, diastol_start, systol_start )
pulse_pressure <- systolic - diastolic


subject <- app$getSubject()
rootDir <- "/opt/study/rubal"

mark_id <- data$getValuesAtTimes( mark_yy, tmvals, rwave_times )

gui$showMessage( paste("Beat statistics complete for signal: ", sig_name, ", subject: ", subject ) )

n <- length(rwave_times)
rri <- rwave_times[2:n]-rwave_times[1:(n-1)]
length(rri) <- n  # add a NA at the end so all the vectors are the same length
 
# tm <- startTime + rwave_times;
beat_no <- c(1:n)

f <- data.frame(beat_no, mark_id, rwave_times, rri, systol_start, systolic, diastol_start, diastolic, pulse_pressure, aop_mean, systol_mean, diastol_mean, dpdt_tm_max, dpdt_max, dpdt_tm_min, dpdt_min ) 

save.image( paste( rootDir, "/", subject, "-", sig_name, ".RData", sep="") )
write.xlsx( f, file=paste(rootDir, "/", subject, "-beat-", sig_name, ".xlsx", sep=""), row.names=FALSE, sheetName=subject )

rm(f)
rm( r_markers, user_markers, pressure_sig )
rm( beat_no )
rm( systolic, diastolic, systol_mean, diastol_mean )
rm( xydata, tmvals )
rm( rri )
rm( diastol_start )
rm( dpdt_min, dpdt_max, dpdt_tm_min, dpdt_tm_max )
rm( mark_yy, mark_id )

do_save_wf <- FALSE
if( do_save_wf ) {
	gui$showMessage( paste("Saving WF data with beat info" ) )

	#
	# create beat_no array that lines up with the pressure wave
	# and numbers beats sequentially
	# 

	beat_no <- 0
	beat_no[ trunc( systol_start * sample_rate ) ] =  c(1:length(rwave_times) )
	length(beat_no) <- length(pressure)
	length( dpdt ) <- length(pressure)

	# fill in the NA gaps in the beat_no
	seq_no <- 0
	for( i in c(1:length(pressure)) ) { 
    	if( is.na(beat_no[i]) ) {
	    	beat_no[i] = seq_no
		} else { 
			seq_no = beat_no[i] 
		} 
	}

	#
	# too many rows for excel.  Write to space/tab deliniated ASCII.
	#
	f <- data.frame( beat_no, pressure, dpdt )
	sz <- length( f$beat_no ) / 2
	write.table( head(f, sz), file=paste(rootDir, "/", subject, "-wf-001-", sig_name, ".csv", sep=""), row.names=FALSE )
	write.table( tail(head(f, sz*2),sz), file=paste(rootDir, "/", subject, "-wf-002-", sig_name, ".csv", sep=""), row.names=FALSE )
}

rm( f )
rm( pressure )
rm( dpdt )
rm( rri_times, systol_start )
rm( sz )

