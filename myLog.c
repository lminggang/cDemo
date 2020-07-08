#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "myCommon.h"

#define LINE_LOG_SIZE 4096
#define DEFAULT_LOG_FILE "/var/log/fpga"

signed char* format_log_content(signed char* level, signed char* content)
{
    static signed char line_log[LINE_LOG_SIZE];
    sprintf(line_log, "%s [%5s] %s [%d]\n", get_date_hms(), level, content, getpid());
    return line_log;
}

signed char* get_save_path(signed char* level, signed char* device_id)
{
    static signed char save_path[32];
    sprintf(save_path, "%s/%s/%s", DEFAULT_LOG_FILE, device_id, get_date_ymd());
    return save_path;
}

void write_log(signed char* save_path, signed char* content)
{   
    extend_folders(save_path);
    signed char log_path[100];
    sprintf(log_path, "%s/log.log", save_path);
    FILE* fp = fopen(log_path, "a");
    fwrite(content, 1, LINE_LOG_SIZE, fp);
    fclose(fp);
}

void info(signed char* file_prefix, signed char* device_id, signed char* content)
{
    signed char level[8] = "info";
    signed char* log_path = get_save_path(level, device_id);
    signed char* con = format_log_content(level, content);

    write_log(log_path, con);
}

void warn(signed char* file_prefix, signed char* device_id, signed char* content)
{
    signed char level[8] = "warn";
    signed char* log_path = get_save_path(level, device_id);
    signed char* con = format_log_content(level, content);

    write_log(log_path, con);
}

void error(signed char* file_prefix, signed char* device_id, signed char* content)
{
    signed char level[8] = "error";
    signed char* log_path = get_save_path(level, device_id);
    signed char* con = format_log_content(level, content);

    write_log(log_path, con);
}

// int main(int argc, signed char* argv[]) 
// {
//     info("read", "126", "info log");
//     warn("send", "126", "warn log");
//     error("conn", "92", "error log");
//     signed char* date1 = get_date();
//     printf("%s\n", date1);
//     return 0;
// }
