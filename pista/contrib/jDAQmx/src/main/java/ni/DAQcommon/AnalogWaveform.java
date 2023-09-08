package ni.DAQcommon;

public class AnalogWaveform { // : ICloneable, ISerializable, IServiceProvider {
	double [] data;
	
    @SuppressWarnings("unchecked")
	public AnalogWaveform(int sampleCount) {
    	// data = (T[])new Object[sampleCount];
    	data = new double[sampleCount];
    }
    
//    public String ChannelName { get; set; }
//    public Type getDataType();
//    public ExtendedPropertyDictionary getExtendedProperties() { }
//    public boolean isPrecisionTimingInitialized() { }
//    public PrecisionWaveformTiming PrecisionTiming { get; set; }
    public int getSampleCount() { return data.length; }
//    public AnalogWaveformSampleCollection<T> Samples { get; }
//    public WaveformScaleMode ScaleMode { get; set; }
//    public WaveformTiming Timing { get; set; }
//    public String UnitDescription { get; set; }
//    // public AnalogWaveform<T> Clone();
//    public static void CopySamples(AnalogWaveform<TData> sourceWaveform, AnalogWaveform<TData> destinationWaveform, int sampleCount);
//    public static void CopySamples(AnalogWaveform<TData> sourceWaveform, int sourceSampleIndex, AnalogWaveform<TData> destinationWaveform, int destinationSampleIndex, int sampleCount);
//    public static AnalogWaveform<TData> FromArray1D(TData[] array);
//    public static AnalogWaveform<TData>[] FromArray2D(TData[,] array);
//    public PrecisionDateTime[] GetPrecisionTimeStamps();
//    public PrecisionDateTime[] GetPrecisionTimeStamps(int sampleIndex, int count);
//    public void GetPrecisionTimeStamps(int sampleIndex, int count, PrecisionDateTime[] buffer, int arrayIndex);
    public double [] getRawData() { return data; } 
//    public T[] getRawData(int sampleIndex, int count);
//    public void getRawData(int sampleIndex, int count, TData[] buffer, int arrayIndex);
//    public double[] getScaledData();
//    public double[] getScaledData(int sampleIndex, int count);
//    public void getScaledData(int sampleIndex, int count, double[] buffer, int arrayIndex);
//    public Date[] getTimeStamps();
//    public Date[] getTimeStamps(int sampleIndex, int count);
//    public void getTimeStamps(int sampleIndex, int count, DateTime[] buffer, int arrayIndex);
}
