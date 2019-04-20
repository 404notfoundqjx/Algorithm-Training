#include <cstdio>
#include <cstdlib>
#define MAXSIZE 1010
using namespace std;

struct node {
  int data;
  struct node* lchild, * rchild;
};
typedef struct node Node;

int n;
int array1[MAXSIZE];
int array2[MAXSIZE];
int array3[MAXSIZE];

Node* newNode(int num) {
  Node* root = (Node*)malloc(sizeof(Node));
  root->data = num;
  root->lchild = NULL;
  root->rchild = NULL;
  return root;
}

void insert(Node *&root, int num) {
  if(root == NULL) {
    root = newNode(num);
    return;
  }
  else {
    if(root->data > num) insert(root->lchild, num);
    else insert(root->rchild, num);
  }
}

void getArray2(Node *root) {
  static int count = 0;
  if(root != NULL) {
    array2[count++] =  root->data;
    getArray2(root->lchild);
    getArray2(root->rchild);
  }
}

void getArray3(Node *root) {
  static int count = 0;
  if(root != NULL) {
    array3[count++] =  root->data;
    getArray3(root->rchild);
    getArray3(root->lchild);
  }
}

void Postorder(Node *root) {
  static int count = 0;
  if(root != NULL) {
    Postorder(root->lchild);
    Postorder(root->rchild);
    printf("%d", root->data);
    count++;
    if(count != n) printf(" ");
  }
}

void Mirror_Postorder(Node *root) {
  static int count = 0;
  if(root != NULL) {
    Mirror_Postorder(root->rchild);
    Mirror_Postorder(root->lchild);
    printf("%d", root->data);
    count++;
    if(count != n) printf(" ");
  }
}

int main() {
  scanf("%d\n", &n);
  Node* root = NULL;
  
  for(int i = 0;i < n;i++) {
    int tmp;
    scanf("%d", &tmp);
    array1[i] = tmp;
    insert(root, tmp);
  }
  
  getArray2(root);
  getArray3(root);
  
  bool flag1 = false, flag2 = false;
  for(int i = 0;i < n;i++) {
    if(array1[i] != array2[i]) flag1 = true;
    if(array1[i] != array3[i]) flag2 = true;
    if(flag1 == true && flag2 == true) {
      printf("NO");
      return 0;
    }
  }
  
  printf("YES\n");
  if(flag1 == false) Postorder(root);
  else Mirror_Postorder(root);
  return 0;
}
