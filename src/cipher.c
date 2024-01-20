#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define SIZE 256

void consol_menu(int a, char *file_name);
void reading(char *file_name);
void writing(char *file_name, char *file);
void encrypt(int n);
void skip_line();
void clear_h(char *name);
void enc_c(char *name, int n);

int main() {
    float v = 0;
    int b, a = 0;
    char file_name[SIZE];
    while (v != -1) {
        b = scanf("%f", &v);
        skip_line();
        if ((b == 1) && ((int)v == v)) {
            a = (int)v;
            consol_menu(a, file_name);
        } else {
            printf("n/a\n");
        }
    }
}

void consol_menu(int a, char *file_name) {
    if (a == 1) {
        scanf("%s", file_name);
        reading(file_name);
    } else if (a == 2) {
        char file[SIZE];
        char c = 'r';
        c = getchar();
        int k = 0;
        while (c != '\n') {
            file[k] = c;
            k++;
            c = getchar();
        }
        writing(file_name, file);
    } else if (a == 3) {
        int n;
        scanf("%d", &n);
        encrypt(n);
    } else if (a != -1) {
        printf("n/a\n");
    }
}

void reading(char *file_name) {
    FILE *fp;
    char file[SIZE];
    fp = fopen(file_name, "r");
    if (!fp) {
        printf("n/a\n");
    } else {
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0) {
            printf("n/a\n");
        } else {
            rewind(fp);
            while (fgets(file, SIZE, fp) != NULL)
                puts(file);
        }
        fclose(fp);
    }
}

void writing(char *file_name, char *file) {
    FILE *fp;
    if (!fopen(file_name, "r")) {
        printf("n/a\n");
    } else {
        fp = fopen(file_name, "at");
        fputs(file, fp);
        fclose(fp);
    }
}

void encrypt(int n) {
    DIR* d;
    struct dirent* dir;
    char direc[SIZE];
    scanf("%s", direc);
    d = opendir(direc);
    char path[SIZE] = "";
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            char* name = dir->d_name;
            if (name[strlen(name) - 1] == 'h') {
                strcpy(path, direc);
                strcat(path, "/");
                strcat(path, name);
                clear_h(path);
            } else if (name[strlen(name) - 1] == 'c') {
                strcpy(path, direc);
                strcat(path, "/");
                strcat(path, name);
                enc_c(path, n);
            }
        }
    }
    closedir(d);
}

void skip_line() {
    char c = getchar();
    while (c != '\n') {
        c = getchar();
    }
}

void clear_h(char *name) {
    FILE *fp;
    fp = fopen(name, "w");
    fclose(fp);
}

void enc_c(char *name, int n) {
    FILE *fp;
    fp = fopen(name, "r+");
    char c, new;
    c = getc(fp);
    while (!feof(fp)) {
        new = (char)(((int)c + (127 + n) % 127) % 127);
        fseek(fp, -1, SEEK_CUR);
        putc(new, fp);
        c = getc(fp);
    }
    fclose(fp);
}
