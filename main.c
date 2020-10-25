#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct komsuNode{

    int komsuPlakaKodu;
    struct komsuNode* next;

}komsuNode;

komsuNode* komsu_sirali_ekle(komsuNode* node,int plaka){

    if(node==NULL){
        node=(komsuNode*)malloc(sizeof(komsuNode));
        node->komsuPlakaKodu=plaka;
        node->next=NULL;
        return node;
    }
    int varmi=0;
    komsuNode* iter=node;

    while(iter!=NULL){

        if(iter->komsuPlakaKodu == plaka){
            printf("%d komsu listede var ekleyemezsiniz.\n",plaka);
            varmi=1;
        }
        iter=iter->next;

    }

    if(varmi==0){

        if(node->komsuPlakaKodu > plaka){
            komsuNode* temp=(komsuNode*)malloc(sizeof(komsuNode));
            temp->komsuPlakaKodu=plaka;
            temp->next=node;
            return temp;
        }

        komsuNode* iter=node;
        while(iter->next!=NULL && iter->next->komsuPlakaKodu < plaka ){
            iter=iter->next;
        }

        komsuNode* temp=(komsuNode*)malloc(sizeof(komsuNode));
        temp->komsuPlakaKodu=plaka;
        temp->next=iter->next;
        iter->next=temp;
        return node;
    }

    return node;

}

komsuNode* komsu_eleman_sil(komsuNode* node,int plaka){

        komsuNode* iter=node;
        if(node==NULL){
            printf("Hic komsu yok!Ilk once komsu ekleyin!\n");
            return node;
        }

        if(node->komsuPlakaKodu == plaka){
            node=node->next;
            free(iter);
            return node;
        }

        else{

            while(iter->next!=NULL && iter->next->komsuPlakaKodu!=plaka){
                iter=iter->next;
            }
            if(iter->next==NULL){

                printf("%d plaka kodlu sehir Listede bulunamadi.\n",plaka);
                return node;

            }

            komsuNode* temp=iter->next;
            iter->next=iter->next->next;
            free(temp);
            return node;
        }

}

void print_komsuList(komsuNode* node){

    FILE* filepointer=fopen("cikti.txt","a");

    if(node==NULL){
        fprintf(filepointer,"Komsu yok. ");
    }

    else{

        while(node!=NULL){

            fprintf(filepointer,"%d ",node->komsuPlakaKodu);
            node=node->next;

        }
    }


    fprintf(filepointer,"\n");
    fclose(filepointer);
}

typedef struct sehirNode{

    int sehirPlakaKodu;
    char sehirAdi[20];
    char sehirBolge[5];
    int sehirKomsuSayisi;

    struct sehirNode* next;
    struct sehirNode* prev;
    komsuNode* komsuNode;

}sehirNode;

sehirNode* sehir_sirali_ekle(sehirNode* node,int plaka,char* isim,char* bolge,int komsuSay){

        int varmi=0;
        sehirNode* iter2=node;
        while(iter2!=NULL){

            if(iter2->sehirPlakaKodu == plaka)
                varmi=1;

            if(strcasecmp(iter2->sehirAdi,isim) == 0)
                varmi=2;

            iter2=iter2->next;
        }


        if(varmi!=0){

            if(varmi==1)
                printf("%d plakali sehir var listeye ekleyemezsiniz.\n",plaka);

            else
                printf("%s isimli sehir var listeye ekleyemezsiniz.\n",isim);

            return node;
        }

        else{

        if(node==NULL){
            node=(sehirNode*)malloc(sizeof(sehirNode));
            node->next=NULL;
            node->prev=NULL;

            node->sehirPlakaKodu=plaka;
            strcpy(node->sehirAdi,isim);
            strcpy(node->sehirBolge,bolge);
            node->sehirKomsuSayisi=komsuSay;
            node->komsuNode=NULL;

            return node;
        }
//x:plaka
        else if(node->sehirPlakaKodu > plaka){
            sehirNode* temp=(sehirNode*)malloc(sizeof(sehirNode));
            temp->prev=NULL;
            temp->next=node;

            temp->sehirPlakaKodu=plaka;
            strcpy(temp->sehirAdi,isim);
            strcpy(temp->sehirBolge,bolge);
            temp->sehirKomsuSayisi=komsuSay;
            temp->komsuNode=NULL;

            node->prev=temp;
            return temp;
        }
        else{

            sehirNode* iter=node;
            while(iter->next!=NULL && iter->next->sehirPlakaKodu < plaka){
                iter=iter->next;
            }
            if(iter->next==NULL){
                sehirNode* temp=(sehirNode*)malloc(sizeof(sehirNode));
                temp->prev=iter;
                temp->next=iter->next;

                temp->sehirPlakaKodu=plaka;
                strcpy(temp->sehirAdi,isim);
                strcpy(temp->sehirBolge,bolge);
                temp->sehirKomsuSayisi=komsuSay;
                temp->komsuNode=NULL;

                iter->next=temp;
                return node;
            }
            else{
                sehirNode* temp=(sehirNode*)malloc(sizeof(sehirNode));
                temp->prev=iter;
                temp->next=iter->next;

                temp->sehirPlakaKodu=plaka;
                strcpy(temp->sehirAdi,isim);
                strcpy(temp->sehirBolge,bolge);
                temp->sehirKomsuSayisi=komsuSay;
                temp->komsuNode=NULL;

                iter->next=temp;
                iter->next->prev=temp;
                return node;
            }

        }
    }

}

sehirNode* sehir_sil_plaka_no_gore(sehirNode* node,int plaka){

    sehirNode* iter=node;
    if(node->sehirPlakaKodu==plaka){
        node=node->next;
        node->prev=NULL;
        free(iter);
        return node;
    }
    while(iter->next!=NULL && iter->next->sehirPlakaKodu!=plaka){
        iter=iter->next;
    }
    if(iter->next==NULL){
        printf("%d plaka kodlu sehir bulunamadi.\n",plaka);
        return node;
    }
    sehirNode *temp=iter->next;
    iter->next=iter->next->next;//SONDAYSA NULL
    free(temp);
    if(iter->next!=NULL)
        iter->next->prev=iter;
    return node;

}

sehirNode* sehire_komsu_ekle(sehirNode* node,int plaka){
    if(plaka!=-1)
        node->komsuNode=komsu_sirali_ekle(node->komsuNode,plaka);
    return node;

}

sehirNode* sehirin_komsusunu_sil(sehirNode* node,int plaka){

    node->komsuNode=komsu_eleman_sil(node->komsuNode,plaka);

    return node;

}

void print_cikti(sehirNode* node){

    if(node==NULL){
        FILE* filepointer=fopen("cikti.txt","a");
        fprintf(filepointer,"Sehir yok eklemek ister misiniz? [Y]\[N]\n");
        fclose(filepointer);
        //################## TEST EDİLECEK ######################
    }


    while(node!=NULL){

        FILE* filepointer=fopen("cikti.txt","a");
        fprintf(filepointer,"%d %s %s %d =====> ",node->sehirPlakaKodu,node->sehirAdi,node->sehirBolge,node->sehirKomsuSayisi);
        fclose(filepointer);
        print_komsuList(node->komsuNode);
        node=node->next;

    }

}

int sehir_plaka_bul(sehirNode* node,char* isim){

    sehirNode* iter=node;

    if(node==NULL){
        printf("Listede sehir yok!Ilk once sehir ekleyin!\n");
        return -1;
    }

    while(iter!=NULL && strcasecmp(iter->sehirAdi,isim) != 0){
        iter=iter->next;
    }

    if(iter==NULL){
        printf("%s Sehir listede yok.\n",isim);
        return -1;
    }

    return iter->sehirPlakaKodu;
}

sehirNode* sehir_node_bul(sehirNode* node,char* isim){

    sehirNode* iter=node;

    if(node==NULL){
        printf("Listede sehir yok!Ilk once sehir ekleyin!\n");
        return node;
    }
    while(iter!=NULL && strcasecmp(iter->sehirAdi,isim) != 0){
        iter=iter->next;
    }

    if(iter==NULL){
        printf("%s Sehir listede yok.\n",isim);
        return node;
    }

    return iter;
}

sehirNode* sehir_node_bul_plaka_ile(sehirNode* node,int plaka){

    sehirNode* iter=node;

    if(node==NULL){
        printf("Listede sehir yok!Ilk once sehir ekleyin!\n");
        return node;
    }
    while(iter!=NULL && iter->sehirPlakaKodu!=plaka){
        iter=iter->next;
    }

    if(iter==NULL){
        printf("%d Sehir listede yok.\n",plaka);
        return node;
    }

    return iter;

}

void sehirler_komsu_sayisi_guncelle(sehirNode* node){

    sehirNode* iter=node;

    komsuNode* iter2=iter->komsuNode;

    int sayac=0;

    while(iter!=NULL){

        while(iter2!=NULL){
            sayac++;
            iter2=iter2->next;
        }

        iter->sehirKomsuSayisi=sayac;
        iter=iter->next;
        if(iter!=NULL)
            iter2=iter->komsuNode;
        sayac=0;
    }

}

void menu_goster(){

    printf("\nYapmak istediginiz islemi secin:\n\n");
    printf("1. Sehir ekle\n");
    printf("2. Sehir sil\n");
    printf("3. Sehire yeni komsu ekle\n");
    printf("4. Sehirin komsusunu sil\n");
    printf("5. Sehir bilgisi goster (Plaka kodu ile ara)\n");
    printf("6. Sehir bilgisi goster (isim ile ara)\n");
    printf("7. Bolgedeki sehirleri goster\n");
    printf("8. x'ten Fazla komsusu olan sehirleri goster\n");
    printf("9. x'ten Az komsusu olan sehirleri goster\n");
    printf("10.x komsusu olan sehirleri goster\n");
    printf("11.Belli bir sayi araliginda komsu\nsayisina sahip sehirlerden belirli ortak\nkomsulara sahip olan sehirlerin listelenmesi\n");
    printf("0.Cikis\n\n");
}

void sehir_bilgisi_goster(sehirNode* node){
    printf("%d ",node->sehirPlakaKodu);
    printf("%s ",node->sehirAdi);
    printf("%s ",node->sehirBolge);
    printf("%d ",node->sehirKomsuSayisi);
    printf("=====> ");
    komsu_bilgisi_goster(node->komsuNode);

}

void komsu_bilgisi_goster(komsuNode*node){

    if(node==NULL){
        printf("Komsu yok.");
    }

    else{

        while(node!=NULL){

            printf("%d ",node->komsuPlakaKodu);
            node=node->next;

        }
    }


    printf("\n");

}

char* strtok_s(char *str,const char *delim,char **nextp){

    char *ret;

    if (str == NULL)
        str = *nextp;


    str += strspn(str, delim);

    if (*str == '\0')
        return NULL;


    ret = str;

    str += strcspn(str, delim);

    if (*str)
        *str++ = '\0';


    *nextp = str;

    return ret;

}

void bolgedeki_sehirleri_goster(sehirNode* node,int bolgesec){

    char* bolge=(char*)malloc(5*sizeof(char));

    if(bolgesec==1)
        bolge="AK";

    else if(bolgesec==2)
        bolge="DA";

    else if(bolgesec==3)
        bolge="EG";

    else if(bolgesec==4)
        bolge="GA";

    else if(bolgesec==5)
        bolge="IA";

    else if(bolgesec==6)
        bolge="MA";

    else if(bolgesec==7)
        bolge="KA";

    else
        printf("Girilen bolge , yoktur.\n");

    sehirNode* iter=node;

    if(iter==NULL){
        printf("Hic sehir yoktur\n");
    }

    while(iter!=NULL){
        if(strcasecmp(iter->sehirBolge,bolge) == 0)
            sehir_bilgisi_goster(iter);
        iter=iter->next;
    }




}

void case8(sehirNode* node,int sayi){

    if(node==NULL)
        printf("Hic sehir yok.\n");

    sehirNode* iter=node;

    while(iter!=NULL){

        if(iter->sehirKomsuSayisi > sayi)
            sehir_bilgisi_goster(iter);

        iter=iter->next;
    }


}

void case9(sehirNode* node,int sayi){

    if(node==NULL)
        printf("Hic sehir yok.\n");

    sehirNode* iter=node;

    while(iter!=NULL){

        if(iter->sehirKomsuSayisi < sayi)
            sehir_bilgisi_goster(iter);

        iter=iter->next;
    }

}

void case10(sehirNode* node,int sayi){

    if(node==NULL)
        printf("Hic sehir yok.\n");

    sehirNode* iter=node;

    while(iter!=NULL){

        if(iter->sehirKomsuSayisi == sayi)
            sehir_bilgisi_goster(iter);

        iter=iter->next;
    }


}

void silinen_sehri_komsulardan_sil(sehirNode* node,char* isim){

    if(node==NULL)
        printf("Hic sehir yok!Once sehir ekleyin!\n");

    sehirNode* iter=node;

    while(iter!=NULL){
        iter=sehirin_komsusunu_sil(iter,sehir_plaka_bul(node,isim));
        iter=iter->next;
    }


}

void case11(sehirNode* sehirler,sehirNode* node1,sehirNode* node2,int buyuk,int kucuk){

    komsuNode* ortak_komsular=NULL;

    komsuNode* komsu1=node1->komsuNode;
    komsuNode* komsu2=node2->komsuNode;



    sehirler_komsu_sayisi_guncelle(sehirler);


    while(komsu1!=NULL){

        while(komsu2!=NULL){

            if(komsu1->komsuPlakaKodu == komsu2->komsuPlakaKodu){
                ortak_komsular=komsu_sirali_ekle(ortak_komsular,komsu1->komsuPlakaKodu);
            }

            komsu2=komsu2->next;
        }

        komsu2=node2->komsuNode;
        komsu1=komsu1->next;

    }

    komsuNode* iter=ortak_komsular;


    while(iter!=NULL){

        if(kucuk <= sehir_node_bul_plaka_ile(sehirler,iter->komsuPlakaKodu)->sehirKomsuSayisi && sehir_node_bul_plaka_ile(sehirler,iter->komsuPlakaKodu)->sehirKomsuSayisi <= buyuk)
            sehir_bilgisi_goster(sehir_node_bul_plaka_ile(sehirler,iter->komsuPlakaKodu));

        iter=iter->next;
    }

}

void sehir_bilgisi_goster_detayli(sehirNode* sehirler,sehirNode* node){

    sehir_bilgisi_goster(node);
    printf("\n\n==========Komsular==========\n");

    komsuNode* iter=node->komsuNode;

    if(iter==NULL)
        printf("\n\n");

    while(iter!=NULL){
        sehirNode* temp=sehir_node_bul_plaka_ile(sehirler,iter->komsuPlakaKodu);
        sehir_bilgisi_goster(temp);
        iter=iter->next;
    }


}
int main()
{

    sehirNode* sehirler=NULL;

    char *saveptr = NULL;

    FILE *filepointer = fopen("sehirler.txt", "r");

    char line[2560];
    size_t readLength = -1;
    int maximumLineLength = 2560;
    char delimiter[]   = ",";

    int plaka,komsu=0;
    char *isim=(char *)malloc(sizeof(char)*100);
    char *bolge=(char *)malloc(sizeof(char)*100);

    if (filepointer != NULL){

        while (fgets(line, maximumLineLength,filepointer) != NULL ){

            char* fieldArray = strtok_s(line,delimiter,&saveptr);

            int i = 1;

            while (fieldArray != NULL){

                if(i==1)
                    plaka=atoi(fieldArray);


                if(i==2)
                    strcpy(isim,fieldArray);


                if(i==3)
                    strcpy(bolge,fieldArray);


                i++;

                fieldArray = strtok_s(NULL,delimiter,&saveptr);
            }

            sehirler=sehir_sirali_ekle(sehirler,plaka,isim,bolge,komsu);

        }

    }


    else
        printf("File not found.\n");


     fclose(filepointer);
     filepointer = fopen("sehirler.txt","r");

     sehirNode* iternode=sehirler;

     char c;

     char* buffer=(char*)malloc(25*sizeof(char));

     int virgul=0;
     int b=0;



     while(!feof(filepointer)){

        c=getc(filepointer);


        buffer[b]=c;
        b++;

        if(c==','){
            virgul++;
            buffer[b-1]='\0';
            if(virgul>3)
                iternode=sehire_komsu_ekle(iternode,sehir_plaka_bul(sehirler,buffer));
            b=0;

        }


        if(c=='\n'){
            buffer[b-1]='\0';
            if(virgul>=3)
                iternode=sehire_komsu_ekle(iternode,sehir_plaka_bul(sehirler,buffer));
            printf("\n\n");
            b=0;
            virgul=0;
            iternode=iternode->next;
        }

        if(c==EOF){
            buffer[b-1]='\0';
            if(virgul>=3)
                iternode=sehire_komsu_ekle(iternode,sehir_plaka_bul(sehirler,buffer));
            printf("\n\n");
            b=0;
            virgul=0;
            iternode=iternode->next;
        }

    }

    fclose(filepointer);

    sehirler_komsu_sayisi_guncelle(sehirler);



    int bolgesec;
    int sayi_case8910;
    int secim;
    menu_goster();
    scanf(" %d",&secim);

    char ad[20];
    char ad2[20];
    char bolge2[20];
    int sayi1,sayi2,buyuk,kucuk;
    char sehir1[25];
    char sehir2[25];
    char yesno;

    while(secim!=0){

        switch(secim){

        case 1:

            printf("Sehrin ismini girin\n");
            scanf(" %s",&ad);
            printf("Sehrin plakasini girin\n");
            scanf(" %d",&plaka);
            printf("Sehrin bolgesini girin\n");
            scanf(" %s",&bolge2);
            komsu=0;

            sehirler=sehir_sirali_ekle(sehirler,plaka,ad,bolge2,komsu);

            sehirler_komsu_sayisi_guncelle(sehirler);

            break;


        case 2:

            printf("Silmek istediginiz sehrin ismini girin:\n");
            scanf(" %s",&ad);
            silinen_sehri_komsulardan_sil(sehirler,ad);
            sehirler=sehir_sil_plaka_no_gore(sehirler,sehir_plaka_bul(sehirler,ad));
            sehirler_komsu_sayisi_guncelle(sehirler);
            break;

        case 3:

            printf("Hangi sehre komsu eklemek istiyorsunuz?:\n");
            scanf(" %s",&ad);
            int ilksehirPlaka=sehir_plaka_bul(sehirler,ad);
            sehirNode* ilksehir=sehir_node_bul(sehirler,ad);

            if(ilksehirPlaka == -1){

                printf("Sehiri eklemek istiyor musunuz? [Y]/[N]:\n");
                scanf(" %c",&yesno);

                if(yesno =='Y' || yesno=='y'){

                    printf("Sehrin plakasini girin:\n");
                    scanf(" %d",&ilksehirPlaka);
                    printf("Sehrin bolgesini girin:\n");
                    scanf(" %s",bolge2);

                    sehirler=sehir_sirali_ekle(sehirler,ilksehirPlaka,ad,bolge2,0);
                    sehirler_komsu_sayisi_guncelle(sehirler);
                }

                else
                    break;

            }



            printf("Hangi sehri eklemek istiyorsunuz?:\n");
            scanf(" %s",&ad2);
            int ikincisehirPlaka=sehir_plaka_bul(sehirler,ad2);
            sehirNode* ikincisehir=sehir_node_bul(sehirler,ad2);

            if(ikincisehirPlaka == -1){

                printf("Sehiri eklemek istiyor musunuz? [Y]/[N]:\n");
                scanf(" %c",&yesno);

                if(yesno =='Y' || yesno=='y'){

                    printf("Sehrin plakasini girin:\n");
                    scanf(" %d",&ikincisehirPlaka);
                    printf("Sehrin bolgesini girin:\n");
                    scanf(" %s",bolge2);

                    sehirler=sehir_sirali_ekle(sehirler,ikincisehirPlaka,ad2,bolge2,0);
                    sehirler_komsu_sayisi_guncelle(sehirler);
                }

                else
                    break;

            }

            ilksehir=sehir_node_bul(sehirler,ad);
            ilksehirPlaka=sehir_plaka_bul(sehirler,ad);

            ikincisehir=sehir_node_bul(sehirler,ad2);
            ikincisehirPlaka=sehir_plaka_bul(sehirler,ad2);


            ilksehir=sehire_komsu_ekle(ilksehir,ikincisehirPlaka);
            ikincisehir=sehire_komsu_ekle(ikincisehir,ilksehirPlaka);

            sehirler_komsu_sayisi_guncelle(sehirler);


            break;

        case 4:

            printf("Hangi sehrin komsusunu silmek istiyorsunuz , ismini girin:\n");
            scanf(" %s",&ad);
            sehirNode* temp1=sehir_node_bul(sehirler,ad);

            printf("Silmek istediginiz komsu sehirin ismini girin:\n");
            scanf(" %s",&ad);
            temp1=sehirin_komsusunu_sil(temp1,sehir_plaka_bul(sehirler,ad));
            sehirler_komsu_sayisi_guncelle(sehirler);
            break;

        case 5:

            printf("Bilgisini gormek istediginiz sehrin plakasini girin:\n");
            scanf(" %d",&plaka);

            sehirNode* temp3=sehir_node_bul_plaka_ile(sehirler,plaka);

            if(temp3->sehirPlakaKodu != plaka){

                printf("Sehri eklemek istiyor musunuz? [Y]/[N]\n");
                scanf(" %c",&yesno);

                if(yesno =='Y' || yesno =='y'){

                    printf("Sehrin ismini girin:\n");
                    scanf(" %s",&ad);

                    printf("Sehrin bolgesini girin:\n");
                    scanf(" %s",&bolge2);

                    sehirler=sehir_sirali_ekle(sehirler,plaka,ad,bolge2,0);
                    sehirler_komsu_sayisi_guncelle(sehirler);


                }

                else
                    break;

            }

            temp3=sehir_node_bul_plaka_ile(sehirler,plaka);
            printf("\n");
            if(temp3->sehirPlakaKodu == plaka)
                sehir_bilgisi_goster_detayli(sehirler,temp3);

            break;


        case 6:

            printf("Bilgisini gormek istediginiz sehrin ismini girin:\n");
            scanf(" %s",&ad);

            sehirNode* temp4=sehir_node_bul(sehirler,ad);
            int temp4plaka=sehir_plaka_bul(sehirler,ad);

            if(temp4plaka == -1){

                printf("Sehri eklemek istiyor musunuz? [Y]/[N]\n");
                scanf(" %c",&yesno);

                if(yesno =='Y' || yesno =='y'){

                    printf("Sehrin plakasini girin:\n");
                    scanf(" %d",&temp4plaka);

                    printf("Sehrin bolgesini girin:\n");
                    scanf(" %s",bolge2);

                    sehirler=sehir_sirali_ekle(sehirler,temp4plaka,ad,bolge2,0);
                    sehirler_komsu_sayisi_guncelle(sehirler);


                }

                else
                    break;


            }


            temp4=sehir_node_bul(sehirler,ad);
            printf("\n");
            if(strcasecmp(temp4->sehirAdi,ad)==0)
                sehir_bilgisi_goster_detayli(sehirler,temp4);

            break;

        case 7:



            printf("Hangi bolgedeki sehirleri gormek istiyorsaniz secin:\n");
            printf("1.Akdeniz // AK\n");
            printf("2.Dogu Anadolu // DA\n");
            printf("3.Ege // EG\n");
            printf("4.Guneydogu Anadolu // GA\n");
            printf("5.Ic Anadolu // IA\n");
            printf("6.Marmara // MA\n");
            printf("7.Karadeniz // KA\n");
            scanf(" %d",&bolgesec);

            bolgedeki_sehirleri_goster(sehirler,bolgesec);

            break;

        case 8:

            printf("Kactan fazla komsusu olan sehirleri gormek istiyorsunuz?:\n");
            scanf(" %d",&sayi_case8910);
            sehirler_komsu_sayisi_guncelle(sehirler);
            case8(sehirler,sayi_case8910);

            break;

        case 9:


            printf("Kactan az komsusu olan sehirleri gormek istiyorsunuz?:\n");
            scanf(" %d",&sayi_case8910);
            sehirler_komsu_sayisi_guncelle(sehirler);
            case9(sehirler,sayi_case8910);

            break;

        case 10:


            printf("Kac komsusu olan sehirleri gormek istiyorsunuz?:\n");
            scanf(" %d",&sayi_case8910);
            sehirler_komsu_sayisi_guncelle(sehirler);
            case10(sehirler,sayi_case8910);

            break;

        case 11:

            printf("Komsu sayisini hangi iki sayi arasinda sinirlandirmak istiyorsunuz?:\n");
            scanf("%d %d",&sayi1,&sayi2);

            if(sayi1>sayi2){
                buyuk=sayi1;
                kucuk=sayi2;
            }
            if(sayi1<sayi2){
                buyuk=sayi2;
                kucuk=sayi1;
            }

            printf("Ilk sehri girin:\n");
            scanf(" %s",&sehir1);

            printf("Ikinci sehri girin:\n");
            scanf(" %s",&sehir2);

            int bulundu=1;

            if(sehir_plaka_bul(sehirler,sehir1) == -1)
                bulundu=0;

            if(sehir_plaka_bul(sehirler,sehir2) == -1)
                bulundu=0;


            if(bulundu==1)
                case11(sehirler,sehir_node_bul(sehirler,sehir1),sehir_node_bul(sehirler,sehir2),buyuk,kucuk);

            break;
        }




        menu_goster();
        sehirler_komsu_sayisi_guncelle(sehirler);
        scanf(" %d",&secim);

    }



    sehirler_komsu_sayisi_guncelle(sehirler);
    print_cikti(sehirler);

}
