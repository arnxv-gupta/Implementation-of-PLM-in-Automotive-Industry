// 15) Batch Utility – Bulk file import 

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
#include<direct.h> 
#include<bom/bom.h> 
#include<tccore/project.h> 
#include<dirent.h>

// --- Program ---
#include"Header.h" 
 
  
int Import_dataset(char* id) 
{ 
 int ifail, count,i; 
 char* error,* object_type,*path, fl_name[100]; 
 tag_t item, rev, rel_type,* sec_object; 
 DIR* d; 
 struct dirent* dir; 
 path = (char*)MEM_alloc(100); 
 
 
 ifail = ITEM_find_item(id, &item); 
 ifail = ITEM_find_revision(item, "A", &rev); 
 ifail = GRM_find_relation_type("IMAN_specification", &rel_type); 
 ifail = GRM_list_secondary_objects_only(rev, rel_type, &count, &sec_object); 
 for ( i = 0; i < count; i++) 
 { 
  WSOM_ask_object_type2(sec_object[i], &object_type); 
  tc_strcpy(path, "D:\\sample\\bulk\\"); 
  d = opendir(path); 
  if (d) 
  { 
   while ((dir=readdir(d))!=NULL) 
   if (tc_strcmp(dir->d_name, ".") != 0 && tc_strcmp(dir->d_name, "..") != 0) 
   { 
    tc_strcpy(fl_name, dir->d_name); 
    tc_strcat(path, fl_name); 
 
    if (tc_strcmp(object_type, "Text") == 0) 
    { 
     ifail = AOM_refresh(sec_object[i], 1); 
ifail = AE_import_named_ref(sec_object[i], "Text",path, NULL, 
SS_TEXT); 
      
if (ifail == ITK_ok) 
     { 
printf("\n\t***Files imported to named ref. 
successfully***"); 
     } 
     else 
     { 
      EMH_ask_error_text(ifail, &error); 
      printf("\n\t%s", error); 
     } 
     ifail = AE_save_myself(sec_object[i]); 
     ifail = AOM_refresh(sec_object[i], 0); 
     tc_strcpy(path, "D:\\sample\\bulk\\"); 
    } 
   } 
  } 
  closedir(d); 
  if (path) 
   MEM_free(path); 
 } 
 if (sec_object) 
  MEM_free(sec_object); 
 return 0; 
}
