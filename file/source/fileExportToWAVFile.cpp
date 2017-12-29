/*
    Copyright 2017 Krzysztof Karbowiak
*/

#include "fileExportToWAVFile.h"
#include "fileBinaryFile.h"

#include "wavStructures.h"

namespace file
{
///////////////////////////////////////////////////////////////////////////////
bool exportToWAVFile(std::string const & file_name, wav::Format const & format, std::vector<double> const & samples)
{
    bool result = false;

    BinaryFile file;

    if (file.open(file_name, BinaryFile::AF_WRITE))
    {
        wav::RIFFChunk riff_chunk = {{'R', 'I', 'F', 'F'},
                                     36 + static_cast<unsigned int>(samples.size()) * format.channels_number * format.sample_resolution / 8,
                                     {'W', 'A', 'V', 'E'}};

        wav::FMTSubchunk fmt_subchunk = {{'f', 'm', 't', ' '},
                                         16,
                                         1,
                                         format.channels_number,
                                         format.sample_rate,
                                         format.sample_rate * format.channels_number * format.sample_resolution / 8,
                                         format.channels_number * format.sample_resolution / 8,
                                         format.sample_resolution};

        wav::DataSubchunk data_subchunk = {{'d', 'a', 't', 'a'},
                                           static_cast<unsigned int>(samples.size()) * format.channels_number * format.sample_resolution / 8};

        bool res = file.write(riff_chunk.chunk_id[0]);
        res = res && file.write(riff_chunk.chunk_id[1]);
        res = res && file.write(riff_chunk.chunk_id[2]);
        res = res && file.write(riff_chunk.chunk_id[3]);
        res = res && file.write(riff_chunk.chunk_size);
        res = res && file.write(riff_chunk.format[0]);
        res = res && file.write(riff_chunk.format[1]);
        res = res && file.write(riff_chunk.format[2]);
        res = res && file.write(riff_chunk.format[3]);
        res = res && file.write(fmt_subchunk.subchunk_id[0]);
        res = res && file.write(fmt_subchunk.subchunk_id[1]);
        res = res && file.write(fmt_subchunk.subchunk_id[2]);
        res = res && file.write(fmt_subchunk.subchunk_id[3]);
        res = res && file.write(fmt_subchunk.subchunk_size);
        res = res && file.write(fmt_subchunk.audio_format);
        res = res && file.write(fmt_subchunk.num_channels);
        res = res && file.write(fmt_subchunk.sample_rate);
        res = res && file.write(fmt_subchunk.byte_rate);
        res = res && file.write(fmt_subchunk.block_align);
        res = res && file.write(fmt_subchunk.bits_per_sample);
        res = res && file.write(data_subchunk.subchunk_id[0]);
        res = res && file.write(data_subchunk.subchunk_id[1]);
        res = res && file.write(data_subchunk.subchunk_id[2]);
        res = res && file.write(data_subchunk.subchunk_id[3]);
        res = res && file.write(data_subchunk.subchunk_size);

        for (std::vector<double>::const_iterator cit = samples.begin(); res && (cit != samples.end()); ++cit)
        {
            if (format.sample_resolution == 16)
            {
                short int sample = static_cast<short int>(*cit * 32760);

                res = res && file.write(sample); // write center / left sample

                if (format.channels_number == 2)
                {
                    res = res && file.write(sample); // write right sample
                }
            }
            else if (format.sample_resolution == 8)
            {
                unsigned char sample = static_cast<unsigned char>((*cit + 1.0) * 127);

                res = res && file.write(sample); // write center / left sample

                if (format.channels_number == 2)
                {
                    res = res && file.write(sample); // write right sample
                }
            }
        }

        result = file.close() && res;
    }

    return result;
}
///////////////////////////////////////////////////////////////////////////////
}

