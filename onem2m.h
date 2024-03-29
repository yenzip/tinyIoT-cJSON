#include <stdio.h>
#include <stdbool.h>
#include "cJSON.h"

typedef enum {
	o_CREATE = 1,
	o_RETRIEVE,
	o_UPDATE,
	o_DELETE
}Operation;

typedef enum {
	t_AE = 2,
	t_CNT,
	t_CIN,
	t_CSE
}ObjectType;

// OneM2M Resource struct
typedef struct {
	char *ct;
	char *lt;
	char *rn;
	char *ri;
	char *pi;
	char *csi;
	int ty;
} CSE;

typedef struct {
	char *et;
	char *ct;
	char *lt;
	char *rn;
	char *ri;
	char *pi;
	char *api;
	char *aei;
	char *lbl;
	int ty;
	bool rr;
} AE;

typedef struct {
	char *et;
	char *ct;
	char *lt;
	char *rn;
	char *ri;
	char *pi;
	char *lbl;
	char *acpi;
	int ty;
	int st;
	int cni;
	int cbs;
} CNT;

typedef struct {
	char *et;
	char *ct;
	char *lt;
	char *rn;
	char *ri;
	char *pi;
	char *con;
	int ty;
	int st;
	int cs;
} CIN;

typedef struct {
	char *rn;
	int ty;
	char *pi;
	char *ri;
	char *ct;
	char *lt;
	char *et;
	char *nu;
	char *net;
	int nct;
} Sub;

typedef struct {
	char *rn;
	char *pi;
	char *ri;
	char *ct;
	char *lt;
	char *et;
	char *pv_acor;
	char *pv_acop;
	char *pvs_acor;
	char *pvs_acop;
	int ty;
} ACP;


typedef struct Node {
	struct Node *parent;
	struct Node *child;
	struct Node *siblingLeft;
	struct Node *siblingRight;

	char *rn;
	char *ri;
	char *pi;
	ObjectType ty;

	int cinSize;
}Node;

typedef struct {
	Node *root;
}RT;

//Request parse function
int Validate_OneM2M_Standard();
Node* Parse_URI(RT *rt);
Operation Parse_Operation();
ObjectType Parse_ObjectType();
ObjectType Parse_ObjectType_Body();
char *Remove_Specific_Asterisk();

//OneM2M CRUD function
void Create_Object(Node* pnode, char *json_payload);
void Retrieve_Object(Node *pnode);
void Update_Object(Node *pnode, char *json_payload);
void Delete_Object();

void Create_AE(Node *pnode, char *json_payload);
void Create_CNT(Node *pnode, char *json_payload);
void Create_CIN(Node *pnode, char *json_payload);

void Retrieve_CSE();
void Retrieve_AE();
void Retrieve_CNT();
void Retrieve_CIN();
void Retrieve_CIN_Ri(char *ri);

void Update_CSE(Node *pnode, char *json_payload);
void Update_AE(Node *pnode, char *json_payload);
void Update_CNT(Node *pnode, char *json_payload);

void Set_CSE(CSE* cse);
void Set_AE(AE* ae, char *pi);
void Set_AE_Update(AE* before, AE* after);
void Set_CNT(CNT* cnt, char *pi);
void Set_CIN(CIN* cin, char *pi);

CSE* JSON_to_CSE(char *json_payload);
AE* JSON_to_AE(char *json_payload);
CNT* JSON_to_CNT(char *json_payload);
CIN* JSON_to_CIN(char *json_payload);

Sub* JSON_to_Sub(char *json_payload);

ACP* JSON_to_ACP(char *json_payload);

char* CSE_to_json(CSE* cse_object);
char* AE_to_json(AE* ae_object);
char* CNT_to_json(CNT* cnt_object);
char* CIN_to_json(CIN* cin_object);

char* Sub_to_json(Sub *sub_object);
char* Noti_to_json(char *sur, int net, char *rep);

char* ACP_to_json(ACP* acp_object);

//DB function
int display(char* database);

int Store_CSE(CSE* cse_object);
int Store_AE(AE* ae_object);
int Store_CNT(CNT* cnt_object);
int Store_CIN(CIN* cin_object);

CSE* Get_CSE();
AE* Get_AE(char *ri);
CNT* Get_CNT(char *ri);
CIN* Get_CIN(char *ri);

AE* Update_AE_DB(AE* ae);

CSE* Delete_CSE(char *ri);
AE* Delete_AE(char *ri);
CNT* Delete_CNT(char *ri);
CIN* Delete_CIN(char *ri);

Node* Get_All_AE();
Node* Get_All_CNT();
Node* Get_All_CIN();

void Free_CSE(CSE* cse);
void Free_AE(AE* ae);
void Free_CNT(CNT* cnt);
void Free_CIN(CIN* cin);

Node* Get_CIN_Period(char *start_time, char *end_time);
Node* Get_CIN_Pi(char* pi);

char* Label_To_URI(char* label);
char* URI_To_Label(char* uri);
int Store_Label(char* label, char* uri);

//Resource Tree function
Node* Create_Node(char *ri, char *rn, char *pi, ObjectType ty);
int Add_child(Node *parent, Node *child);
char* Node_to_json(Node *node);
void Delete_Node_Object(Node *node, int flag);
void Free_Node(Node *node);

void TreeViewerAPI(Node *node);
void Tree_data(Node *node, char **viewer_data, int cin_num);
void Restruct_ResourceTree();
Node* Restruct_childs(Node *node, Node *list);

//etc
void init();
char* Get_LocalTime(int diff);
void CIN_in_period(Node *pnode);
Node *LatestCINs(Node *cinList, int num);
void ObjectTestAPI(Node *node);
char* JSON_label_value(char *json_payload);
