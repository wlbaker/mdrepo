package idea.persistmanager.daq;

/*
 * libcommon
 * utility/helper classes for myself
 *
 * Copyright (c) 2014-2017 saki t_saki@serenegiant.com
 * Licensed under the Apache License, Version 2.0 (the "License");
*/

//import android.support.annotation.NonNull;
//import android.support.annotation.Nullable;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.CharBuffer;
import java.nio.DoubleBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.nio.LongBuffer;
import java.nio.ShortBuffer;
import java.nio.channels.ByteChannel;
import java.nio.charset.Charset;

/**
 */
public class ChannelHelper {
	private static final Charset UTF8 = Charset.forName("UTF-8");

	/**
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static boolean readBoolean(final ByteChannel channel) throws IOException {

		return readBoolean(channel, null);
	}

	/**
	 * 
	 * @param channel
	 * @param work
	 * @return
	 * @throws IOException
	 */
	public static boolean readBoolean(final ByteChannel channel, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 1);
		final int readBytes = channel.read(buf);
		if (readBytes != 1)
			throw new IOException();
		buf.clear();
		return buf.get() != 0;
	}

	/**
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static byte readByte(final ByteChannel channel) throws IOException {

		return readByte(channel, null);
	}

	/**
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static byte readByte(final ByteChannel channel, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 1);
		final int readBytes = channel.read(buf);
		if (readBytes != 1)
			throw new IOException();
		buf.clear();
		return buf.get();
	}

	/**
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static char readChar(final ByteChannel channel) throws IOException {

		return readChar(channel, null);
	}

	/**
	 * 
	 * @param channel
	 * @param work
	 * @return
	 * @throws IOException
	 */
	public static char readChar(final ByteChannel channel, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 2);
		final int readBytes = channel.read(buf);
		if (readBytes != 2)
			throw new IOException();
		buf.clear();
		return buf.getChar();
	}

	/**
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static short readShort(final ByteChannel channel) throws IOException {

		return readShort(channel, null);
	}

	/**
	 * 
	 * @param channel
	 * @param work
	 * @return
	 * @throws IOException
	 */
	public static short readShort(final ByteChannel channel, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 2);
		final int readBytes = channel.read(buf);
		if (readBytes != 2)
			throw new IOException();
		buf.clear();
		return buf.getShort();
	}

	/**
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static int readInt(final ByteChannel channel) throws IOException {

		return readInt(channel, null);
	}

	/**
	 * 
	 * @param channel
	 * @param work
	 * @return
	 * @throws IOException
	 */
	public static int readInt(final ByteChannel channel, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 4);
		final int readBytes = channel.read(buf);
		if (readBytes != 4)
			throw new IOException();
		buf.clear();
		return buf.getInt();
	}

	/**
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static long readLong(final ByteChannel channel) throws IOException {

		return readLong(channel, null);
	}

	/**
	 * 
	 * @param channel
	 * @param work
	 * @return
	 * @throws IOException
	 */
	public static long readLong(final ByteChannel channel, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 8);
		final int readBytes = channel.read(buf);
		if (readBytes != 8)
			throw new IOException();
		buf.clear();
		return buf.getLong();
	}

	/**
	 * ByteChannel float
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static float readFloat(final ByteChannel channel) throws IOException {

		final ByteBuffer buf = ByteBuffer.allocate(4);
		final int readBytes = channel.read(buf);
		if (readBytes != 4)
			throw new IOException();
		buf.clear();
		return buf.getFloat();
	}

	/**
	 * ByteChannel float
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static float readFloat(final ByteChannel channel, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 4);
		final int readBytes = channel.read(buf);
		if (readBytes != 4)
			throw new IOException();
		buf.clear();
		return buf.getFloat();
	}

	/**
	 * ByteChannel double
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static double readDouble(final ByteChannel channel) throws IOException {

		return readDouble(channel, null);
	}

	/**
	 * ByteChannel double
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static double readDouble(final ByteChannel channel, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 8);
		final int readBytes = channel.read(buf);
		if (readBytes != 8)
			throw new IOException();
		buf.clear();
		return buf.getDouble();
	}

	/**
	 * ByteChannel String
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static String readString(final ByteChannel channel) throws IOException {

		final int bytes = readInt(channel);
		final byte[] buf = new byte[bytes];
		final ByteBuffer b = ByteBuffer.wrap(buf);
		final int readBytes = channel.read(b);
		if (readBytes != bytes)
			throw new IOException();
		return new String(buf, UTF8);
	}

	/**
	 * ByteChannel boolean
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static boolean[] readBooleanArray(final ByteChannel channel) throws IOException {

		final int n = readInt(channel);
		final ByteBuffer buf = ByteBuffer.allocate(n);
		final int readBytes = channel.read(buf);
		if (readBytes != n)
			throw new IOException();
		buf.clear();
		final boolean[] result = new boolean[n];
		for (int i = 0; i < n; i++) {
			result[i] = buf.get() != 0;
		}
		return result;
	}

	/**
	 * ByteChannel byte
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static byte[] readByteArray(final ByteChannel channel) throws IOException {

		final int n = readInt(channel);
		final byte[] result = new byte[n];
		final ByteBuffer buf = ByteBuffer.wrap(result);
		final int readBytes = channel.read(buf);
		if (readBytes != n)
			throw new IOException();
		return result;
	}

	/**
	 * ByteChannel char
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static char[] readCharArray(final ByteChannel channel) throws IOException {

		final int n = readInt(channel);
		final ByteBuffer buf = ByteBuffer.allocate(n * 2).order(ByteOrder.BIG_ENDIAN);
		final int readBytes = channel.read(buf);
		if (readBytes != n * 2)
			throw new IOException();
		buf.clear();
		final CharBuffer result = buf.asCharBuffer();
		if (result.hasArray()) {
			return result.array();
		} else {
			final char[] b = new char[n];
			result.get(b);
			return b;
		}
	}

	/**
	 * ByteChannel short
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static short[] readShortArray(final ByteChannel channel) throws IOException {

		final int n = readInt(channel);
		final ByteBuffer buf = ByteBuffer.allocate(n * 2).order(ByteOrder.BIG_ENDIAN);
		final int readBytes = channel.read(buf);
		if (readBytes != n * 2)
			throw new IOException();
		buf.clear();
		final ShortBuffer result = buf.asShortBuffer();
		if (result.hasArray()) {
			return result.array();
		} else {
			final short[] b = new short[n];
			result.get(b);
			return b;
		}
	}

	/**
	 * ByteChannel int
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static int[] readIntArray(final ByteChannel channel) throws IOException {

		final int n = readInt(channel);
		final ByteBuffer buf = ByteBuffer.allocate(n * 4).order(ByteOrder.BIG_ENDIAN);
		final int readBytes = channel.read(buf);
		if (readBytes != n * 4)
			throw new IOException();
		buf.clear();
		final IntBuffer result = buf.asIntBuffer();
		if (result.hasArray()) {
			return result.array();
		} else {
			final int[] b = new int[n];
			result.get(b);
			return b;
		}
	}

	/**
	 * ByteChannel long
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static long[] readLongArray(final ByteChannel channel) throws IOException {

		final int n = readInt(channel);
		final ByteBuffer buf = ByteBuffer.allocate(n * 8).order(ByteOrder.BIG_ENDIAN);
		final int readBytes = channel.read(buf);
		if (readBytes != n * 8)
			throw new IOException();
		buf.clear();
		final LongBuffer result = buf.asLongBuffer();
		if (result.hasArray()) {
			return result.array();
		} else {
			final long[] b = new long[n];
			result.get(b);
			return b;
		}
	}

	/**
	 * ByteChannel float
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static float[] readFloatArray(final ByteChannel channel) throws IOException {

		final int n = readInt(channel);
		final ByteBuffer buf = ByteBuffer.allocate(n * 4).order(ByteOrder.BIG_ENDIAN);
		final int readBytes = channel.read(buf);
		if (readBytes != n * 4)
			throw new IOException();
		buf.clear();
		final FloatBuffer result = buf.asFloatBuffer();
		if (result.hasArray()) {
			return result.array();
		} else {
			final float[] b = new float[n];
			result.get(b);
			return b;
		}
	}

	/**
	 * ByteChannel double
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static double[] readDoubleArray(final ByteChannel channel) throws IOException {

		final int n = readInt(channel);
		final ByteBuffer buf = ByteBuffer.allocate(n * 8).order(ByteOrder.BIG_ENDIAN);
		final int readBytes = channel.read(buf);
		if (readBytes != n * 8)
			throw new IOException();
		buf.clear();
		final DoubleBuffer result = buf.asDoubleBuffer();
		if (result.hasArray()) {
			return result.array();
		} else {
			final double[] b = new double[n];
			result.get(b);
			return b;
		}
	}

	/**
	 * ByteChannel ByteBuffer
	 * 
	 * @param channel
	 * @return
	 * @throws IOException
	 */
	public static ByteBuffer readByteBuffer(final ByteChannel channel) throws IOException {

		return readByteBuffer(channel, null, true);
	}

	/**
	 * ByteChannel ByteBuffer throwsIOException
	 * 
	 * @param channel
	 * @param buf
	 * @return
	 * @throws IOException
	 */
	public static ByteBuffer readByteBuffer(final ByteChannel channel, final ByteBuffer buf) throws IOException {

		return readByteBuffer(channel, buf, false);
	}

	/**
	 * ByteChannel ByteBuffer
	 * 
	 * @param channel
	 * @param readBuf
	 * @param canReAllocate
	 * @return
	 * @throws IOException
	 */
	public static ByteBuffer readByteBuffer(final ByteChannel channel, final ByteBuffer readBuf,
			final boolean canReAllocate) throws IOException {

		final int n = readInt(channel);
		final int pos = readBuf != null ? readBuf.position() : 0;
		ByteBuffer buf = readBuf;
		if ((buf == null) || (buf.remaining() < n)) {
			if (canReAllocate) {
				if (buf == null) {
					buf = ByteBuffer.allocateDirect(n);
				} else {
					final ByteBuffer temp = ByteBuffer.allocateDirect(readBuf.limit() + n);
					buf.flip();
					temp.put(buf);
					buf = temp;
				}
			} else {
				throw new IOException();
			}
		}
		buf.limit(pos + n);
		final int readBytes = channel.read(buf);
		if (readBytes != n)
			throw new IOException();
		buf.position(pos);
		buf.limit(pos + n);
		return buf;
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final boolean value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final boolean value, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 1);
		buf.put((byte) (value ? 1 : 0));
		buf.flip();
		channel.write(buf);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final byte value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final byte value, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 1);
		buf.put(value);
		buf.flip();
		channel.write(buf);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final char value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final char value, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 2);
		buf.putChar(value);
		buf.flip();
		channel.write(buf);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final short value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final short value, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 2);
		buf.putShort(value);
		buf.flip();
		channel.write(buf);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final int value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final int value, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 4);
		buf.putInt(value);
		buf.flip();
		channel.write(buf);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final long value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final long value, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 8);
		buf.putLong(value);
		buf.flip();
		channel.write(buf);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final float value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final float value, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 4);
		buf.putFloat(value);
		buf.flip();
		channel.write(buf);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final double value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final double value, final ByteBuffer work) throws IOException {

		final ByteBuffer buf = checkBuffer(work, 8);
		buf.putDouble(value);
		buf.flip();
		channel.write(buf);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final String value) throws IOException {

		final byte[] buf = value.getBytes(UTF8);
		write(channel, buf.length);
		channel.write(ByteBuffer.wrap(buf));
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final boolean[] value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final boolean[] value, final ByteBuffer work)
			throws IOException {

		final int n = value.length;
		write(channel, n, work);
		final ByteBuffer buf = checkBuffer(work, n);
		for (int i = 0; i < n; i++) {
			buf.put((byte) (value[i] ? 1 : 0));
		}
		buf.flip();
		channel.write(buf);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final byte[] value) throws IOException {

		write(channel, value.length);
		channel.write(ByteBuffer.wrap(value));
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final char[] value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final char[] value, final ByteBuffer work) throws IOException {

		final int n = value.length;
		write(channel, n, work);
		final ByteBuffer buf = checkBuffer(work, n * 2);
		for (int i = 0; i < n; i++) {
			buf.putChar(value[i]);
		}
		buf.flip();
		channel.write(buf);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final short[] value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final short[] value, final ByteBuffer work) throws IOException {

		final int n = value.length;
		write(channel, n, work);
		final ByteBuffer buf = checkBuffer(work, n * 2);
		for (int i = 0; i < n; i++) {
			buf.putShort(value[i]);
		}
		buf.flip();
		channel.write(buf);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final int[] value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final int[] value, final ByteBuffer work) throws IOException {

		final int n = value.length;
		write(channel, n, work);
		final ByteBuffer buf = checkBuffer(work, n * 4);
		for (int i = 0; i < n; i++) {
			buf.putInt(value[i]);
		}
		buf.flip();
		channel.write(buf);
	}

	/**
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final long[] value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * 
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final long[] value, final ByteBuffer work) throws IOException {

		final int n = value.length;
		write(channel, n, work);
		final ByteBuffer buf = checkBuffer(work, n * 8);
		for (int i = 0; i < n; i++) {
			buf.putLong(value[i]);
		}
		buf.flip();
		channel.write(buf);
	}

	/**
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final float[] value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final float[] value, final ByteBuffer work) throws IOException {

		final int n = value.length;
		write(channel, n, work);
		final ByteBuffer buf = checkBuffer(work, n * 4);
		for (int i = 0; i < n; i++) {
			buf.putFloat(value[i]);
		}
		buf.flip();
		channel.write(buf);
	}

	/**
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final double[] value) throws IOException {

		write(channel, value, null);
	}

	/**
	 * @param channel
	 * @param value
	 * @param work
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final double[] value, final ByteBuffer work)
			throws IOException {

		final int n = value.length;
		write(channel, n, work);
		final ByteBuffer buf = checkBuffer(work, n * 8);
		for (int i = 0; i < n; i++) {
			buf.putDouble(value[i]);
		}
		buf.flip();
		channel.write(buf);
	}

	/**
	 * @param channel
	 * @param value
	 * @throws IOException
	 */
	public static void write(final ByteChannel channel, final ByteBuffer value) throws IOException {

		write(channel, value.remaining());
		channel.write(value);
	}

	/**
	 * @param work
	 * @param sz
	 * @return
	 */
	private static ByteBuffer checkBuffer(final ByteBuffer work, final int sz) {

		ByteBuffer buf = work;
		if ((buf == null) || (work.capacity() < sz)) {
			buf = ByteBuffer.allocateDirect(sz);
		}
		buf.order(ByteOrder.BIG_ENDIAN);
		buf.clear();
		buf.limit(sz);
		return buf;
	}
}