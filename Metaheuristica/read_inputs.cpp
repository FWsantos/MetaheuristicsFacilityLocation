#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
// #include <sys/types.h>

using namespace std;
int list_dir(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("Diretorio não encontrado");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; (entry = readdir(dir)) != NULL ; ++i){
        if(i >= 2){
            // cout << entry->d_name <<endl;
            
            char ch[100] = "";
            int k;
            for(k = 0; path[k] != '\0';k++)
                ch[k] = path[k];
            
            for (int i = 0; *(entry->d_name+i) != '\0' ; ++i)
                ch[k+i] = *(entry->d_name+i);

            cout  << endl;
            for (int i = 0; ch[i] != '\0'; ++i)
                cout << ch[i];
            cout  << endl;


            FILE* fp = fopen(ch, "r");
            if(!fp) {
                perror("Falha em abrir o arquivo");
                return EXIT_FAILURE;
            }

            // int c; // note: int, not char, required to handle EOF
            // while ((c = fgetc(fp)) != EOF) { // standard C I/O file reading loop
            //  putchar(c);
            // }

            if (ferror(fp))
                puts("Erro na Leitura do arquivo");
            else if (feof(fp))
                puts("Arquivo lido com sucesso");

            fclose(fp);
        }
    }
    closedir(dir);
    return 0;
}
int main() {

    // FILE* fp = fopen("test.txt", "r");
    // if(!fp) {
    //  perror("File opening failed");
    //  return EXIT_FAILURE;
    // }

    // int c; // note: int, not char, required to handle EOF
    // while ((c = fgetc(fp)) != EOF) { // standard C I/O file reading loop
    //  putchar(c);
    // }

    // if (ferror(fp))
    //  puts("I/O error when reading");
    // else if (feof(fp))
    //  puts("End of file reached successfully");

    // fclose(fp);

    int a = list_dir("testes/");
}