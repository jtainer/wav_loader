// 
// wav file loading/unloading functions
// 
// 2022, Jonathan Tainer
// 

#ifndef WAV_H
#define WAV_H

#define uint8	unsigned char
#define uint16	unsigned short
#define uint32	unsigned int

typedef struct wav_header {
	uint8	riff[4];	// "RIFF"
	uint32	file_size;	// overall file size - 8 bytes
	uint8	wave[4];	// "WAVE"
	uint8	fmt_marker[4];	// "fmt\0"
	uint32	fmt_length;	// length of format data
	uint16	fmt_type;	// 1 for PCM
	uint16	num_channels;
	uint32	sample_rate;	// samples per second
	uint32	byte_rate;	// sample_rate * bit_depth / 8
	uint16	block_align;	// num_channels * bit_depth / 8
	uint16	bit_depth;	// bits per sample
	uint8	data[4];	// "data" - beginning of data section
	uint32	data_size;	// num_samples * num_channels * bit_depth / 8
} wav_header;

typedef struct wav_file {
	wav_header header;
	void* data;
} wav_file;

wav_file load_wav(const char* filename);

void unload_wav(wav_file* file);

void save_wav(wav_file* file, const char* filename);

#endif
