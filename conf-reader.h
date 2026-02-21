char* config_reader(char* conf_file, char* conf_name)
{
    FILE* f = fopen(conf_file, "rb");
    char buffer[300];
    char name[100];
    char value[200];

    while(fgets(buffer, 300, f))
    {
        // mini parser
        sscanf(buffer, "%s = %s", name, value);

        if(strcmp(name, conf_name) == 0){
            fclose(f);
            return strdup(value);
        }
    }
    fclose(f);
    return NULL;
}