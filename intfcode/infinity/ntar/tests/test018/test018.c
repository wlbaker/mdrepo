#include <ntar.h>
#include <time.h>
#include <string.h>

int main()
{
	ntar_file_handle *file_handle;
	int ret_value;
	char file_name[256];
	time_t SystemTime;
	struct tm *lt;
	unsigned int num_blocks = 0;

	file_name[255] = 0;
	printf("File name: ");
	fgets(file_name, 255, stdin);
	file_name[strlen(file_name) - 1] = 0;

	SystemTime = time(NULL);
	lt = localtime(&SystemTime);

	if (lt != NULL)
 		fprintf(stderr, "Test started at %.04u-%.02u-%.02u %.02u:%02u:%02u\n", 
 			lt->tm_year,
			lt->tm_mon,
			lt->tm_mday,
			lt->tm_hour,
 			lt->tm_min,
			lt->tm_sec);
	else
 		fprintf(stderr,"Test started at <UNKNOWN TIME>\n");

	ret_value = ntar_open(file_name,"r",&file_handle);

	if (ret_value == NTAR_SUCCESS)
	{
		ntar_section_handle *section_handle;

		fprintf(stderr, "File opened\n");

		ret_value = ntar_get_next_section(file_handle, &section_handle);

		if (ret_value == NTAR_SUCCESS)
		{
			ntar_block_handle *block_handle;

			fprintf(stderr,"Section opened\n");

			ret_value = ntar_get_next_block(section_handle, &block_handle);
			
			while(ret_value == NTAR_SUCCESS)
			{
				num_blocks++;
				
				ret_value = ntar_close_block(block_handle);

				if (ret_value != NTAR_SUCCESS)
					fprintf(stderr,"Block closed\n");

				ret_value = ntar_get_next_block(section_handle, &block_handle);
			}

			if (ret_value != NTAR_FAILURE_NOMOREBLOCKS && ret_value != NTAR_FAILURE_EOF)
				fprintf(stderr, "ERROR get next_block returned %d\n", ret_value);

			ret_value = ntar_close_section(section_handle);

			if (ret_value == NTAR_SUCCESS)
				fprintf(stderr,"Section closed\n");
			else
				fprintf(stderr,"ERROR closing section: %d\n", ret_value);
		}

		ret_value = ntar_close(file_handle);

		if (ret_value == NTAR_SUCCESS)
			fprintf(stderr,"File closed\n");
		else
			fprintf(stderr,"ERROR closing file: %d\n", ret_value);
	}
	else
		fprintf(stderr, "ERROR opening file: %d\n", ret_value);


	printf("Number of blocks = %u\n", num_blocks);

	SystemTime = time(NULL);
	lt = localtime(&SystemTime);

	if (lt != NULL)
 		fprintf(stderr, "Test ended at %.04u-%.02u-%.02u %.02u:%02u:%02u\n", 
 			lt->tm_year,
			lt->tm_mon,
			lt->tm_mday,
			lt->tm_hour,
 			lt->tm_min,
			lt->tm_sec);
	else
 		fprintf(stderr,"Test ended at <UNKNOWN TIME>\n");


	return 0;
}
