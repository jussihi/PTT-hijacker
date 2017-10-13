#include <os.h>
 
#define SRC_DIR "\\documents\\MyLib\\"
#define DST_DIR "\\exammode\\usr\\Press-to-Test\\"
 
#define BUF_SIZE 256
 
int is_ptt(void)
{
        char buffer[BUF_SIZE] = {'\0'};
        NU_Current_Dir("A:", buffer);
        return strcmp(buffer, "\\documents\\");
}
 
int copy_file(const char *src, const char *dst)
{
        FILE *in = fopen(src, "rb"), *out;
        int c;
        if (!in)
                return -1;
        out = fopen(dst, "wb");
        if (!out) 
       {
                fclose(in);
                return -1;
        }
        while ((c = fgetc(in)) != EOF)
        {
                fputc(c, out);
        }
        fclose(in);
        fclose(out);
        return 0;
}
 
void copy_files(void)
{
        struct dstat file;
        NU_Get_First(&file, SRC_DIR "*.*");
        do {
                char src[BUF_SIZE] = {'\0'};
                char dst[BUF_SIZE] = {'\0'};
                sprintf(src, SRC_DIR "%s", file.filepath);
                sprintf(dst, DST_DIR "%s", file.filepath);
                copy_file(src, dst);
        } while (NU_Get_Next(&file) == 0);
        NU_Done(&file);
}
 
int main(void)
{
        if (is_ptt())
        {
                copy_files();
        }

        return EXIT_SUCCESS;
}
