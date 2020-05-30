#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

bool is_jpeg(BYTE *buffer);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // read from the images file
    FILE *image_file = fopen(argv[1], "r");
    if (image_file == NULL)
    {
        fprintf(stderr, "Could not open image file.\n");
        return 1;
    }

    // working with a FAT file system whose "block size" is 512 bytes
    // with the above in mind, create a buffer that holds 512 bytes of a block of memory
    BYTE *buffer = malloc(512);
    if (buffer == NULL)
    {
        fprintf(stderr, "Could not allocate memory for buffer.\n");
        return 1;
    }

    // block of memory to the temporary name of the image
    char *image_name = malloc(8);
    if (image_name == NULL)
    {
        fprintf(stderr, "Could not allocate memory for image_name.\n");
        return 1;
    }

    // jpeg file
    FILE *image = NULL;
    int counter_images = 0;
    while (true)
    {
        fread(buffer, 1, 512, image_file);
        if (feof(image_file))
        {
            break;
        }
        else if (ferror(image_file))
        {
            fprintf(stderr, "Could not read image_file.\n");
            return 1;
        }

        if (is_jpeg(buffer))
        {
            // close the stream of the jpeg file because we completed the image
            if (image != NULL)
            {
                fclose(image);
            }

            // new name for the jpeg file
            sprintf(image_name, "%03i.jpg", counter_images++);

            // create a new jpeg file
            image = fopen(image_name, "w");
            if (image == NULL)
            {
                fprintf(stderr, "Could not create a image.\n");
                return 1;
            }
        }

        if (image != NULL)
        {
            // write from the memory to the jpeg file
            fwrite(buffer, 1, 512, image);
            if (ferror(image))
            {
                fprintf(stderr, "Could not write to image.\n");
                return 1;
            }
        }
    }

    // close all streams opened
    fclose(image_file);
    fclose(image);
    // close the memory allocated
    free(buffer);
    free(image_name);
}

// checks if the first 4 bytes of the buffer have a jpeg signature
bool is_jpeg(BYTE *buffer)
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }

    return false;
}
