#include <ntar.h>

int main()
{
	ntar_file_handle *file_handle;
	int ret_value;

	ret_value = ntar_open("test013_in.ntar","r",&file_handle);

	if (ret_value == NTAR_SUCCESS)
	{
		ntar_section_handle *section_handle;

		fprintf(stderr, "File opened\n");

		ret_value = ntar_get_next_section(file_handle, &section_handle);
		while( ret_value == NTAR_SUCCESS)
		{
			ntar_block_handle *block_handle;
			ntar_option *options;

			fprintf(stderr,"Section opened\n");

			ret_value = ntar_get_next_block(section_handle, &block_handle);

			while(ret_value == NTAR_SUCCESS)
			{
				u_int32 block_type;			

				fprintf(stderr,"Block opened\n");

				ret_value = ntar_get_block_type(block_handle, &block_type);

				if (ret_value == NTAR_SUCCESS)
				{
					fprintf(stderr, "Retrieved block type\n");
					if (block_type == BLOCK_ID_IDB)
					{
						interface_description_block *idb;
	
						ret_value = ntar_get_block_data(block_handle, (void**)&idb);

						if (ret_value == NTAR_SUCCESS)
                            fprintf(stderr, "Snaplen %d - linktype %d\n", idb->snaplen, idb->link_type);
						else
							fprintf(stderr, "ERROR retrieving block data\n");
					}
				}
				else
					fprintf(stderr, "ERROR retrieving block type: %d\n", ret_value);

				ret_value = ntar_get_block_options(block_handle, &options);

				if (ret_value == NTAR_SUCCESS)
				{
					fprintf(stderr, "Block options retrieved\n");
					while (options != NULL)
					{
						fprintf(stderr, "Option code %u\n", options->code);
						options = options->next;
					}
				}
				else
					fprintf(stderr,"ERROR retrieving block options: %d\n", ret_value);

				ret_value =	ntar_close_block(block_handle);

				if (ret_value == NTAR_SUCCESS)
					fprintf(stderr,"Block closed\n");
				else
					fprintf(stderr,"ERROR closing block: %d\n", ret_value);

				ret_value = ntar_get_next_block(section_handle, &block_handle);
			}

			if (ret_value != NTAR_FAILURE_NOMOREBLOCKS && ret_value != NTAR_FAILURE_EOF)
				fprintf(stderr, "ERROR get_next block returned %d\n", ret_value);
            
			ret_value = ntar_close_section(section_handle);

			if (ret_value == NTAR_SUCCESS)
				fprintf(stderr,"Section closed\n");
			else
				fprintf(stderr,"ERROR closing section: %d\n", ret_value);
	
			ret_value = ntar_get_next_section(file_handle, &section_handle);
		}

		ret_value = ntar_close(file_handle);

		if (ret_value == NTAR_SUCCESS)
			fprintf(stderr,"File closed\n");
		else
			fprintf(stderr,"ERROR closing file: %d\n", ret_value);
	}
	else
		fprintf(stderr, "ERROR opening file: %d\n", ret_value);
	return 0;
}

