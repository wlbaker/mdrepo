package org.pistax.test;

import org.pistax.PistaDataPacket;
import org.pistax.PistaDev;
import org.pistax.PistaEventHandler;

import static org.pistax.pista_datatyp.*;

public class PropaqEventHandler extends PistaEventHandler {
	 public int event(PistaDev dev, PistaDataPacket pkt) {
		 System.out.println("data packet: " + pkt );
		 int nfields = pkt.getDescriptorCount();
		 for( int idx = 0; idx < nfields; idx++ ) {
			 String loc = pkt.getDescriptorLoc(idx);
			 int typ = pkt.getFieldSubtyp(idx);
			 System.out.print(loc + ": ");
			 if( typ == INT_TYP ) {
				 System.out.print( "" + pkt.getInt( idx ) );
			 } else if( typ == FLOAT_TYP ) {
				 System.out.print( "" + pkt.getFloat( idx ) );
			 } else if( typ == DOUBLE_TYP ) {
				 System.out.print( "" + pkt.getFloat( idx ) );
			 } else if( typ == LONG_TYP ) {
				 System.out.print( "" + pkt.getLong( idx ) );
			 } else if( typ == STRING_TYP ) {
				 System.out.print( "" + pkt.getString( idx ) );
			 }
			 System.out.println();
			 
		 }
		 
		 System.out.println("total fields: " + nfields );
		 
		 return 0;
	  }

}
