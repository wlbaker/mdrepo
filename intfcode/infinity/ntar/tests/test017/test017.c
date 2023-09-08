#include <ntar.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	ntar_file_handle *file_handle;
	int ret_value;
	unsigned int num_packets;
	unsigned int packet_size;
	char file_name[256];
	char line[256];
	time_t SystemTime;
	struct tm *lt;

	line[255] = 0;
	
	do
	{	
		printf("Packet size: ");
		fgets(line, 255, stdin);
	}
	while(sscanf(line,"%u", &packet_size) == 0 || packet_size > 1518);

	do
	{	
		printf("Number of packets: ");
		fgets(line, 255, stdin);
	}
	while(sscanf(line,"%u", &num_packets) == 0);

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

	ret_value = ntar_open(file_name,"w",&file_handle);

	if (ret_value == NTAR_SUCCESS)
	{
		ntar_section_handle *section_handle;

		fprintf(stderr, "File created\n");

		ret_value = ntar_create_section(file_handle, &section_handle);

		if (ret_value == NTAR_SUCCESS)
		{
			interface_description_block idb_data;
			ntar_block_handle *block_handle;
			pkt_block pkt_data;
			char packet[1518];
			unsigned int i;

			fprintf(stderr,"Section created\n");

			idb_data.link_type = 2;
			idb_data.snaplen = 96;
			idb_data.reserved = 0;

			ret_value = ntar_create_block(section_handle, BLOCK_ID_IDB, &idb_data, &block_handle);

			if (ret_value == NTAR_SUCCESS)
			{

				ret_value = ntar_close_block(block_handle);

				if (ret_value != NTAR_SUCCESS)
					fprintf(stderr,"ERROR closing block: %d\n", ret_value);
			}			
			else
				fprintf(stderr,"ERROR creating block: %d\n", ret_value);

			pkt_data.captured_len = packet_size;
			pkt_data.drops_count = 0;
			pkt_data.interface_id = 0;
			pkt_data.packet_data = packet;
			pkt_data.packet_len = packet_size;
			pkt_data.timestamp_high = 0;
			pkt_data.timestamp_low = 0;

			memset(packet, rand(),1518);

			for (i = 0; i < num_packets; i++)
			{
				ret_value = ntar_create_block(section_handle, BLOCK_ID_PKTB, &pkt_data, &block_handle);
				if (ret_value == NTAR_SUCCESS)
				{
					ret_value = ntar_close_block(block_handle);

					if (ret_value != NTAR_SUCCESS)
					{
						fprintf(stderr,"ERROR closing block: %d\n", ret_value);
						break;
					}
				}
				else
				{
					fprintf(stderr, "ERROR creating block: %d\n", ret_value);
					break;
				}
			}
			
			ret_value = ntar_close_section(section_handle);

			if (ret_value == NTAR_SUCCESS)
				fprintf(stderr,"Section closed\n");
			else
				fprintf(stderr,"ERROR closing section: %d\n", ret_value);

		}
		else
			fprintf(stderr, "ERROR creating section: %d\n", ret_value);

		ret_value = ntar_close(file_handle);

		if (ret_value == NTAR_SUCCESS)
			fprintf(stderr,"File closed\n");
		else
			fprintf(stderr,"ERROR closing file: %d\n", ret_value);

	}
	else
		fprintf(stderr, "ERROR creating file: %d\n", ret_value);

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
