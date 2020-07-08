#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

static int CRC_TABLE_H[256] = {0};
static int CRC_TABLE_L[] = {0,27,54,45,108,119,90,65,216,195,238,245,180,175,130,153,432,427,390,413,476,455,490,497,360,371,350,325,260,287,306,297,864,891,854,845,780,791,826,801,952,931,910,917,980,975,994,1017,720,715,742,765,700,679,650,657,520,531,574,549,612,639,594,585,1728,1755,1782,1773,1708,1719,1690,1665,1560,1539,1582,1589,1652,1647,1602,1625,1904,1899,1862,1885,1820,1799,1834,1841,1960,1971,1950,1925,1988,2015,2034,2025,1440,1467,1430,1421,1484,1495,1530,1505,1400,1379,1358,1365,1300,1295,1314,1337,1040,1035,1062,1085,1148,1127,1098,1105,1224,1235,1278,1253,1188,1215,1170,1161,3456,3483,3510,3501,3564,3575,3546,3521,3416,3395,3438,3445,3380,3375,3330,3353,3120,3115,3078,3101,3164,3143,3178,3185,3304,3315,3294,3269,3204,3231,3250,3241,3808,3835,3798,3789,3724,3735,3770,3745,3640,3619,3598,3605,3668,3663,3682,3705,3920,3915,3942,3965,3900,3879,3850,3857,3976,3987,4030,4005,4068,4095,4050,4041,2880,2907,2934,2925,2860,2871,2842,2817,2968,2947,2990,2997,3060,3055,3010,3033,2800,2795,2758,2781,2716,2695,2730,2737,2600,2611,2590,2565,2628,2655,2674,2665,2080,2107,2070,2061,2124,2135,2170,2145,2296,2275,2254,2261,2196,2191,2210,2233,2448,2443,2470,2493,2556,2535,2506,2513,2376,2387,2430,2405,2340,2367,2322,2313};
static int crc_data_count = 4080;
static int crc_count = 8;
static char crc_format_arr[32] = "";
static char str[32] = "";

char* crc64_pair(char * data)
{
    strcpy(crc_format_arr, "");
    int shr, tmp_1h, tmp_1l, table_i, crc_h, crc_l;
    crc_h = 0xFFFFFFFF; 
    crc_l = 0xFFFFFFFF;

    for (int j = 0; j < crc_data_count; ++j)
    {
        shr = (crc_l >> 24) & 0xFF;
        tmp_1h = (crc_h << 8) | shr;
        tmp_1h = tmp_1h & 0xFFFFFFFF;
        tmp_1l = (crc_l << 8);
        tmp_1l = tmp_1l & 0xFFFFFFFF;
        table_i = ((crc_h >> 24) ^ data[j]) & 0xFF;
        crc_h = tmp_1h ^ CRC_TABLE_H[table_i];
        crc_l = tmp_1l ^ CRC_TABLE_L[table_i];
    }

    sprintf(crc_format_arr, "%08X%08X", crc_h, crc_l);
    return crc_format_arr;
}

char* get_crc_data(char* crc_data) {
    char crc_d[4];
    strcpy(str, "");
    for (int i = 0; i < crc_count; ++i)
    {
        sprintf(crc_d, "%02X", (unsigned char)crc_data[i]);
        strcat(str, crc_d);
    }
    return str;
}

int check_crc(char* data, char* crc_data)
{
    char* data_crc = crc64_pair(data);
    char* check_crc = get_crc_data(crc_data);

    printf("%s %s\n", data_crc, check_crc);
    if (strncmp(data_crc, check_crc, 16) != 0){
        return 0;
    } else {
        return 1;
    }
}

int main(int argc, char* argv[]) 
{
    FILE *fp = NULL;
    // TUDO: char s[(数值太大会造成 Segmentation fault (core dumped) 测试最大边界值: 8377120)]
    char data[crc_data_count];
    char crc_data[crc_count];
    char crc_test[4];
    fp = fopen("126_20200702_1322\22.data", "rb");

    for (int i = 0; i < 20; ++i)
    {
        fread(data, crc_data_count, 1, fp);
        fread(crc_data, crc_count, 1, fp);
        fread(crc_test, 4, 1, fp);
        fread(crc_test, 4, 1, fp);
        

        double begin_time, end_time;

        begin_time = clock();
        int res = check_crc(data, crc_data);
        end_time = clock();

        // printf("run time: %f ms\n", (end_time - begin_time) / 1000);
        // printf("result: %d  // (0为false，1位true)\n", res);
    }
    

    fclose(fp);
    return 0;
}
