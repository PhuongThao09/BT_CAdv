#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"inc/bc.h"
#include"inc/bt.h"
#include"inc/btree.h"
#include"inc/btree_int.h"

int main(){

  int i,n, size;
  long sdt;
  char name[80];
  BTA * book;
  int luachon;
  btinit();//khoi tao b tree
  book = btopn("my book", 0 ,0);
  if(!book){
    printf("create my book\n");
    book = btcrt("mybook",0, 0);
    printf("inseet data\n");
    sdt =98345678;
    if(btins(book, "Dung", (char*)&sdt, sizeof(long)))
      printf("ERROR, can not insert Dung\n");
	   
  }
  do{
    printf("1. Them vao danh ba\n");
    printf("2. Xoa khoi danh ba\n");
    printf("3. Tim kiem ten trong danh ba\n");
    printf("4. In danh ba\n");
    printf("5. Dong bt file\n");
    printf("6. Exit\n");
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &luachon);
    switch(luachon){
    case 1:
      while(getchar()!='\n');
      printf("Name: ");
      gets(name);
      printf("so dien thoai: ");
      scanf("%ld", &sdt);
      btins(book, name, (char*)&sdt, sizeof(long));
      break;
    case 2:
      while(getchar()!='\n');
      printf("Name: ");
      gets(name);
      btdel(book, name);
      break;
    case 3:
      while(getchar()!='\n');
      printf("Name: ");
      gets(name);
      if(btsel(book, name, (char*)&sdt, sizeof(long), &size))
	printf("Not found number for %s\n", name);
      else
	printf("Phone number of %s is %ld\n", name, sdt);
      break;
    case 4:
      btsel(book,"",(char*)&sdt, sizeof(long),&size);
      while( btsel(book,"",(char*)&sdt, sizeof(long),&size)==0){
	printf("%s\t%10ld\n",name,sdt);
      }
      break;
    case 5:
      btcls(book);
      break;
    }while(luachon!=6);
    return 0;
  }
      
