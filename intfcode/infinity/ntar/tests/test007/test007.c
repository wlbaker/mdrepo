#include <ntar.h>

int main()
{
	ntar_file_handle *file_handle;
	int ret_value;


	ret_value = ntar_open("test007.ntar","w",&file_handle);

	if (ret_value == NTAR_SUCCESS)
	{
		ntar_section_handle *section_handle;

		fprintf(stderr, "File created\n");

		ret_value = ntar_create_section(file_handle, &section_handle);

		if (ret_value == NTAR_SUCCESS)
		{
			ntar_block_handle *block_handle;
			interface_description_block idb_data;

			fprintf(stderr,"Section created\n");
			
			idb_data.link_type = 2;
			idb_data.snaplen = 96;
			idb_data.reserved = 0;

			ret_value = ntar_create_block(section_handle, BLOCK_ID_IDB, &idb_data, &block_handle);

			if (ret_value == NTAR_SUCCESS)
			{
				u_int64 speed;
				ntar_option opt1, opt2;
				spb_block spb_data;
				char packet[1000];

				fprintf(stderr,"Block created\n");

				opt1.code = IDB_OPTION_IF_DESCRIPTION;
				opt1.data = "Stupid ethernet interface";

				ret_value = ntar_add_block_option(block_handle, &opt1);
				
				if (ret_value == NTAR_SUCCESS)
					fprintf(stderr,"Block option added\n");
				else
					fprintf(stderr,"ERROR adding block option: %d\n", ret_value);

				speed = 100000000;
				opt2.code = IDB_OPTION_IF_SPEED;
				opt2.data = &speed;
				
				ret_value = ntar_add_block_option(block_handle, &opt2);

				if (ret_value == NTAR_SUCCESS)
					fprintf(stderr, "Added block option\n");
				else
					fprintf(stderr, "ERROR adding block option: %d\n", ret_value);

				ret_value = ntar_close_block(block_handle);

				if (ret_value == NTAR_SUCCESS)
					fprintf(stderr,"Block closed\n");
				else
					fprintf(stderr,"ERROR closing block: %d\n", ret_value);

				spb_data.captured_len = 123;
				spb_data.packet_data = packet;
				spb_data.packet_len = 1000;
	
				ret_value = ntar_create_block(section_handle, BLOCK_ID_SPB, &spb_data, &block_handle);
				
				if (ret_value == NTAR_SUCCESS)
				{

					fprintf(stderr,"Block created\n");

					ret_value = ntar_close_block(block_handle);
					if (ret_value == NTAR_SUCCESS)
						fprintf(stderr,"Block closed\n");
					else
						fprintf(stderr,"ERROR closing block: %d\n", ret_value);

				}
				else
					fprintf(stderr,"ERROR creating block: %d\n", ret_value);

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
