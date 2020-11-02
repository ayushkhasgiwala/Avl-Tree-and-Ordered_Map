#include<bits/stdc++.h>

using namespace std;

template<class T>
class AVL{
    public: 
    struct node{
        T data;
        struct node* left;
        struct node* right;
        int height;
    };
    struct node* root;

    public:
    AVL()
    {
        root=(struct node*)malloc(sizeof(struct node));
        root=NULL;
    }

    void insert(T val)
    {
        root=insertkey(val,root);
        return;
    }

    void inordertrav()
    {
        inorder(root);
    }
    
    void preordertrav()
    {
        preorder(root);
    }

    void deletion(T val)
    {
        root=deletekey(val,root);
    }

    int height(node* root)
    {
        if(root==NULL)
            return 0;
        else return root->height;
    }

    node* inorderpred(node* root)
    {
        node* curr=root;
        while(curr->right!=NULL)
        {
            curr=curr->right;
        }
        return curr;
    }

    node* inordersucc(node* root)
    {
        node* curr=root;
        while(curr->left!=NULL)
        {
            curr=curr->left;
        }
        return curr;
    }

    node* rightrotate(node* root)
    {
        node* t1=root->left;
        node* t2=t1->right;
        t1->right=root;
        root->left=t2;

        root->height=max(height(root->left),height(root->left))+1;

        t1->height=max(height(t1->left),height(t1->right))+1;

        return t1;

        /*node* t1=root->left->right;
        node* t2=root->left;
        node* t3=root;
        root=t2;
        t2->right=t3;
        t3->left=t1;
        root->height=max(height(root->left),height(root->left))+1;
        t3->height=max(height(t3->left),height(t3->right))+1;
        return root;*/
    }

    node* leftrotate(node* root)
    {
        node* t1=root->right;
        node* t2=t1->left;
        t1->left=root;
        root->right=t2;

        root->height=max(height(root->left),height(root->left))+1;

        t1->height=max(height(t1->left),height(t1->right))+1;

        return t1;
        /*node* t1=root->right->left;
        node* t2=root->right;
        node* t3=root;
        root=t2;
        t2->left=t3;
        t3->right=t1;
        root->height=max(height(root->left),height(root->left))+1;
        t3->height=max(height(t3->left),height(t3->right))+1;
        return root;*/

    }

    
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
            }
            else if(root->data > val)
            {
                root->left=insertkey(val,root->left);
            }
            
        }

        hl=height(root->left);
        hr=height(root->right);
        root->height=max(hr,hl)+1;

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

    void inorder(node* root)
    {
        if(root==NULL)
            return;
        
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }

    void preorder(node* root)
    {
        if(root==NULL)
            return;
        
        cout<<root->data<<" ";
        preorder(root->left);
        preorder(root->right);
    }

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
                //root->left=deletekey(temp->data,root->left);
                root->right=deletekey(temp->data,root->right);
            }
            
        }
        
        if(root==NULL)
            return root;

        int hl,hr;
        hl=height(root->left);
        hr=height(root->right);
        root->height=max(hr,hl)+1;

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


    /*int search(T val)
    {
        node* temp= searchval(node* root, T val);
        if(temp==NULL)
            return 0;
        else return 1;
    }

    node* searchval(node* root, T val)
    {
        if(root->data == val || root==NULL)
            return root;
        
        else if(root->data > val)
        {
            return searchval(root->left,val);
        }

        else return searchval(root->right,val);
    }*/

    void levelorder_helper(node* root){
            queue<node*> q;
            q.push(root); 

            while(!q.empty()){

                node* node = q.front();
                q.pop();

                cout<<node->data<<" ";

                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }

    void levelOrder(){
        levelorder_helper(root);
    }

    void postorder(){
        postordertrav(root);
    }

    void postordertrav(node* root)
    {
        static int diff=0;
        if(root==NULL)
        return;

        postordertrav(root->left);
        postordertrav(root->right);
        if(root->left!=NULL && root->right!=NULL)
        {
            diff=(root->left->height) - (root->right->height);
        }
        else if(root->left!=NULL || root->right!=NULL)
        {
            if(root->left!=NULL)
            diff=root->left->height;

            if(root->right!=NULL)
                diff=-1*root->right->height;
        }
            
        cout<<root->data<<" "<<diff<<endl;
    }
};

int main()
{
    /*AVL<int> a;
    a.insert(30);
    a.insert(10);
    a.insert(20);
    //a.insert(40);
    //a.insert(50);
   // a.insert(25);
    //a.insert(35);
    cout<<"inorder = "<<endl;
    a.inordertrav();
    cout<<endl<<"preorder"<<endl;
    a.preordertrav();
    cout<<endl;*/

   /* AVL<float> t;
    t.insert(1.3);
    t.insert(2.4);
    t.insert(3.5);
    t.insert(4.6);
    t.insert(5.7);
    t.insert(6.8);
    t.insert(7.9);
    t.levelOrder();
    cout<<endl;
    t.deletion(5.7);
    t.deletion(6.8);
    t.deletion(2.4);
    t.levelOrder();
    cout<<endl;*/

    /*AVL<int> v;
    v.insert(9);
    v.insert(5);
    v.insert(10);
    v.insert(0);
    v.insert(6);
    v.insert(11);
    v.insert(-1);
    v.insert(1);
    v.insert(2);
    v.preordertrav();
    cout<<endl;
    v.levelOrder();
    cout<<endl;
    v.deletion(10);
    //v.deletion(9);
    v.preordertrav();
    cout<<endl;
    v.inordertrav();
    cout<<endl;
    v.postorder();
    cout<<endl;
    v.levelOrder();
    cout<<endl;*/
    AVL<int> v;
    for(int i=1;i<11;i++)
    {
        v.insert(i);
    }
    for(int i=2;i<11;i+=2)
    {
        v.deletion(i);
    }
    v.preordertrav();
    cout<<endl;
    v.inordertrav();
    cout<<endl;
}