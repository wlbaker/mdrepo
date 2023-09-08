package experiment;

import java.io.File;

import org.bytedeco.javacpp.avcodec;
import org.bytedeco.javacv.FFmpegFrameRecorder;

import lombok.Getter;
import lombok.Setter;

public class AltOut {
	@Getter
	@Setter
	private File file;
	private FFmpegFrameRecorder enc;
	private int sampleAudioRateInHz = 11025;
	private int audioChannels = 3;
	
	public void initVideo() {
		int imageWidth = 100;
		int imageHeight = 100;
		int frameRate = 20;
		
		enc = new FFmpegFrameRecorder(file, imageWidth, imageHeight);

		// enc.setFormat("mp4");

		// recorder.setSampleRate(sampleAudioRateInHz);
		enc.setImageWidth(imageWidth);
		enc.setImageHeight(imageHeight);

		// re-set in the surface changed method as well
		enc.setVideoCodec(avcodec.AV_CODEC_ID_H264);
		enc.setFrameRate(frameRate);
		enc.setVideoBitrate(200000);
		// enc.setVideoQuality(0.8);
		
	}
	
	void initAudio() {
		
		//recorder = new FFmpegFrameRecorder(ffmpeg_link, imageWidth, imageHeight, 1); 
        enc.setFormat("flv"); 
        enc.setSampleRate(sampleAudioRateInHz); 
        // Set in the surface changed method 
        // recorder.setFrameRate(frameRate); 
        
		enc.setAudioChannels(audioChannels);
		// Create audio recording thread
		//audioRecordRunnable = new AudioRecordRunnable();
		//audioThread = new Thread(audioRecordRunnable);

	}

	public static void main(String[] args) {
		AltOut ao = new AltOut();
		ao.setFile( new File("/tmp/ao.mp4"));
	}

}
