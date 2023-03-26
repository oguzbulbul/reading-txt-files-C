#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <locale.h>

void etiket_arama(char string[300])
{
    char karakter='[';
    char *ilk_gectigi_ptr=strchr(string,karakter);
    int index=ilk_gectigi_ptr-string;
    int length=0;
    FILE *fp=fopen("output.txt","a");

    //char etiket[50];

    if(ilk_gectigi_ptr==NULL)
    {
        //printf("yok\n");
    }
    else
    {
        //printf("\n");
        while(string[index+length]!=']')
        {
            length++;
        }
        if( string[index+1]=='[' && string[index+length]==']' && string[index+length+1]==']')
        {
            for(int i=index+2; i<index+length; i++)
            {
                //printf("%c",string[i]);
                fputc(string[i],fp);
                if(i==index+length-1) fputc('\n',fp);
            }
            fclose(fp);
            //printf("\n");
            strcpy(string,ilk_gectigi_ptr+length+2);
        }
        else
        {
            strcpy(string,ilk_gectigi_ptr+index+length+2);

        }
        etiket_arama(string);
    }
}

void kelime_arama(FILE *fp,char string[300],char s[50])
{    

    int satir_sayisi=0;
    while (fgets(string, 300, fp) != NULL)
    {
        int count=0;
        char *ptr=strstr(string,s);

        satir_sayisi++;
        //printf("\n%d. satir: %s\n", satir_sayisi, string);
        
        while(ptr!=NULL){
            count++;
            ptr=strstr(ptr+1,s);
        }
        if(count>=1){
            printf("%d. satirda %d kere geciyor\n",satir_sayisi,count); 
            printf("\n%d. satir: %s\n", satir_sayisi,string);
        }
        etiket_arama(string);
    }
}

void output_cikti2(char string[50],char path[300])
{
    char string2[45][50];
    char string3[45][50];
    FILE *fp=fopen("output.txt","r");
    int i=0,j=0;
    int size=40;
    while (fgets(string,50, fp) != NULL)
    {
        // printf("%s\n",string);
        strcpy(string2[i],string);
        //printf("%s\n",string2[i]);
        i++;  
    }
    for(i=0;i<40;i++)
    {
        int boy=strlen(string2[i]);
        string2[i][boy-1]='\0';
    }
    int k=0,n=1;
    int count[25];
    // duplicate etiketleri ayıklama sayılarını tespit etme
    for(i=0;i<size;i++)
    {
        n=1;
        for(j=i+1;j<size;j++)
        {      

            if(strcmp(string2[i],string2[j])==0)
            {
                for(k=j;k<size-1;k++)
                {
                    strcpy(string2[k],string2[k+1]);
                }
            n++;
            size--;
            j--;
            }  
        count[i]=n;
        }
    }

    // for(i=0;i<40;i++)
    // {
    //     printf("%d,%s\n",count[i],string2[i]);
    // }
    fclose(fp);
    fp=fopen("output.txt","w");
    for(i=0;i<31;i++)
    {
        fprintf(fp,"%d \t \t %s %c",count[i],string2[i],'\n');
    }
    fclose(fp);

    printf("\n------------\n");
    for(i=0;i<40;i++)
    {
        strcat(string2[i],".txt");
        yetim_etiket(path,string2[i]);
    }
}
void yetim_etiket(char path[300],char s[50])
{
    char path_2[300];
    struct dirent *entry;
    DIR *directory=opendir(path);
    FILE *dosya;

    if(directory==NULL){
        dosya=fopen(path,"r");
       // printf("%s\n",path);

        const char ch='/';
        char *ret=strrchr(path,ch);
        char ret_2[40][50];
       // printf("%s",ret_2);
        int length=strlen(ret);
        for(int i=0;i<length;i++)
        {
            strcpy(ret_2[i],ret+i+1);
        }
      // printf("%s\n",ret_2);

       if(strcmp(ret_2,s)==0)
       {
        
        printf("%s\n",ret_2);
       }

    }else{
        while((entry=readdir(directory))!= NULL)
        {
            if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0)
            {
                strcpy(path_2,path);
                strcat(path_2,"/");
                strcat(path_2,entry->d_name);
                yetim_etiket(path_2,s);
            }
        }  
    closedir(directory);
    }
}

void dosyada_gezinme(char path[300],char s[50])
{
    char path_2[300];
    struct dirent *entry;
    DIR *directory=opendir(path);
    char string[300];
    FILE *fp;


    if(directory==NULL){
    const char ch='.';
    char *ret;
    ret=strrchr(path,ch);
    const char *cp=".txt";

    if(strcmp(ret,cp)==0)
    {
        printf("%s\n\n",path);
        fp=fopen(path,"r");
        if(fp==NULL){
           printf("dosya yok\n");
        }else{
           kelime_arama(fp,string,s);
        } 
    }
    }else{
    while((entry=readdir(directory))!= NULL)
    {
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0)
        {
            strcpy(path_2,path);
            strcat(path_2,"/");
            strcat(path_2,entry->d_name);
            dosyada_gezinme(path_2,s);
        }
    }  
    closedir(directory);
   }
}

void interface_print(){
    printf("     PROLAB 1 - Proje 1     \n\nDokuwiki\nHangi islemi yapmak istersiniz?\n");
    printf("1)kelime aramak icin 1 giriniz \n2)Etiket aramasi icin 2 giriniz\n");
    printf("3)Dosyaya yazdirmak icin 3 giriniz\n4)output.txt ciktisini yazdirmak icin 4 giriniz\n5)programi sonlandirmak icin 5 giriniz\n");
    printf("secim : ");
}

int main()
{
    setlocale(LC_ALL,"Turkish");    
    int devam=1;
    while(devam)
    {
        //FILE *fp=fopen("output.txt","w");
        interface_print();
                
        char secim;
        scanf("%c",&secim);
        char path[300]=".";
        
        switch (secim) 
        {
        case '1':
            printf(" KELIME ARAMA SECILDI\n");
            char s[50];
            printf("aramak istediginiz kelimeyi giriniz:");
            scanf("%s", s);
            dosyada_gezinme(path,s);     
            break;
        case '2':
            printf("ETIKET ARAMA SECILDI");
            char setiket[50]={};
            char s2[50]={};
            printf("aramak istediginiz kelimeyi giriniz:");
            scanf("%s", s2);
            strcat(setiket,"[[");
            strcat(setiket,s2);
            strcat(setiket,"]]");
            printf("\n***%s",setiket);
            dosyada_gezinme(path,setiket);
            break;
            
        case '3':
        printf("DOSYAYA YAZDIRMA\n");
        char string2[50]={};
        output_cikti2(string2,path);
            break;
        case '4':
            printf("OUTPUT.TXT CIKTISI\n");
            //char ch[50]="Termodinamik.txt";
           // yetim_etiket(path,ch);
             char string25[50]={};

            output_cikti2(string25,path);
            break;
        case '5':
            printf("PROGRAMI SONLANDIR\n");
            devam=0;
            break;
        default:
        break;
        }
    }
}