#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ext_utils.h"

#define LINE_LOG_SIZE 40960
#define DEFAULT_LOG_FILE_BASE_NAME "/var/log/fpga"
#define DEFAULT_LOG_FILE_SUFFIX_NAME ".log"

static signed char line_log[LINE_LOG_SIZE];

signed char* format_log_content(signed char* level, signed char* content)
{
    strcpy(line_log, "");
    sprintf(line_log, "%s.%ld [%5s] %s [%d]\n", get_date_hms(), get_date_millis(), level, content, getpid());
    return line_log;
}

signed char* get_save_path(signed char* level, signed char* device_id)
{
    static signed char save_path[4096];
    sprintf(save_path, "%s/%s/%s", DEFAULT_LOG_FILE_BASE_NAME, device_id, get_date_ymd());
    extend_folders(save_path);
    return save_path;
}

void write_log(signed char* file_prefix, signed char* save_path, signed char* content)
{   
    signed char log_path[4096];
    sprintf(log_path, "%s/%s%s", save_path, file_prefix, DEFAULT_LOG_FILE_SUFFIX_NAME);
    FILE* fp = fopen(log_path, "a+");
    fputs(content, fp);
    fclose(fp);
}

void ext_info(signed char* file_prefix, signed char* device_id, signed char* content)
{
    signed char level[8] = "info";
    signed char* log_path = get_save_path(level, device_id);
    signed char* con = format_log_content(level, content);

    write_log(file_prefix, log_path, con);
}

void ext_warn(signed char* file_prefix, signed char* device_id, signed char* content)
{
    signed char level[8] = "warn";
    signed char* log_path = get_save_path(level, device_id);
    signed char* con = format_log_content(level, content);

    write_log(file_prefix, log_path, con);
}

void ext_error(signed char* file_prefix, signed char* device_id, signed char* content)
{
    signed char level[8] = "error";
    signed char* log_path = get_save_path(level, device_id);
    signed char* con = format_log_content(level, content);

    write_log(file_prefix, log_path, con);
}


int main(int argc, signed char* argv[]) 
{   
    // int a = 3334;
    // ext_info("test", "126", fmt_str1("fmt_str1: %s", "123"));
    // ext_warn("test", "126", fmt_str2("fmt_str2: %s - %s", "123", "234"));
    // ext_error("test", "126", fmt_str3("fmt_str3: %s - %s - %s", "123", "123", "123"));
    
    // char* data = get_date_hms();

    // printf("%s\n", data);
    
    int64_t s = get_timestamp();
    char str[20];
    sprintf(str, "%ld", s);
    printf("int64_t: %ld\n", s);
    printf("str %s\n", str);

    return 0;
}

