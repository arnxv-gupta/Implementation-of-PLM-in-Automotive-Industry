// 12) Batch Utility – Print_BOM_line_item_id (Multi level childs) 

// --- Header Files ---
Use previous program’s header

// --- Program ---
#include"Header.h" 
 
int Print_BOM_line_item_id(char* id) 
{ 
 int ifail, count; 
 tag_t item, rev, * childs, window, bom_line; 
 
 ifail = ITEM_find_item(id, &item); 
 ifail = ITEM_find_revision(item, "A", &rev); 
 ifail = BOM_create_window(&window); 
 ifail = BOM_set_window_top_line(window, item, rev, NULLTAG, &bom_line); 
 ifail = BOM_line_ask_all_child_lines(bom_line, &count, &childs); 
 printf("\n\tParent item_id = %s", id); 
 if (count > 0) 
  print_bom_line(count, childs); 
 if (childs) 
  MEM_free(childs); 
 return 0; 
} 
 
print_bom_line(int count,tag_t *childs) 
{ 
 int i,ifail1, count1; 
 char* value_id, * value_name; 
 tag_t* childs1; 
 
 for (i = 0; i < count; i++) 
 { 
  AOM_ask_value_string(childs[i], "bl_item_item_id", &value_id); 
  AOM_ask_value_string(childs[i], "bl_rev_object_name", &value_name); 
  printf("\n\t\titem_id = %s , Name = %s", value_id, value_name); 
  ifail1 = BOM_line_ask_all_child_lines(childs[i], &count1, &childs1); 
  if (count1 > 0) 
   print_bom_line(count1, childs1); 
 } 
 return 0; 
}
