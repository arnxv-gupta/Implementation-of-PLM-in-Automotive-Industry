// 2) Batch Utility – Item create (in home folder) 

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
 
int Item_create( id, name, u);

// --- Program ---
#include"Header.h" 
 
int Item_create(char* id, char* name, char* u) 
{ 
 int ifail1; 
     char* error1; 
 tag_t item, rev,user,Home; 
 
 ifail1= ITEM_create_item(id, name, "Item", "A", &item, &rev); 
 if (ifail1 == ITK_ok) 
 { 
  printf("\n\t***item created Successfully***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail1, &error1); 
  printf("\n\t%s", error1); 
 } 
 
 ifail1 = ITEM_save_item (item); 
 printf("\n\t***item saved Successfully***"); 
  
 ifail1 = SA_find_user2(u, &user); 
 ifail1 = SA_ask_user_home_folder(user, &Home); 
 
 ifail1 = FL_insert(Home, item, 999); 
 if (ifail1 == ITK_ok) 
 { 
  printf("\n\t***item inserted to Home folder Successfully***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail1, &error1); 
  printf("\n\t%s", error1); 
 } 
 
 ifail1 = AOM_save_with_extensions(Home); 
 if (ifail1 == ITK_ok) 
 { 
  printf("\n\t***item saved to Home folder Successfully***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail1, &error1); 
  printf("\n\t%s", error1); 
 } 
 return 0; 
}
