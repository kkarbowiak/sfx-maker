#ifndef WAV_STRUCTURES_H__DDK
#define WAV_STRUCTURES_H__DDK

namespace wav
{
    struct Format
    {
        unsigned int sample_rate;
        unsigned int sample_resolution;
        unsigned int channels_number;
    };

    struct RIFFChunk
    {
        char         chunk_id[4]; // "RIFF"
        unsigned int chunk_size;  // size of entire file minus 8 bytes (chunk_id and chunk_size)
        char         format[4];   // "WAVE"
    };

    struct FMTSubchunk
    {
        char               subchunk_id[4];  // "fmt "
        unsigned int       subchunk_size;   // 16 for PCM
        unsigned short int audio_format;    // 1 for PCM
        unsigned short int num_channels;
        unsigned int       sample_rate;
        unsigned int       byte_rate;       // byte_rate = sample_rate * num_channels * bits_per_sample / 8
        unsigned short int block_align;     // block_align = num_channels * bits_per_sample / 8
        unsigned short int bits_per_sample;
    };

    struct DataSubchunk
    {
        char         subchunk_id[4]; // "data"
        unsigned int subchunk_size;  // subchunk_size = num_samples * num_channels * bits_per_sample / 8
    };
}

#endif /* WAV_STRUCTURES_H__DDK */

