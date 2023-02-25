#include <iostream>
#include <string>
using namespace std;

class lexicon
{
  private:
    class node
    {
      node(const string &s):data(s),left(NULL),right(NULL),count(0){}
      ~node()
      {
        data.clear();
      }
      string data;
      node *left;
      node *right;
      int count;
      friend class lexicon;
    };
    node *root;
    bool empty()
    {
      return root==NULL;
    }
    bool insert(node *t, const string &x)
    {
      if(t->data>x)
      {
        if(t->left==NULL)
        {
          node *neos=new node(x);
          (neos->count)++;
          t->left=neos;
          return true;
        }
        else
        {
          return insert(t->left,x);
        }
      }
      else if(t->data<x)
      {
        if(t->right==NULL)
        {
          node *neos=new node(x);
          (neos->count)++;
          t->right=neos;
          return true;
        }
        else
        {
          return insert(t->right,x);
        }
      }

      else
      {
        t->count++;
        return false;
      }
    }


    int lookup(node *t, const string &x)const
    {
      if(t==NULL)
        return 0;
      if(t->data==x)
        return t->count;
      else if(t->data<x)
      {
        return lookup(t->right,x);
      }
      else
      {
        return lookup(t->left,x);
      }
    }

    int depth(node *t, const string &x)const
    {
      node *current=t;
      int tempDepth=1;
      while(current!=NULL)
      {
        if(current->data==x)
          return tempDepth;
        else if(current->data<x)
        {
          tempDepth++;
          current=current->right;
        }
        else
        {
          tempDepth++;
          current=current->left;
        }
      }
      return 0;
    }

    node * leftdown (node *t)
    {
      if(t==NULL)
        return NULL;
      if(t->left==NULL)
        return t;
      else
        return leftdown(t->left);
    }

    node *rightdown (node *t)
    {
      if(t->right==NULL)
        return t;
      else
        return rightdown(t->right);
    }

    node * find (node *t,const string &x2)
    {
      if(t!=NULL)
      {
        if(t->data>x2)
        {
          return find(t->left,x2);
        }
        else if(t->data<x2)
        {
          return find(t->right,x2);
        }
        else
          return t;
      }
      return NULL;
    }
    bool replace (node *t, const string &x1, const string &x2)
    {
      node *parent;
      node *current;
      current=t;
      parent=current;
      bool found=false;
      bool isLeftChild;
      if(t==NULL)//se periptwsh pou to dentro einai keno tote den ginetai tipota
        return false;
      while(current!=NULL)
      {
        if(x1<current->data)
        {
          parent=current;
          isLeftChild=true;
          current=current->left;
        }
        else if(x1==current->data)
        {
          found=true;
          break;
        }
        else
        {
          isLeftChild=false;
          parent=current;
          current=current->right;
        }
      }

      if(found==false) //otan i frasi den yparxei sto dentro tote den ginetai tipota
        return false;

      if(current->right==NULL and current->left==NULL)
      {//an o komvos einai fyllo symvainei to exhs
        int temp=lookup(x1);
        if(parent==current)
        {//an diagrafetai o komvos rizas exoume
          root=NULL;
          delete current;
        }

        else if(isLeftChild)
        {
          parent->left=NULL;
          delete current;
        }
        else
        {
          parent->right=NULL;
          delete current;
        }

        if(lookup(x2)==0)
        {
          insert(x2);
          (find(root,x2)->count)=temp;
        }
        else
          (find(root,x2)->count)+=temp;
      }

      else if(current->right==NULL and current->left!=NULL)
      {//an exei mono aristero paidi exoume
        int temp=lookup(x1);
        if(parent==current)
        {//an diagrafetai o komvos rizas exoume
          root=current->left;
          delete current;
        }
        else if(isLeftChild)
        {
          parent->left=current->left;
          delete current;
        }
        else
        {
          parent->right=current->left;
          delete current;
        }

        if(lookup(x2)==0)
        {
          insert(x2);
          (find(root,x2)->count)=temp;
        }
        else
          (find(root,x2)->count)+=temp;
      }


      else if(current->right!=NULL and current->left==NULL)
      {//exei mono deksi paidi exoume
        int temp=lookup(x1);
        if(parent==current)
        {//an diagrafetai o komvos rizas exoume
          root=current->right;
          delete current;
        }
        else if(isLeftChild)
        {
          parent->left=current->right;
          delete current;
        }
        else
        {
          parent->right=current->right;
          delete current;
        }

        if(lookup(x2)==0)
        {
          insert(x2);
          (find(root,x2)->count)=temp;
        }
        else
          (find(root,x2)->count)+=temp;
      }

      else if(current->right!=NULL and current->left!=NULL)
      {//an exei kai deksi kai aristero paidi exoume
        int temp=lookup(x1);
        if(current==root)
        {//an diagrafetai o komvos rizas exoume
          root=current->left;
          node *bottomright=rightdown(current->left);
          bottomright->right=current->right;
          delete current;
        }
        else if(isLeftChild)
        {
          parent->left=current->left;
          node *bottomright=rightdown(current->left);
          bottomright->right=current->right;
          delete current;
        }
        else if(!isLeftChild)
        {
          parent->right=current->left;
          node *bottomright=rightdown(current->left);
          bottomright->right=current->right;
          delete current;
        }
        if(lookup(x2)==0)
        {
          insert(x2);
          (find(root,x2)->count)=temp;
        }

        else
          find(root,x2)->count+=temp;
      }
      return true;
    }

    void print(ostream & out, node *t)const
    {
      if(t!=NULL)
      {
        print(out,t->left);
        out << t->data << " " << t->count <<endl;
        print(out,t->right);
      }
    }

    void purge (node *t)
    {
      if(t!=NULL)
      {
        purge(t->left);
        purge(t->right);
        delete t;
      }
    }

  public:
    lexicon():root(NULL){}

    ~lexicon()
    {
      purge(root);
    }

    void insert(const string &s)
    {
      if(empty())
      {
        node *neos=new node(s);
        root=neos;
        neos->count++;
      }
      else
      {
        insert(root,s);
      }
    }

    int lookup(const string &s) const
    {
      return lookup(root,s);
    }

    int depth(const string &s) const
    {
      return depth(root,s);
    }

    void replace(const string &s1, const string &s2)
    {
      if(!replace (root,s1,s2))
        return;
    }

    friend ostream & operator << (ostream &out, const lexicon &l)
    { // xrhsimopoioume thn infix diasxhsh kai exoume
      l.print(out, l.root);
      return out;
    }
};
