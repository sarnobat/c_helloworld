// gcc -print-libgcc-file-name /Volumes/numerous/usr/local/homebrew/Cellar/libexif/0.6.23/lib/libexif.12.dylib -I/Volumes/numerous/usr/local/homebrew/Cellar/libexif/0.6.23/include/  photographer.c -o photographer

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <libexif/exif-data.h>

/* Show the tag name and contents if the tag exists */
static void show_tag(ExifData *ed, ExifIfd ifd, ExifTag tag, char* filename)
{
    /* See if this tag exists */
    ExifEntry *entry = exif_content_get_entry(ed->ifd[ifd],tag);
    if (entry) {
        char buf[1024];

        /* Get the contents of the tag in human-readable form */
        exif_entry_get_value(entry, buf, sizeof(buf));

        /* Don't bother printing it if it's entirely blank */

        if (*buf) {
            printf("%-90s\t%-7s\t%s\n", filename, exif_tag_get_name_in_ifd(tag,ifd), buf);
        }
    }
}

int main(int argc, char **argv)
{

    ExifEntry *entry;

    if (argc < 2) {
        printf("Usage: %s image.jpg\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];
    ExifData *ed = exif_data_new_from_file(argv[1]);
    if (ed) {
		char buf[1024];
		char buf2[1024];

		bool hasMake = false;
		bool hasModel = false;
// 		show_tag(ed, EXIF_IFD_0, EXIF_TAG_MAKE, argv[1]);
		ExifIfd ifd = EXIF_IFD_0;

		{
			ExifTag tag = EXIF_TAG_MAKE;
			ExifEntry *entry = exif_content_get_entry(ed->ifd[ifd],tag);
			if (entry) {
				exif_entry_get_value(entry, buf, sizeof(buf));
				if (*buf) {
					hasMake = true;
				}
			}
		}
		{
			ExifTag tag2 = EXIF_TAG_MODEL;
			ExifEntry *entry2 = exif_content_get_entry(ed->ifd[ifd],tag2);
			if (entry2) {		
				exif_entry_get_value(entry2, buf2, sizeof(buf2));
				if (*buf2) {
					hasModel = true;
				}
			}
		}
		if (hasMake && hasModel) {
			printf("%-90s\t%-7s\t%s\n", filename, buf, buf2);
			//printf("%-90s\t%-7s\t%s%s\n", filename, exif_tag_get_name_in_ifd(tag,ifd), buf, buf2);
		}
//		show_tag(ed, EXIF_IFD_0, EXIF_TAG_MODEL, argv[1]);
// 		show_tag(ed, EXIF_IFD_0, EXIF_TAG_FILE_SOURCE, argv[1]);
// 		show_tag(ed, EXIF_IFD_1, EXIF_TAG_FILE_SOURCE, argv[1]);
// 		show_tag(ed, EXIF_IFD_0, EXIF_TAG_DOCUMENT_NAME, argv[1]);
// 		show_tag(ed, EXIF_IFD_1, EXIF_TAG_DOCUMENT_NAME, argv[1]);
		
		/* Free the EXIF data */
		exif_data_unref(ed);
    } else {
        printf("File not readable or no EXIF data in file %s\n", argv[1]);
        return 2;
    }


    return 0;
}
