#include <ntar.h>

int main()
{
	ntar_file_handle *file_handle;
	int ret_value;

	ret_value = ntar_open(NULL,"r",&file_handle);

	if (ret_value == NTAR_SUCCESS)
	{
		ntar_section_handle *section_handle;

		fprintf(stderr, "File opened\n");

		ret_value = ntar_get_next_section(file_handle, &section_handle);

		while( ret_value == NTAR_SUCCESS)
		{
			ntar_option *options;

			fprintf(stderr,"Section opened\n");

			ret_value = ntar_get_section_options(section_handle, &options);

			if (ret_value == NTAR_SUCCESS)
			{
				fprintf(stderr, "Section options retrieved\n");
				while (options != NULL)
				{
					fprintf(stderr, "Option code %u\n", options->code);
					options = options->next;
				}
			}
			else
				fprintf(stderr,"ERROR retrieving section options: %d\n", ret_value);

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

