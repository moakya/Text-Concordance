#include <iostream>
#include <new>
using namespace std;

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

template <typename DataType>
class BST
{
 public:
  /***** Function Members *****/
  BST();
  /*------------------------------------------------------------------------
    Construct a BST object.

    Precondition:  None.
    Postcondition: An empty BST has been constructed.
   -----------------------------------------------------------------------*/

  bool empty() const;
  /*------------------------------------------------------------------------
    Check if BST is empty.

    Precondition:  None.
    Postcondition: Returns true if BST is empty and false otherwise.
   -----------------------------------------------------------------------*/

  bool search(const DataType & item) const; 
  /*------------------------------------------------------------------------
    Search the BST for item.

    Precondition:  None.
    Postcondition: Returns true if item found, and false otherwise.
   -----------------------------------------------------------------------*/
   
  void insert(const DataType & item);
  /*------------------------------------------------------------------------
    Insert item into BST.

    Precondition:  None.
    Postcondition: BST has been modified with item inserted at proper 
        position to maintain BST property. 
  ------------------------------------------------------------------------*/
  
  //specific method for concord obj insert
  void BSTKonkInsert(const DataType & item);

  void remove(const DataType & item);
  /*------------------------------------------------------------------------
    Remove item from BST.

    Precondition:  None.
    Postcondition: BST has been modified with item removed (if present);
        BST property is maintained.
    Note: remove uses private auxiliary function search2() to locate 
          the node containing item and its parent.
 ------------------------------------------------------------------------*/

   void graph(ostream & out) const;
  /*------------------------------------------------------------------------
    Graphic output of BST.

    Precondition:  ostream out is open.
    Postcondition: Graphical representation of BST has been output to out.
    Note: graph() uses private auxiliary function graphAux().
 ------------------------------------------------------------------------*/
 
  void inorder(ostream & out) const;
  /*------------------------------------------------------------------------
    Inorder traversal of BST.

    Precondition:  ostream out is open.
    Postcondition: BST has been inorder traversed and values in nodes 
        have been output to out.
    Note: inorder uses private auxiliary function inorderAux().
 ------------------------------------------------------------------------*/

  //--- ADD PROTOTYPES OF preorder() AND postorder() HERE
  void preorder(ostream & out) const;
  void postorder(ostream & out) const;

  //--- ADD PROTOTYPE OF DESTRUCTOR HERE
  ~BST();
  
  //--- ADD PROTOTYPE OF COPY CONSTRUCTOR HERE
  BST(const BST<DataType> &original);
  
  //--- ADD PROTOTYPE OF ASSIGNMENT OPERATOR HERE
  const BST<DataType> &operator = (const BST<DataType> &rhs);

  //--- ADD PROTOTYPE OF LEVEL-BY-LEVEL TRAVERSAL HERE

  //--- ADD PROTOTYPE OF LEVEL FINDER HERE
 
 private:
  /***** Node class *****/
  class BinNode 
  {
   public:
    DataType data;
    BinNode * left;
    BinNode * right;

    // BinNode constructors
    // Default -- data part is default DataType value; both links are null.
    BinNode()
    : left(0), right(0)
    {}

    // Explicit Value -- data part contains item; both links are null.
    BinNode(DataType item)
    : data(item), left(0), right(0)
    {}
 
  };// end of class BinNode declaration

  typedef BinNode * BinNodePointer; 
  
  /***** Private Function Members *****/
  
  void search2(const DataType & item, bool & found,
               BinNodePointer & locptr, BinNodePointer & parent) const;
  /*------------------------------------------------------------------------
    Locate a node containing item and its parent.
 
    Precondition:  None.
    Postcondition: locptr points to node containing item or is null if 
        not found, and parent points to its parent.#include <iostream>
  ------------------------------------------------------------------------*/
 
  void inorderAux(ostream & out, 
                  BinNodePointer subtreePtr) const;
  /*------------------------------------------------------------------------
    Inorder traversal auxiliary function.

    Precondition:  ostream out is open; subtreePtr points to a subtree 
        of this BST.
    Postcondition: Subtree with root pointed to by subtreePtr has been
        output to out.
  ------------------------------------------------------------------------*/

  void preorderAux(ostream & out,
	  BinNodePointer subtreePtr) const;

  void postorderAux(ostream & out,
	  BinNodePointer subtreePtr) const;

  void graphAux(ostream & out, int indent,
                      BinNodePointer subtreeRoot) const;
  /*------------------------------------------------------------------------
    Graph auxiliary function.

    Precondition:  ostream out is open; subtreePtr points to a subtree 
        of this BST.
    Postcondition: Graphical representation of subtree with root pointed 
        to by subtreePtr has been output to out, indented indent spaces.
  ------------------------------------------------------------------------*/
  void destroy(BinNodePointer subtreeRoot);

  void copyTree(BinNodePointer origRoot, BinNodePointer &subtreeRoot);

 /***** Data Members *****/
  BinNodePointer myRoot; 

}; // end of class template declaration

//--- Definition of constructor
template <typename DataType>
inline BST<DataType>::BST()
: myRoot(0)
{}

//--- Definition of empty()
template <typename DataType>
inline bool BST<DataType>::empty() const
{ return myRoot == 0; }

//--- Definition of search()
template <typename DataType>
bool BST<DataType>::search(const DataType & item) const
{
   BST<DataType>::BinNodePointer locptr = myRoot;
   bool found = false;
   while (!found && locptr != 0)
   {
      if (item < locptr->data)       // descend left
        locptr = locptr->left;
      else if (locptr->data < item)  // descend right
        locptr = locptr->right;
      else                           // item found
        found = true;
   }
   return found;
}

//--- Definition of insert()
template <typename DataType>
inline void BST<DataType>::insert(const DataType & item)
{
   BST<DataType>::BinNodePointer 
        locptr = myRoot,   // search pointer
        parent = 0;        // pointer to parent of current node
   bool found = false;     // indicates if item already in BST
   while (!found && locptr != 0)
   {
      parent = locptr;
      if (item < locptr->data)       // descend left
         locptr = locptr->left;
      else if (locptr->data < item)  // descend right
         locptr = locptr->right;
	  else                           // item found
		  found = true;
   }
   if (!found)
   {                                 // construct node containing item
      locptr = new(nothrow) BST<DataType>::BinNode(item);  
      if (locptr == 0)	
      {
        cerr << "*** Out of memory -- terminating program ***\n";
	exit(1);
      }

      if (parent == 0)               // empty tree
         myRoot = locptr;
      else if (item < parent->data )  // insert to left of parent
         parent->left = locptr;
      else                           // insert to right of parent
         parent->right = locptr;
   }
   else
     cout << "Item already in the tree\n";	 
}

//--- Definition of BSTKonkinsert()
template <typename DataType>
inline void BST<DataType>::BSTKonkInsert(const DataType & item)
{
	BST<DataType>::BinNodePointer
		locptr = myRoot,   // search pointer
		parent = 0;        // pointer to parent of current node
	bool found = false;     // indicates if item already in BST
	while (!found && locptr != 0)
	{
		parent = locptr;
		if (item < locptr->data)       // descend left
			locptr = locptr->left;
		else if (locptr->data < item)  // descend right
			locptr = locptr->right;
		else {                           // item found
			found = true;
			(locptr->data).concQInsert(item.concQFRet());
		}
	}
	if (!found)
	{                                 // construct node containing item
		locptr = new(nothrow) BST<DataType>::BinNode(item);
		if (locptr == 0)
		{
			cerr << "*** Out of memory -- terminating program ***\n";
			exit(1);
		}

		if (parent == 0)               // empty tree
			myRoot = locptr;
		else if (item < parent->data)  // insert to left of parent
			parent->left = locptr;
		else                           // insert to right of parent
			parent->right = locptr;
	}
	
}

//--- Definition of remove()
template <typename DataType>
void BST<DataType>::remove(const DataType & item)
{
   bool found;                      // signals if item is found
   BST<DataType>::BinNodePointer 
      x,                            // points to node to be deleted
      parent;                       //    "    " parent of x and xSucc
   search2(item, found, x, parent);

   if (!found)
   {
      cout << "Item not in the BST\n";
      return;
   }
   //else
   if (x->left != 0 && x->right != 0)
   {                                // node has 2 children
      // Find x's inorder successor and its parent
      BST<DataType>::BinNodePointer xSucc = x->right;
      parent = x;
      while (xSucc->left != 0)       // descend left
      {
         parent = xSucc;
         xSucc = xSucc->left;
      }

     // Move contents of xSucc to x and change x 
     // to point to successor, which will be removed.
     x->data = xSucc->data;
     x = xSucc;
   } // end if node has 2 children

   // Now proceed with case where node has 0 or 2 child
   BST<DataType>::BinNodePointer 
      subtree = x->left;             // pointer to a subtree of x
   if (subtree == 0)
      subtree = x->right;
   if (parent == 0)                  // root being removed
      myRoot = subtree;
   else if (parent->left == x)       // left child of parent
      parent->left = subtree; 
   else                              // right child of parent
      parent->right = subtree;
   delete x;
}

//--- Definition of graph()
template <typename DataType>
inline void BST<DataType>::graph(ostream & out) const
{ graphAux(out, 0, myRoot); }

//--- Definition of search2()
template <typename DataType>
void BST<DataType>::search2(const DataType & item, bool & found,
                            BinNodePointer & locptr, 
                            BinNodePointer & parent) const
{
   locptr = myRoot;
   parent = 0;
   found = false;
   while (!found && locptr != 0)
   {
      if (item < locptr->data)       // descend left
      {
         parent = locptr;
         locptr = locptr->left;
      }
      else if (locptr->data < item)  // descend right
      {
         parent = locptr;
         locptr = locptr->right;
      }
      else                           // item found
         found = true;
   }
}


//--- Definition of graphAux()
#include <iomanip>

template <typename DataType>
void BST<DataType>::graphAux(ostream & out, int indent, 
                             BinNodePointer subtreeRoot) const
{
  if (subtreeRoot != 0)
    {
      graphAux(out, indent + 8, subtreeRoot->right);
      out << setw(indent) << " " << subtreeRoot->data << endl;
      graphAux(out, indent + 8, subtreeRoot->left);
    }
}

//--- Definition of inorder()
template <typename DataType>
inline void BST<DataType>::inorder(ostream & out) const
{ 
   inorderAux(out, myRoot); 
}

//--- Definition of inorderAux()
template <typename DataType>
void BST<DataType>::inorderAux(ostream & out, 
                               BinNodePointer subtreeRoot) const
{
   if (subtreeRoot != 0)
   {
      inorderAux(out, subtreeRoot->left);    // L operation
      out << subtreeRoot->data << "  ";      // V operation
      inorderAux(out, subtreeRoot->right);   // R operation
   }
}

//--- PUT DEFINITIONS OF THE ADDED OPERATIONS HERE

//--- Definition of preorder()
template <typename DataType>
inline void BST<DataType>::preorder(ostream & out) const{
	preorderAux(out, myRoot);
}	//end preorder

//--- Definition of preorderAux()
template <typename DataType>
void BST<DataType>::preorderAux(ostream & out,
	BinNodePointer subtreeRoot) const{
	if (subtreeRoot != NULL){
		out << subtreeRoot->data << "  ";      // V operation
		preorderAux(out, subtreeRoot->left);    // L operation
		preorderAux(out, subtreeRoot->right);   // R operation
	}	//end if
}	//end preorderAux

//--- Definition of postorder()
template <typename DataType>
inline void BST<DataType>::postorder(ostream & out) const{
	postorderAux(out, myRoot);
}	//end postorder

//--- Definition of preorderAux()
template <typename DataType>
void BST<DataType>::postorderAux(ostream & out,
	BinNodePointer subtreeRoot) const{
	if (subtreeRoot != NULL){
		postorderAux(out, subtreeRoot->left);    // L operation
		postorderAux(out, subtreeRoot->right);   // R operation
		out << subtreeRoot->data << "  ";      // V operation
	}	//end if
}	//end postorderAux

template <typename DataType>
inline BST<DataType>::~BST() {
	destroy(myRoot);
}	//end destructor

template <typename DataType>
void BST<DataType>::destroy(BinNodePointer subtreeRoot){
	if (subtreeRoot != NULL) {
		destroy(subtreeRoot->left);
		destroy(subtreeRoot->right);
		delete subtreeRoot;
	}	//end if
	cerr << "\nNode destroyed\n";
}	//end destroy

template <typename DataType>
inline BST<DataType>::BST(const BST<DataType> &original) {
	copyTree(original.myRoot, myRoot);
}	//end copy constructor

template <typename DataType>
void BST<DataType>::copyTree(BinNodePointer origRoot, 
	BinNodePointer &subtreeRoot) {
	if (origRoot == NULL)
		subtreeRoot = NULL;
	else {
		subtreeRoot = new(nothrow) BinNode(origRoot->data);
		copyTree(origRoot->left, subtreeRoot->left);
		copyTree(origRoot->right, subtreeRoot->right);
	}	//end else
}	//end copytree


template <typename DataType>
const BST<DataType> &BST<DataType>::operator=(const BST<DataType> &rhs) {
	if (this != &rhs) {
		if(myRoot != NULL)
			destroy(myRoot);
		copyTree(rhs.myRoot, myRoot);
	}	//end if
	return *this;
}	//end operator=

#endif