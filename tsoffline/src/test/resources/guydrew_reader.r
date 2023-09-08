#' Parse the Guy Drew date
#'
#' @param line		A Date or Date+Time value used in Guy Drew waveform and vitals files.
#'
#' @return	a POSIXct date
#'
#' @export
parseGuyDrewDate <- function( line ) {
	ltime <- strptime( line, format="%A, %B %d, %Y %H:%M:%S" )
	if( is.na(ltime) ) {
		ltime <- strptime( line, format="%A, %B %d, %Y" )
	}
	ptime <- as.POSIXct( ltime )
	ptime
}

#' Read DAQ Header
#'
#' This functions reads either a VTL or a DAT (waveform) header from Guy Drew ASCII Files.
#'
#' @param file		The ASCII VTL file to open
#'
#' @return			A list of the header variables including the end of the Guy Drew header.
#'                  The additional variable dataStart indicates where data reading should begin.
#'
#' @export
readHeader <- function( file ) {
	 
	l <- list()
	lines <- readLines(file, n=20 )
	
	date_line = 3
	i <- 1
	h <- FALSE
	
	for( line in lines ) {
		var <- NULL 
		if( h ) {
			l[["header"]] = line
			l[["ncols"]] = length( strsplit( line, "\t" )[[1]] )
			break
		}
		if( nchar(line) == 0 ) {
			if( i ==5 ) next			# waveform files have a blank line under the date
			h <- TRUE                   # probably a vitals file
			next
		}
		 
		if( i == 1 ) {
			if( line != "Dynamic Research Evaluation Workstation" ) {
				stop("Invalid Guy Drew ASCII file.")
			}
		} else if( i == 2 ) {
			if( startsWith( line, "Vitals Report") ) {
				l[["type"]] <- "vitals"
			} else if( startsWith( line, "Analog Waveform") ) {
				l[["type"]] <- "waveform"
			} else if( startsWith( line, "Notes") ) {
				l[["type"]] <- "notes"
			} else if( startsWith( line, "Electronic Lab Book") ) {
				l[["type"]] <- "book"
			} else {
				stop("Unknown header in Guy Drew ASCII file.")
			}
		} else if ( i == date_line ) {
			val <- parseGuyDrewDate( line )
			var <- "studyDate"
		} else {
		    arr <- strsplit( line, ":" )[[1]]
			var <- gsub("[[:space:]]", "", arr[1] )
			val <- gsub("^[[:space:]]*", "", arr[2] )
		    
			if( var == "SugeryDate") {
				var = "SurgeryDate"  # for programmers who cant spell
			}
 			if( var == "DAQOperator(s)" ) {
				var = "DAQOperator"
			}
		}
		if( !is.null(var) ) {
			l[[var]] <- val
		}
		
		i <- i + 1
	}
	l[["dataStart"]] <- i
	
	l
}
