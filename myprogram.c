#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    char *input_name = NULL;
    char *output_name = NULL;

    int size = 4096;
    int opt;
    while ((opt = getopt(argc, argv, "s:")) != -1)
    {
        switch (opt)
        {
            case 's':
                size = atoi(optarg);
                break;
            default:
                perror("Unknown option");
				exit(EXIT_FAILURE);
        }
    }
    
	for (;optind < argc; optind++) {
		char *file = (char *) malloc(strlen(argv[optind]) + 1);
		strcpy(file, argv[optind]);
		if (input_name == NULL) {
			input_name = file;
			continue;
		}
		if (output_name == NULL) {
			output_name = file;
			continue;
		}
		perror("Extra parametr");
		exit(EXIT_FAILURE);
	}
    
    if (input_name != NULL && output_name == NULL) {
        output_name = input_name;
        input_name = NULL;
    }
    if (output_name == NULL || input_name != NULL && 
        strcmp(input_name, output_name) == 0 || size < 1){
        perror("Error in parametrs");
		exit(EXIT_FAILURE);
	}

    int input_fd = STDIN_FILENO;
    int output_fd;
    
    if (input_name != NULL)
        input_fd = open(input_name, O_RDONLY);
        output_fd = open(output_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (input_fd == -1 || output_fd == -1){
        perror("File open error");
		exit(EXIT_FAILURE);
	}

    char *buffer = (char *) malloc(size);
	ssize_t read_bytes_count = read(input_fd, buffer, size);
    while (read_bytes_count != 0)
    {
        if (read_bytes_count == -1){
            perror("File read error");
			exit(EXIT_FAILURE);
		}
        if (read_bytes_count == 0)
            break;
        char *buffer_ = buffer;
        bool zero_block = true;
        for (int index = 0; index < read_bytes_count; index++)
            if (*(buffer_++)) {
                zero_block = false;
                break;
            }
        if (zero_block == true) {
            if (lseek(output_fd, size, SEEK_CUR) == -1){
                perror("lseek error");
				exit(EXIT_FAILURE);
			}
        }
        else
            if (write(output_fd, buffer, read_bytes_count) != read_bytes_count){
                perror("write error");
				exit(EXIT_FAILURE);
			}
		read_bytes_count = read(input_fd, buffer, size);
    }

    if (input_name == NULL && close(input_fd) == -1 || close(output_fd) == -1)
	{
		perror("File close error");
		exit(EXIT_FAILURE);
	}

}