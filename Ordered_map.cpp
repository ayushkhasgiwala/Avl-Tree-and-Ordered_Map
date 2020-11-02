#include<bits/stdc++.h>
#include <typeinfo>
using namespace std;

template<class T, class X>
class MAP{
    public: 
    struct node{
        T key;
        X value;
        struct node* left;
        struct node* right;
        int height;
    };
    struct node* root;
    int count=0;

    public:
    MAP()
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
        cout<<"{"<<root->key<<" "<<root->value<<"}"<<" ";
        inorder(root->right);
    }

    //preorder helper
    void preorder(node* root)
    {
        if(root==NULL)
            return;
        
        cout<<"{"<<root->key<<" "<<root->value<<"}"<<" ";
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

        return t1;
    }

    //insertion
    void insert(T data, X val)
    {
        node* p=search(data);
        if(p!=NULL)
        {
            p->value=val;
        }
        else
        {
            count++;
            root=insertkey(data,val,root); 
        }
        return;
    }
    
    //insertion helper
    node* insertkey(T data, X val, node* root)
    {
        int hl,hr;
        //if tree is empty
        if(root==NULL)
        {
            struct node* temp=(struct node*)malloc(sizeof(struct node));
            temp->key=data;
            temp->value=val;
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
            if(root->key < data)
            {
                root->right=insertkey(data,val,root->right);
            }
            else if(root->key > data)
            {
                root->left=insertkey(data,val,root->left);
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
                if(data < root->left->key)
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
                if(data > root->right->key)
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
    void deletion(T data)
    {
        node* p=search(data);
        if(p==NULL)
        {
            cout<<"Error : The key is not present"<<endl;
            return;
        }
        else
        {
            root=deletekey(data,root);
            count--; 
        }
        return;
    }

    //.deletion helper
    node* deletekey(T data, node* root)
    {
        if(root==NULL)
            return NULL;

        if(root->key > data)
        {
            root->left=deletekey(data,root->left);
        }

        else if( root->key < data)
        {
            root->right=deletekey(data,root->right);
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
                root->key=temp->key;
                //root->left=deletekey(temp->data,root->left);
                root->right=deletekey(temp->key,root->right);
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

    //search
    node* search(T data)
    {
        node* temp= searchval(root, data);
        return temp;
    }

    //.main se search call krne wala.
    bool find(T data)
    {
        node* temp= searchval(root,data);
        if(temp==NULL)
            return false;
        else return true;
    }

    //search helper
    node* searchval(node* root, T data)
    {
        if(root==NULL || root->key == data)
            return root;
        
        else if(root->key > data)
        {
            return searchval(root->left,data);
        }

        else return searchval(root->right,data);
    }

    
    //find the keys present in the map
    int size()
    {
        return count;
    }

    //clear()
    void clear()
    {
        clearall(root);
    }

    //clearall helper
    void clearall(node* root)
    {
        if(root==NULL)
            return;
        
        clearall(root->left);
        clearall(root->right);
        cout<<"the node removed is = "<<root->key<<endl;
        free(root);
        count--;
    }

    //subscript operator
    X* operator[](T data)
    {
        node* p=searchval(root,data);
        if(p==NULL)
        {
            X t={};
            insert(data,t);
            node* q=searchval(root,data);
            return &(q->value);
            //throw "Exception thrown : the key is not present";
        }
        return &(p->value);
            
    }
};

int main()
{
    MAP<int,int> mp;
    mp.insert(30,1);
    mp.insert(10,2);
    mp.insert(20,3);
    mp.insert(40,4);
    mp.insert(50,5);
    mp.insert(25,6);
    mp.insert(35,7);
    mp.insert(50,8);
    cout<<"inorder is = ";
    mp.inordertrav();
    cout<<endl<<"preorder is = ";
    mp.preordertrav();
    cout<<endl<<"size of map is = "<<mp.size()<<endl;

    //mp.clear();
    //cout<<endl<<"size of map is = "<<mp.size()<<endl;
    cout<<*mp[35]<<endl;
    *mp[12]=2;
    cout<<*mp[12]<<endl;
    cout<<*mp[124]<<endl;
}