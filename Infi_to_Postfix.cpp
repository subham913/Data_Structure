#include<bits/stdc++.h>
using namespace std;



struct Stack
{
    int data;
    struct Stack* next;
};
 
struct Stack* newNode(int data)
{
    struct Stack* stackNode =(struct Stack*) malloc(sizeof(struct Stack));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}
 
int isEmpty(struct Stack *s)
{
    return !s;
}
 
void push(struct Stack** s, int data)
{
    struct Stack* stackNode = newNode(data);
    stackNode->next = *s;
    *s = stackNode;
    //printf("%d pushed to stack\n", data);
}
 
int pop(struct Stack** s)
{
    if (isEmpty(*s))
        return INT_MIN;
    struct Stack* temp = *s;
    *s = (*s)->next;
    int popped = temp->data;
    free(temp);
 
    return popped;
}
 
int Top(struct Stack* s)
{
    if (isEmpty(s))
        return INT_MIN;
    return s->data;
}

int str_to_num(string s){
    int l=s.size();
    int i=l-1;
    int out = (s[i]-48);
    i--;
    while(i>=0){
        out=out*10+(s[i]-48);
        i--;
    }
   // printf("\n%d\n",out);
    return out;
}

int main(){
    int t;
    scanf("%d\n",&t);
    for(int q=0;q<t;q++){
        char c;
    vector<char> s(1) ;
    int x;
    int y;
    
    vector< pair<int,char> > postfix;
     scanf("%c", &c);
     s[0]=c;
    int i=0;
    while(s[i]!='\n'){
        scanf("%c", &c);
        if(c!=' '){
        s.push_back(c);
        i++;
        }
    }
    scanf("%d %d",&x,&y);
    vector<int> arr;
    //   for(i=0;i<s.size();i++){
    //       printf("%c",s[i]);
    //   }
    //   printf("%d %d %d\n",x,y,i);

    for(int i=0;i<s.size()-1;i++){
        int j=i;
        while((s[j]!='+')&&(s[j]!='-')&&(s[j]!='*')&&(s[j]!='/')&&(s[j]!='\n')){
            j++;
        }
        i=j;
        //printf("value of j =%d\n",j);
        j--;
        int product1=1;
        if(s[j]=='x'||s[j]=='y'){
            int flag=0;
            if(s[j]=='x'){
                flag=1;
            }
            int k=j;
            k--;
            //printf("flag=%d\n",flag);
            if(flag==1){
               
                product1 = product1*x;
                //printf("%d\n",product1);
            }
            else{
                product1 *= y;
            }
            if(k>=0&&(s[k]=='x'||s[k]=='y')){
                int check=0;
                int product2;
                if(s[k]=='x'){
                    check=1;
                }
                if(check){
                    product1 *= x;
                }
                else{
                    product1 *= y;
                }
         
                k--;
            }
            int cnt=0;
            string str;
            while((k>=0)&&((s[k]!='+')&&(s[k]!='-')&&(s[k]!='*')&&(s[k]!='/'))){
              str+=s[k];
              cnt=1;
              k--;
            }
            if(cnt==1){
                int product3=str_to_num(str);
                product1*=product3;
            }
           // printf("%d\n",product1);
            arr.push_back(product1);
            j++;
            if(s[j]=='+'){
                arr.push_back(-1);
            }
            else if(s[j]=='-'){
                arr.push_back(-2);
            }
            else if(s[j]=='*'){
                arr.push_back(-3);
            }
            else if(s[j]=='/'){
                arr.push_back(-4);
            }
            
        }
        else{
            int k = j;
            j++;
            string str;
            while((k>=0)&&((s[k]!='+')&&(s[k]!='-')&&(s[k]!='*')&&(s[k]!='/')&&s[k]!='\n')){
                str+=s[k];
                k--;
            }
            int val1=str_to_num(str);
            product1*=val1;
           // printf("val1=%d\n",val1);
            arr.push_back(val1);
            if(s[j]=='+'){
                arr.push_back(-1);
            }
            else if(s[j]=='-'){
                arr.push_back(-2);
            }
            else if(s[j]=='*'){
                arr.push_back(-3);
            }
            else if(s[j]=='/'){
                arr.push_back(-4);
            }
        }


     }
      
    //   for(i=0;i<arr.size();i++){
    //       printf("%d ",arr[i]);
    //   }
    //   printf("\n");
    // int q=arr.size();
    // printf("size=%d\n",q);
     
    struct Stack* Q = NULL;
    struct Stack* P = NULL;
    //createStack(Q,500);
    //createStack(P,500);
    for(i=0;i<arr.size();i++){
        if(i%2==0){
            postfix.push_back(make_pair(arr[i],'a'));
        }
        else if(arr[i]==-1){
            while(true){
                if(Top(P)==-3||Top(P)==-4||Top(P)==-1||Top(P)==-2){
                    int out=pop(&P);
                    postfix.push_back(make_pair(out,'b'));
                }
                else break;
            }
            push(&P,-1);
        }
        else if(arr[i]==-2){
            while(true){
                if(Top(P)==-3||Top(P)==-4||Top(P)==-2||Top(P)==-1){
                    int out=pop(&P);
                    postfix.push_back(make_pair(out,'b'));
                }
                else break;
            }
            push(&P,-2);
        }
        else if(arr[i]==-3){
            while(true){
                if(Top(P)==-3||Top(P)==-4){
                    int out=pop(&P);
                    postfix.push_back(make_pair(out,'b'));
                }
                else break;
            }
            push(&P,-3);
        }
        else if(arr[i]==-4){
            while(true){
                if(Top(P)==-3||Top(P)==-4){
                    int out=pop(&P);
                    postfix.push_back(make_pair(out,'b'));
                }
                else break;
            }
            push(&P,-4);
        }
    }
    
    while(isEmpty(P)!=1){
        int out=pop(&P);
        postfix.push_back(make_pair(out,'b'));
    }

    for(i=0;i<postfix.size();i++){
        if(postfix[i].second=='a'){
            push(&Q,postfix[i].first);
        }
        else{
            int a=pop(&Q);
            int b=pop(&Q);
            int out;
            if(postfix[i].first==-1){
                out=b+a;
            }
            else if(postfix[i].first==-2){
                out=b-a;
            }
            else if(postfix[i].first==-3){
                out=b*a;
            }
            else if(postfix[i].first==-4){
                out=b/a;
            }
            push(&Q,out);
        }
    }
    int evaluated=pop(&Q);
    printf("%d\n",evaluated);
    // while(isEmpty(Q)!=1){
    //     int out=pop(&Q);
    //     }
    getchar();
    }
    return 0;
}