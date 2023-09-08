package dsi;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SeekableByteChannel;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;
import java.util.LinkedList;

import idea.persistmanager.daq.ChannelHelper;
import idea.repository.DaqUtil;

public class PnmWaveformReader {

	private File file;
	private SeekableByteChannel chan;

	public PnmWaveformReader( File file ) {
		this.file = file;
	}
	
	public void rewind() throws IOException {

		close();

		chan = Files.newByteChannel(file.toPath(), StandardOpenOption.READ);

		readHeader();
		readChannels();
	}

	private void readHeader() throws IOException {
		var magic = ChannelHelper.readInt( chan );
		
		System.out.println("MAGIC=" + magic);
		for( var tag : PnmTagReader.readTagBlock( chan, Pnm.Tag.HeaderBegin )) {
			
		}
	}

	private void readChannels() {
		// TODO Auto-generated method stub
		
	}

	public void close() throws IOException {
		if (chan != null) {
			chan.close();
			chan = null;
		}

	}

	public static void main(String[] args) throws IOException {
		File file = new File( "C:\\opt\\study\\burmeister\\Experiment_July17_2019.3809.20190717144703.PnmWav");
		PnmWaveformReader r = new PnmWaveformReader( file );
		r.rewind();

	}

}
