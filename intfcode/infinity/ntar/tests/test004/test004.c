#include <ntar.h>

int main()
{
	ntar_file_handle *file_handle;
	int ret_value;

	ret_value = ntar_open("test004.ntar","w",&file_handle);

	if (ret_value == NTAR_SUCCESS)
	{
		ntar_section_handle *section_handle;

		fprintf(stderr,"File opened\n");
		
		ret_value = ntar_create_section(file_handle, &section_handle);

		if (ret_value == NTAR_SUCCESS)
		{
			ntar_option opt, opt2;
			fprintf(stderr,"Section created\n");
			
			opt.code = SHB_OPTION_APPLICATION;
			opt.data = "Test004.exe";

			ret_value = ntar_add_section_option(section_handle, &opt);
			if (ret_value == NTAR_SUCCESS)
				fprintf(stderr, "Added section option\n");
			else
				fprintf(stderr, "ERROR adding section option: %d\n", ret_value);

			opt2.code = SHB_OPTION_OS;
			opt2.data = "Windows XP";
			
			ret_value = ntar_add_section_option(section_handle, &opt2);

			if (ret_value == NTAR_SUCCESS)
				fprintf(stderr, "Added section option\n");
			else
				fprintf(stderr, "ERROR adding section option: %d\n", ret_value);

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
