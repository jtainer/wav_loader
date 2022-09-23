// 
// wav file loading/unloading functions
//
// 2022, Jonathan Tainer
//

#include "wav.h"
#include <stdio.h>
#include <stdlib.h>

wav_file load_wav(const char* filename) {
	wav_file file = { 0 };
	FILE* fptr = NULL;
	fptr = fopen(filename, "rb");
	
	if (fptr == NULL) {
		printf("ERROR: Failed to open file \'%s\'\n", filename);
		return file;
	}
	
	// first read header to determine file size
	fread(&file.header, sizeof(wav_header), 1, fptr);

	// Determine how many samples to load
	int bytes_per_sample = file.header.bit_depth / 8;
	int num_samples = file.header.data_size / bytes_per_sample;

	file.data = malloc(file.header.data_size);
	fread(file.data, bytes_per_sample, num_samples, fptr);
	fclose(fptr);

	printf("Loaded file \'%s\' (%u bytes)\n", filename, file.header.file_size + 8);

	return file;
}

void unload_wav(wav_file* file) {
	if (file->data == NULL) return;

	free(file->data);
	file->data = NULL;
	printf("Unloaded file\n");
}

void save_wav(wav_file* file, const char* filename) {
	FILE* fptr = NULL;
	fptr = fopen(filename, "wb");

	if (fptr == NULL) {
		printf("ERROR: Failed to open file \'%s\'\n", filename);
		return;
	}
	
	// Write header to file
	fwrite(&file->header, sizeof(wav_header), 1, fptr);

	// Determine num of samples to write
	int bytes_per_sample = file->header.bit_depth / 8;
	int num_samples = file->header.data_size / bytes_per_sample;
	
	fwrite(file->data, bytes_per_sample, num_samples, fptr);
	fclose(fptr);
	
	printf("Saved file \'%s\' (%u bytes)\n", filename, file->header.file_size + 8);
	
	return;
}

