#include "wav.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("No files specified\n");
		return 0;
	}

	int num_files = argc - 1;
	wav_file* file = (wav_file*)malloc(sizeof(wav_file) * num_files);
	
	for (int i = 0; i < num_files; i++) {
		file[i] = load_wav(argv[i + 1]);
	}

	for (int i = 0; i < num_files; i++) {
		unload_wav(&file[i]);
	}

	return 0;
}
