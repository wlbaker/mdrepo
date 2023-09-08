#include <ntar.h>

int main()
{
	ntar_file_handle *file_handle;
	int ret_value;

	ret_value = ntar_open("test012.ntar","w",&file_handle);

	if (ret_value == NTAR_SUCCESS)
	{
		ntar_section_handle *section_handle;

		fprintf(stderr, "File created.\n");
		
		ret_value = ntar_create_section(file_handle, &section_handle);

		if (ret_value == NTAR_SUCCESS)
		{
			ntar_option opt;
			ntar_block_handle *block_handle;
			interface_description_block data;
			
			fprintf(stderr, "Section created\n");

			opt.code = OPTION_COMMENT;
			opt.data = "Hello world";

			ret_value = ntar_add_section_option(section_handle, &opt);

			if (ret_value == NTAR_SUCCESS)
				fprintf(stderr, "Section option added\n");
			else
				fprintf(stderr, "ERROR adding section option: %d\n", ret_value);

			data.link_type = 1240;
			data.snaplen = 124;
			data.reserved = 0;

			ret_value = ntar_create_block(section_handle, BLOCK_ID_IDB, &data, &block_handle);

			if (ret_value == NTAR_SUCCESS)
			{
				u_int64 speed;
				ntar_option bopt, bopt2;

				fprintf(stderr,"Block created\n");

				bopt.code = IDB_OPTION_IF_DESCRIPTION;
				bopt.data = "Stupid ethernet interface";
				ret_value = ntar_add_block_option(block_handle, &bopt );
				
				if (ret_value == NTAR_SUCCESS)
					fprintf(stderr, "Block option added\n");
				else
					fprintf(stderr, "ERROR adding block option: %d\n", ret_value);
				
				speed = 10000000000;

				bopt2.code = IDB_OPTION_IF_SPEED;
				bopt2.data = &speed;

				ret_value = ntar_add_block_option(block_handle, &bopt2 );
				
				if (ret_value == NTAR_SUCCESS)
					fprintf(stderr, "Block option added\n");
				else
					fprintf(stderr, "ERROR adding block option: %d\n", ret_value);
				
				ret_value = ntar_close_block(block_handle);

				if (ret_value == NTAR_SUCCESS)
					fprintf(stderr, "Block closed\n");
				else
					fprintf(stderr, "ERROR closing block: %d\n", ret_value);
			}
			else
				fprintf(stderr, "ERROR creating block: %d\n", ret_value);

			ret_value = ntar_close_section(section_handle);
			if (ret_value == NTAR_SUCCESS)
				fprintf(stderr, "Section closed\n");
			else
				fprintf(stderr, "ERROR closing section: %d\n", ret_value);
		}
		else
			fprintf(stderr, "ERROR creating section: %d\n", ret_value);

		ret_value = ntar_close(file_handle);
		if (ret_value == NTAR_SUCCESS)
			fprintf(stderr, "File closed\n");
		else
			fprintf(stderr, "ERROR closing file: %d\n", ret_value);

	}
	else
		fprintf(stderr, "ERROR creating file: %d\n", ret_value);

	return 0;
}
