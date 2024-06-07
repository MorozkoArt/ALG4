typedef struct Node
{
	float num;
	char sign;
	Node* left;
	Node* right;
}Node;
Node* New(int num, char sign);
int Prior(int a);
Node* MakeTree(char* Expression, int first, int last);
void Print_pre(Node* v);
void Print_in(Node* v);
void Print_post(Node* v);
float CalcTree(Node* Tree);
