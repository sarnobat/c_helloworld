// gcc -print-libgcc-file-name /Volumes/numerous/usr/local/homebrew/Cellar/libexif/0.6.23/lib/libexif.12.dylib -I/Volumes/numerous/usr/local/homebrew/Cellar/libexif/0.6.23/include/  photographer.c -o photographer

#include <stdio.h>
#include <string.h>
#include <libexif/exif-data.h>

/* Show the tag name and contents if the tag exists */
static void show_tag(ExifData *ed, ExifIfd ifd, ExifTag tag)
{
    /* See if this tag exists */
    ExifEntry *entry = exif_content_get_entry(ed->ifd[ifd],tag);
    if (entry) {
        char buf[1024];

        /* Get the contents of the tag in human-readable form */
        exif_entry_get_value(entry, buf, sizeof(buf));

        /* Don't bother printing it if it's entirely blank */

        if (*buf) {
            printf("%s:\t%s\n", exif_tag_get_name_in_ifd(tag,ifd), buf);
        }
    }
}

int main(int argc, char **argv)
{
    ExifData *ed;
    ExifEntry *entry;

    if (argc < 2) {
        printf("Usage: %s image.jpg\n", argv[0]);
        printf("Displays tags potentially relating to ownership "
                "of the image.\n");
        return 1;
    }

    /* Load an ExifData object from an EXIF file */
    ed = exif_data_new_from_file(argv[1]);
    if (!ed) {
        printf("File not readable or no EXIF data in file %s\n", argv[1]);
        return 2;
    }
    show_tag(ed, EXIF_IFD_0, EXIF_TAG_MAKE);
	show_tag(ed, EXIF_IFD_0, EXIF_TAG_MODEL);

    /* Free the EXIF data */
    exif_data_unref(ed);

    return 0;
}