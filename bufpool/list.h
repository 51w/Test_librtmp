#ifndef _LIST_H_
#define _LIST_H_

/**********************************************************
����: ����MEMBER��Ա��TYPE�ṹ���е�ƫ����
**********************************************************/
#define offsetof(TYPE, MEMBER) (unsigned long)(&(((TYPE*)0)->MEMBER))

/********************************************************** 
����: ��������Ԫ�ص���ʼ��ַ 
����:  
    ptr��    type�ṹ���е�����ָ�� 
    type:   �ṹ������ 
    member: �����Ա���� 
**********************************************************/  
#define container_of(ptr, type, member) (type *)((char*)(ptr) - offsetof(type, member))  
  
#define LIST_HEAD_INIT(name)    {&(name), &(name)}  
  
struct list  
{  
    struct list *prev, *next;  
};  
  
static inline void list_init(struct list *list)  
{  
    list->next = list;  
    list->prev = list;  
}  
  
static inline int list_empty(struct list *list)  
{  
    return list->next == list;  
}  
  
// ��new_link���뵽link֮ǰ  
static inline void list_insert(struct list *link, struct list *new_link)  
{  
    new_link->prev        = link->prev;  
    new_link->next        = link;  
    new_link->prev->next = new_link;  
    new_link->next->prev = new_link;  
}  
  
/********************************************************** 
����: ��new_link�ڵ㸽�ӵ�list������ 
**********************************************************/  
static inline void list_append(struct list *list, struct list *new_link)  
{  
    list_insert(list, new_link);  
}  
  
/********************************************************** 
    ����: ���������Ƴ��ڵ� 
**********************************************************/  
static inline void list_remove(struct list *link)  
{  
    link->prev->next = link->next;  
    link->next->prev = link->prev;  
}  
  
/********************************************************** 
��ȡlink�ڵ��Ӧ�Ľṹ�������ַ 
link:   ����ڵ�ָ�� 
type:   �ṹ�������� 
member: �ṹ���Ա������ 
**********************************************************/  
#define list_entry(link, type, member)  container_of(link, type, member)  
  
  
/********************************************************** 
��ȡ����ͷ�ڵ��Ӧ�Ľṹ�������ַ 
list:   ����ͷָ�� 
type:   �ṹ�������� 
member: �ṹ���Ա������ 
Note: 
����ͷ�ڵ�ʵ��Ϊ����ͷ����һ���ڵ�,����ͷδʹ�ã��൱���ڱ� 
**********************************************************/  
#define list_head(list, type, member) list_entry((list)->next, type, member)  
  
/********************************************************** 
��ȡ����β�ڵ��Ӧ�Ľṹ�������ַ 
list:   ����ͷָ�� 
type:   �ṹ�������� 
member: �ṹ���Ա������ 
**********************************************************/  
#define list_tail(list, type, member) list_entry((list)->prev, type, member)  
  
/********************************************************** 
����������һ���ڵ��Ӧ�Ľṹ��ָ�� 
elm:    �ṹ�����ָ�� 
type:   �ṹ�������� 
member: �ṹ���Ա������(���������) 
**********************************************************/  
#define list_next(elm,type,member) list_entry((elm)->member.next, type, member)  
  
/********************************************************** 
�����������нڵ��Ӧ�Ľṹ�� 
pos : �ṹ��ָ�� 
type : �ṹ�������� 
list : ����ͷָ�� 
member : �ṹ���Ա������(���������) 
Note : ����ͷδʹ�ã���˱���������posָ��Ĳ�����Ч�Ľṹ���ַ 
**********************************************************/
#define list_for_each_entry(pos, type, list, member) \
for(pos = list_head(list, type, member); \
	&pos->member != (list); \
	pos = list_next(pos, type, member))
	

#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
	pos = n, n = pos->next)	
	
	
#endif 