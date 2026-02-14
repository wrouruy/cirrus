bool endswith(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return false;

    size_t len_str = strlen(str);
    size_t len_suffix = strlen(suffix);

    if (len_suffix > len_str)
        return false;

    return (strcmp(str + len_str - len_suffix, suffix) == 0);
}

bool include_str(char* str, char** arr, int len)
{
    for(int i = 0; i < len; i++) {
        if(strcmp(arr[i], str) == 0)
            return true;
    }
    return false;
}

char* strbefore(char* str, char symbol)
{
    char* res = malloc(strlen(str));
    for(size_t i = 0; i < sizeof(res); i++){
        if(str[i] == symbol){
            res[i] = '\0';
            break;
        }
        res[i] = str[i];
    }
    return res;
}

void open_url(char* url)
{
    char* result;
    size_t size;

    #ifdef __linux
        size = strlen("xdg-open ") + strlen(url) + 1;
        result = malloc(size);
        snprintf(result, size, "xdg-open %s\0", url);
    #elif __WIN32
        size = strlen("start ") + strlen(url) + 1;
        result = malloc(size);
        snprintf(result, size, "start %s\0", url);
    #elif MAC_OS_X
        size = strlen("open ") + strlen(url) + 1;
        result = malloc(size);
        snprintf(result, size, "open %s\0", url);
    #endif

    system(result);
    free(result);
}

char* fvalue(char* filename)
{
    FILE* fsrc = fopen(filename, "rb");
    fseek(fsrc, 0, SEEK_END);
    long size = ftell(fsrc);
    rewind(fsrc);

    char* buffer = malloc(size + 1);
    fread(buffer, 1, size, fsrc);
    buffer[size] = '\0';
    fclose(fsrc);

    return buffer;
}

char* get_file_format(char* filename)
{
    char* dot = strrchr(filename, '.');
    if (!dot || dot == filename) {
        return "";
    }
    return dot + 1;
}

bool file_exists(char *filename)
{
    FILE *file;
    if ((file = fopen(filename, "r"))) {
        fclose(file);
        return true;
    } else
        return false;
}

char* get_path(char* filename)
{
    char exe_path[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path)-1);
    if (len == -1) {
        perror("readlink");
        exit(1);
    }
    exe_path[len] = '\0';

    char* last = strrchr(exe_path, '/');
    if (last) *last = '\0';

    char* fullpath = malloc(PATH_MAX);
    snprintf(fullpath, PATH_MAX, "%s/%s", exe_path, filename);
    return fullpath;
}

void ThrowError(char* typeError, char* message, ...)
{
    va_list args;
    int written_chars;
    char* buffer = malloc(512);
    size_t buffer_size = 512;

    va_start(args, message);
    written_chars = vsnprintf(buffer, buffer_size, message, args);
    va_end(args);

    printf("\033[1;31m%s:\033[0m %s\n", typeError, buffer);
    exit(1);
}

short file_type(char *path) {
    struct stat st;

    // Check if stat call succeeded
    if (stat(path, &st) == -1) {
        perror("stat"); // Prints the error in case of failure (e.g., file not found)
        return -1; // Error
    }

    if (S_ISDIR(st.st_mode))
        return 0; // Directory
    else if (S_ISREG(st.st_mode))
        return 1; // Regular file
    else
        return 2; // Other type
}