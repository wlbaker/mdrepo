/*
 * Created on Apr 5, 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package idea;

import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Calendar;
import java.util.Date;

import javax.imageio.ImageIO;
import javax.imageio.ImageReader;
import javax.imageio.stream.ImageInputStream;

import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.JRRewindableDataSource;

//import com.sun.image.codec.jpeg.ImageFormatException;
//import com.sun.image.codec.jpeg.JPEGCodec;
//import com.sun.image.codec.jpeg.JPEGImageDecoder;


/**
 * @author bbaker
 *  
 */
public class ReportHelper {

	public static JRRewindableDataSource rewind( JRRewindableDataSource rewindable ) {
		try {
			rewindable.moveFirst();
		} catch (JRException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return rewindable;
	}
	
    public static Date addDate( Date dt, int calField, int delta ) {
        Calendar cal = Calendar.getInstance();
        if( dt != null) cal.setTime( dt );
        cal.add( calField, delta);
        dt = cal.getTime();
        
        return dt;
    }
    
    public static String lpad(String s, int length, char pad) {
    	StringBuffer buffer = new StringBuffer(s);
    	while (buffer.length() < length) {
    		buffer.insert(0, pad);
    	}
    	return buffer.toString();
    }
    
    public static String getFormattedAddressFromEmployeeNo(Connection conn, int empNo ) {

        final String sql = "select "
            + " emp.ADDRESS1, emp.ADDRESS2, emp.CITY, emp.ST, emp.ZIP"
            + " from EMPLOYE2 emp"
            + " where emp.EMP_NO=?"
            ;

        String szAddress = "<none>";

        PreparedStatement pstmt;
        try {
            
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, empNo );
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                String addr1 = rs.getString(1);
                String addr2 = rs.getString(2);
                String city = rs.getString(3);
                String st = rs.getString(4);
                String zip = rs.getString(5);

                szAddress =addr1 + "\n";
                if (addr2 != null && addr2.trim().length() > 0) szAddress += addr2 + "\n";
                szAddress += city + ", " + st + " " + zip;

            }
            rs.close();
            pstmt.close();
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        return szAddress;
    }
    
    public static String getSysFileValue(Connection conn, int div, String paramName ) {

        if (conn == null){
    		try {
                Class.forName("com.mysql.jdbc.Driver");
        		conn = DriverManager.getConnection("jdbc:mysql://replica.priefert.com/MyDataMode?user=bbaker&password=12345");
            } catch (Exception e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }	
        }
    	
    	final String sql = "select sf.VALUE"
            + " from SYSFILE sf"
            + " where sf.DIV = ? and sf.NAME=?"
            ;

        String value = "(unspecified)";
        
        PreparedStatement pstmt;
        try {
            
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, div );
            pstmt.setString(2, paramName );
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                value = rs.getString(1);
            }
            rs.close();
            pstmt.close();
        } catch (SQLException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        return value;
    }
    

    
    public static Image getEmployeeImage(Connection conn, int iDiv, String szEmpNo) {
    	
        Image image = null;
        
        final String sql = "select PHOTO from EMPLOYE_P where `DIV`=? and `EMP_NO`=?";
        
        PreparedStatement pstmt;
        try {
            
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, iDiv);
            pstmt.setString(2, szEmpNo);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                InputStream is = rs.getBinaryStream(1);
                if( is != null ) {
	                // FileImageInputStream out = new FileImageInputStream( is );
                	
                	// fancy footwork, though I don't know if it actually works or not!
	            	ImageReader decoder = (ImageReader)ImageIO.getImageReadersByFormatName("JPEG").next();
	            	ImageInputStream _iis = ImageIO.createImageInputStream( is);
	            	decoder.setInput(_iis, true, true);
	            	
	            	BufferedImage buffered = decoder.read(0);
	            	// ImageIcon imageIcon = new ImageIcon();
	            	// imageIcon.setImage( decoder.read(0));
	            	image = buffered; // imageIcon.getImage();
	            	
	                // JPEGImageDecoder decoder = JPEGCodec.createJPEGDecoder( is );
	                //image = decoder.decodeAsBufferedImage();

	            	/*
	            	JPEGImageWriteParam param = new JPEGImageWriteParam(null);

	            	param.setCompressionMode(ImageWriteParam.MODE_EXPLICIT);
	            	param.setCompressionQuality(compression);

	            	encoder.setOutput(out);
	            	encoder.write((IIOMetadata) null, new IIOImage(image,null,null), param);

	            	out.close();
	            	*/
                } else {
                    System.out.println( "no image for: " + szEmpNo );
                }
            }
            rs.close();
            pstmt.close();
        } catch ( SQLException e ) {
            e.printStackTrace();            
//        } catch (ImageFormatException e) {
//            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        return image;
    }
    
    public static File getDefaultBaseDir( String child ) {
    	File baseDir = getDefaultBaseDir();
    	baseDir = new File( baseDir, child );
    	return baseDir;
    }
    
    public static File getDefaultBaseDir() {

    	File baseDir = null;
    	String workspaceName = "reports";
    	
    	Object area = System.getProperty( "osgi.instance.area" );
    	if( area != null ) {
    		String fileName = (String)area;
    		if( fileName.startsWith("file:") ) {
    			fileName = fileName.replaceFirst("file:", "");
    		}
    		File parent = new File( fileName );
    		baseDir = new File( parent, workspaceName );
    	}
    	
        return baseDir;
    }

}
