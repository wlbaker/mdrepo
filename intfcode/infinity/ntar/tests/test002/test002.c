#include <ntar.h>

int main()
{
	ntar_file_handle *file_handle;
	int ret_value;

	ret_value = ntar_open("test002.ntar","w",&file_handle);

	if (ret_value == NTAR_SUCCESS)
	{
		ntar_section_handle *section_handle;

		fprintf(stderr, "File created\n");

		ret_value = ntar_create_section(file_handle, &section_handle);

		if (ret_value == NTAR_SUCCESS)
		{
			ntar_block_handle *block_handle;
			interface_description_block idb;
			
			memset(&idb, 0, sizeof(idb));

			fprintf(stderr,"Section created\n");
			
			ret_value = ntar_create_block(section_handle, BLOCK_ID_IDB, &idb, &block_handle);

			if (ret_value == NTAR_SUCCESS)
			{
				fprintf(stderr, "Block created\n");
				ret_value = ntar_close_block(block_handle);

				if (ret_value == NTAR_SUCCESS)
					fprintf(stderr,"Block closed\n");
				else
					fprintf(stderr,"ERROR closing block: %d\n", ret_value);
			}
			else
				fprintf(stderr,"ERROR creating block: %d\n", ret_value);

				ret_value = ntar_close_section(section_handle);
				if (ret_value == NTAR_SUCCESS)
					fprintf(stderr,"Section closed\n");
				else
					fprintf(stderr,"ERROR closing section: %d\n", ret_value);
		}
		else
			fprintf(stderr,"ERROR creating section: %d\n", ret_value);

		ret_value = ntar_close(file_handle);

		if (ret_value == NTAR_SUCCESS)
			fprintf(stderr,"File closed\n");
		else
			fprintf(stderr,"ERROR closing file: %d\n", ret_value);


	}
	else
		fprintf(stderr,"ERROR creating file: %d\n", ret_value);
	return 0;
}
