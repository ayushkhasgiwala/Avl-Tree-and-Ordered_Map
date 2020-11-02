#include<bits/stdc++.h>
#include <typeinfo>
using namespace std;

template<class T>
class AVL{
    public: 
    struct node{
        T data;
        struct node* left;
        struct node* right;
        int height;
        int freq;
        int count;
    };
    struct node* root;
    T lb,ub,m,me;
    //int lb=INT_MAX,ub=INT_MAX,m=INT_MAX;
    //int lb=INT_MIN;
    int flag,sflag=0;

    public:
    
    AVL()
    {
        root=(struct node*)malloc(sizeof(struct node));
        root=NULL;
    }

    //inorder traversal
    void inordertrav()
    {
        inorder(root);
    }
    
    //preorder traversal
    void preordertrav()
    {
        preorder(root);
    }

    //inorder helper
    void inorder(node* root)
    {
        if(root==NULL)
            return;
        
        inorder(root->left);
        for(int i=0;i<root->freq;i++)
            cout<<root->data<<" "<<root->count<<" "<<root->freq<<endl;
        inorder(root->right);
    }

    //preorder helper
    void preorder(node* root)
    {
        if(root==NULL)
            return;
        
        for(int i=0;i<root->freq;i++)
            cout<<root->data<<" ";
        preorder(root->left);
        preorder(root->right);
    }
    
    //to calculate the height
    int height(node* root)
    {
        if(root==NULL)
            return 0;
        else return root->height;
    }
    

    //to get count
    int getcount(node* root)
    {
        if(root==NULL)
        {
            return 0;
        }
        if(root->left==NULL && root->right==NULL)
            return root->freq;

        if(root->left==NULL || root->right==NULL)
        {
            if(root->left!=NULL)
                return (root->freq)+(root->left->count);
            if(root->right!=NULL)
                return (root->freq)+(root->right->count);
        }
        return (root->freq)+(root->left->count)+(root->right->count);
    }


    //inorder predeccor
    node* inorderpred(node* root)
    {
        node* curr=root;
        while(curr->right!=NULL)
        {
            curr=curr->right;
        }
        return curr;
    }

    //inorder successor
    node* inordersucc(node* root)
    {
        node* curr=root;
        while(curr->left!=NULL)
        {
            curr=curr->left;
        }
        return curr;
    }
    
    //right rotation
    node* rightrotate(node* root)
    {
        node* t1=root->left;
        node* t2=t1->right;
        t1->right=root;
        root->left=t2;

        root->height=max(height(root->left),height(root->left))+1;

        t1->height=max(height(t1->left),height(t1->right))+1;
        root->count=getcount(root);
        t1->count=getcount(t1);
        

        return t1;

    }

    //left rotation
    node* leftrotate(node* root)
    {
        node* t1=root->right;
        node* t2=t1->left;
        t1->left=root;
        root->right=t2;

        root->height=max(height(root->left),height(root->left))+1;

        t1->height=max(height(t1->left),height(t1->right))+1;
        root->count=getcount(root);
        t1->count=getcount(t1);
        //root->count=getcount(root);
        return t1;
    }

    //insertion
    void insert(T val)
    {
        
        root=insertkey(val,root); 
       
    }
    
    //insertion helper
    node* insertkey(T val, node* root)
    {
        int hl,hr;
        //if tree is empty
        if(root==NULL)
        {
            struct node* temp=(struct node*)malloc(sizeof(struct node));
            temp->data=val;
            temp->left=NULL;
            temp->right=NULL;
            temp->height=1;
            temp->freq=1;
            temp->count=1;
            root=temp;
            //free(temp);
            return root;
        }

        //if tree is not empty
        else
        {
            if(root->data < val)
            {
                root->right=insertkey(val,root->right);
                //root->count=getcount(root)
            }
            else if(root->data > val)
            {
                root->left=insertkey(val,root->left);
            }
            else
            {
                root->freq++;
                root->count=getcount(root);
            }
            
        }

        hl=height(root->left);
        hr=height(root->right);
        root->height=max(hr,hl)+1;
        root->count=getcount(root);

        //now check whether the tree is balanced or not
        int diff=abs(hl-hr);
        if(diff<=1)
            return root;
        
        else
        {
            if(hl>hr)
            {
                if(val < root->left->data)
                {
                    return rightrotate(root);
                }
                else
                {
                    root->left=leftrotate(root->left);
                    return rightrotate(root);
                }
                
            }
            else
            {
                if(val > root->right->data)
                {
                    return leftrotate(root);
                }
                else{
                    root->right=rightrotate(root->right);
                    return leftrotate(root);
                }
            }
        }
        return root;
    }

    //deletion
    void deletion(T val)
    {
        /*node* p=search(val);
        if(p!=NULL && p->freq > 1)
        {
            p->freq--;
            p->count=getcount(p);
        }
        else
        {*/
            root=deletekey(val,root); 
        //}
        return;
    }

    //deletion helper
    node* deletekey(T val, node* root)
    {
        if(root==NULL)
            return NULL;

        if(root->data > val)
        {
            root->left=deletekey(val,root->left);
        }

        else if( root->data < val)
        {
            root->right=deletekey(val,root->right);
        }

        else
        {
            if(root->freq>1)
            {
                if(sflag==1)
                {
                    root->freq=1;
                    return deletekey(val,root);
                }
                else
                {
                    root->freq--;
                    root->count=getcount(root);
                }
            }
            
            else{
                struct node* temp;
                if(root->left==NULL)
                {
                    temp=root->right;
                    free(root);
                    return temp;
                }
                if(root->right==NULL)
                {
                    temp=root->left;
                    free(root);
                    return temp;
                }

                else
                {
                    //temp=inorderpred(root->left);
                    temp=inordersucc(root->right);
                    root->data=temp->data;
                    if(temp->freq>1)
                    {
                        sflag=1;
                        root->freq=temp->freq;
                        root->count=temp->count;
                    }
                    //root->freq=temp->freq;
                    //root->count=temp->count;
                    //root->left=deletekey(temp->data,root->left);
                    root->right=deletekey(temp->data,root->right);
                }
            }
            
            
        }
        
        if(root==NULL)
            return root;

        int hl,hr;
        hl=height(root->left);
        hr=height(root->right);
        root->height=max(hr,hl)+1;
        root->count=getcount(root);

        //now check whether the tree is balanced or not
        int diff=(hl-hr);
        if(diff<=1 && diff>=-1)
            return root;
        
        else
        {
            if(hl>hr)
            {
                int l=height(root->left->left);
                int h=height(root->left->right);
                
                if(l>=h)
                {
                    return rightrotate(root);
                }
                else
                {
                    root->left=leftrotate(root->left);
                    return rightrotate(root);
                }
                
            }
            else
            {
                int l=height(root->right->left);
                int h=height(root->right->right);
                
                if(l<=h)
                {
                    return leftrotate(root);
                }
                else{
                    root->right=rightrotate(root->right);
                    return leftrotate(root);
                }
            }
        }
        return root;
    }

    //search
    node* search(T val)
    {
        node* temp= searchval(root, val);
        return temp;
    }

    //main se search call krne wala
    int mainsearch(T val)
    {
        node* temp= searchval(root,val);
        if(temp==NULL)
            return 0;
        else return 1;
    }

    //search helper
    node* searchval(node* root, T val)
    {
        if(root==NULL || root->data == val)
            return root;
        
        else if(root->data > val)
        {
            return searchval(root->left,val);
        }

        else return searchval(root->right,val);
    }

    
    //find the occurance of the element
    int countoccurance(T val)
    {
        node* p=search(val);
        if(p==NULL)
            return 0;
        return p->freq;
    }

    //lowerbound
    T  lowerbound(T val)
    {
        //T lb;
        return lowerboundhelper(root,val);
        //return lb;
    }
    
    //lower bound helper
    T lowerboundhelper(node* root,T val)
    {
        if(root==NULL)
            return lb;
        
        if(root->data == val)
            return val;

        if(root->data > val)
        {
            lb=root->data;
            return lowerboundhelper(root->left,val);
        }
        return lowerboundhelper(root->right,val);
    }

    //upperbound
    T  upperbound(T val)
    {
        return upperboundhelper(root,val);
        //return lb;
    }
    
    //upper bound helper
    T upperboundhelper(node* root,T val)
    {
        if(root==NULL)
            return ub;

        if(root->data > val)
        {
            ub=root->data;
            return upperboundhelper(root->left,val);
        }
        return upperboundhelper(root->right,val);
    }


    //closest value to some value 
    T closestvalue(T val)
    {
        T res;
    
        T high=lowerbound(val);
        T low=mini(root,val);

        if(abs(high-val)<abs(low-val))
        {
            res=high;
        }
        else{
            res=low;
        }
        //cout<<low<<" "<<high<<endl;
        return res;
    }

    //closest value helper
    T mini(node* root, T val)
    {
        if(root==NULL)
            return m;

        if(root->data < val)
        {
            m=root->data;
            return mini(root->right,val);
        }
        return mini(root->left,val);
    }

    //find the kth largest element
    T kthlargest(int k)
    {
        return klarge(root,k);
    }

    //kth largest helper
    T klarge(node* root, int k)
    {
        static int c;
        if(root->right!=NULL)
        {
            c=getcount(root->right);
        }
        else c=0;
        if(c+root->freq>=k && c<k)
            return root->data;
        
        else{
                if(c+root->freq > k)
                {
                    return klarge(root->right,k);
                }
        }
            
        return klarge(root->left,(k-(c+root->freq)));
    }

    //count the elements in the range 
    int countinrange(T v1, T v2)
    {
        node* temp=root;
        while(temp->left!=NULL)
        {
            temp=temp->left;
        }
        T low=temp->data;
        temp=root;
        while(temp->right!=NULL)
        {
            temp=temp->right;
        }
        T high=temp->data;
        if((v1<low && v2<low) || (v1>high && v2>high))
            return 0;
        if(v1<=low)
            v1=low;
        if(v2>=high)
            v2=high;
        //cout<<v1<<" "<<v2<<" ";
        if(v1==v2)
        {
            node* p=searchval(root,v1);
            if(p==NULL)
                return 0;
            else return p->freq;
        }
            
        //node* lnode=searchval(root,v1);
        //node* hnode=searchval(root,v2);
        T lower=lowerbound(v1);
        //cout<<lower<<" ";
        //node* ln=searchval(root,lower);
        int countl=0;
        int cl=countless(root,lower,countl);
        //cout<<cl<<" ";
        T higher=minequal(root,v2);
        //cout<<higher<<" ";
        int countm=0;
        int ch=countmore(root,higher,countm);
        //cout<<ch<<" ";
        int total=root->count;
        //cout<<total<<" ";
        return total-(ch+cl);
    }

    int countless(node* root, T lower, int &countl)
    {
        if(root==NULL)
            return countl;
        if(root->data<lower)
        {
            if(root->left!=NULL)
                countl+=((root->freq)+(root->left->count));
            else countl+=root->freq;
            return countless(root->right,lower,countl);
        }
        return countless(root->left,lower,countl);
    }

    T minequal(node* root, int val)
    {
        if(root==NULL)
            return me;

        if(root->data <= val)
        {
            me=root->data;
            return minequal(root->right,val);
        }
        return minequal(root->left,val);
    }

    int countmore(node* root, T higher, int &countm)
    {
        if(root==NULL)
            return countm;
        
        if(root->data > higher)
        {
            if(root->right!=NULL)
                countm+=((root->freq)+(root->right->count));
            else countm+=root->freq;
            return countmore(root->left,higher,countm);
        }
        return countmore(root->right,higher,countm);
    }
};

int main()
{
    AVL<int> a;
    a.insert(30);
    a.insert(10);
    a.insert(25);
    a.insert(20);
    a.insert(40);
    a.insert(50);
    a.insert(25);
    a.insert(35);
    a.insert(50);
    a.insert(25);
    cout<<"inorder = "<<endl;
    a.inordertrav();
    cout<<endl<<"preorder"<<endl;
    a.preordertrav();
    cout<<endl;
    cout<<a.mainsearch(12);
    cout<<endl;
    cout<<a.mainsearch(50)<<endl;
    cout<<"the occurance of 50 is : - "<<a.countoccurance(50)<<endl;
    cout<<"the occurance of 30 is : - "<<a.countoccurance(30)<<endl;
    cout<<"the occurance of 12 is : - "<<a.countoccurance(12)<<endl;
    cout<<".........................."<<endl;
    cout<<"lower bound of 7 is = "<<a.lowerbound(7)<<endl;
    cout<<"lower bound of 40 is = "<<a.lowerbound(40)<<endl;
    cout<<"lower bound of 22 is = "<<a.lowerbound(22)<<endl;
    cout<<".........................."<<endl;
    cout<<"upper bound of 7 is = "<<a.upperbound(7)<<endl;
    cout<<"upper bound of 40 is = "<<a.upperbound(40)<<endl;
    cout<<"upper bound of 31 is = "<<a.upperbound(31)<<endl;
    cout<<".........................."<<endl;
    cout<<"closest value to 7 is = "<<a.closestvalue(7)<<endl;
    cout<<"closest value to 22 is = "<<a.closestvalue(22)<<endl;
    cout<<"closest value to 7 is = "<<a.closestvalue(7)<<endl;
    cout<<"closest value to 60 is = "<<a.closestvalue(60)<<endl;
    cout<<".........................."<<endl;
    cout<<"1 largest value is = "<<a.kthlargest(1)<<endl;
    cout<<"2 largest value is = "<<a.kthlargest(2)<<endl;
    cout<<"3 largest value is = "<<a.kthlargest(3)<<endl;
    cout<<"4 largest value is = "<<a.kthlargest(4)<<endl;
    cout<<"5 largest value is = "<<a.kthlargest(5)<<endl;
    cout<<"6 largest value is = "<<a.kthlargest(6)<<endl;
    cout<<"7 largest value is = "<<a.kthlargest(7)<<endl;
    cout<<"8 largest value is = "<<a.kthlargest(8)<<endl;
    cout<<"9 largest value is = "<<a.kthlargest(9)<<endl;
    cout<<"10 largest value is = "<<a.kthlargest(10)<<endl;
    cout<<"....................................."<<endl;
    cout<<"count of elements between 7 and 60 is "<<a.countinrange(7,60)<<endl;
    cout<<"count of elements between 7 and 30 is "<<a.countinrange(7,30)<<endl;
    cout<<"count of elements between 7 and 10 is "<<a.countinrange(7,10)<<endl;
    cout<<"count of elements between 7 and 20 is "<<a.countinrange(7,20)<<endl;
    cout<<"count of elements between 10 and 60 is "<<a.countinrange(10,60)<<endl;
    cout<<"count of elements between 25 and 60 is "<<a.countinrange(25,60)<<endl;
    cout<<"count of elements between 50 and 60 is "<<a.countinrange(50,60)<<endl;
    cout<<"count of elements between 35 and 60 is "<<a.countinrange(35,60)<<endl;
    cout<<"count of elements between 10 and 40 is "<<a.countinrange(10,40)<<endl;
    cout<<"count of elements between 30 and 50 is "<<a.countinrange(30,50)<<endl;
    cout<<"count of elements between 25 and 50 is "<<a.countinrange(25,50)<<endl;
    a.deletion(25);
    a.deletion(10);
    a.deletion(40);
    cout<<"inorder = "<<endl;
    a.inordertrav();
    cout<<endl<<"preorder"<<endl;
    a.preordertrav();
    cout<<endl;
    cout<<a.mainsearch(12);
    cout<<endl;
    cout<<a.mainsearch(50)<<endl;
    cout<<"the occurance of 50 is : - "<<a.countoccurance(50)<<endl;
    cout<<"the occurance of 30 is : - "<<a.countoccurance(30)<<endl;
    cout<<"the occurance of 12 is : - "<<a.countoccurance(12)<<endl;
    cout<<".........................."<<endl;
    cout<<"lower bound of 7 is = "<<a.lowerbound(7)<<endl;
    cout<<"lower bound of 40 is = "<<a.lowerbound(40)<<endl;
    cout<<"lower bound of 22 is = "<<a.lowerbound(22)<<endl;
    cout<<".........................."<<endl;
    cout<<"upper bound of 7 is = "<<a.upperbound(7)<<endl;
    cout<<"upper bound of 40 is = "<<a.upperbound(40)<<endl;
    cout<<"upper bound of 31 is = "<<a.upperbound(31)<<endl;
    cout<<".........................."<<endl;
    cout<<"closest value to 7 is = "<<a.closestvalue(7)<<endl;
    cout<<"closest value to 22 is = "<<a.closestvalue(22)<<endl;
    cout<<"closest value to 7 is = "<<a.closestvalue(7)<<endl;
    cout<<"closest value to 60 is = "<<a.closestvalue(60)<<endl;
    cout<<".........................."<<endl;
    cout<<"1 largest value is = "<<a.kthlargest(1)<<endl;
    cout<<"2 largest value is = "<<a.kthlargest(2)<<endl;
    cout<<"3 largest value is = "<<a.kthlargest(3)<<endl;
    cout<<"4 largest value is = "<<a.kthlargest(4)<<endl;
    cout<<"5 largest value is = "<<a.kthlargest(5)<<endl;
    cout<<"6 largest value is = "<<a.kthlargest(6)<<endl;
    cout<<"7 largest value is = "<<a.kthlargest(7)<<endl;
    cout<<".........................................."<<endl;
    cout<<"count of elements between 7 and 60 is "<<a.countinrange(7,60)<<endl;
    cout<<"count of elements between 7 and 30 is "<<a.countinrange(7,30)<<endl;
    cout<<"count of elements between 7 and 10 is "<<a.countinrange(7,10)<<endl;
    cout<<"count of elements between 7 and 20 is "<<a.countinrange(7,20)<<endl;
    cout<<"count of elements between 10 and 60 is "<<a.countinrange(10,60)<<endl;
    cout<<"count of elements between 25 and 60 is "<<a.countinrange(25,60)<<endl;
    cout<<"count of elements between 50 and 60 is "<<a.countinrange(50,60)<<endl;
    cout<<"count of elements between 35 and 60 is "<<a.countinrange(35,60)<<endl;
    cout<<"count of elements between 10 and 40 is "<<a.countinrange(10,40)<<endl;
    cout<<"count of elements between 30 and 50 is "<<a.countinrange(30,50)<<endl;
    cout<<"count of elements between 25 and 50 is "<<a.countinrange(25,50)<<endl;
    cout<<"count of elements between 22 and 47 is "<<a.countinrange(22,47)<<endl;
}