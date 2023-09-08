package video;

import java.awt.image.BufferedImage;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

import org.bytedeco.javacpp.avcodec;
import org.bytedeco.javacpp.avutil;
import org.bytedeco.javacv.FFmpegFrameRecorder;
import org.bytedeco.javacv.Frame;
import org.bytedeco.javacv.FrameRecorder.Exception;
import org.bytedeco.javacv.Java2DFrameConverter;

public class RgbEncodingProblem {

	public static void main(String [] args) throws Exception {
		int size = 100;

	    BufferedImage img = new BufferedImage( size, size, BufferedImage.TYPE_INT_RGB );
	    for(int y = 0; y < size; y++) {
	        for( int x = 0; x < size; x++ ) {
	            img.setRGB( x, y, 0xe07030 );
	        }
	    }
	    JOptionPane.showMessageDialog( null, new JLabel( new ImageIcon( img ) ) );

	    FFmpegFrameRecorder recorder = new FFmpegFrameRecorder( "test.mp4", 0 );
	    recorder.setFrameRate( 10 );
	    recorder.setImageWidth( size );
	    recorder.setImageHeight( size );
	    recorder.setVideoCodec( avcodec.AV_CODEC_ID_H264 );
	    recorder.setVideoOption( "preset", "veryfast" );
	    
	    recorder.start();

	    Java2DFrameConverter converter = new Java2DFrameConverter();
	    for(int i = 0; i < 10; i++) {
	        Frame frame = converter.convert( img );
		    recorder.record( frame, avutil.AV_PIX_FMT_ARGB );
	    }

	    recorder.stop();
	    recorder.release();
	}
}
