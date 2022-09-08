  #include "BST.h"

  // constructor, initialize class variables and pointers here if need.
  BST::BST(){
    // Your code here
    root_ptr_ = shared_ptr <bst_node>(NULL);//set root_ptr_ to a null 
  }

  //deconstructor,
  BST::~BST(){
  }

  shared_ptr<bst_node> BST::InitNode(int data){
    // Your code here
    shared_ptr<bst_node> child(new bst_node);  
    child-> data = data;
    child -> left = NULL;
    child -> right = NULL;
    return child;
  }

  void BST::Insert(shared_ptr<bst_node> new_node){
    // Your code here
     shared_ptr<bst_node> current(new bst_node);
    //tree is empty so inset node at root
    if(root_ptr_ == NULL){
      root_ptr_ = new_node;
      //create childeren for the node to have
      new_node -> left = new_node -> right = NULL;}
    
else{
    //allow the root_node be the current node so we can recursively search for an insertion spot
    current = root_ptr_;

    //tree is not empty seach left and right
    while(current){//run until we reach a leaf node
    //check if the current data is less than the new node. If yes we search left for a leaf
    if(new_node->data < current->data ){
      if(!current->left){//check if the left node of the node is NULL
      current->left = new_node;
      //update the current node to NULL to terminate search
      current = NULL;
      }
      else { //if left child is not NUll keep searching tree
        current = current->left;
        }
      }
    //The current data is greater than the new node. Search right for a leaf
      else{
        if(!current->right){//check if the right node of the node is NULL
        current->right = new_node;
        //update the current node to NULL to terminate search
        current = NULL;
        }
        else { //if right child is not NUll keep searching tree
          current = current->right;
          }
      //update the node childeren to NULL after placing
      new_node->left = NULL;
      new_node->right = NULL; 
      }
 
    }
  }
}

  void BST::InsertData(int data){
    // Your code here
        //create two shared pointers to work with since we are not given a search key
    //shared_ptr<bst_node> new_node(new bst_node);
    shared_ptr<bst_node> current(new bst_node);
    shared_ptr<bst_node> new_node = InitNode(data);// Place the interger data in a new node using the function InitNode
    Insert(new_node);
  }

  void BST::Remove(int data){
    // Your code here

    //create nodes that so we can track where we are in the tree
    shared_ptr<bst_node> current(root_ptr_);// create node to track location. Intiallly point to root
     shared_ptr<bst_node> parent(new bst_node);//create parent to define which node is the parent when traversing BST
     shared_ptr<bst_node> suc(new bst_node);// suc is used to track the successor node in the case of removing a node with two kids
     shared_ptr<bst_node> suc_copy(new bst_node);//Node to copy suc data to temporarily hold while Remove is recursively called

    while(current){// search tree while the node is not NULL

    if(current->data == data){//found node now process depending on child situation
    //We have a leaf node
    if(!current->left && !current->right){
      if(!parent){
        root_ptr_ = NULL;
      }
      //check left child 
      else if(parent->left == current){
        parent->left = NULL;
      }
      //we are working with the right child 
      else{
        parent->right = NULL;
      }
    }

    //node has a left child 
    else if(current->left && !current->right){
      if (parent->left==current)
        parent->left = current->left;
    }

    //node has a right child
    else if(!current->left && current->right){
      if(parent->right==current)
      parent->right = current->right;
    }

    //else node has two childeren
    else if(current->left && current->right){
      //find succesor to the current node,i.e., the node with the smallest key larger than the current
      //to do this search right than as far left as possible until we reach NULL
      suc = current->right;

      while(suc->left){
        suc = suc->left;
      }
      //copy data temp 
      suc_copy->data = suc->data;
      //Remove the data from the sucessor
      Remove(suc->data);
      //Finally assign the succesors data to the node we wish to replace
      current->data = suc_copy->data;
    }

    //node found lets exit
    return;
    }
    //update parent and curret nodes
    else if (current->data < data)//search right 
    {
      parent = current;
      current = current->right;
    }

    else{//search left
      parent = current;
      current = current->left;
    }
    
    }
  return;//node not found
  }

  bool BST::Contains(shared_ptr<bst_node> subt, int data){
    // Your code here
    
    //check if tree is empty 
    if(!subt){
      return NULL;
    } 

    //return true if this is the value requested 
    if(data == subt->data){
      return true;
    }

    //search left recurssivly
    else if(subt->data < data){
      return Contains(subt->right,data);
    }
    //search right recurssivly
    else if(subt->data > data){
      return Contains(subt->left,data);
    }
    //recurssive search was unsuccesful
    else{
      return false;
    }

  }

  shared_ptr<bst_node> BST::GetNode(shared_ptr<bst_node> subt, int data){
    // tree is empty so nothing to return 
    if(!subt)
    return shared_ptr<bst_node>(NULL);

    //check if node is the node we seek
    if(subt->data==data){
      return subt;
    }

    //check left child for data 
    else if (subt->data < data)
    {
      return GetNode(subt->right,data);
    }

    //recursivly search right
    else if (subt->data > data)
    {
      return GetNode(subt->left,data);
    }
    
  }

  int BST::Size(shared_ptr<bst_node> subt){
    // Your code here
    //if empty return size = 0
    if(!subt)
    return 0;

    else{
      //count left 
      int left  = Size(subt->left);
      
      //count right 
      int right = Size(subt->right);

      //return +1 as we want to count the root
      return left + right + 1;
    }
  }

  void BST::ToVector(shared_ptr<bst_node> subt, vector<int>& vec){
    // Your code here
    // eventually fill in vec ex. vec[0] = 1;
    if(!subt)
      return;

    ToVector(subt->left,vec);

    vec.push_back(subt->data);

    ToVector(subt->right,vec);

  }

  // This function is implemented for you
  // Returns the root pointer
  shared_ptr<bst_node> BST::GetRoot(){
    return root_ptr_;
  }

  // This function is implemented for you
  // sets a given pointer as the top pointer
  void BST::SetRoot(shared_ptr<bst_node> root_ptr){
    root_ptr_ = root_ptr;
  }