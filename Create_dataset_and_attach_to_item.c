// 3) Batch Utility – Create dataset and attach to item 

// --- Header Files ---
#include<conio.h> 
#include<stdio.h> 
#include<tcinit/tcinit.h> 
#include<tc/emh.h> 
#include<tc/tc_startup.h> 
#include<tccore/item.h> 
#include<sa/user.h> 
#include<tc/folder.h> 
#include<tccore/aom.h> 
#include<tccore/tctype.h> 
#include<ae/dataset.h> 
#include<ae/datasettype.h> 
#include<tccore/grm.h> 
 
//int Item_create( id, name, u); 
int Create_dataset(id, name, u);

// --- Program ---
#include"Header.h" 
 
int Create_dataset(char* id, char* name, char* u) 
{ 
 int ifail4; 
 char* error4; 
 tag_t item,user,home,rev,dtype,dataset,relation_type,item_rev,relation; 
 
 ifail4 = ITEM_create_item(id, name, "Item", "A", &item, &rev); 
 if (ifail4 == ITK_ok) 
 { 
  printf("\n\t***Item Created successfully***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail4, &error4); 
  printf("%s", error4); 
 } 
 ifail4 = ITEM_save_item(item); 
 ifail4 = SA_find_user2(u, &user); 
 ifail4 = SA_ask_user_home_folder(user, &home); 
 ifail4 = FL_insert(home, item, 999); 
 if (ifail4 == ITK_ok) 
 { 
  printf("\n\t***Item inserted to home folder successfully***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail4, &error4); 
  printf("%s", error4); 
 } 
 
 ifail4 = AOM_save_with_extensions(home); 
 if (ifail4 == ITK_ok) 
 { 
  printf("\n\t***Item saved to home folder successfully***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail4, &error4); 
  printf("%s", error4); 
 } 
 
 
 
 ifail4 = AE_find_datasettype2("PDF", &dtype); 
 ifail4 = AE_create_dataset_with_id(dtype, "First", "first_desc", NULL, "0", &dataset); 
 ifail4 = AE_save_myself(dataset); 
 ifail4 = GRM_find_relation_type("IMAN_reference", &relation_type); 
 ifail4 = ITEM_find_revision(item, "A", &item_rev); 
 ifail4 = GRM_create_relation(item_rev, dataset, relation_type, NULLTAG, &relation); 
 ifail4 = GRM_save_relation(relation); 
 if (ifail4 == ITK_ok) 
 { 
  printf("\n\t***Dataset attached successfully***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail4, &error4); 
  printf("%s", error4); 
 } 
 return 0; 
 
}
