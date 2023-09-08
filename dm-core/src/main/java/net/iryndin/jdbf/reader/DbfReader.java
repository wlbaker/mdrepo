package net.iryndin.jdbf.reader;

import java.io.BufferedInputStream;
import java.io.Closeable;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;

import net.iryndin.jdbf.core.DbfFileTypeEnum;
import net.iryndin.jdbf.core.DbfMetadata;
import net.iryndin.jdbf.core.DbfRecord;
import net.iryndin.jdbf.util.DbfMetadataUtils;

public class DbfReader implements Closeable {

    private InputStream dbfInputStream;
    private MemoReader memoReader;
    private DbfMetadata metadata;
    private byte[] oneRecordBuffer;
    private int recordsCounter = 0;
    private static final int BUFFER_SIZE = 8192;

    public DbfReader(File dbfFile) throws IOException {
        this(new FileInputStream(dbfFile));
    }

    public DbfReader(File dbfFile, File memoFile) throws IOException {
        this(new FileInputStream(dbfFile), new FileInputStream(memoFile));
    }

    public DbfReader(InputStream dbfInputStream) throws IOException {
        this.dbfInputStream = new BufferedInputStream(dbfInputStream, BUFFER_SIZE);
        readMetadata();
    }

    public DbfReader(InputStream dbfInputStream, InputStream memoInputStream) throws IOException {
        this.dbfInputStream = new BufferedInputStream(dbfInputStream, BUFFER_SIZE);
        this.memoReader = new MemoReader(memoInputStream);
        readMetadata();
    }

    public DbfMetadata getMetadata() {
        return metadata;
    }

    private void readMetadata() throws IOException {
        this.dbfInputStream.mark(1024*1024);
        metadata = new DbfMetadata();
        readHeader();
        DbfMetadataUtils.readFields(metadata, dbfInputStream);

        oneRecordBuffer = new byte[metadata.getOneRecordLength()];

        findFirstRecord();
    }

    private void readHeader() throws IOException {
        // 1. Allocate buffer
        byte[] bytes = new byte[16];
        // 2. Read 16 bytes
        dbfInputStream.read(bytes);
        // 3. Fill header fields
        DbfMetadataUtils.fillHeaderFields(metadata, bytes);
        // 4. Read next 16 bytes (for most DBF types these are reserved bytes)
        dbfInputStream.read(bytes);

		// 11-Mar-15 WLB: for DBFv7 files, read the language driver
		if( metadata.getType() == DbfFileTypeEnum.dBASE_LEVEL7 ) {
        	byte[] lang = new byte[36];
        	dbfInputStream.read(lang);

			// expecting DBWINUS0
		}
    }

    @Override
    public void close() throws IOException {
        if (memoReader != null) {
            memoReader.close();
            memoReader = null;
        }
        if (dbfInputStream != null) {
            dbfInputStream.close();
            dbfInputStream = null;
        }
        metadata = null;
        recordsCounter = 0;
    }

    public void findFirstRecord() throws IOException {
        seek(dbfInputStream, metadata.getFullHeaderLength());
    }

    private void seek(InputStream inputStream, int position) throws IOException {
        inputStream.reset();
        inputStream.skip(position);
    }

    public DbfRecord read() throws IOException {
        Arrays.fill(oneRecordBuffer, (byte)0x0);
        int readLength = dbfInputStream.read(oneRecordBuffer);

        if (readLength < metadata.getOneRecordLength()) {
            return null;
        }

        return createDbfRecord();
    }

    private DbfRecord createDbfRecord() {
        return new DbfRecord(oneRecordBuffer, metadata, memoReader, ++recordsCounter);
    }

	public void skip(int count) {
		// FIXME: skip not ready
		System.err.println("FIXME: Not ready");
	}
}
