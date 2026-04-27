// 8) Batch Utility – Bulk_item_create_through_csv 

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
#include<tccore/aom_prop.h> 
#include<tccore/workspaceobject.h> 
#include<fclasses/tc_string.h> 
#include<sa/tcfile.h> 
#include<base_utils/Mem.h> 
#include<qry/qry.h> 
#include<ss/ss_const.h>

// --- Program ---
#include"Header.h" 
 
int Bulk_item_create_through_csv(char* file_name,char* u) 
{ 
 if (file_name == NULL) 
 { 
  printf("\n\t-file_name=(csv file path with file name & extension)"); 
  return 0; 
 } 
 char* Item_id, * Item_name, * item_type; 
 FILE* f1; 
 char buffer[2024]; 
 int ifail=0, k = 0; 
 char* error; 
 tag_t item, rev, user, home; 
 
 f1 = fopen(file_name, "rt"); 
 if (f1) 
 { 
  while (fgets(buffer, sizeof(buffer), f1)) 
  { 
   if (k > 0) 
   { 
    printf("\n\n\tBuffer=%s", buffer); 
    Item_id = strtok(buffer, ","); 
    Item_name = strtok(NULL, ","); 
    item_type = strtok(NULL, ","); 
printf("\n\tItem_id = %s, Item_name = %s, item_type = %s", Item_id, 
Item_name, item_type); 
    ITEM_create_item(Item_id, Item_name, item_type, "A", &item, &rev); 
    ITEM_save_item(item); 
    SA_find_user2(u, &user); 
    SA_ask_user_home_folder(user, &home); 
    FL_insert(home, item, 999); 
    ifail = AOM_save(home); 
   } 
   k++; 
  } 
 } 
 
 
 if (ifail == ITK_ok) 
 { 
  printf("\n\t Item Created Sucessfully"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail, &error); 
  printf("\n\tError = %s", error); 
 } 
 fclose(f1); 
 return 0; 
}
