package idea.analysis.ecg;

import no.uib.cipr.matrix.DenseMatrix;
import no.uib.cipr.matrix.DenseVector;

public class RRIQuadraticSolver {

	private static final int QUADRATIC = 3;
	private int dimension;
	private double [] d;
	private double [] t; 
	private int n = 0;
	private DenseMatrix m;
	
	// based on the formula y = a*x**2 + b*x + c
	double a,b,c;
	double errsq = 0.0;
	
	public RRIQuadraticSolver( int dimension ) {
		this.dimension = dimension;
		d = new double[dimension];
		t = new double[dimension];
		
		for( int i = 0; i < dimension ; i++ ) {
			t[i] = i;
		}

		// hmmm....you only need t and the dimension to calculate the matrix coefficients
		double [][] coeff = { 
				{ 0.0, 0.0, 0.0 },
				{ 0.0, 0.0, 0.0 },
				{ 0.0, 0.0, 0.0 }
		};
		
		coeff[0][0] = dimension;
		coeff[0][1] = sum( t );           // sum(t(1:n)); 
		coeff[0][2] = dot_product(t,t) ;  // dot_product(t(1:n),t(1:n)); 

		coeff[1][0] = coeff[0][1];
		coeff[1][1] = coeff[0][2];

		coeff[1][2] = dot_cube( t, t, t );     //  sum(t(1:n)**3); 

		coeff[2][0] = coeff[0][2];
		coeff[2][1] = coeff[1][2];

		coeff[2][2] = dot_4th( t );     // sum(t(1:n)**4); 

		m = new DenseMatrix(coeff);
	}
	
	public void add( double rri ) {
		
		for( int i = 0; i < dimension - 1; i++ ) {
			d[i] = d[i+1];
		}
		d[dimension-1] = rri;
		
		if( n < dimension - 1 ) {
			n++;
		} else {
			solve();
		}
	}
	
	private void solve() {
		double [] rhs = new double[QUADRATIC];
		
		rhs[0] = sum(d);              // sum(d(1:n));
		rhs[1] = dot_product( d, t ); // d(1:n)*t(1:n)); 
		rhs[2] = dot_cube(d, t, t);    // sum ( d(1:n)*t(1:n)**2);

		DenseVector rhsv = new DenseVector(rhs);
		DenseVector solution = new DenseVector(QUADRATIC);
		m.solve(rhsv, solution );
		
		//DenseVector rri = new DenseVector(d);
		//System.out.println( "rri=" + rri );
		// System.out.println( "b=" + rhsv );
		//System.out.println( "solution =" + solution );
		
		a = solution.get(0);
		b = solution.get(1);
		c = solution.get(2);
		
		for( int i=0; i < dimension ; i++ ) {
			double err = c * t[i] * t[i] + b* t[i] + a - d[i];
			errsq += err*err;
		}
		
		process( a,b,c, errsq );
		/*
		DenseMatrix i = Matrices.identity(3);
		DenseMatrix i2 = Matrices.identity(3);
		DenseMatrix mi = Matrices.identity(3);
		m.solve( i, mi );
		System.out.println( "identify =" + i );
		System.out.println( "inverse =" + mi );
		m.mult( mi, i2 );
		System.out.println( "i2 =" + i2 );
		mi.mult( rhsv, outv );
		System.out.println( "outv =" + outv );
		*/

	}
	
	public void process(double a, double b, double c, double errsq) {
		// System.out.println( "abc = (" + a + "," + b + "," + c + ") errsq=" + errsq );
	}

	private double sum( double [] v ) {
		double s = 0.0;
		for( double val : v ) {
			s += val;
		}
		
		return s;
	}

	private double dot_product( double [] a, double [] b ) {
		double s = 0.0;
		for( int i=0; i < a.length ; i++) {
			s += a[i] * b[i];
		}
		
		return s;
	}

	private double dot_cube( double [] a, double [] b, double [] c ) {
		double s = 0.0;
		for( int i=0; i < a.length ; i++) {
			s += a[i] * b[i] * c[i];
		}
		
		return s;
	}
	
	private double dot_4th( double [] v ) {
		double s = 0.0;
		for( double val : v ) {
			s += val * val * val * val;
		}
		
		return s;
	}

	public int getDim() {
		return dimension;
	}

	public double getErrorSquared() {
		return errsq;
	}

	public double evaluate(double x) {
		// return a*x*x + b*x + c;
		return a + b*x + c*x*x;
	}
}
