#include "cachelab.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>


/* 构造cache_line结构体 */
struct cache_line
{
    int valid;
    unsigned tag;
    int LRU_counter;        
};

int cache_init(struct cache_line* caches, int S, int E);
int cache_ls(struct cache_line* cache_set,char identifier,unsigned address,int size,unsigned tag,int E);

/* 全局变量定义 */
int hits = 0,misses = 0,evictions = 0;
int flag = 0;
int global_counter = 0;     /* 每次访问内存时counter++，并赋值给LRU_counter,类似时间戳 */

int main(int argc, char *argv[] )
{
    int opt;
    int s,b,S,E,B;
    char *filename;
    FILE *trace_file; 

    char identifier;
    unsigned address,tag, set,set_;
    /* unsigned offset; */
    int size;

    /* 命令行参数读取 */
    while((opt = getopt(argc, argv, "v::s:E:b:t:")) != -1){
        switch(opt)
        {
            case 'v':
            flag = 1;
            break;

            case 's':
            s = atoi(optarg);
            S = 1 << s;
            printf("S = %d\n",S);
            break;

            case 'E':
            E = atoi(optarg);
            printf("E = %d\n",E);
            break;

            case 'b':
            b = atoi(optarg);
            B = 1 << b;
            printf("B = %d\n",B);    
            break;

            case 't':
            filename = optarg;
            printf("filename = %s\n",filename);
            break;

            default:break;
        }
    }
    struct cache_line * caches = (struct cache_line*)malloc(S * E * sizeof(struct cache_line) ) ;
    cache_init(caches, S, E);

    /* trace文件读取解析 */
    trace_file = fopen(filename,"r"); 
    while(fscanf(trace_file," %c %x,%d", &identifier, &address, &size)>0){
        set_ = ~((~0)<<s);
        set = (address >> b) & set_;
        /* offset = address & 0xF; */
        tag = address >> (s + b);
        struct cache_line* cache_set = &caches[set * E];
        switch(identifier){
            case 'L':
            cache_ls(cache_set,identifier,address,size,tag,E);
            break;

            case 'S':
            cache_ls(cache_set,identifier,address,size,tag,E);
            break;

            case 'M':
            cache_ls(cache_set,identifier,address,size,tag,E);
            for(int i=0;i<E;i++){
                if((cache_set[i].valid == 1)&&(cache_set[i].tag == tag)){
                    hits++;
                    cache_set[i].LRU_counter++;
                    if(flag)
                        printf(" hit\n");
                }
            }
            default:break;
        }
    }

    fclose(trace_file);
    free(caches);
    printSummary(hits, misses, evictions);
    return 0;
}

int cache_init(struct cache_line* caches, int S, int E)
{
    int len = S*E;
    for(int i = 0;i<len;i++){
        caches[i].valid = 0;
        caches[i].LRU_counter = 0;
    }
    return 0;
}

int cache_ls(struct cache_line* cache_set,char identifier,unsigned address,int size,unsigned tag, int E)
{
    global_counter++;
    int evict_index = 0;
    for(int i=0;i<E;i++){
        if((cache_set[i].valid == 1)&&(cache_set[i].tag == tag)){
            hits++;
            cache_set[i].LRU_counter = global_counter;
            if(flag)
                printf("%c %x,%d hit",identifier,address,size);
            if(identifier!='M')
                printf("\n");
            return 0;
        }
    }
    for(int i=0;i<E;i++){
        if(cache_set[i].valid == 0 ){
            misses++;
            cache_set[i].valid = 1;
            cache_set[i].tag = tag;
            cache_set[i].LRU_counter = global_counter;
            if(flag)
                printf("%c %x,%d miss",identifier,address,size);
            if(identifier!='M')
                printf("\n");
            return 0;
        }
    }
    for(int i=0;i<E-1;i++){
        if(cache_set[evict_index].LRU_counter > cache_set[i+1].LRU_counter )
            evict_index = i+1;
    } 
    misses++;           
    evictions++;
    cache_set[evict_index].tag = tag;
    cache_set[evict_index].LRU_counter=global_counter;
    if(flag)
        printf("%c %x,%d miss eviction",identifier,address,size);
    if(identifier!='M')
        printf("\n");
    return 0;
}

