package ni.DAQcommon;


public interface IFilteredTypeDescriptor {
	ICustomTypeDescriptor getFilteredTypeDescriptor(PropertyFilterType filterType);
	ICustomTypeDescriptor getFilteredTypeDescriptor(PropertyFilterType filterType, PropertyFilterFlags filterFlags);
}
