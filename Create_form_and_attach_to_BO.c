// 14) Batch Utility – Create form and attach to BO 

// --- Header Files ---
Use previous program’s header

// --- Program ---
#include"Header.h" 
 
int Create_form(char* id) 
{ 
 int ifail; 
 char* error; 
 tag_t item, rev, rel, form_type, create_ip, bo, bo_rel; 
 
 ifail = ITEM_find_item(id, &item); 
 ifail = ITEM_find_revision(item, "A", &rev); 
 ifail = GRM_find_relation_type("IMAN_specification", &rel); 
 ifail = TCTYPE_find_type("BomChange Form", "Form", &form_type); 
 ifail = TCTYPE_construct_create_input(form_type, &create_ip); 
 ifail = AOM_set_value_string(create_ip, "object_name", "Test"); 
 ifail = TCTYPE_create_object(create_ip, &bo); 
 if (ifail == ITK_ok) 
 { 
  printf("\n\t*** Form created successfully ***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail, &error); 
  printf("\n\t%s", error); 
 } 
 ifail = AOM_save(bo); 
 ifail = GRM_create_relation(rev, bo, rel, NULLTAG, &bo_rel); 
 ifail = GRM_save_relation(bo_rel); 
 if (ifail == ITK_ok) 
 { 
  printf("\n\t*** Form attached successfully ***"); 
 } 
 else 
 { 
  EMH_ask_error_text(ifail, &error); 
  printf("\n\t%s", error); 
 } 
 return 0; 
}
