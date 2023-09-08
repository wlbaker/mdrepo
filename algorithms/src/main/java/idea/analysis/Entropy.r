# this routine is close...but it might be missing an endpoint

sampen <- function( signal = rnorm(10), r=0.2, M=2, n=length(signal) ) {
	entropy = -1e100
		
	M = M+1;
	run = rep( 0, n )
	lastrun = rep( 0, n)
	A = rep( 0, M )
	B = rep( 0, M )
	p = rep( 0, M )

	# WARNING: should this be 1:(n+1) ???
    for (i in (1L:n) ) {
		nj = n - i;
		y1 = signal[i];

		for ( jj in (1:nj) ) {
			j = jj + i - 1;
			y_j = signal[j]
			
			#xx <- sprintf( " loop: (%d,%d) j=%d", i, jj, j)
			#print( xx )
			
			if ( abs(y_j - y1) < r) {
				
				#xx <- sprintf( "  comparing %f =? %f   diff=%f", y_j, y1, abs(y_j - y1) )
				#print( xx )
				
				run[jj] = lastrun[jj] + 1
				M1 = min( M, run[jj] )
		
				for (m in (1:M1) ) {
					A[m] = A[m] + 1
					if (j < n ) {
						B[m] = B[m] + 1
					}
				}
			} else {
				run[jj] = 0
			}
			
		} # for jj 
								
		# print( "outer loop: i=%d, nj=%d, y1=%f\n", i, nj, y1);
	
		for ( j in (1:nj) ) {
			lastrun[j] = run[j];
		}
	} # for i
			
		N = (n * (n - 1) / 2)
		p[0] = A[0] / N

		entropy = -log(p[0])
	# out.format("SampEn(0,%g,%d) = %f\n", r, n, entropy);

	print( "final results")
	for (m in (2:M) ) {
		xx <- sprintf( "%d --> %f / %f", m, A[m], B[m-1])
		print( xx )
		
		p[m] = A[m] / B[m - 1]
		if (p[m] == 0) {
			entropy = 1e100
			print("No matches! = Inf!\n")
		} else {
			entropy = -log(p[m])
		}
	}
	
	entropy
}

